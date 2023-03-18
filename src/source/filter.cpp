# include <iostream>
# include <string>
# include <vector>
# include <fstream>
# include <sstream>
# include <math.h>
# include "filter.h"

using namespace std;

Filter::Filter(string path) {
    fstream f;
    f.open(path);
    string line;
    while(getline(f, line)) {
        vector<double> temp;
        double num;
        stringstream stream(line);
        while(stream >> num) {
            temp.push_back(num);
        }
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
                        sum += (double)(pad_img.pixel[m+this->padding_size][n+this->padding_size][k]);
                    }
                }
                res = sum / (this->kernel_size * this->kernel_size);
                res_img.pixel[i][j][k] = (uint8_t) res;
            }
        }
    }
    return res_img;
}

Image grayScale(Image img) {
    cout << "in gray" << endl;
    // img.printSize();
    int max_channel;
    if (img.channel >=3) {
        max_channel = 3;
    } else {
        max_channel = img.channel;
    }
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
    img.channel = 1;
    // img.printSize();
    return img;
}

Image colorBalance(Image img) {
    // img.printSize();
    int max_channel;
    int avg_intensity = 0;
    int num_pixel = img.width * img.height;
    if (img.channel >=3) {
        max_channel = 3;
    } else {
        max_channel = img.channel;
    }
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
    for (int i = 0; i < max_channel; i++) {
        avg_intensity += channel_avg[i];
    }
    avg_intensity = avg_intensity / 3;
    for (int i = 0; i < img.height; i++) {
        for (int j = 0; j < img.width; j++) {
            int sum = 0;
            for (int k = 0; k < max_channel; k++) {
                int diff = (avg_intensity - channel_avg[k]) / num_pixel;
                img.pixel[i][j][k] = img.pixel[i][j][k] + diff;
            }
        }
    }

    return img;
}

Image boxBlur(Image img) {
    return img;
}

Image gaussianBlur(Image img) {
    return img;
}
