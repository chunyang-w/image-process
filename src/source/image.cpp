#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "image.h"
#include <fstream>

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
    // cout << "hello 111 " << this->pixel.size() << endl;
    this->pixel.resize(w);
    for (int i = 0; i < w; i++) {
        this->pixel[i].resize(h);
    }
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            this->pixel[i][j].resize(c);
        }
    }
    // construct 3-D vector pixel:
    unsigned char* pix = img;
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            for (int k = 0; k < c; k++) {
                pixel[i][j][k] = (uint8_t) *pix;
                pix +=1;
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
                p[i][j][k] = (uint8_t) old_obj.pixel[i][j][k];
            }
        }
    }
    this->pixel = p;
}

Image::~Image() {
    // cout << "deconstructor called" << endl;
}

void Image::write(string path) {
    // cout << "writing image with" << endl;
    cout << "In writing" << endl;
    this->printSize();
    unsigned char *img = new unsigned char[this->width * this->height * this->channel];
    unsigned char *pix;
    pix = img;

    // to del
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            for (int k = 0; k < this->channel; k++) {
                if (j < 20) {
                    this->pixel[i][j][k] = (unsigned char) 0;
                }
            }
        }
    }
    // to del
    // for (int i = 0; i < this->width; i++) {
    //     for (int j = 0; j < this->height; j++) {
    //         if (this->pixel[i][j][0] == 0 ) {
    //             cout <<"*"<< i << " " << j << endl;
    //         }
    //     }
    // }
    // this->printSize();

    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            for (int k = 0; k < this->channel; k++) {
                *pix = (unsigned char) pixel[i][j][k];
                // if (j < 40) {
                //     *pix = (unsigned char) 0;
                // }
                pix ++;
            }
        }
    }
    // int count  = 0;
    // for (unsigned char* p = img; p != img + (this->width*this->height*this->channel); p += this->channel) {
    //     // cout <<(count % w)  << endl;
    //         if ((count % this->width) < 50) {
    //             *p =  0;
    //             *(p+1) =  0;
    //             *(p+2) =  0;
    //         }
    //         count++;
    // } 
    // del
    cout << "***" << endl << this->width << " " << this->height << endl;

    int success = stbi_write_png(path.c_str(), this->width, this->height, this->channel, img, 0);
    if (success == 0) {
        throw runtime_error("writing image failed");
    } else {
        cout << "writing success" << endl;
    }
    delete[] img;
    // del
    pix = img;
    fstream f;
    f.open("./test.txt");
    for (int i = 0; i < this->width; i++) {
        int sum = 0;
        for (int j = 0; j < this->height; j++) {
            sum++;
            *pix = (unsigned char) pixel[i][j][0];
            pix+=this->channel;
            f << (int)*pix << " ";
        }
        f << " sum is : " << sum;
        f << endl;
    }
}

void Image::printSize() {
    cout << "Image size (w, h, c): (" << this->width << ", " << this->height << ", " << this->channel << ")" << endl;
}

Image Image::pad(int padding) {
    cout << "padding with length: " << padding << endl;
    Image new_img = Image(*this);
    // set padded size
    new_img.height = this->height + 2*padding;
    new_img.width = this->width + 2*padding;
    this->printSize();
    new_img.printSize();
    // construct a new image with padded size
    vector<std::vector<std::vector<unsigned char>>> new_pixel;
    new_pixel.resize(new_img.width);
    for (int i = 0; i < new_img.width; i++) {
        new_pixel[i].resize(new_img.height);
    }
    for (int i = 0; i < new_img.width; i++) {
        for (int j = 0; j < new_img.height; j++) {
            new_pixel[i][j].resize(new_img.channel);
        }
    }
    new_img.pixel = new_pixel;
    // new_img.write("../Output/j.png");
    cout << new_img.pixel.size() << " " << new_img.pixel[0].size() << " " << new_img.pixel[0][0].size() << endl;
    cout << "here" << endl;
    // copy pixels form old image to padded image
    for (int i = 0; i < new_img.width; i++) {
        for (int j = 0; j < new_img.height; j++) {
            for (int k = 0; k < new_img.channel; k++) {
                new_img.pixel[i][j][k] = (uint8_t) 0;
            }
        }
    }
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            for (int k = 0; k < this->channel; k++) {
                // cout << i << "," << j << "->" << i+padding << " " << j+padding << endl;
                new_img.pixel[i+padding][j+padding][k] = (uint8_t) 225;
            }
        }
    }
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < 1; j++) {
            for (int k = 0; k < this->channel; k++) {
                this->pixel[i][j][k] = (uint8_t) 255;
            }
        }
    }
    new_img.printSize();
    this->write("../Output/beforepad.png");
    new_img.write("../Output/afterpad.png");
    cout << "nice" << endl;
    return new_img;
}