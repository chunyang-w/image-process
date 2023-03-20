# include <iostream>
# include <string>
# include <vector>
# include <fstream>
# include <sstream>
# include <math.h>
# include "projection.h"

using namespace std;

Image max_projection(Volume voxel) {
    Image res_img(voxel.files[0]);
    for (int m = 1; m < voxel.img_num; m++) {
        Image img(voxel.files[m]);
        for (int i = 0; i < res_img.height; i++) {
            for (int j = 0; j < res_img.width; j++) {
                for (int k = 0; k < res_img.channel; k++) {
                    double current_pixel = img.pixel[i][j][k];
                    if (current_pixel > res_img.pixel[i][j][k]) {
                        res_img.pixel[i][j][k] = current_pixel;
                    }
                }
            }
        }
    }
    return res_img;
}

Image min_projection(Volume voxel) {
    Image res_img(voxel.files[0]);
    for (int m = 1; m < voxel.img_num; m++) {
        Image img(voxel.files[m]);
        for (int i = 0; i < res_img.height; i++) {
            for (int j = 0; j < res_img.width; j++) {
                for (int k = 0; k < res_img.channel; k++) {
                    double current_pixel = img.pixel[i][j][k];
                    if (current_pixel < res_img.pixel[i][j][k]) {
                        res_img.pixel[i][j][k] = current_pixel;
                    }
                }
            }
        }
    }
    return res_img;
}

Image ave_projection(Volume voxel) {
    Image res_img(voxel.files[0]);
    for (int m = 1; m < voxel.img_num; m++) {
        Image img(voxel.files[m]);
        for (int i = 0; i < res_img.height; i++) {
            for (int j = 0; j < res_img.width; j++) {
                for (int k = 0; k < res_img.channel; k++) {
                    double current_pixel = img.pixel[i][j][k];
                    res_img.pixel[i][j][k] += current_pixel;
                    if(m == voxel.img_num - 1) {
                        res_img.pixel[i][j][k] /= voxel.img_num;
                    }
                }
            }
        }
    }
    return res_img;
}

Image Z_projection(Volume voxel) {
    cout << "Please enter your projection method:" << endl;
    cout << "1: max projection" << endl;
    cout << "2: min projection" << endl;
    cout << "3: average projection" << endl;
    int method;
    cin >> method;
    Image res_img(voxel.files[0]);
    for (int m = 1; m < voxel.img_num; m++) {
        Image img(voxel.files[m]);
        for (int i = 0; i < res_img.height; i++) {
            for (int j = 0; j < res_img.width; j++) {
                for (int k = 0; k < res_img.channel; k++) {
                    double current_pixel = img.pixel[i][j][k];
                    if (method == 1) {
                        if (current_pixel > res_img.pixel[i][j][k]) {
                            res_img.pixel[i][j][k] = current_pixel;
                        }
                    }
                    else if (method == 2) {
                        if (current_pixel < res_img.pixel[i][j][k]) {
                            res_img.pixel[i][j][k] = current_pixel;
                        }
                    }
                    else if (method == 3) {
                        res_img.pixel[i][j][k] += current_pixel;
                        if(m == voxel.img_num - 1) {
                            res_img.pixel[i][j][k] /= voxel.img_num;
                        }
                    }
                }
            }
        }
    }
    return res_img;
}
