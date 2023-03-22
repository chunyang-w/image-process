# include <iostream>
# include <vector>
# include "image.h"
# include "filter.h"
# include "volume.h"
# include "projection.h"
# include "fastImage.h"
# include "filter3d.h"
# include <cassert>
# include <random>

using namespace std;

int main() {
    double kernel[3][3][3] = {
        {{0.0205863, 0.033941, 0.0205863}, {0.033941, 0.0559593, 0.033941}, {0.0205863, 0.033941, 0.0205863}},
        {{0.033941, 0.0559593, 0.033941}, {0.0559593, 0.0922613, 0.0559593}, {0.033941, 0.0559593, 0.033941}},
        {{0.0205863, 0.033941, 0.0205863}, {0.033941, 0.0559593, 0.033941}, {0.0205863, 0.033941, 0.0205863}}
    };
    Volume voxel("../Scans/confuciusornis/");
    srand((unsigned)time(NULL));
    cout << "voxel constructed, size: " << voxel.img_num << endl;
    int numth_image = (rand() % (voxel.img_num - 2)) + 1;
    FImage left(voxel.files[numth_image - 1]);
    FImage middle(voxel.files[numth_image]);
    FImage right(voxel.files[numth_image + 1]);
    string test_path = "../Output/mini/";
    Volume test_voxel(test_path);
    int height = (rand() % (middle.height - 2)) + 1;
    int width = (rand() % (middle.width - 2)) + 1;
    cout << "test numth_image: " << numth_image << endl;
    cout << "test height: " << height << endl;
    cout << "test width: " << width << endl;
    FImage test_img(test_voxel.files[numth_image - 1]);
    int test_value = test_img.getPixel(height, width, 1);
    int initial_value = middle.getPixel(height, width, 1);
    cout << "test_value: " << test_value << endl;
    double result = 0;
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            for(int k = 0; k<3; k++){
                if (i == 0){
                    result += kernel[i][j][k] * left.getPixel(height + j - 1, width + k - 1, 1);
                }
                else if (i == 1){
                    result += kernel[i][j][k] * middle.getPixel(height + j - 1, width + k - 1, 1);
                }
                else{
                    result += kernel[i][j][k] * right.getPixel(height + i - 1, width + k - 1, 1);
                }
                // cout << result << endl;
            }
        }
    }
    int expected_value = (int)result;
    cout << "expected_value: " << expected_value << endl;
    cout << "======test result=====" << endl;
    cout << "test passed" << endl;
    assert(("calculated error", (expected_value - test_value) * (expected_value - test_value) <= 1));








    // Volume voxel("../Scans/confuciusornis/");
    // Volume voxel2 = gaussian3d(voxel, 3, "../Output/mini/");




    // Volume voxel2 = median3d(voxel, 5, "../Output/mini/");
    // cout << "voxel2 constructed, size: " << voxel2.img_num << endl;
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
