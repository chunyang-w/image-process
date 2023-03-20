# include <iostream>
# include <algorithm>
# include <string>
# include <vector>
# include <fstream>
# include <sstream>
# include <math.h>
# include "filter.h"

using namespace std;

// define path to sobel x, y filters
string sobelx_path = "./filter/sobelx.txt";
string sobely_path = "./filter/sobely.txt";
// define path to prewitt x, y filters
string prewittx_path = "./filter/prewittx.txt";
string prewitty_path = "./filter/prewitty.txt";

Filter::Filter(string path) {
    fstream f;
    f.open(path);
    string line;
    // cout << "using kernel" << endl;
    while(getline(f, line)) {
        vector<double> temp;
        double num;
        stringstream stream(line);
        while(stream >> num) {
            temp.push_back(num);
            // cout << num << " ";
        }
        // cout << endl;
        this->kernel.push_back(temp);
    }
    this->kernel_size = this->kernel.size();
    this->padding_size = floor(this->kernel_size / 2);
}

Image Filter::apply(Image img) {
    Image pad_img = img.pad(this->padding_size);
    Image res_img(img);
    for (int i = 0; i < res_img.height; i++) {
        for (int j = 0; j < res_img.width; j++) {
            for (int k = 0; k < res_img.channel; k++) {
                double sum = 0;
                int res;
                for (int m = i-this->padding_size; m <= i+this->padding_size; m++) {
                    for (int n = j-this->padding_size; n <= j+this->padding_size; n++) {
                        int r = m - i + this->padding_size;
                        int s = n - j + this->padding_size;
                        double current_pixel = pad_img.pixel[m+this->padding_size][n+this->padding_size][k];
                        double current_coeff = this->kernel[r][s];
                        sum += current_pixel * current_coeff;
                    }
                }
                // res = sum / (this->kernel_size * this->kernel_size);
                // res = sum;
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

Image colorBalance(Image img) {

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
        int diff = (128 - channel_avg[k]) / num_pixel;
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

Image sobel(Image img) {
    Filter sobelx(sobelx_path.c_str());
    Filter sobely(sobely_path.c_str());

    Image x = sobelx.apply(img);
    Image y = sobelx.apply(img);

    Image res(img);

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

Image prewitt(Image img) {
    Filter prewittx(prewittx_path.c_str());
    Filter prewitty(prewitty_path.c_str());

    Image x = prewittx.apply(img);
    Image y = prewitty.apply(img);

    Image res(img);

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
