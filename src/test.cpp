
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


