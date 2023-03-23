
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
        std::cout << "Test passed" << std::endl;
    } else {
        std::cout << "Test failed" << std::endl;
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
        std::cout << "Test passed" << std::endl;
    } else {
        std::cout << "Test failed" << std::endl;
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
        std::cout << "Test passed" << std::endl;
    } else {
        std::cout << "Test failed" << std::endl;
    }
}

void test_imageBlur() {
    Image test_img(2, 2, 3);
    test_img.pixel = {{{100, 150, 200}, {50, 100, 150}},
                      {{150, 200, 250}, {200, 250, 255}}};

    // Test with Median Blur and kernel size = 3
    Image result1 = imageBlur(test_img, 1, 3);
    Image expected_result1(2, 2, 3);
    expected_result1.pixel = {{{90, 140, 190}, {40, 90, 140}},
                             {{140, 190, 240}, {190, 240, 245}}};

    // Test with Box Blur and kernel size = 3
    Image result2 = imageBlur(test_img, 2, 3);
    Image expected_result2(2, 2, 3);
    expected_result1.pixel = {{{55, 77, 95}, {55, 77, 95}}, 
                               {{55, 77, 95}, {55, 77, 95}}};

    // Test with Gaussian Blur and kernel size = 5
    Image result3 = imageBlur(test_img, 3, 5);
    Image expected_result3(2, 2, 3);
    expected_result1.pixel = {{{45, 65, 83}, {44, 64, 80}},
                               {{54, 73, 89}, {54, 74, 88}}};

    if (result1.isEqual(expected_result1) && result2.isEqual(expected_result2) && result3.isEqual(expected_result3)) {
        std::cout << "Test passed" << std::endl;
    } else {
        std::cout << "Test failed" << std::endl;
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
        std::cout << "Test passed" << std::endl;
    } else {
        std::cout << "Test failed" << std::endl;
    }
}   

void test_EdgeDetection() {
    Image test_img(2, 2, 3);
    test_img.pixel = {{{100, 150, 200}, {50, 100, 150}},
                      {{150, 200, 250}, {200, 250, 255}}};

    // Test with Sobel method 
    Image result1 = edgeDetection(test_img, 1);
    Image expected_result1(2, 2, 3);
    expected_result1.pixel = {{{153}, {6}},
                             {{244}, {101}}};

    // Test with Prewitt method 
    Image result2 = edgeDetection(test_img, 2);
    Image expected_result2(2, 2, 1);
    expected_result1.pixel = {{{193}, {121}}, 
                              {{50}, {11}}};

    // Test with Scharr method
    Image result3 = edgeDetection(test_img, 3);
    Image expected_result3(2, 2, 2);
    expected_result1.pixel = {{{141}, {132},
                               {166}, {224}}};
    
    // Test with Roberts Cross method 
    Image result4 = edgeDetection(test_img, 4);
    Image expected_result4(2, 2, 3);
    expected_result1.pixel = {{{106}, {188},
                               {160}, {231}}};

    if (result1.isEqual(expected_result1) && result2.isEqual(expected_result2) 
       && result3.isEqual(expected_result3) && result4.isEqual(expected_result4)) {
        std::cout << "Test passed" << std::endl;
    } else {
        std::cout << "Test failed" << std::endl;
    }
}











