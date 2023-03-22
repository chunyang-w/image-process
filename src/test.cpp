# include <iostream>
# include <vector>
# include "image.h"
# include "filter.h"
# include "volume.h"
# include "projection.h"
# include "fastImage.h"
# include "filter3d.h"
# include <cassert>

using namespace std;

int test_gaussian_filter(){
    /**test gaussian filter
     * This function is used to test the gaussian filter
     * and it will generate 10 random sets of paramters to test the filter.
     * (The kernel is calculated by hand and set as static for the test)
     */
    Volume voxel("../Scans/confuciusornis/");
    Volume voxel2 = gaussian3d(voxel, 3, "../Output/test_Gaussian/");
    double kernel[3][3][3] = {
    {{0.0205863, 0.033941, 0.0205863}, {0.033941, 0.0559593, 0.033941}, {0.0205863, 0.033941, 0.0205863}},
    {{0.033941, 0.0559593, 0.033941}, {0.0559593, 0.0922613, 0.0559593}, {0.033941, 0.0559593, 0.033941}},
    {{0.0205863, 0.033941, 0.0205863}, {0.033941, 0.0559593, 0.033941}, {0.0205863, 0.033941, 0.0205863}}
    };
    srand((unsigned)time(NULL));
    cout << "voxel constructed, size: " << voxel.img_num << endl;
    for(int test_time = 0; test_time < 10; test_time++){
        int numth_image = (rand() % (voxel.img_num - 2)) + 1;
        FImage left(voxel.files[numth_image - 1]);
        FImage middle(voxel.files[numth_image]);
        FImage right(voxel.files[numth_image + 1]);
        string test_path = "../Output/test_Gaussian/";
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
                }
            }
        }
        int expected_value = (int)result;
        cout << "expected_value: " << expected_value << endl;
        cout << "======test result=====" << endl;
        cout << "test passed" << endl;
        assert(("calculated error", (expected_value - test_value) * (expected_value - test_value) <= 1));
    }
    return 0;
}


int main() {
    cout << "Do you want to test whole gaussian filter? (Y/N)" << endl;
    cout << "(It may take about 5 minutes)" << endl;
    char input;
    cin >> input;
    if (input == 'Y' || input == 'y'){
        test_gaussian_filter();
    }
    return 0;
}
