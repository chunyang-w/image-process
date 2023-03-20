# include <iostream>
# include <vector>
# include "image.h"
# include "fastImage.h"
# include "filter.h"
# include "volume.h"

using namespace std;

int main() {
    FImage fimg("../Images/gracehopper.png");
    fimg.printSize();

    Image img("../Images/gracehopper.png");
    img.printSize();

    FImage fimg2(fimg.height, fimg.width, fimg.channel);

    // for (int i = 0; i < img.height; i++) {
    //     for (int j = 0; j < img.width; j++) {
    //         for (int k = 0; k < img.channel; k++) {
    //             // unsigned char fpix = fimg.getPixel(i, j, k);
    //             // unsigned char pix = img.pixel[i][j][k];
    //             // if (int(fpix) == int(pix)) {
    //             //     cout << "failed at " << i << " " << j << " " << k << " | " << int(fpix) << " " << int(pix) << endl;
    //             //  }
    //             fimg2.setPixel(i, j, k, fimg.getPixel(i, j, k));
    //         }
    //     }
    // }

    fimg2.write("../Output/fimg2.png");

    FImage fimg3(fimg.height, fimg.width, fimg.channel);
    fimg3.write("../Output/fimg3.png");

    FImage fimg4 = fimg.pad(20);

    fimg.write("../Output/fimg1.png");
    fimg4.write("../Output/fimg4.png");

    cout << "success" << endl;

    // Volume voxel("../Scans/confuciusornis/");
    // Image img("/Users/cw1722/Documents/Imperial/ap_cw2/Scans/confuciusornis/confuYZ0249.png");
    // img.printSize();
    // Filter box3x3("./filter/box3x3.txt");
    // Filter gaussian3x3("./filter/gaussian3x3.txt");
    // Filter box5x5("./filter/box5x5.txt");
    // Filter sobelx("./filter/sobelx.txt");
    // Filter prewittx("./filter/prewittx.txt");

    // box3x3.apply(img).write("../Output/box_gracehopper.png");
    // gaussian3x3.apply(img).write("../Output/gau_gracehopper.png");
    // box5x5.apply(img).write("../Output/box5_gracehopper.png");
    // sobelx.apply(box3x3.apply(grayScale(img))).write("../Output/sobelx_gracehopper.png");
    // prewittx.apply(box3x3.apply(grayScale(img))).write("../Output/prewittx_gracehopper.png");

    // sobel(grayScale(img)).write("../Output/sobel_gracehopper.png");
    // prewitt(grayScale(img)).write("../Output/prewitt_gracehopper.png");
    return 0;
}