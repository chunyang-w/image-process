# include <iostream>
# include <string>
# include <vector>
# include <fstream>
# include <sstream>
# include <math.h>
# include "projection.h"
# include "fastimage.h"

using namespace std;

FImage max_projection(Volume voxel) {
    FImage res_img(voxel.files[0]);
    for (int m = 1; m < voxel.img_num; m++) {
        FImage img(voxel.files[m]);
        for (int i = 0; i < res_img.height; i++) {
            for (int j = 0; j < res_img.width; j++) {
                for (int k = 0; k < res_img.channel; k++) {
                    // double current_pixel = img.pixel[i][j][k];
                    double current_pixel = img.getPixel(i, j, k);
                    if (current_pixel > res_img.getPixel(i, j, k)) {
                        // res_img.pixel[i][j][k] = current_pixel;
                        res_img.setPixel(i, j, k, current_pixel);
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

FImage Z_projection(Volume voxel) {
    cout << "Please enter your projection method:" << endl;
    cout << "1: max projection" << endl;
    cout << "2: min projection" << endl;
    cout << "3: average projection" << endl;
    int method;
    cin >> method;
    FImage res_img(voxel.files[0]);
    for (int m = 1; m < voxel.img_num; m++) {
        FImage img(voxel.files[m]);
        for (int i = 0; i < res_img.height; i++) {
            for (int j = 0; j < res_img.width; j++) {
                for (int k = 0; k < res_img.channel; k++) {
                    double current_pixel = img.getPixel(i, j, k);
                    if (method == 1) {
                        if (current_pixel > res_img.getPixel(i, j, k)) {
                            res_img.setPixel(i, j, k, current_pixel);
                        }
                    }
                    else if (method == 2) {
                        if (current_pixel < res_img.getPixel(i, j, k)) {
                            res_img.setPixel(i, j, k, current_pixel);
                        }
                    }
                    else if (method == 3) {
                        res_img.setPixel(i, j, k, res_img.getPixel(i, j, k) + current_pixel);
                        if(m == voxel.img_num - 1) {
                            res_img.setPixel(i, j, k, res_img.getPixel(i, j, k) / voxel.img_num);
                        }
                    }
                }
            }
        }
    }
    return res_img;
}

FImage X_projection(Volume voxel) {
    FImage example_img(voxel.files[0]);
    FImage res_img(example_img.height, voxel.img_num, example_img.channel);
    for (int m = 1; m < voxel.img_num; m++) {
        FImage img(voxel.files[m]);
        for (int i = 0; i < res_img.height; i++) {
            for (int j = 0; j < res_img.width; j++) {
                for (int k = 0; k < res_img.channel; k++) {
                    double current_pixel = img.getPixel(i, j, k);
                    if (current_pixel > res_img.getPixel(i, m, k)) {
                        res_img.setPixel(i, m, k, current_pixel);
                    }
                }
            }
        }
    }
    return res_img;
}


FImage choose_projection(Volume voxel) {
    cout << "Please enter your projection method:" << endl;
    cout << "1: max projection" << endl;
    cout << "2: min projection" << endl;
    cout << "3: average projection" << endl;
    int method;
    cin >> method;
    cout << "Please enter your final projection plane:" << endl;
    cout << "1: XY plane" << endl;
    cout << "2: XZ plane" << endl;
    cout << "3: YZ plane" << endl;
    int plane;
    cin >> plane;
    int length;
    vector<vector<vector<int>>> init_pixel;
    FImage example_img(voxel.files[0]);
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
    for (int m = 1; m < voxel.img_num; m++) {
        FImage img(voxel.files[m]);
        for (int i = 0; i < res_img.height; i++) {
            for (int j = 0; j < res_img.width; j++) {
                for (int k = 0; k < res_img.channel; k++) {
                    double current_pixel = img.getPixel(i, j, k);
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
                    if (method == 1) {
                        if (current_pixel > res_img.getPixel(w, h, c)) {
                            res_img.setPixel(w, h, c, current_pixel);
                        }
                    }
                    else if (method == 2) {
                        if (current_pixel < res_img.getPixel(w, h, c)) {
                            res_img.setPixel(w, h, c, current_pixel);
                        }
                    }
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