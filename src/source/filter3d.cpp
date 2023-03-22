# include <iostream>
# include <string>
# include <vector>
# include <fstream>
# include <deque>
# include <cmath>
# include <sstream>
# include <math.h>
# include <algorithm>
# include <sys/stat.h>
# include <filesystem>
# include "volume.h"
# include "fastImage.h"
# include "filter3d.h"
# include "fastimage.h"

using namespace std;

Volume gaussian3d(Volume voxel, int kernel_size, string dest_path){
    int count = 1;
    double res = 0;
    int photo_num = 1;
    double kernel[kernel_size][kernel_size][kernel_size];
    int x, y, z;
    double sum_result = 0;
    int success = mkdir(dest_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    if (success != 0) {
        cout << "Creat path failed";
        throw runtime_error("not able to create path");
    }
    for(int i = 0; i < kernel_size; i++){
        for(int j = 0; j < kernel_size; j++){
            for(int k = 0; k < kernel_size; k++){
                x = i - (kernel_size-1)/2;
                y = j - (kernel_size-1)/2;
                z = k - (kernel_size-1)/2;
                kernel[i][j][k] = exp(-(x*x+y*y+z*z)/2)/(sqrt(2*3.1415926)*1);
                sum_result = sum_result + kernel[i][j][k];
            }
        }
    }
    for(int i = 0; i < kernel_size; i++){
        for(int j = 0; j < kernel_size; j++){
            for(int k = 0; k < kernel_size; k++){
                kernel[i][j][k] = kernel[i][j][k]/sum_result;
            }
        }
    }

    deque<FImage> buffer;
    for (int i = 0; i < kernel_size; i++) {
        FImage single_img(voxel.files[i]);
        buffer.push_back(single_img);
    }
    int padding = (kernel_size-1)/2;
    FImage res_img(voxel.files[0]);
    cout<< voxel.img_num << endl;
    for (int o = kernel_size-1; o < voxel.img_num; o++) {
        cout << o << endl;
        if(o != kernel_size-1){
        buffer.pop_front();
        FImage single_img(voxel.files[o]);
        buffer.push_back(single_img);
        }
        for (int i = padding; i < res_img.height-padding; i++) {
            for (int j = padding; j < res_img.width-padding; j++) {
                for (int k = 0; k < res_img.channel; k++) {
                    for(int m=0; m<kernel_size; m++){
                        for(int n=0; n<kernel_size; n++){
                            for(int p=0; p<kernel_size; p++){
                                res += kernel[m][n][p] * buffer[m].getPixel(i+n-padding, j+p-padding, k);
                            }
                        }
                    }
                    res_img.setPixel(i, j, k, res);
                    res = 0;
                }
            }
        }

        string path_to_write = dest_path + to_string(count) + ".png";
        count+=1;
        res_img.write(path_to_write);

        // photo_num +=1;
        // string path = root_path + to_string(photo_num) + ".png";
    }
    Volume res_voxel(dest_path);
    return res_voxel;
}


FImage getMedian(deque<FImage> &buffer, int kernel_size, int h, int w, int c) {
    int padding = (kernel_size - 1) / 2;
    FImage res(h-(padding*2), (w-padding*2), c);
    for (int i = 0; i < res.height; i++) {
        for (int j = 0; j < res.width; j++) {
            for (int k = 0; k < res.channel; k++) {
                vector<uint8_t> temp;
                for (int l = i; l < i+kernel_size; l++) {
                    for (int m = j; m < j+kernel_size; m++) {
                        for (int n = 0; n < buffer.size(); n++) {
                            temp.push_back(buffer[n].getPixel(l, m, k));
                        }
                    }
                }
                sort(temp.begin(), temp.end());
                res.setPixel(i, j, k, temp[temp.size()-1]);
            }
        }
    }
    return res;
}

// read voxel and return a voxel
Volume median3d(Volume voxel, int kernel_size, string dest_path) {
    // cout << "in gaussian3d" << endl;
    int count = 1;

    int success = mkdir(dest_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if (filesystem::exists(dest_path.c_str())) {
        cout << "Path exists" << endl;
    } 
    else {
        cout << "creating the path" << endl;
        if (success != 0) {
        cout << "Creat path failed";
        throw runtime_error("not able to create path");
        }
    }

    int h, w, c;
    int padding = (kernel_size - 1) / 2;
    if (voxel.img_num > 0) {
        FImage temp(voxel.files[0]);
        h = temp.height; w = temp.width; c = temp.channel;
    } else {
        cout << "This Volume do not contain any images" << endl;
        return voxel;
    }
    deque<FImage> buffer;
    for (int i = 0; i < kernel_size; i++) {
        buffer.push_back(FImage(voxel.files[i]));
    }
    for (int i = padding; i < voxel.img_num-padding; i++) {
        FImage img = getMedian(buffer, kernel_size, h, w, c);
        if (i != voxel.img_num - padding) {
            buffer.pop_front();
            buffer.push_back(voxel.files[i + padding]);
        }
        // cout << "done" << endl;
        // write image
        string path_to_write = dest_path + to_string(count) + ".png";
        count+=1;
        img.write(path_to_write);
    }
    Volume res_voxel(dest_path);
    return res_voxel;
}