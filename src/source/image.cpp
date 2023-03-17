#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "image.h"

using namespace std;

Image::Image(string path) {
    // cout << "constructor called" << endl;
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

// copy constructor
Image::Image(const Image & old_obj): width(old_obj.width), height(old_obj.height), channel(old_obj.channel)
{
    // cout << "copy constructor called" << endl;
    vector<std::vector<std::vector<unsigned char>>> p;
    p.resize(old_obj.width);
    for (int i = 0; i < old_obj.width; i++) {
        p[i].resize(old_obj.height);
    }
    for (int i = 0; i < old_obj.width; i++) {
        for (int j = 0; j < old_obj.height; j++) {
            p[i][j].resize(old_obj.channel);
        }
    }
    // construct 3-D vector pixel:
    for (int i = 0; i < old_obj.width; i++) {
        for (int j = 0; j < old_obj.height; j++) {
            for (int k = 0; k < old_obj.channel; k++) {
                p[i][j][k] = old_obj.pixel[i][j][k];
            }
        }
    }
    this->pixel = p;
}

Image::~Image() {
    // cout << "deconstructor called" << endl;
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