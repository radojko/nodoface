# Nodoface

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg?style=square-flat)](https://www.gnu.org/licenses/gpl-3.0)

C++ Addon for fast and efficient facial analytics on Nodejs/TypeScript. 

# CCExtractor + Google Summer of Code = :purple_heart:
Nodoface is the backbone of [Poor Man's Rekognition](https://github.com/sziraqui/pmr-gsoc-tracker) being developed under Google Summer of Code 2019 for CCExtractor Development.

<div width="100%" height="240" display="flex" align-items="center">
    <img src="https://github.com/CCExtractor/ccextractor-org-media/raw/master/static/ccx_logo_transparent_800x600.png"
    height="240" alt="CCExtractor Logo">
    <img src="https://developers.google.com/open-source/gsoc/resources/downloads/GSoC-icon-192.png"
    height="240">
</div>

# Features
This Addon provides bindings to all OpenFace 2.0 features except the visualization utilities and FaceAnalyser class. Face detection can be easily run in realtime on any modern CPU. The Addon is built using node-addon-api.
 
## Available classes from OpenFace
- ImageCapture
- SequenceCapture
- FaceDetectorMTCNN
- FaceDetectorHaar
- FaceDetectorHOG
- CLNF (LandmarkDetectorModel in OpenFace)
- LandmarkModelConfig (FaceModelParameters in OpenFace)
- GazeAnalyser (GazeAnalysis in OpenFace) [Does not work]
  
CLNF also provides HOG-based and Haar Cascades face detector. GazeAnalysis is a namespace with static classes in OpenFace but GazeAnalyser is a class in Nodoface.

## Bindings to some OpenCV types
- Image (`cv::Mat`)
- IntImage (`cv::Mat_<int>`)
- FloatImage (`cv::Mat_<float>`)
- rectangle (`cv::rectangle()`)
- showImage (`cv::imshow()`)
- readImage (`cv::imread()`)
- saveImage (`cv::imwrite`)
- destroyWindow (`cv::destroyWindow()`)
- destroyAllWindows (`cv::destroyAllWindows()`)
- waitkey (`cv::waitKey()`)
- VideoCapture (`cv::VideoCapture`)
Note: All methods return RGB image instead of BGR unlike OpenCV
OpenCV classes are partial bindings just sufficient for passing underlying Mat to/from nodejs and C++.

# Installation
### Dependencies
- OpenFace >= 2.1.0
- OpenCV >= 3.4.0
- dlib >= 19.13   
  All above libs must be compiled as a **shared library**
- node-addon-api >= 1.6.3

Step 1: [Install](https://docs.opencv.org/3.4.0/d7/d9f/tutorial_linux_install.html) OpenCV 3.4.x.    
If opencv is already installed, ensure it is recognised by pkg-config by executing:
```
$ pkg-config --modversion opencv
```
Step 2: [Install](http://dlib.net/compile.html) dlib 19.13 or greater as a shared library (default is static). 
Check [this](https://stackoverflow.com/a/33997825/6699069) answer by DavisKing for compiling it as shared library.     
Ensure it is recognised by pkg-config:
```
$ pkg-config --modversion dlib
```
Step 3: Install OpenFace. The original repo has some issues. It can only compile as static library. 
So use my OpenFace fork instead. I have modified CMakelists.txt to compile OpenFace as shared lib.
```
$ git clone https://github.com/sziraqui/OpenFace.git && cd OpenFace
$ git checkout dynamic-compile
$ ./download_models.sh
$ mkdir build && cd build
$ cmake -D CMAKE_BUILD_TYPE=RELEASE CMAKE_CXX_FLAGS="-std=c++11" -D CMAKE_EXE_LINKER_FLAGS="-std=c++11" 
$ make -j2
$ sudo make install
```
Step 4: Compile the bindings.
```
$ git clone https://github.com/sziraqui/nodoface.git && cd nodoface
$ npm install
```
If you encounter errors, see my [gsoc notes](https://github.com/sziraqui/pmr-gsoc-tracker/blob/master/notes/CP1-W2.md#build-errors) for some assistance.
The addon is exported from ./api/nodoface.js
I will publish it to npm soon.

# Examples
Run some samples to test if everything is working.
```
$ node examples/mtcnn_on_video.js path/to/a/video/file <OpenFace_REPO_DIR>/lib/local/LandmarkDetector/model/mtcnn_detector/MTCNN_detector.txt
```
### Here's sample run:
[![IMAGE ALT Video Annotation](https://img.youtube.com/vi/7PUnz9dDZPQ/0.jpg)](https://www.youtube.com/watch?v=7PUnz9dDZPQ)

# Mentors
- [Carlos Fernandez](https://github.com/cfsmp3)
- [Johannes Lochter](https://scholar.google.com/citations?user=bOzlOZ8AAAAJ&hl=en)
  
# License
GNU General Public License 3.0 (GPL-v3.0)     
Please carefully read OpenFace 2.0 license. You must also respect opencv and dlib license.
