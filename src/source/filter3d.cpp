# include <iostream>
# include <string>
# include <vector>
# include <fstream>
# include <deque>
# include <sstream>
# include <math.h>
# include "filter3d.h"
# include "fastimage.h"
# include <cmath>
# include <map>


using namespace std;
// double generate(int kernel_size, int &kernel){
//     // double res[kernel_size][kernel_size][kernel_size];
//     // vector<vector<vector<double>>> res;

//     int x, y, z;
//     for(int i = 0; i < kernel_size; i++){
//         for(int j = 0; j < kernel_size; j++){
//             for(int k = 0; k < kernel_size; k++){
//                 x = i - (kernel_size-1)/2;
//                 y = j - (kernel_size-1)/2;
//                 z = k - (kernel_size-1)/2;
//                 res[i][j][k] = exp(-(x*x+y*y+z*z)/(2*1*1))/(sqrt(2*3.1415926)*1);
//             }
//         }
//     }
//     return res;
// }


// double kernel[3][3][3] = {
//     {{0.0206, 0.0339, 0.0206}, {0.0339, 0.0560, 0.0339}, {0.0206, 0.0339, 0.0206}},
//     {{0.0339, 0.0560, 0.0339}, {0.0560, 0.0924, 0.0560}, {0.0339, 0.0560, 0.0339}},
//     {{0.0206, 0.0339, 0.0206}, {0.0339, 0.0560, 0.0339}, {0.0206, 0.0339, 0.0206}}
// };
FImage filter_3d(Volume voxel){
    int kernel_size = 5;
    double res = 0;
    int photo_num = 1;
    double kernel[kernel_size][kernel_size][kernel_size];
    int x, y, z;
    double sum_result = 0;
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

    string root_path = "../filter3d_result/result_num";
    deque<FImage> buffer;
    for (int i = 0; i < kernel_size; i++) {
        FImage single_img(voxel.files[i]);
        buffer.push_back(single_img);
    }
    int padding = (kernel_size-1)/2;
    FImage res_img(voxel.files[0]);
    // int w = res_img.width; int h = res_img.height; int c = res_img.channel;
    for (int m = padding; m < voxel.img_num - padding; m++) {
        buffer.pop_front();
        FImage single_img(voxel.files[m]);
        buffer.push_back(single_img);
        // for (int i = m - padding; i < m + padding; i++) {
        //     read_figure.erase();
        //     read_figure.push_back(FImage(voxel.files[i]));
        // }
        // FImage left(voxel.files[m-1]);
        // FImage middle(voxel.files[m]);
        // FImage right(voxel.files[m+1]);
        for (int i = padding; i < res_img.height-padding; i++) {
            for (int j = padding; j < res_img.width-padding; j++) {
                for (int k = 0; k < res_img.channel; k++) {
                    for(int m=0; m<kernel_size; m++){
                        for(int n=0; n<kernel_size; n++){
                            for(int p=0; p<kernel_size; p++){
                                res += kernel[m][n][p] * buffer[m].getPixel(i+n-padding, j+p-padding, k);
                                // if (m == 0){
                                //     res += kernel[m][n][p] * left.getPixel(i+n-padding, j+p-padding, k);
                                // }
                                // else if (m == 1){
                                //     res += kernel[m][n][p] * middle.getPixel(i+n-padding, j+p-padding, k);
                                // }
                                // else if (m == 2){
                                //      res += kernel[m][n][p] * right.getPixel(i+n-padding, j+p-padding, k);
                                // }
                            }
                        }
                    }
                    res_img.setPixel(i, j, k, res);
                    res = 0;
                }
            }
        }
        photo_num +=1;
        string path = root_path + to_string(photo_num) + ".png";
        res_img.write(path);
    }
}
