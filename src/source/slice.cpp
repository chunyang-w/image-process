# include <string>
# include "helper.h"
# include "fastImage.h"
# include "volume.h"

using namespace std;

// slice volume form start-th(included) img to end-th(not included) img (index start from 0).
// then write the image to the path. (if not exist, create a specific path)
// axis = 0: slice the voxel along z axis, the image has shape (x,y)
// axis = 1: slice the voxel along y axis, the image has shape (x,z)
// axis = 2: slice the voxel along y axis, the image has shape (y,z)
Volume slice(Volume voxel, int start, int end, int axis, string path) {
    cout << "in slice" << endl;
    if (start >= end || voxel.img_num < 1)
        throw runtime_error("not sliceable");

    if (axis == 0) { // slicing along z-axis, looking from front to back
        bool sliceable = (end < voxel.img_num);
        if (!sliceable)
            throw runtime_error("Voxel not sliceable.");
        createFolder(path);
        for (int i = start; i < end; i++) {
            string path_to_write = path + num2string(i) + ".png";
            FImage(voxel.files[i]).write(path_to_write);
        }
    } else if (axis == 1) { // slicing along y axis, looking from top to bottom
        voxel.preload();
        createFolder(path);
        FImage example_img = voxel.data[0];
        int w = example_img.width; int c = example_img.channel;
        for (int n = start; n < end; n++) {
            FImage temp(voxel.img_num, w, c);
            for (int i = 0; i < voxel.img_num; i++) {
                for (int j = 0; j < w; j++) {
                    for (int k = 0; k < c; k++) {
                        int i_idx = voxel.img_num - i - 1;
                        temp.setPixel(i, j, k, voxel.data[i_idx].getPixel(n, j, k));
                    }
                }
            }
            string path_to_write = path + num2string(n) + ".png";
            temp.write(path_to_write);
        }
        voxel.unload();
    } else if (axis == 2) { // slicing along y axis, looking from left to right
        voxel.preload();
        createFolder(path);
        FImage example_img = voxel.data[0];
        int h = example_img.height; int c = example_img.channel; 
        for (int n = start; n < end; n++) {
            FImage temp(h, voxel.img_num, c);
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < voxel.img_num; j++) {
                    for (int k = 0; k < c; k++) {
                        int j_idx = voxel.img_num - j - 1;
                        temp.setPixel(i, j, k, voxel.data[j_idx].getPixel(i, n, k));
                    }
                }
            }
            string path_to_write = path + num2string(n) + ".png";
            temp.write(path_to_write);
        }
        voxel.unload();
    } else {
        throw runtime_error("invalid axis input");
    }
    return Volume(path);
}