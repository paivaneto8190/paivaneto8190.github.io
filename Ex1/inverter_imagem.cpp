#include <iostream>
#include <opencv2/opencv.hpp>

int main(int, char** argv){
  cv::Mat image;
  int pixel_x1, pixel_y1, pixel_x2, pixel_y2, height, width;

  image= cv::imread(argv[1],cv::IMREAD_GRAYSCALE);
  if(!image.data)
    std::cout << "nao abriu " << argv[1] << std::endl;

  cv::namedWindow("Janela", cv::WINDOW_AUTOSIZE);

  width = image.cols;
  height = image.rows;

  std::cout << "Tamanho da imagem: " << width << " x " << height << std::endl;

  std::cout << "Digite as coordenadas do ponto 1:" << std::endl;
  std::cin >> pixel_x1 >> pixel_y1;
  std::cout << "Digite as coordenadas do ponto 2:" << std::endl;
  std::cin >> pixel_x2 >> pixel_y2;

  if (pixel_x1 >= 0 && pixel_x2 <= width) {
    if (pixel_y1  >= 0 && pixel_y2 <= height) {

      cv::imshow("Imagem original", image);  
      cv::waitKey();

      for(int i=pixel_x1;i<pixel_x2;i++){
        for(int j=pixel_y1;j<pixel_y2;j++){
          image.at<uchar>(i,j) = 255 - image.at<uchar>(i,j);
        }
      }

  cv::imshow("Imagem negativa", image);  
  cv::waitKey();
    }
  }
  else {
    std::cout << "Coordenadas invalidas" << std::endl;
  }

  return 0;
}