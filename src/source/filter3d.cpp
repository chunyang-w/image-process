# include <iostream>
# include <string>
# include <vector>
# include <fstream>
# include <deque>
# include <cmath>
# include <sstream>
# include <math.h>
# include <sys/stat.h>
# include "helper.h"
# include "volume.h"
# include "fastImage.h"
# include "filter3d.h"
# include "fastImage.h"


using namespace std;

/**
@brief Gaussian filter for 3D images dataset.
This function is used to filter 3D images dataset with Gaussian filter, via the following steps:
1. Check and create the destination path which is used to store all of the output images
2. Calculate the kernel for gaussian filter according to the input kernel size
3. Convolve this kernal with the images from the 3D images dataset.
@param Volume The filepaths of the input images.
@param int The size of the kernel.
@param string The path of the destination folder.
@return The final images path after filtering (it will also write all of the images into the destination folder.)
*/
Volume gaussian3d(Volume voxel, int kernel_size, string dest_path){

    int count = 1;
    double res = 0;
    int photo_num = 1;
    double kernel[kernel_size][kernel_size][kernel_size];
    double x, y, z;
    double sum_result = 0;
    int padding = (kernel_size - 1) / 2;
    int success = mkdir(dest_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    // Check and create the destination path
    struct stat sb;
    if (stat(dest_path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode)) {
        cout << "Path exists" << std::endl;
    } 
    else {
        cout << "creating the path" << std::endl;
        if (success != 0) {
        cout << "Creat path failed";
        throw runtime_error("not able to create path");
        }
    }

    // Calculate the kernel
    for(int i = 0; i < kernel_size; i++){
        for(int j = 0; j < kernel_size; j++){
            for(int k = 0; k < kernel_size; k++){
                x = i - (kernel_size-padding)/2;
                y = j - (kernel_size-padding)/2;
                z = k - (kernel_size-padding)/2;
                kernel[i][j][k] = exp(-(x*x+y*y+z*z)/2)/(pow((2*3.1415926), 3/2));
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

    // Filter all of the images
    deque<FImage> buffer;

    // The buffer size is equal to the kernel size
    for (int i = 0; i < kernel_size; i++) {
        FImage single_img(voxel.files[i]);
        buffer.push_back(single_img);
    }
    FImage res_img(voxel.files[0]);
    cout<< voxel.img_num << endl;
    for (int o = kernel_size-1; o < voxel.img_num; o++) {
        // For each loop, we need to pop the first image and push the next image
        cout << "Processing Image Number: "<< o << endl;
        if(o != kernel_size-1){
        buffer.pop_front();
        FImage single_img(voxel.files[o]);
        buffer.push_back(single_img);
        }
        // Process all of the images in the buffer with the kernel
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

        // Write the image into the destination path
        string num_output = to_string(count);
        string eight_bit = "";
        for (int i = 0; i < 8 - num_output.length(); i++) {
            eight_bit += "0";
        }
        eight_bit = eight_bit + num_output;
        string path_to_write = dest_path + eight_bit + ".png";
        count+=1;
        res_img.write(path_to_write);
    }
    Volume res_voxel(dest_path);
    return res_voxel;
}


/**
@brief Returns a median filtered image using the deque buffer
This function calculates the median pixel value for each pixel of the output image
using the pixels in the kernel_size x kernel_size x buffer.size() neighborhood of the input image.
The buffer is a deque of FImages containing the most recent images in the stream.
Padding is added to the input image to ensure that the output image is of the same size as the input.
The quickSort algorithm is used to find the median pixel value.
The output image is returned as an FImage object.
@param buffer Deque of FImages to use for median filtering
@param kernel_size Size of the kernel for median filtering
@param h Height of the output image
@param w Width of the output image
@param c Number of channels of the output image
@return FImage The median filtered output image
*/
FImage getMedian(deque<FImage> &buffer, int kernel_size, int h, int w, int c) {
    int padding = (kernel_size - 1) / 2;
    FImage res(h-(padding*2), (w-padding*2), c);
    for (int i = 0; i < res.height; i++) {
        for (int j = 0; j < res.width; j++) {
            for (int k = 0; k < res.channel; k++) {
                int count = 0;
                int size = kernel_size*kernel_size*kernel_size;
                uint8_t temp[size];
                for (int l = i; l < i+kernel_size; l++) {
                    for (int m = j; m < j+kernel_size; m++) {
                        for (int n = 0; n < buffer.size(); n++) {
                            temp[count] = buffer[n].getPixel(l, m, k);
                            count++;
                        }
                    }
                }
                quickSort(temp, 0, size-1);
                int mid = size / 2;

                res.setPixel(i, j, k, temp[mid]);
            }
        }
    }
    return res;
}

/**
@brief Compute the median blur of a 3D volume.
The median filter is applied to each slice of the 3D volume independently, and the filtered images
are stored in the directory specified by dest_path. The size of the filter kernel should be odd.
If the Volume object does not contain any images, the function will return the original Volume object.
If the destination path does not exist, the function will create the directory.
@param voxel: a Volume object representing the 3D volume to be filtered.
@param kernel_size: an integer representing the size of the filter kernel to be applied.
@param dest_path: a string representing the path of the directory to store the filtered images.
@return a Volume object representing the filtered 3D volume.
*/
Volume median3d(Volume voxel, int kernel_size, string dest_path) {
    int count = 1;

    int success = mkdir(dest_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    struct stat sb;
    if (stat(dest_path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode)) {
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
        string path_to_write = dest_path + num2string(count) + ".png";
        count+=1;
        img.write(path_to_write);
    }
    Volume res_voxel(dest_path);
    return res_voxel;
}