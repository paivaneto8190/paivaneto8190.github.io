#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
	cv::Mat image;
    cv::Point p;
	int width, height;
    int holes = 0, bubbles=0;

    image = cv::imread(argv[1],cv::IMREAD_GRAYSCALE);
    
    if(!image.data)
        std::cout << "nao abriu " << argv[1] << std::endl;

    cv::namedWindow("Janela", cv::WINDOW_AUTOSIZE);

    cv::imshow("janelaOriginal", image);

    width = image.cols;
    height = image.rows;
    p.x = 0;
    p.y = 0;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (image.at<uchar>(i, j) == 255) {
                if (i == 0 || j == 0 || i == (height - 1) || j == (width - 1)) {
                    p.x = j;
                    p.y = i;
                    cv::floodFill(image, p, 0);
                }
            }
        }
    }

    p.x = 0;
    p.y = 0;
    cv::floodFill(image, p, 200);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (image.at<uchar>(i, j) == 255) {
                p.x = j;
                p.y = i;
                bubbles++;
                cv::floodFill(image, p, 30);
            }
        }
    }

    cv::imshow("Imagem bolhas", image);
    cv::imwrite("Imagem_bolhas.png", image);
    cv::waitKey();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (image.at<uchar>(i, j) == 0) {
                if (image.at<uchar>(i - 1, j) != 200) {
                    holes++;
                    p.x = j;
                    p.y = i;
                    cv::floodFill(image, p, 200);
                }
            }
        }
    }

    cv::imshow("labeling", image);
    cv::imwrite("labeling.png", image);

    int aux = bubbles - holes; //calcula o complemento para saber quantas bolhas não tem buracos
    std::cout << "Numero de bolhas com buracos: " << holes << std::endl;
    std::cout << "Numero de bolhas sem buracos: " << aux << std::endl;
    std::cout << "Numero de bolhas: " << bubbles << std::endl;
    cv::waitKey();

    return 0;
}