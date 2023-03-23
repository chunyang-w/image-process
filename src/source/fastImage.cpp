/* Group: Monte Carlo
Members: Zepeng Chen    | acse-zc522
         Ruichen Ding   | acse-rd422
         Georgie Mercer | edsml-gm1722
         Chunyang Wang  | acse-cw17222
         Lizzie Withers | edsml-lcw22
*/

# include "fastImage.h"
# include <fstream>

using namespace std;

FImage::FImage(string path) {
    // cout << "constructor called" << endl;
    int w, h, c;
    unsigned char* img;
    // Read in image file
    img = stbi_load(path.c_str(), &w, &h, &c, 0);
    if (img != NULL) {
        // cout << "Image loaded with size " << w << " x " << h << " with " << c << " channel(s)." << std::endl; 
    } else {
        throw runtime_error("open file failed");
    }
    // set width, height and channel number
    this->width = w; this->height = h; this->channel = c;
    // init 3-D vector pixel
    // cout << "hello 111 " << this->pixel.size() << endl;
    this->pixel = img;
}

FImage::FImage(int h, int w, int c) {
    this->height = h;
    this->width = w;
    this->channel = c;
    unsigned char *ptr = new unsigned char[h*w*c];
    for (unsigned char* p = ptr; p != ptr + (w*h*c); p ++) {
        *p = 0;
    } 
    this->pixel = ptr;
}

FImage::FImage(const FImage & old_obj): width(old_obj.width), height(old_obj.height), channel(old_obj.channel)
{
    unsigned char * old_ptr = old_obj.pixel;
    int num_pixel = old_obj.width*old_obj.height*old_obj.channel;
    unsigned char * new_ptr = new unsigned char [num_pixel];
    for (unsigned char * p = new_ptr; p != new_ptr + num_pixel; p ++) {
        *p = *old_ptr;
        old_ptr++;  
    }
    this->pixel = new_ptr;
}

FImage::~FImage() {
    // cout << "deconstructor called" << endl;
    stbi_image_free(this->pixel);
}

void FImage::write(string path) {
    int success = stbi_write_png(path.c_str(), this->width, this->height, this->channel, this->pixel, 0);
    if (success == 0) {
        throw runtime_error("writing image failed");
    } else {
        cout << "writing success" << endl;
    }
}

void FImage::printSize() {
    cout << "Image size (w, h, c): (" << this->width << ", " << this->height << ", " << this->channel << ")" << endl;
}

unsigned char FImage::getPixel(int i, int j, int k) {
    unsigned char* ptr;
    ptr = this->pixel;
    ptr += (i*(this->width * this->channel)) + (j * this->channel) + k;
    return *ptr;
}

void FImage::setPixel(int i, int j, int k, unsigned char val) {
    unsigned char* ptr;
    ptr = this->pixel;
    ptr += (i*(this->width * this->channel)) + (j * this->channel) + k;
    *ptr = val;
    return;
}



FImage FImage::pad(int padding) {
    // cout << "padding with length: " << padding << endl;
    FImage new_img = FImage(this->height + 2*padding, this->width + 2*padding, this->channel);
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            for (int k = 0; k < this->channel; k++) {
                new_img.setPixel(i+padding, j+padding, k, this->getPixel(i, j, k));
            }
        }
    }
    return new_img;
}