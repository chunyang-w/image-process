#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "image.h"

using namespace std;

Image::Image(string path) {
    cout << "constructor called" << endl;
    int w, h, c;
    unsigned char* img;
    // Read in image file
    img = stbi_load(path.c_str(), &w, &h, &c, 0);
    if (img != NULL) {
        cout << "Image loaded with size " << w << " x " << h << " with " << c << " channel(s)." << std::endl; 
    } else {
        throw runtime_error("open file failed");
    }
    // set width, height and channel number
    this->width = w; this->height = h; this->channel = c;
    // init 3-D vector pixel
    pixel.resize(w);
    for (int i = 0; i < w; i++) {
        pixel[i].resize(h);
    }
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            pixel[i][j].resize(c);
        }
    }
    // construct 3-D vector pixel:
    unsigned char* pix = img;
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            for (int k = 0; k < c; k++) {
                pixel[i][j][k] = *pix;
                pix ++;
            }
        }
    }
    // free memory
    stbi_image_free(img);
}

Image::~Image() {
    cout << "deconstructor called" << endl;
}

void Image::write(string path) {
    unsigned char *img = new unsigned char[this->width * this->height * this->channel];
    unsigned char* pix = img;
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            for (int k = 0; k < this->channel; k++) {
                *pix = pixel[i][j][k];
                pix ++;
            }
        }
    }
    int success = stbi_write_png(path.c_str(), this->width, this->height, this->channel, img, 0);
    if (success == 0) {
        throw runtime_error("writing image failed");
    } else {
        cout << "writing success" << endl;
    }
    delete[] img;
}

void Image::printSize() {
    cout << "Image size (w, h, c): (" << this->width << ", " << this->height << ", " << this->channel << ")" << endl;
}