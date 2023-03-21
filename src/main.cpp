# include <iostream>
# include <vector>
# include "image.h"
# include "filter.h"
# include "volume.h"
# include "projection.h"
# include "fastImage.h"
# include "filter3d.h"

using namespace std;

int main() {
    Volume voxel("../Scans/fracture/");
    // Volume voxel2 = gaussian3d(voxel, 21, "../Output/mini/");
    Volume voxel2 = median3d(voxel, 5, "../Output/mini/");
    cout << "voxel2 constructed, size: " << voxel2.img_num << endl;
    // FImage  XY_projection = choose_projection(voxel);
    // XY_projection.write("../Output/YZ_ave_confuciusornis.png");
    // Image max_img = max_projection(voxel);
    // max_img.write("../Output/max_fracture.png");
    // Volume voxel("../Scans/fracture/");
    // // cout << "Here" << endl;
    // Image max_img = max_projection(voxel);
    // Image min_img = min_projection(voxel);
    // FImage ave_img = Z_projection(voxel);
    // FImage ave_img = Z_projection(voxel);
    // max_img.write("../Output/max_confuciusornis.png");
    // min_img.write("../Output/min_confuciusornis.png");

    // ave_img.write("../Output/ave_confuciusornis.png");
    // XZ_projection.write("../Output/YZ_ave_fracture.png");
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
