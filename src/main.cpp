# include <iostream>
# include <vector>
# include "image.h"
# include "filter.h"

using namespace std;

int main() {
    Image img("../Images/gracehopper.png");
    Filter box3x3("./filter/box3x3.txt");
    Filter gaussian3x3("./filter/gaussian3x3.txt");
    Filter box5x5("./filter/box5x5.txt");
    Filter sobelx("./filter/sobelx.txt");
    Filter prewittx("./filter/prewittx.txt");

    box3x3.apply(img).write("../Output/box_gracehopper.png");
    gaussian3x3.apply(img).write("../Output/gau_gracehopper.png");
    box5x5.apply(img).write("../Output/box5_gracehopper.png");
    sobelx.apply(box3x3.apply(grayScale(img))).write("../Output/sobelx_gracehopper.png");
    prewittx.apply(box3x3.apply(grayScale(img))).write("../Output/prewittx_gracehopper.png");

    sobel(grayScale(img)).write("../Output/sobel_gracehopper.png");
    prewitt(grayScale(img)).write("../Output/prewitt_gracehopper.png");
    return 0;
}