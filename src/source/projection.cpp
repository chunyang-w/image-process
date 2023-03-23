# include <iostream>
# include <string>
# include <vector>
# include <fstream>
# include <sstream>
# include <math.h>
# include "projection.h"
# include "fastImage.h"

using namespace std;

FImage choose_projection(Volume voxel) {
    /**Projection for 3D images dataset into single 2D image.
     * This function is used to project 3D images into 2D images.
     * It provides three methods to project 3D images dataset into single 2D image.
     * 
     * 1. The first method is max projection, which is used to find the maximum value 
     * 2. The second method is min projection, which is used to find the minimum value
     * 3. The third method is average projection, which is used to find the average value
     * 
     * it also provides three planes to project 3D images dataset into single 2D image.
     * 
     * 1. The first plane is XY plane, which is used to project 3D images dataset into image height and width plane.
     * 2. The second plane is XZ plane, which is used to project 3D images dataset into image height and depth plane.
     * 3. The third plane is YZ plane, which is used to project 3D images dataset into image width and depth plane.
     *
     * @param All of the path of the images. (It can be generated by volume class)
     * @return The final image after projection.
     */

    // Choose projection method and projection plane
    bool flag = true;
    int method;
    int plane;
    while(flag){
        cout << "Please enter your projection method:" << endl;
        cout << "1: max projection" << endl;
        cout << "2: min projection" << endl;
        cout << "3: average projection" << endl;
        if(!cin >> method){
            cin.clear();
            cin.ignore();
            cout << "You enter an invalid character" << endl;
            }
            else{
            cin >> method;
            }
        // Choose projection plane
        cout << "Please enter your final projection plane:" << endl;
        cout << "1: XY plane" << endl;
        cout << "2: XZ plane" << endl;
        cout << "3: YZ plane" << endl;
        if(!cin >> plane){
            cin.clear();
            cin.ignore();
            cout << "You enter an invalid character" << endl;
            }
            else{
            cin >> plane;
            }
            if(method != 1 && method != 2 && method != 3 && plane != 1 && plane != 2 && plane != 3){
                cout << "You enter an invalid number" << endl;
            }
            else{
                flag = false;
            }
    }
    // Choose projection plane
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
                    // change projection plane accoring to the w, h, c
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

                    // max projection
                    if (method == 1) {
                        if (current_pixel > res_img.getPixel(w, h, c)) {
                            res_img.setPixel(w, h, c, current_pixel);
                        }
                    }
                    // min projection
                    else if (method == 2) {
                        if (current_pixel < res_img.getPixel(w, h, c)) {
                            res_img.setPixel(w, h, c, current_pixel);
                        }
                    }
                    // average projection
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