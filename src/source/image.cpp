/* Group: Monte Carlo
Members: Zepeng Chen    | acse-zc522
         Ruichen Ding   | acse-rd422
         Georgie Mercer | edsml-gm1722
         Chunyang Wang  | acse-cw17222
         Lizzie Withers | edsml-lcw22
*/

# define STB_IMAGE_WRITE_IMPLEMENTATION
# define STB_IMAGE_IMPLEMENTATION
# include "image.h"
# include <fstream>

using namespace std;

// Default constructor
Image::Image() {};

Image::Image(string path) {
    // cout << "constructor called" << endl;
    int w, h, c;
    unsigned char* img;
    // Read in image file
    img = stbi_load(path.c_str(), &w, &h, &c, 0);
    if (img != NULL) {
        cout << "Image loaded with size " << w << " x " << h << " with " << c << " channel(s)." << std::endl; 
    } else {
        throw runtime_error("Open file failed");
    }
    // set width, height and channel number
    this->width = w; this->height = h; this->channel = c;
    // init 3-D vector pixel
    // cout << "hello 111 " << this->pixel.size() << endl;
    this->pixel.resize(h);
    for (int i = 0; i < h; i++) {
        this->pixel[i].resize(w);
    }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            this->pixel[i][j].resize(c);
        }
    }
    // construct 3-D vector pixel:
    unsigned char* pix = img;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
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
    p.resize(old_obj.height);
    for (int i = 0; i < old_obj.height; i++) {
        p[i].resize(old_obj.width);
    }
    for (int i = 0; i < old_obj.height; i++) {
        for (int j = 0; j < old_obj.width; j++) {
            p[i][j].resize(old_obj.channel);
        }
    }
    // construct 3-D vector pixel:
    for (int i = 0; i < old_obj.height; i++) {
        for (int j = 0; j < old_obj.width; j++) {
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
    unsigned char *img = new unsigned char[this->width * this->height * this->channel];
    unsigned char *pix;
    pix = img;

    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            for (int k = 0; k < this->channel; k++) {
                *pix = (unsigned char) pixel[i][j][k];
                pix ++;
            }
        }
    }

    int success = stbi_write_png(path.c_str(), this->width, this->height, this->channel, img, 0);
    if (success == 0) {
        throw runtime_error("writing image failed");
    } else {
        cout << "Image saved" << endl;
    }
    delete[] img;
}

void Image::printSize() {
    cout << "Image size (w, h, c): (" << this->width << ", " << this->height << ", " << this->channel << ")" << endl;
}

Image Image::pad(int padding) {
    // cout << "padding with length: " << padding << endl;
    Image new_img = Image(*this);
    // set padded size
    new_img.height = this->height + 2*padding;
    new_img.width = this->width + 2*padding;
    // construct a new image with padded size
    vector<std::vector<std::vector<unsigned char>>> new_pixel;
    new_pixel.resize(new_img.height);
    for (int i = 0; i < new_img.height; i++) {
        new_pixel[i].resize(new_img.width);
    }
    for (int i = 0; i < new_img.height; i++) {
        for (int j = 0; j < new_img.width; j++) {
            new_pixel[i][j].resize(new_img.channel);
        }
    }
    new_img.pixel = new_pixel;
    // copy pixels form old image to padded image
    for (int i = 0; i < new_img.height; i++) {
        for (int j = 0; j < new_img.width; j++) {
            for (int k = 0; k < new_img.channel; k++) {
                new_img.pixel[i][j][k] = (uint8_t) 0;
            }
        }
    }
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            for (int k = 0; k < this->channel; k++) {
                new_img.pixel[i+padding][j+padding][k] = this->pixel[i][j][k];
            }
        }
    }
    return new_img;
}

Image::Image(int w, int h, int c) {
    this->width = w;
    this->height = h;
    this->channel = c;

    // Initialize the 3-D pixel vector
    this->pixel.resize(h);
    for (int i = 0; i < h; i++) {
        this->pixel[i].resize(w);
    }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            this->pixel[i][j].resize(c);
        }
    }
}

// Compare two images
bool Image::isEqual(const Image& other) const {
    if (width != other.width || height != other.height || channel != other.channel) {
        return false;
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < channel; k++) {
                if (pixel[i][j][k] != other.pixel[i][j][k]) {
                    return false;
                }
            }
        }
    }

    return true;
}
