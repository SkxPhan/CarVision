# CarVision: Real-Time Car Detection with OpenCV

This is a simple C++ program using OpenCV to detect cars in a video stream.

## Prerequisites

- OpenCV (>= 3.0)

## Usage

1. Clone the repository:
git clone https://github.com/SkxPhan/CarVision.git
2. Compile the code:
cd CarVision
mkdir build && cd build
cmake ..
make
3. Run the executable:
./CarVision ../data/video.mp4

## Description

The program performs the following steps:

1. Read the input video file.
2. Apply background subtraction to detect moving objects (cars).
3. Perform thresholding to create a binary mask.
4. Perform erosion and dilation to reduce noise and smooth contours.
5. Find contours of objects in the binary mask.
6. Filter contours based on minimum area to detect cars.
7. Draw bounding boxes around detected cars and label them.
8. Display the processed frames with detected cars in real-time.

## Parameters

- `bgmaskThreshold`: Threshold value for background binary mask.
- `erosionDilationIterations`: Number of iterations for erosion and dilation.
- `minContourArea`: Minimum contour area threshold for detecting cars.

## License

This project is licensed under the MIT License - see the [LICENSE](https://github.com/SkxPhan/CarVision/blob/main/LICENSE) file for details.