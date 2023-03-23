/* Group: Monte Carlo
Members: Zepeng Chen    | acse-zc522
         Ruichen Ding   | acse-rd422
         Georgie Mercer | edsml-gm1722
         Chunyang Wang  | acse-cw17222
         Lizzie Withers | edsml-lcw22
*/

# include <string>
# include "helper.h"
# include "fastImage.h"
# include "volume.h"

using namespace std;

/**
@brief Extract a slice from a 3D volume and save it as a set of image files.
The `slice` function extracts a slice from a 3D volume along a specified axis and saves
it as a set of image files in the specified directory. The slice is defined by a start
index (inclusive) and an end index (exclusive) along the specified axis. The function
returns a `Volume` object that represents the saved images.
@param voxel The `Volume` object to extract the slice from.
@param start The index of the first voxel along the specified axis to include in the slice.
@param end The index of the first voxel along the specified axis to exclude from the slice.
@param axis The axis along which to extract the slice. 0 for z-axis, 1 for y-axis, or 2 for x-axis.
@param path The directory path to save the slice images in. The directory will be created if it does not exist.
@return A `Volume` object that represents the saved images.
@throws std::runtime_error If the `voxel` is not sliceable along the specified axis or the `axis` input is invalid.
 */
Volume slice(Volume voxel, int start, int end, int axis, string path) {
    cout << "in slice" << endl;
    if (start >= end || voxel.img_num < 1)
        throw runtime_error("not sliceable");

    if (axis == 0) { // Slicing along z-axis, looking from front to back
        bool sliceable = (end < voxel.img_num);
        if (!sliceable)
            throw runtime_error("Voxel not sliceable.");
        createFolder(path);
        for (int i = start; i < end; i++) {
            string path_to_write = path + num2string(i) + ".png";
            FImage(voxel.files[i]).write(path_to_write);
        }
    } else if (axis == 1) { // Slicing along y axis, looking from top to bottom
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
    } else if (axis == 2) { // Slicing along x axis, looking from left to right
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