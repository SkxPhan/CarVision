#include <iostream>

#include "opencv2/opencv.hpp"
#include "opencv2/video/background_segm.hpp"

using namespace cv;

int main(int argc, char** argv) {
  constexpr auto bgmaskThreshold{200};
  constexpr auto erosionDilationIterations{2};
  constexpr auto minContourArea{2000.0};

  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <video_file_path>\n";
    return -1;
  }

  const std::string videoFilePath{argv[1]};

  VideoCapture cap{videoFilePath};

  if (!cap.isOpened()) {
    std::cerr << "Error opening video stream or file\n";
    return -1;
  }

  Ptr<BackgroundSubtractorMOG2> bgsubtractor{createBackgroundSubtractorMOG2()};

  Mat frame, bgmask, combinedImage;

  std::cout << "Press 'ESC' to quit.\n";

  while (true) {
    cap >> frame;
    if (frame.empty()) break;

    bgsubtractor->apply(frame, bgmask);

    threshold(bgmask, bgmask, bgmaskThreshold, 255, THRESH_BINARY);

    Mat kernel{getStructuringElement(MORPH_ELLIPSE, Size(5, 5))};
    erode(bgmask, bgmask, kernel, Point(-1, -1), erosionDilationIterations);
    dilate(bgmask, bgmask, kernel, Point(-1, -1), erosionDilationIterations);

    std::vector<std::vector<Point>> contours;
    std::vector<Vec4i> hierarchy;
    findContours(bgmask, contours, hierarchy, RETR_EXTERNAL,
                 CHAIN_APPROX_SIMPLE);

    for (const auto& contour : contours) {
      if (contourArea(contour) > minContourArea) {
        Rect boundingRect{cv::boundingRect(contour)};
        rectangle(frame, boundingRect, Scalar(0, 0, 255), 2);
        putText(frame, "Car Detected",
                Point(boundingRect.x, boundingRect.y - 10),
                FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 2, LINE_AA);
      }
    }

    cvtColor(bgmask, bgmask, COLOR_GRAY2BGR);
    hconcat(frame, bgmask, combinedImage);
    resize(combinedImage, combinedImage, Size(2 * 1280, 720));
    imshow("Car detection", combinedImage);

    if (waitKey(50) == 27) break;
  }

  cap.release();

  cv::destroyAllWindows();

  return 0;
}