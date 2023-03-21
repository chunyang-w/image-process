
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
    expected_result.pixel = {{{150, 150, 150}, {100, 100, 100}},
                             {{200, 200, 200}, {250, 250, 250}}};

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
    Image test_img(3, 3, 1);
    test_img.pixel = {{{100}, {150}, {200}},
                      {{50}, {100}, {150}},
                      {{25}, {50}, {100}}};

    // Test with median blur (method = 1) and kernel_size = 3
    Image result1 = imageBlur(test_img, 1, 3);
    Image expected_result1(3, 3, 1);
    expected_result1.pixel = {{{100}, {100}, {150}},
                              {{50}, {100}, {150}},
                              {{50}, {50}, {100}}};

    // Test with mean blur (method = 2) and kernel_size = 3
    Image result2 = imageBlur(test_img, 2, 3);
    Image expected_result2(3, 3, 1);
    expected_result2.pixel = {{{83}, {95}, {117}},
                              {{64}, {76}, {98}},
                              {{41}, {53}, {75}}};

    if (result1.isEqual(expected_result1) && result2.isEqual(expected_result2)) {
        std::cout << "Test passed" << std::endl;
    } else {
        std::cout << "Test failed" << std::endl;
    }
}

void test_histogramEqualisation() {

// testing hist equalisation is difficult because results may differ due to rounding in the CDF calculation. 
// Here, we test if the result remains the same after applying the filter twice, which it should

    Image test_img(2, 2, 3);
    test_img.pixel = {{{100, 150, 200}, {50, 100, 150}},
                      {{150, 200, 250}, {200, 250, 255}}};
    Image result = histogramEqualisation(test_img);
    Image result2 = histogramEqualisation(result);
    

    if (result.isEqual(result2)) {
        std::cout << "Test passed" << std::endl;
    } else {
        std::cout << "Test failed" << std::endl;
    }
}











