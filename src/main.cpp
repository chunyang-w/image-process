# include <iostream>
# include "image.h"
# include "filter.h"

using namespace std;

int main() {
    Image img("../Images/gracehopper.png");
    img.printSize();
    Filter::grayScale(img).write("../Output/gray_gracehopper.png");
    img.write("../Output/gracehopperx.png");
    img.printSize();
    Filter::grayScale(img).printSize();
    return 0;
}