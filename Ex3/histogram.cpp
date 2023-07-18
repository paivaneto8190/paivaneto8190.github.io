#include <iostream>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <string>

int SIDE = 256;
int PERIODOS = 4;

int main(int argc, char** argv) {
  std::stringstream ss_img, ss_img_nova, ss_yml;
  cv::Mat image, image_res;

  ss_yml << "senoide-" << SIDE << ".yml";
  image = cv::Mat::zeros(SIDE, SIDE, CV_32FC1);

  cv::FileStorage fs(ss_yml.str(), cv::FileStorage::WRITE);

  for (int i = 0; i < SIDE; i++) {
    for (int j = 0; j < SIDE; j++) {
      image.at<float>(i, j) = 127 * sin(2 * M_PI * PERIODOS * j / SIDE) + 128;
    }
  }

  fs << "mat" << image;
  fs.release();

  cv::normalize(image, image, 0, 255, cv::NORM_MINMAX);
  image.convertTo(image, CV_8U);
  ss_img << "senoide-" << SIDE << ".png";
  cv::imwrite(ss_img.str(), image);

  fs.open(ss_yml.str(), cv::FileStorage::READ);
  fs["mat"] >> image_res;

  cv::normalize(image, image_res, 0, 255, cv::NORM_MINMAX);
  image.convertTo(image, CV_8U);

  cv::imshow("image", image);
  cv::waitKey();

  //Parte em que compara as duas imagens
  for (int i = 0; i < SIDE; i++) {
    for (int j = 0; j < SIDE; j++) {
      image_res.at<float>(i,j) = image_res.at<float>(i,j) - image.at<int>(i,j);
    }
  }

  cv::normalize(image_res, image_res, 0, 255, cv::NORM_MINMAX);
  image_res.convertTo(image_res, CV_8U);
  ss_img_nova << "senoide_convertida-" << SIDE << ".png";
  cv::imwrite(ss_img_nova.str(), image_res);
    std::cout << image_res;

  return 0;
}