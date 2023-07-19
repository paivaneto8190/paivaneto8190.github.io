#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	cv::Mat image, eq_image;
    cv::Point p;

    image = cv::imread(argv[1],cv::IMREAD_GRAYSCALE);
    
    if(!image.data)
        std::cout << "nao abriu " << argv[1] << std::endl;

    cv::namedWindow("Janela", cv::WINDOW_AUTOSIZE);

    cv::equalizeHist(image, eq_image); //Equaliza o histograma

    cv::imshow("Escala de cinza", image);
    cv::imwrite("Imagem_esc_cinza.png", image);
    cv::imshow("Imagem_equalizada", eq_image);
    cv::imwrite("Imagem_equalizada.png", eq_image);
    cv::waitKey(0);

    return 0;
}