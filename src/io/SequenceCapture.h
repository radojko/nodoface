//
// Created by sziraqui on 7/6/19.
//

#ifndef NODOFACE_SEQUENCECAPTURE_H
#define NODOFACE_SEQUENCECAPTURE_H
// system includes
#include <vector>
#include <string>

// opencv includes
#include <opencv2/opencv.hpp>

// OpenFace includes
#include <OpenFace/SequenceCapture.h>

// napi
#include <napi.h>

// locals
#include "../extras/ndarray.h"
#include "../extras/napiextra.h"
#include "../jserrors/JSErrors.h"
#include "../cvtypes/Mat.h"

namespace Nodoface {

    class SequenceCapture : public Napi::ObjectWrap<Nodoface::SequenceCapture> {

    public:
        SequenceCapture(const Napi::CallbackInfo &info);

        ~SequenceCapture();

        static Napi::Object Init(Napi::Env env, Napi::Object exports);

    private:
        static Napi::FunctionReference constructor;

        // Opening based on command line arguments
        // bool Open(std::vector<std::string>& arguments);
        Napi::Value Open(const Napi::CallbackInfo &info);

        // Direct opening

        // Webcam
        // bool OpenWebcam(int device_id, int image_width = 640, int image_height = 480, float fx = -1, float fy = -1, float cx = -1, float cy = -1);
        Napi::Value OpenWebcam(const Napi::CallbackInfo &info);

        // Image sequence in the directory
        // bool OpenImageSequence(std::string directory, float fx = -1, float fy = -1, float cx = -1, float cy = -1);
        Napi::Value OpenImageSequence(const Napi::CallbackInfo &info);

        // Video file
        // bool OpenVideoFile(std::string video_file, float fx = -1, float fy = -1, float cx = -1, float cy = -1);
        Napi::Value OpenVideoFile(const Napi::CallbackInfo &info);

        // bool IsWebcam() { return is_webcam; }
        Napi::Value IsWebcam(const Napi::CallbackInfo &info);

        // Getting the next frame
        // cv::Mat GetNextFrame();
        Napi::Value GetNextFrame(const Napi::CallbackInfo &info);

        // Getting the most recent grayscale frame (need to call GetNextFrame first)
        // cv::Mat_<uchar> GetGrayFrame();
        Napi::Value GetGrayFrame(const Napi::CallbackInfo &info);

        // Parameters describing the sequence and it's progress
        // double GetProgress();
        Napi::Value GetProgress(const Napi::CallbackInfo &info);

        // size_t GetFrameNumber() { return frame_num; }
        Napi::Value GetFrameNumber(const Napi::CallbackInfo &info);

        // bool IsOpened();
        Napi::Value IsOpened(const Napi::CallbackInfo &info);

        // GetSet for public variables
        // int image_width;
        Napi::Value GetFrameWidth(const Napi::CallbackInfo &info);

        void SetFrameWidth(const Napi::CallbackInfo &info, const Napi::Value &value);

        // int image_height
        Napi::Value GetFrameHeight(const Napi::CallbackInfo &info);

        void SetFrameHeight(const Napi::CallbackInfo &info, const Napi::Value &value);

        // float fx, fy, cx, cy;
        Napi::Value GetFx(const Napi::CallbackInfo &info);

        void SetFx(const Napi::CallbackInfo &info, const Napi::Value &value);

        Napi::Value GetFy(const Napi::CallbackInfo &info);

        void SetFy(const Napi::CallbackInfo &info, const Napi::Value &value);

        Napi::Value GetCx(const Napi::CallbackInfo &info);

        void SetCx(const Napi::CallbackInfo &info, const Napi::Value &value);

        Napi::Value GetCy(const Napi::CallbackInfo &info);

        void SetCy(const Napi::CallbackInfo &info, const Napi::Value &value);

        // Reference to actual class
        Utilities::SequenceCapture *sequenceCapture;

        // double fps;
        Napi::Value GetFPS(const Napi::CallbackInfo &info);

        void SetFPS(const Napi::CallbackInfo &info, const Napi::Value &value);

        // double time_stamp;
        Napi::Value GetTimeStamp(const Napi::CallbackInfo &info);

        void SetTimeStamp(const Napi::CallbackInfo &info, const Napi::Value &value);

        // Name of the video file, image directory, or the webcam
        // std::string name;
        Napi::Value GetName(const Napi::CallbackInfo &info);

        void SetName(const Napi::CallbackInfo &info, const Napi::Value &value);

        // Allows to differentiate if failed because no input specified or if failed to open a specified input
        // bool no_input_specified;
        Napi::Value GetNoInputSpecified(const Napi::CallbackInfo &info);

        void SetNoInputSpecified(const Napi::CallbackInfo &info, const Napi::Value &value);

        // Storing the captured data queue
        // static const int CAPTURE_CAPACITY = 200; // 200 MB
        static Napi::Value GetCaptureCapacity(const Napi::CallbackInfo &info);

        Napi::Value Close(const Napi::CallbackInfo& info) {
            this->sequenceCapture->Close();
            return info.Env().Undefined();
        }

    };
}

#endif //NODOFACE_SEQUENCECAPTURE_H
