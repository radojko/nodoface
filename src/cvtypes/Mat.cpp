//
// Created by sziraqui on 17/6/19.
//

#include "Mat.h"
#include "../extras/napiextra.h"
#include "../jserrors/JSErrors.h"


Napi::FunctionReference Nodoface::Image::constructor;

// static methods
Napi::Object Nodoface::Image::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "Image", {
        InstanceMethod("shape", &Nodoface::Image::Shape),
        InstanceMethod("type", &Nodoface::Image::Type)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("Image", func);
    return exports;
}

Napi::Object Nodoface::Image::NewObject(Napi::Env env, cv::Mat& mat) {
    // Get continuous mat data
    uchar* data;
    int length = mat.total() * mat.channels();
    if (mat.isContinuous()) {
        data = mat.data;
    } else {
        cv::Mat flatView = mat.reshape(1, length);
        std::vector<uchar> vec = flatView.clone(); // Is clone redundant?
        data = vec.data();
    }
    // Create ArrayBuffer from data
    auto ab = Napi::ArrayBuffer::New(env, data, sizeof(uchar) / sizeof(uint8_t));
    auto arr = Napi::TypedArrayOf<uchar>::New(env, length, ab, 0); // arg0
    // Create array for mat dimensions
    std::vector<int> sizeVec(mat.size.dims());
    for(int i = 0; i < mat.size.dims(); ++i) {
        sizeVec[i] = mat.size[i];
    }

    auto sizeBuf = Napi::ArrayBuffer::New(env, sizeVec.data(), sizeof(int)/sizeof(uint8_t));
    auto size = Napi::Int32Array::New(env, sizeVec.size(), sizeBuf, 0); // arg1
    // Create mat type Number
    auto type = Napi::Number::New(env, mat.type());  // arg2

    Napi::Object imageObj = Image::constructor.New({ arr, size, type });
    return imageObj;
}
// cpp only
cv::Mat Nodoface::Image::NewMat(Napi::TypedArrayOf<uchar> &arr, Napi::Int32Array &size, Napi::Number &type) {
    // Get mat data
    auto buf = arr.ArrayBuffer();
    uchar* data = reinterpret_cast<uchar *>(buf.Data()); // reinterpret_cast for void* to uchar*
    // Get mat size
    auto sizeBuf = size.ArrayBuffer();
    const int* matSize = reinterpret_cast<int *>(sizeBuf.Data());
    // Get Mat type
    int matType = type.Int32Value();
    // Create mat
    cv::Mat mat(size.ElementLength(), matSize, matType, data);
    return mat;
}

// constructor
Nodoface::Image::Image(const Napi::CallbackInfo& info) : ObjectWrap<Nodoface::Image>(info) {
    std::cout<<"inside Mat constructor\n";
    int len = info.Length();
    auto env = info.Env();
    if(len == 0 || len == 2) {
        JSErrors::InsufficientArguments(env, 3, 0);
    } else if (len == 1 && info[0].IsObject()) {
        // copy constructor
        std::cout<<"Mat Unwrap start\n";
        Image * img = Napi::ObjectWrap<Image>::Unwrap(info[1].As<Napi::Object>());
        std::cout<<"Mat Unwrap end\n";
        this->mat = img->mat;
    } else if (len == 3) {
        // constructor with data as arrays
        if(!info[0].IsTypedArray()) {
            JSErrors::IncorrectDatatype(env, JSErrors::TYPEDARRAY, 1);
        }
        if(!info[1].IsTypedArray()) {
            JSErrors::IncorrectDatatype(env, JSErrors::TYPEDARRAY, 2);
        }
        if(!info[2].IsNumber()) {
            JSErrors::IncorrectDatatype(env, JSErrors::NUMBER, 3);
        }
        auto arr = info[0].As<Napi::TypedArrayOf<uchar>>();
        auto size = info[1].As<Napi::Int32Array>();
        auto type = info[2].As<Napi::Number>();
        cv::Mat mat = Image::NewMat(arr, size, type);
        this->mat = &mat;
    } else  {
        JSErrors::TooManyArguments(env, 3, len);
    }
    std::cout<<"Mat constructor finish\n";
}
// instance methods
Napi::Value Nodoface::Image::Shape(const Napi::CallbackInfo &info) {
    std::vector<int32_t > vec(this->mat->size.p, this->mat->size.p + this->mat->size.dims());
    vec.push_back(this->mat->channels());
    auto ab = Napi::ArrayBuffer::New(info.Env(), vec.data(), sizeof(int32_t)/ sizeof(uint8_t));
    auto arr = Napi::Int32Array::New(info.Env(), vec.size(), ab, 0);
    return arr;
}

Napi::Value Nodoface::Image::Type(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->mat->type());
}
// cpp only
cv::Mat Nodoface::Image::GetMat() {
    return *this->mat;
}