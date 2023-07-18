#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char**argv) {
  cv::Mat imagemEsteg, imagemFinal;
  cv::Vec3b valDecode, valFinal;
  int nbits = 3;

  imagemEsteg = cv::imread(argv[1], cv::IMREAD_COLOR);

  if (imagemEsteg.empty()) {
    std::cout << "imagem nao carregou corretamente" << std::endl;
    return (-1);
  }

  imagemFinal = imagemEsteg.clone();

  for (int i = 0; i < imagemEsteg.rows; i++) {
    for (int j = 0; j < imagemEsteg.cols; j++) {
        valDecode = imagemEsteg.at<cv::Vec3b>(i, j);
        valDecode[0] = valDecode[0] << (8 - nbits);
        valDecode[1] = valDecode[1] << (8 - nbits);
        valDecode[2] = valDecode[2] << (8 - nbits);
        imagemFinal.at<cv::Vec3b>(i, j) = valDecode;
    }
  }

  imwrite("estegDecoded.png", imagemFinal);
  return 0;
}