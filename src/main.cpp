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
    box3x3.apply(img).write("../Output/box_gracehopper.png");
    gaussian3x3.apply(img).write("../Output/gau_gracehopper.png");
    box5x5.apply(img).write("../Output/box5_gracehopper.png");
    // img.printSize();
    // img.write("../Output/test_gracehopper.png");

    // Image img("../Images/vh_anatomy.png");
    // img.printSize();
    // img.write("../Output/test_stinkbug.png");

    // grayScale(img).write("../Output/gray_gracehopper.png");
    // img.write("../Output/gracehopper.png");
    // img.printSize();
    // grayScale(img).printSize();
    // pad(img).write("../Output/pad_test.png");
    // img.pad(10).write("../Output/goodgh.png");
    return 0;
}

    // vector<int> a;
    // a.push_back(1);
    // a.push_back(1);
    // a.push_back(1);
    // a.push_back(1);
    // a.push_back(1);
    // a[3] = 10;
    // for (int i = 0; i < a.size(); i++) {
    //     cout << a[i] << " ";
    // }
    // cout << endl;