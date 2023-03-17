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