# include <iostream>
# include "filter.h"

using namespace std;

Image Filter::grayScale(Image img) {
    // img.printSize();
    int max_channel;
    if (img.channel >=3) {
        max_channel = 3;
    } else {
        max_channel = img.channel;
    }
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
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

Image Filter::colorBalance(Image img) {
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
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
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
    cout << avg_intensity << endl;
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            int sum = 0;
            for (int k = 0; k < max_channel; k++) {
                int diff = (avg_intensity - channel_avg[k]) / num_pixel;
                img.pixel[i][j][k] = img.pixel[i][j][k] + diff;
            }
        }
    }

    return img;
}

Image Filter::boxBlur(Image img) {
    return img;
}

Image Filter::gaussianBlur(Image img) {
    return img;
}