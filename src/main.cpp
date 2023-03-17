# include <iostream>
# include "image.h"
# include "filter.h"

using namespace std;

int main() {
    // Image img("../Images/gracehopper.png");
    Image img("../Images/test.png");
    img.printSize();
    // Filter::grayScale(img).write("../Output/gray_gracehopper.png");
    // img.write("../Output/gracehopper.png");
    // img.printSize();
    // Filter::grayScale(img).printSize();
    Filter::colorBalance(img).write("../Output/adj_test.png");
    return 0;
}