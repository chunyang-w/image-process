# include <iostream>
# include <string>
# include <vector>
# include <fstream>
# include <sstream>
# include <math.h>
# include <cmath>
# include "filter.h"

using namespace std;


// Function to find the median of a vector
template<typename T>
T median(vector<T>& vec) {
    int size = vec.size();
    int middle = size / 2;
    
    // Sort the vector
    for (int i = 0; i <= middle; i++) {
        for (int j = i + 1; j < size; j++) {
            if (vec[j] < vec[i]) {
                swap(vec[i], vec[j]);
            }
        }
    }
    // Return median
    return vec[middle];
}

// To initialise gaussian operator
Filter::Filter(int kernel_size) {
    double sigma = 1.0;
    double sum = 0.0;

    for (int i = -kernel_size/2; i <= kernel_size/2; i++) {
        vector<double> temp;
        for (int j = -kernel_size/2; j <= kernel_size/2; j++) {
            double val = exp(-(i*i + j*j) / (2 * sigma*sigma));
            temp.push_back(val);
            sum += val;
        }
        this->kernel.push_back(temp);
    }
    // Normalize the kernel
    for (int i = 0; i < kernel_size; i++) {
        for (int j = 0; j < kernel_size; j++) {
            this->kernel[i][j] /= sum;
        }
    }  
    this->kernel_size = this->kernel.size();
    this->padding_size = floor((this->kernel_size) / 2); 
}

// To initialise edge detection operators
Filter::Filter(char* optr) {

    if (optr == "prewittx") {
        this->kernel = {
            {1, 0, -1},
            {1, 0, -1},
            {1, 0, -1}
        };
    } else if (optr == "prewitty") {
        this->kernel = {
            {1, 1, 1},
            {0, 0, 0},
            {-1, -1, -1}
        };
    } else if (optr == "scharrx") {
        this->kernel = {
            {3, 0, -3},
            {10, 0, -10},
            {3, 0, -3}
        };
    } else if (optr == "scharry") {
        this->kernel = {
            {3, 10, 3},
            {0, 0, 0},
            {-3, -10, -3}
        };
    } else if (optr == "sobelx") {
        this->kernel = {
            {1, 0, -1},
            {12, 0, -2},
            {1, 0, -1}
        };
    } else if (optr == "sobely") {
        this->kernel = {
            {1, 2, 1},
            {0, 0, 0},
            {-1, -2, -1}
        };
    } else if (optr == "robertscrossx") {
        this->kernel = {
            {1, 0},
            {0, -1}
        };
    } else if (optr == "robertscrossy") {
        this->kernel = {
            {0, 1},
            {-1, 0}
        };
    }
    this->kernel_size = this->kernel.size();
    this->padding_size = floor((this->kernel_size) / 2);
}


Image Filter::apply(Image img) {

    // Pad image to allow convolution at edges
    Image pad_img = img.pad(this->padding_size);
    Image res_img(img);

    // Loop through pixels in each channel
    for (int i = 0; i < res_img.height; i++) {
        for (int j = 0; j < res_img.width; j++) {
            for (int k = 0; k < res_img.channel; k++) {

                double sum = 0;
                int res;
                int increment;

                // Ensure convolution works for both odd and even sized operators
                if (this->kernel.size()%2 == 0) {
                    increment = this->padding_size - 1;}
                else {increment = this->padding_size;}

                // Calculate new value for each pixel based on the values of its neighbours
                for (int m = i-this->padding_size; m <= i+increment; m++) {
                    for (int n = j-this->padding_size; n <= j+increment; n++) {
                        int r = m - i + this->padding_size;
                        int s = n - j + this->padding_size;
                        double current_pixel = pad_img.pixel[m+this->padding_size][n+this->padding_size][k];
                        double current_coeff = this->kernel[r][s];
                        sum += current_pixel * current_coeff;
                    }
                }
                res_img.pixel[i][j][k] = (uint8_t) sum;
            }
        }
    }
    return res_img;
}

Image grayScale(Image img) {

    // Determine size of for loops
    int max_channel;
    if (img.channel >=3) {
        max_channel = 3;
    } else {
        max_channel = img.channel;
    }

    // Calculate average of each pixel across channels
    for (int i = 0; i < img.height; i++) {
        for (int j = 0; j < img.width; j++) {
            int sum = 0;
            for (int k = 0; k < max_channel; k++) {
                sum += int(img.pixel[i][j][k]);
            }
            img.pixel[i][j][0] = sum / max_channel;
            img.pixel[i][j].resize(1);
        }
    }

    // Output is only one channel
    img.channel = 1;

    return img;
}

Image colourBalance(Image img) {

    // Determine size of for loops
    int max_channel;
    int avg_intensity = 0;
    int num_pixel = img.width * img.height;
    if (img.channel >=3) {
        max_channel = 3;
    } else {
        max_channel = img.channel;
    }

    // Find average intensity of each channel
    vector<int> channel_avg;
    channel_avg.resize(max_channel);
    for (int i = 0; i < img.height; i++) {
        for (int j = 0; j < img.width; j++) {
            int sum = 0;
            for (int k = 0; k < max_channel; k++) {
                channel_avg[k] += int(img.pixel[i][j][k]);
            }
        }
    }

    // Find average intensity of all channels
    for (int i = 0; i < max_channel; i++) {
        avg_intensity += channel_avg[i];
    }
    avg_intensity = avg_intensity / 3;

    // Adjust each pixel by the difference between the channel's average and overall average
    for (int k = 0; k < max_channel; k++) {
        int diff = (avg_intensity - channel_avg[k]) / num_pixel;
        for (int i = 0; i < img.height; i++) {
            for (int j = 0; j < img.width; j++) {
                int sum = 0;

                // If statements to ensure no overflow if new value would be outside the 0-255 range
                if (int(img.pixel[i][j][k]) < 0-diff) {
                    img.pixel[i][j][k] = 0;}
                else if (int(img.pixel[i][j][k]) > 255-diff) {
                    img.pixel[i][j][k] = 255;}
                else {img.pixel[i][j][k] = img.pixel[i][j][k] + diff;}
            }
        }
    }
    return img;
}

Image Brightness(Image img) {

    // Determine size of for loops
    int max_channel;
    int num_pixel = img.width * img.height;
    if (img.channel >=3) {
        max_channel = 3;
    } else {
        max_channel = img.channel;
    }

    // Find average intensity of each channel
    vector<int> channel_avg;
    channel_avg.resize(max_channel);
    for (int i = 0; i < img.height; i++) {
        for (int j = 0; j < img.width; j++) {
            int sum = 0;
            for (int k = 0; k < max_channel; k++) {
                channel_avg[k] += int(img.pixel[i][j][k]);
            }
        }
    }

    // Adjust each pixel by the difference between the default value (128) and the channel's average 
    for (int k = 0; k < max_channel; k++) {
        int diff = 128 - (channel_avg[k]/num_pixel);
        for (int i = 0; i < img.height; i++) {
            for (int j = 0; j < img.width; j++) {
                int sum = 0;
                if (int(img.pixel[i][j][k]) < 0-diff) {
                    img.pixel[i][j][k] = 0;}
                else if (int(img.pixel[i][j][k]) > 255-diff) {
                    img.pixel[i][j][k] = 255;}
                else {img.pixel[i][j][k] = img.pixel[i][j][k] + diff;}
            }
        }
    }
    return img;
}

Image Brightness(Image img, int brightness) {

    // Determine size of for loops
    int max_channel;
    int num_pixel = img.width * img.height;
    if (img.channel >=3) {
        max_channel = 3;
    } else {
        max_channel = img.channel;
    }

    // Adjust each pixel by the value specified
    for (int k = 0; k < max_channel; k++) {
        for (int i = 0; i < img.height; i++) {
            for (int j = 0; j < img.width; j++) {
                int sum = 0;
                if (int(img.pixel[i][j][k]) < 0-brightness) {
                    img.pixel[i][j][k] = 0;}
                else if (int(img.pixel[i][j][k]) > 255-brightness) {
                    img.pixel[i][j][k] = 255;}
                else {img.pixel[i][j][k] = img.pixel[i][j][k] + brightness;}
            }
        }
    }
    return img;
}

Image imageBlur(Image img, int method, int kernel_size) {

    // Check if we need to look up gaussian operator
    if (method == 3) {

        // Convolve gaussian operator with image
        Filter gaussian(kernel_size);
        Image res_img = gaussian.apply(img);

        return res_img;}

    else {

        // Pad image to allow calculation at edges
        int padding_size = floor((kernel_size) / 2);
        Image pad_img = img.pad(padding_size);
        Image res_img(img);

        // Loop through pixels in each channel
        for (int i = 0; i < res_img.height; i++) {
            for (int j = 0; j < res_img.width; j++) {
                for (int k = 0; k < res_img.channel; k++) {

                    vector<int> values;
                    int sum = 0;
            
                    // Fill in vector containing values of the pixels in the kernel
                    for (int m = i-padding_size; m <= i+padding_size; m++) {
                        for (int n = j-padding_size; n <= j+padding_size; n++) {
                            values.push_back(pad_img.pixel[m+padding_size][n+padding_size][k]);
                            sum += pad_img.pixel[m+padding_size][n+padding_size][k];
                        }
                    }

                    // Take median or mean depending on method specified
                    if (method == 1) {
                        res_img.pixel[i][j][k] = median(values);}
                    else if (method == 2) {
                        res_img.pixel[i][j][k] = sum/(kernel_size*kernel_size);
                    }
                }
            }
        }
        return res_img;
    }
}

Image edgeDetection(Image img, int method) {

    // Convert image to grayscale before any edge detection
    img = grayScale(img);

    char* optr_x;
    char* optr_y;
    
    // Choose operator
    if (method == 1) {
        optr_x = "sobelx";
        optr_y = "sobely";
    }
    else if (method == 2) {
        optr_x = "prewittx";
        optr_y = "prewitty";
    }
    else if (method == 3) {
        optr_x = "scharrx";
        optr_y = "scharry";
    } 
    else if (method == 4) {
        optr_x = "robertscrossx";
        optr_y = "robertscrossy";
    } 

    // Convolve image with operator
    Filter edge_x(optr_x);
    Filter edge_y(optr_y);

    Image x = edge_x.apply(img);
    Image y = edge_y.apply(img);

    Image res(img);

    // Combine results of x and y operators
    for (int i = 0; i < res.height; i++) {
        for (int j = 0; j < res.width; j++) {
            for (int k = 0; k < res.channel; k++) {
                int x_pix = x.pixel[i][j][k];
                int y_pix = y.pixel[i][j][k];
                res.pixel[i][j][k] = sqrt(pow(x_pix, 2) + pow(y_pix, 2));
            }
        }
    } 
    return res;
}

 // Histogram equalization filter for colour images
Image histogramEqualisation(Image img) {
    Image res(img);

    for (int c = 0; c < img.channel; c++) {
        // Compute histogram of current channel
        vector<int> hist(256, 0);
        for (int i = 0; i < img.height; i++) {
            for (int j = 0; j < img.width; j++) {
                hist[img.pixel[i][j][c]]++;
            }
        }

        // Compute cumulative distribution function (CDF)
        vector<int> cdf(256, 0);
        cdf[0] = hist[0];
        for (int i = 1; i < 256; i++) {
            cdf[i] = cdf[i-1] + hist[i];
        }

        // Compute normalized CDF
        vector<double> norm_cdf(256, 0);
        int total_pixels = img.height * img.width;
        for (int i = 0; i < 256; i++) {
            norm_cdf[i] = (double) cdf[i] / total_pixels;
        }

        // Create lookup table for mapping pixel values
        vector<int> lookup(256, 0);
        for (int i = 0; i < 256; i++) {
            lookup[i] = round(norm_cdf[i] * 255);
        }

        // Apply lookup table to current channel
        for (int i = 0; i < res.height; i++) {
            for (int j = 0; j < res.width; j++) {
                res.pixel[i][j][c] = lookup[img.pixel[i][j][c]];
            }
        }
    }

    return res;
}

