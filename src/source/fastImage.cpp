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

/**
@brief Constructs an FImage object by loading image from file specified by the given path.
@param path The path of the image file to be loaded.
@throws runtime_error if failed to open the image file.
@note The image file is assumed to be in RGB format.
@note The 3-D vector pixel is initialized using the image data loaded from the file.
@note The width, height and channel number of the image are set based on the loaded image data.
*/
FImage::FImage(string path) {
    int w, h, c;
    unsigned char* img;
    // Read in image file
    img = stbi_load(path.c_str(), &w, &h, &c, 0);
    if (img == NULL) {
        throw runtime_error("open file failed");
    }
    // Set width, height and channel number
    this->width = w; this->height = h; this->channel = c;
    // Init 3-D vector pixel
    this->pixel = img;
}

/**
@brief A class constructor that creates a black image with the given height, width, and channel.
This constructor initializes the FImage object with the specified height, width, and channel number.
It creates a new unsigned char array of size hwc, where each pixel is initialized to 0, resulting in
a black image.
@param h The height of the image.
@param w The width of the image.
@param c The number of channels in the image.
*/
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

/**
@brief Copy constructor for FImage class.
@param old_obj the FImage object to be copied.
*/
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

/**
@brief The FImage destructor.
This destructor is responsible for freeing the memory used by the FImage object.
*/
FImage::~FImage() {
    stbi_image_free(this->pixel);
}

/**
@brief Write the image to a file path in PNG format.
@param path: A string representing the file path.
@throws runtime_error if the image writing operation fails.
*/
void FImage::write(string path) {
    int success = stbi_write_png(path.c_str(), this->width, this->height, this->channel, this->pixel, 0);
    if (success == 0) {
        throw runtime_error("writing image failed");
    } else {
        cout << "writing success" << endl;
    }
}

/**
@brief Print the size of the image in the format "(width, height, channel)".
*/
void FImage::printSize() {
    cout << "Image size (w, h, c): (" << this->width << ", " << this->height << ", " << this->channel << ")" << endl;
}

/**
@brief Get the pixel value at (i,j,k) position.
@param i The row index of the pixel.
@param j The column index of the pixel.
@param k The channel index of the pixel.
*/
unsigned char FImage::getPixel(int i, int j, int k) {
    unsigned char* ptr;
    ptr = this->pixel;
    ptr += (i*(this->width * this->channel)) + (j * this->channel) + k;
    return *ptr;
}

/**
@brief Set the pixel value at the specified position
Sets the value of the pixel at the specified position (i, j, k) to the
given value (val). The image is assumed to be stored in row-major order
(i.e., each row of pixels is stored contiguously in memory).
@param i The row index of the pixel (0-indexed)
@param j The column index of the pixel (0-indexed)
@param k The channel index of the pixel (0-indexed)
@param val The new value to set the pixel to
*/
void FImage::setPixel(int i, int j, int k, unsigned char val) {
    unsigned char* ptr;
    ptr = this->pixel;
    ptr += (i*(this->width * this->channel)) + (j * this->channel) + k;
    *ptr = val;
    return;
}


/**
@brief Creates a new image with padding around the edges of the original image.
@param padding An integer value representing the amount of padding to add around the edges of the image.
@return A new FImage object with the specified amount of padding added around the edges.
*/
FImage FImage::pad(int padding) {
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