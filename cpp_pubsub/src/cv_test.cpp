#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
  // Load the image.
  cv::Mat image = cv::imread("image.jpg");

  // Find the minimum and maximum values in the image.
  double minVal, maxVal;
//   cv::Point minLoc, maxLoc;
  cv::minMaxLoc(image, &minVal, &maxVal);

  // Print the minimum and maximum values.
  std::cout << "Minimum value: " << minVal << std::endl;
  std::cout << "Maximum value: " << maxVal << std::endl;

  // Print the coordinates of the minimum and maximum values.
//   std::cout << "Minimum location: " << minLoc << std::endl;
//   std::cout << "Maximum location: " << maxLoc << std::endl;

  // Display the image.
  cv::namedWindow("Image");
  cv::imshow("Image", image);
  cv::waitKey(0);

  return 0;
}