# include <iostream>
# include "image.h"

using namespace std;

int main() {
    Image img("../Images/gracehopper.png");
    img.printSize();
    img.write("../Output/gracehopper.png");
    return 0;
}