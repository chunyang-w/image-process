
// Testing functions for the 2D filter implementations

# include <iostream>
# include <vector>
# include "image.h"
# include "filter.h"
# include <cassert>

using namespace std;


void test_grayScale() {
    Image test_img(2, 2, 3);
    test_img.pixel = {{{100, 150, 200}, {50, 100, 150}},
                      {{150, 200, 250}, {200, 250, 255}}};
    Image result = grayScale(test_img);
    Image expected_result(2, 2, 1);
    expected_result.pixel = {{{150}, {100}},
                             {{200}, {235}}};

    if (result.isEqual(expected_result)) {
        std::cout << "grayScale test passed" << std::endl;
    } else {
        std::cout << "grayScale test failed" << std::endl;
    }
}

void test_colourBalance() {
    Image test_img(2, 2, 3);
    test_img.pixel = {{{100, 150, 200}, {50, 100, 150}},
                      {{150, 200, 250}, {200, 250, 255}}};
    Image result = colourBalance(test_img);
    Image expected_result(2, 2, 3);
    expected_result.pixel = {{{146, 147, 158}, {96, 97, 108}}, 
                             {{196, 197, 208}, {246, 247, 213}}};

    if (result.isEqual(expected_result)) {
        std::cout << "colourBalance test passed" << std::endl;
    } else {
        std::cout << "colourBalance test failed" << std::endl;
    }
}

void test_Brightness() {
    Image test_img(2, 2, 3);
    test_img.pixel = {{{100, 150, 200}, {50, 100, 150}},
                      {{150, 200, 250}, {200, 250, 255}}};
    Image result = Brightness(test_img, -10);
    Image expected_result(2, 2, 3);
    expected_result.pixel = {{{90, 140, 190}, {40, 90, 140}},
                             {{140, 190, 240}, {190, 240, 245}}};

    if (result.isEqual(expected_result)) {
        std::cout << "Brightness test passed" << std::endl;
    } else {
        std::cout << "Brightness test failed" << std::endl;
    }
}

void test_imageBlur() {
    Image test_img(2, 2, 3);
    test_img.pixel = {{{100, 150, 200}, {50, 100, 150}},
                      {{150, 200, 250}, {200, 250, 255}}};

    // Test with Median Blur and kernel size = 3
    Image result1 = imageBlur(test_img, 1, 3);
    Image expected_result1(2, 2, 3);
    expected_result1.pixel = {{{0, 0, 0}, {0, 0, 0}},
                              {{0, 0, 0}, {0, 0, 0}}};

    // Test with Box Blur and kernel size = 3
    Image result2 = imageBlur(test_img, 2, 3);
    Image expected_result2(2, 2, 3);
    expected_result2.pixel = {{{55, 77, 95}, {55, 77, 95}}, 
                               {{55, 77, 95}, {55, 77, 95}}};

    // Test with Gaussian Blur and kernel size = 5
    Image result3 = imageBlur(test_img, 3, 5);
    Image expected_result3(2, 2, 3);
    expected_result3.pixel = {{{47, 68, 86}, {46, 67, 83}}, 
                              {{56, 77, 94}, {58, 78, 92}}};

    if (result1.isEqual(expected_result1)) {
        std::cout << "medianBlur test passed" << std::endl;
    } else {
        std::cout << "medianBlur test failed" << std::endl;
    }
    if (result2.isEqual(expected_result2)) {
        std::cout << "boxBlur test passed" << std::endl;
    } else {
        std::cout << "boxBlur test failed" << std::endl;
    }
    if (result3.isEqual(expected_result3)) {
        std::cout << "gaussianBlur test passed" << std::endl;
    } else {
        std::cout << "gaussianBlur test failed" << std::endl;
    }
}

void test_histogramEqualisation() {



    Image test_img(2, 2, 3);
    test_img.pixel = {{{100, 150, 200}, {50, 100, 150}},
                      {{150, 200, 250}, {200, 250, 255}}};

    Image result = histogramEqualisation(test_img);
    Image expected_result(2, 2, 3);
    expected_result.pixel = {{{128, 128, 128}, {64, 64, 64}}, 
                             {{191, 191, 191}, {255, 255, 255}}};

    if (result.isEqual(expected_result)) {
        std::cout << "histogramEqualisation test passed" << std::endl;
    } else {
        std::cout << "histogramEqualisation test failed" << std::endl;
    }
}   

void test_EdgeDetection() {
    Image test_img(2, 2, 3);
    test_img.pixel = {{{100, 150, 200}, {50, 100, 150}},
                      {{150, 200, 250}, {200, 250, 255}}};

    // Test with Sobel method 
    Image result1 = edgeDetection(test_img, 1);
    Image expected_result1(2, 2, 1);
    expected_result1.pixel = {{{1}, {255}},
                             {{255}, {104}}};

    // Test with Prewitt method 
    Image result2 = edgeDetection(test_img, 2);
    Image expected_result2(2, 2, 1);
    expected_result2.pixel = {{{1}, {255}, 
                             {250}, {101}}};

    // Test with Scharr method
    Image result3 = edgeDetection(test_img, 3);
    Image expected_result3(2, 2, 1);
    expected_result3.pixel = {{{1}, {255},
                               {255}, {104}}};
    
    // Test with Roberts Cross method 
    Image result4 = edgeDetection(test_img, 4);
    Image expected_result4(2, 2, 1);
    expected_result4.pixel = {{{106}, {188},
                               {160}, {231}}};

    if (result1.isEqual(expected_result1)) {
        std::cout << "Sobel test passed" << std::endl;
    } else {
        std::cout << "Sobel test failed" << std::endl;
    }
    if (result2.isEqual(expected_result2)) {
        std::cout << "Prewitt test passed" << std::endl;
    } else {
        std::cout << "Prewitt test failed" << std::endl;
    }
    if (result3.isEqual(expected_result3)) {
        std::cout << "Scharr test passed" << std::endl;
    } else {
        std::cout << "Scharr test failed" << std::endl;
    }
    if (result4.isEqual(expected_result4)) {
        std::cout << "Roberts Cross test passed" << std::endl;
    } else {
        std::cout << "Roberts Cross test failed" << std::endl;
    }
}


int main() {
    
    test_grayScale();
    test_colourBalance();
    test_Brightness();
    test_imageBlur();
    test_histogramEqualisation();
    test_EdgeDetection();   

    return 0; 
}











