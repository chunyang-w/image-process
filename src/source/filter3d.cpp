# include <deque>
# include <string>
# include <iostream>
# include <algorithm>
# include "volume.h"
# include "fastImage.h"
# include "filter3d.h"

using namespace std;

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

Volume median3d(Volume voxel, int kernel_size) {
    cout << "in gaussian3d" << endl;
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
        string path_to_write = "../Output/con" + to_string(i) + ".png";
        img.write(path_to_write);
    }
    return voxel;
}

// Volume median3d(Volume voxel, int kernel_size) {
//     cout << "in gaussian3d" << endl;
//     int h, w, c;
//     int padding = (kernel_size - 1) / 2;
//     if (voxel.img_num > 0) {
//         FImage temp(voxel.files[0]);
//         h = temp.height; w = temp.width; c = temp.channel;
//     } else {
//         cout << "This Volume do not contain any images" << endl;
//         return voxel;
//     }
//     voxel.preload();
//     cout << "preload complete" << endl;

//     for (int x = padding; x < voxel.img_num - padding; x++) {
//         FImage res(h-(padding*2), (w-padding*2), c);
//         for (int i = 0; i < res.height; i++) {
//             for (int j = 0; j < res.width; j++) {
//                 for (int k = 0; k < res.channel; k++) {
//                     vector<uint8_t> temp;
//                     for (int l = i; l < i+kernel_size; l++) {
//                         for (int m = j; m < j+kernel_size; m++) {
//                             for (int n = x-padding; n <= x+padding; n++) {
//                                 temp.push_back(voxel.data[n].getPixel(l, m, k));
//                             }
//                         }
//                     }
//                     sort(temp.begin(), temp.end());
//                     res.setPixel(i, j, k, temp[temp.size()-1]);
//                 }
//             }
//         }
//         cout << "Fimage constructed" << endl;
//     }

//     voxel.unload();
//     return voxel;
// }