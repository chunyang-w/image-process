/* Group: Monte Carlo
Members: Zepeng Chen    | acse-zc522
         Ruichen Ding   | acse-rd422
         Georgie Mercer | edsml-gm1722
         Chunyang Wang  | acse-cw17222
         Lizzie Withers | edsml-lcw22
*/

# include <iostream>
# include <vector>
# include "image.h"
# include "filter.h"
# include "volume.h"
# include "projection.h"
# include "fastImage.h"
# include "slice.h"
# include "filter3d.h"
# include <cassert>
# include "helper.h"

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
        std::cout << "grayScale test passed" << std::endl;
    } else {
        std::cout << "grayScale test failed" << std::endl;
    }
}

void test_colourBalance() {
    Image test_img(2, 2, 3);
    test_img.pixel = {{{100, 150, 200}, {50, 100, 150}},
                      {{150, 200, 250}, {200, 250, 255}}};
    Image result = colourBalance(test_img);
    Image expected_result(2, 2, 3);
    expected_result.pixel = {{{146, 147, 158}, {96, 97, 108}}, 
                             {{196, 197, 208}, {246, 247, 213}}};

    if (result.isEqual(expected_result)) {
        std::cout << "colourBalance test passed" << std::endl;
    } else {
        std::cout << "colourBalance test failed" << std::endl;
    }
}

void test_Brightness() {
    Image test_img(2, 2, 3);
    test_img.pixel = {{{100, 150, 200}, {50, 100, 150}},
                      {{150, 200, 250}, {200, 250, 255}}};
    Image result = Brightness(test_img, -10);
    Image expected_result(2, 2, 3);
    expected_result.pixel = {{{90, 140, 190}, {40, 90, 140}},
                             {{140, 190, 240}, {190, 240, 245}}};

    if (result.isEqual(expected_result)) {
        std::cout << "Brightness test passed" << std::endl;
    } else {
        std::cout << "Brightness test failed" << std::endl;
    }
}

void test_imageBlur() {
    Image test_img(2, 2, 3);
    test_img.pixel = {{{100, 150, 200}, {50, 100, 150}},
                      {{150, 200, 250}, {200, 250, 255}}};

    // Test with Median Blur and kernel size = 3
    Image result1 = imageBlur(test_img, 1, 3);
    Image expected_result1(2, 2, 3);
    expected_result1.pixel = {{{0, 0, 0}, {0, 0, 0}},
                              {{0, 0, 0}, {0, 0, 0}}};

    // Test with Box Blur and kernel size = 3
    Image result2 = imageBlur(test_img, 2, 3);
    Image expected_result2(2, 2, 3);
    expected_result2.pixel = {{{55, 77, 95}, {55, 77, 95}}, 
                               {{55, 77, 95}, {55, 77, 95}}};

    // Test with Gaussian Blur and kernel size = 5
    Image result3 = imageBlur(test_img, 3, 5);
    Image expected_result3(2, 2, 3);
    expected_result3.pixel = {{{47, 68, 86}, {46, 67, 83}}, 
                              {{56, 77, 94}, {58, 78, 92}}};

    if (result1.isEqual(expected_result1)) {
        std::cout << "medianBlur test passed" << std::endl;
    } else {
        std::cout << "medianBlur test failed" << std::endl;
    }
    if (result2.isEqual(expected_result2)) {
        std::cout << "boxBlur test passed" << std::endl;
    } else {
        std::cout << "boxBlur test failed" << std::endl;
    }
    if (result3.isEqual(expected_result3)) {
        std::cout << "gaussianBlur test passed" << std::endl;
    } else {
        std::cout << "gaussianBlur test failed" << std::endl;
    }
}

void test_histogramEqualisation() {



    Image test_img(2, 2, 3);
    test_img.pixel = {{{100, 150, 200}, {50, 100, 150}},
                      {{150, 200, 250}, {200, 250, 255}}};

    Image result = histogramEqualisation(test_img);
    Image expected_result(2, 2, 3);
    expected_result.pixel = {{{128, 128, 128}, {64, 64, 64}}, 
                             {{191, 191, 191}, {255, 255, 255}}};

    if (result.isEqual(expected_result)) {
        std::cout << "histogramEqualisation test passed" << std::endl;
    } else {
        std::cout << "histogramEqualisation test failed" << std::endl;
    }
}   

void test_EdgeDetection() {
    Image test_img(2, 2, 3);
    test_img.pixel = {{{100, 150, 200}, {50, 100, 150}},
                      {{150, 200, 250}, {200, 250, 255}}};

    // Test with Sobel method 
    Image result1 = edgeDetection(test_img, 1);
    Image expected_result1(2, 2, 1);
    expected_result1.pixel = {{{0}, {255}},
                             {{255}, {104}}};

    // Test with Prewitt method 
    Image result2 = edgeDetection(test_img, 2);
    Image expected_result2(2, 2, 1);
    expected_result2.pixel = {{{0}, {255}, 
                             {250}, {101}}};

    // Test with Scharr method
    Image result3 = edgeDetection(test_img, 3);
    Image expected_result3(2, 2, 1);
    expected_result3.pixel = {{{0}, {255},
                               {255}, {104}}};
    

    if (result1.isEqual(expected_result1)) {
        std::cout << "Sobel test passed" << std::endl;
    } else {
        std::cout << "Sobel test failed" << std::endl;
    }

}


FImage set_pixel(int method, int direction){
    /**
     * This function is to set the picture which is the expected answer of projection
     * @param method which projection method we shoose to examine
     * 1: max projection
     * 2: min projection
     * 3: average projection 
     * @param direction which direction we choose to examine
     * 1: XY plane
     * 2: XZ plane
     * 3: YZ plane
     * @return The expected answer after projection.
     */

    string dest_path = "../Output/Testimage/";
    FImage pic1 = FImage(3, 3, 3);
    FImage pic2 = FImage(3, 3, 3);
    FImage pic3 = FImage(3, 3, 3);


    createFolder(dest_path);


    pic1.write("../Output/Testimage/test1.png");
    pic2.write("../Output/Testimage/test2.png");
    pic3.write("../Output/Testimage/test3.png");

    FImage expected_pic = FImage(3, 3, 3);
    for (int i = 0; i < 2; i++){
        for(int m = 0; m < 2; m++){
            for(int n = 0; n < 2; n++){
                pic1.setPixel(i, m, n, 2);
                pic2.setPixel(i, m, n, 3);
                pic3.setPixel(i, m, n, 4);
                if (method == 1){
                    expected_pic.setPixel(i, m, n, 4); // Maximum intensity projection result.
                }
                else if (method == 2)
                {
                    expected_pic.setPixel(i, m, n, 2); // Minimum intensity projection result.
                }
                else if (method == 3)
                {
                    expected_pic.setPixel(i, m, n, 3); // Average intensity projection
                }
            }
        }
    }
    return expected_pic;
}

void Testchoose_projection(FImage expected, int method, int direction){
    /**
     * This function is to use the choose_projection function to get the actual answer
     * and compare the two answers.
     * @param path The location of the folder where the generated test pictures are saved
     * @param method which projection method we choose to use
     * @param direction which direction we choose to project
    */

    Volume path("../Output/Testimage/");
    if(method == 1){
        FImage result = choose_projection(path);
        if(result == expected){
        cout << "The test for the maximum projection is successful." << endl;
        }
        else{
            cout << "The test for the maximum projection is failed." << endl;
        }
    }
    else if (method == 2)
    {
        FImage result = choose_projection(path);
        if(result == expected){
        cout << "The test for the minimum projection is successful." << endl;
        }
        else{
            cout << "The test for the minimum projection is failed." << endl;
        }
    }
    else if (method == 3)
    {
        FImage result = choose_projection(path);
        if(result == expected){
        cout << "The test for the average projection is successful." << endl;
        }
        else{
            cout << "The test for the average projection is failed." << endl;
        }
    }
}








int test_gaussian_filter(){
    /**test gaussian filter
     * This function is used to test the gaussian filter
     * and it will generate 10 random sets of paramters to test the filter.
     * (The kernel is calculated by hand and set as static for the test)
     */
    Volume voxel("../Images/test_set/");
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
    cout << "Testing for each 2d filter here" << endl;
    test_grayScale();
    test_colourBalance();
    test_Brightness();
    test_imageBlur();
    test_histogramEqualisation();
    test_EdgeDetection();  
    cout << "Do you want to test whole gaussian filter? (Y/N)" << endl;
    char input;
    cin >> input;
    if (input == 'Y' || input == 'y'){
        test_gaussian_filter();
    }
    cout << "Test whole choose_projection function here" << endl;
    Testchoose_projection(set_pixel(1, 1), 1, 1);
    return 0;
}
