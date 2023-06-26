#include <iostream>
#include <opencv2/opencv.hpp>

int main(int, char**){
  cv::Mat image, translated_image;
  cv::Mat img_q1, img_q2, img_q3, img_q4, sup_img, inf_img;
  int height, width;

  image= cv::imread("pexels.png",cv::IMREAD_GRAYSCALE);
  if(!image.data)
    std::cout << "nao abriu pexels.png" << std::endl;

  width = image.cols;
  height = image.rows;

  cv::namedWindow("Janela", cv::WINDOW_AUTOSIZE);
  
  cv::imshow("image original", image);  
  cv::waitKey();

  img_q1 = cv::Mat(image, cv::Rect(0, 0, image.cols/2, image.rows/2));
  img_q2 = cv::Mat(image, cv::Rect(image.rows/2, 0, image.cols/2, image.rows/2));
  img_q3 = cv::Mat(image, cv::Rect(0, image.cols/2, image.cols/2, image.rows/2));
  img_q4 = cv::Mat(image, cv::Rect(image.rows/2, image.cols/2, image.cols/2, image.rows/2));

  cv::hconcat(img_q4, img_q3, sup_img);
  cv::hconcat(img_q2, img_q1, inf_img);

  cv::vconcat(sup_img, inf_img, translated_image);


  cv::imwrite("translated_image.png", translated_image);
  cv::imshow("image transladada", translated_image);  
  cv::waitKey();
  return 0;
}