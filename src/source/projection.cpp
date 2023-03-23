/* Group: Monte Carlo
Members: Zepeng Chen    | acse-zc522
         Ruichen Ding   | acse-rd422
         Georgie Mercer | edsml-gm1722
         Chunyang Wang  | acse-cw17222
         Lizzie Withers | edsml-lcw22
*/

# include <iostream>
# include <string>
# include <vector>
# include <fstream>
# include <sstream>
# include <math.h>
# include "projection.h"
# include "fastImage.h"

using namespace std;


/**
@brief Returns an FImage object representing the 2D projection of a given 3D volume.
This function prompts the user to select a projection method and projection plane, and then calculates
the 2D projection of the input 3D volume data using the chosen method and plane. The function supports
three projection methods: max projection, min projection, and average projection, and three projection
planes: XY plane, XZ plane, and YZ plane.
@param voxel - A Volume object containing the input 3D volume data.
@return FImage - An FImage object representing the 2D projection of the input 3D volume data.
*/
FImage choose_projection(Volume voxel) {

    // Choose projection method and projection plane
    cout << "Please enter your projection method:" << endl;
    cout << "1: max projection" << endl;
    cout << "2: min projection" << endl;
    cout << "3: average projection" << endl;
    int method;
    cin >> method;

    // Choose projection plane
    cout << "Please enter your final projection plane:" << endl;
    cout << "1: XY plane" << endl;
    cout << "2: XZ plane" << endl;
    cout << "3: YZ plane" << endl;
    int plane;
    cin >> plane;
    int length;
    vector<vector<vector<int>>> init_pixel;
    FImage example_img(voxel.files[0]);

    // Initialize the dimension of final image
    if(plane == 1){
        FImage res_img(voxel.files[0]);
        length = voxel.img_num;
        init_pixel.resize(example_img.height);
        for (int i = 0; i < example_img.height; i++) {
            init_pixel[i].resize(example_img.width);
        }
        for (int i = 0; i < example_img.height; i++) {
            for (int j = 0; j < example_img.width; j++) {
                init_pixel[i][j].resize(example_img.channel);
            }
        }
    }
    else if(plane == 2){
        FImage res_img(example_img.height, voxel.img_num, example_img.channel);
        length = example_img.width;
        init_pixel.resize(example_img.height);
        for (int i = 0; i < example_img.height; i++) {
            init_pixel[i].resize(voxel.img_num);
        }
        for (int i = 0; i < example_img.height; i++) {
            for (int j = 0; j < voxel.img_num; j++) {
                init_pixel[i][j].resize(example_img.channel);
            }
        }
    }
    else if(plane == 3){
        FImage res_img(voxel.img_num, example_img.width, example_img.channel);
        length = example_img.height;
        init_pixel.resize(voxel.img_num);
        for (int i = 0; i < voxel.img_num; i++) {
            init_pixel[i].resize(example_img.width);
        }
        for (int i = 0; i < voxel.img_num; i++) {
            for (int j = 0; j < example_img.width; j++) {
                init_pixel[i][j].resize(example_img.channel);
            }
        }
    }
    vector<vector<vector<int>>> total_pixel = init_pixel;
    int w, h, c;
    FImage res_img(voxel.files[0]);
    for (int m = 1; m < voxel.img_num; m++) {    // Loop for all images
        FImage img(voxel.files[m]);              // Read single image in each loop
        for (int i = 0; i < res_img.height; i++) {
            for (int j = 0; j < res_img.width; j++) {
                for (int k = 0; k < res_img.channel; k++) {
                    double current_pixel = img.getPixel(i, j, k);
                    // Change projection plane accoring to the w, h, c
                    // (w, h) plane is the final projection plane
                    if(plane == 1){
                        w = i;
                        h = j;
                        c = k;
                    }
                    else if(plane == 2){
                        w = i;
                        h = m;
                        c = k;
                    }
                    else if(plane == 3){
                        w = m;
                        h = j;
                        c = k;
                    }

                    // Max projection
                    if (method == 1) {
                        if (current_pixel > res_img.getPixel(w, h, c)) {
                            res_img.setPixel(w, h, c, current_pixel);
                        }
                    }
                    // Min projection
                    else if (method == 2) {
                        if (current_pixel < res_img.getPixel(w, h, c)) {
                            res_img.setPixel(w, h, c, current_pixel);
                        }
                    }
                    // Average projection
                    else if (method == 3) {
                        if (m == 1) {
                            total_pixel[w][h][c] = example_img.getPixel(w, h, c) + current_pixel;
                        }
                        else {
                            total_pixel[w][h][c] = total_pixel[w][h][c] + current_pixel;
                        }
                        if(m == voxel.img_num - 1) {
                            res_img.setPixel(w, h, c, total_pixel[w][h][c] / length);
                        }
                    }
                }
            }
        }
    }
    return res_img;
}