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

/**
@brief Default constructor for the Image class.
This constructor initializes an empty Image object with no data.
*/
Image::Image() {};

/**
@brief Constructs an Image object from the image file specified by the path.
@param path A string representing the path of the image file.
This constructor reads in an image file using the stbi_load function from the stb_image library.
If the file is loaded successfully, it initializes the Image object with its width, height, and
channel number, and constructs a 3-D vector pixel that stores the image data. If the file loading
fails, a runtime_error is thrown. The memory allocated by stbi_load is freed before exiting the
constructor.
*/
Image::Image(string path) {
    int w, h, c;
    unsigned char* img;
    // Read in image file
    img = stbi_load(path.c_str(), &w, &h, &c, 0);
    if (img != NULL) {
        cout << "Image loaded with size " << w << " x " << h << " with " << c << " channel(s)." << std::endl; 
    } else {
        throw runtime_error("Open file failed");
    }
    // Set width, height and channel number
    this->width = w; this->height = h; this->channel = c;

    // Init 3-D vector pixel
    this->pixel.resize(h);
    for (int i = 0; i < h; i++) {
        this->pixel[i].resize(w);
    }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            this->pixel[i][j].resize(c);
        }
    }
    // Construct 3-D vector pixel:
    unsigned char* pix = img;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            for (int k = 0; k < c; k++) {
                pixel[i][j][k] = (uint8_t) *pix;
                pix +=1;
            }
        }
    }
    // Free memory
    stbi_image_free(img);
}

/**
@brief Copy constructor of for the Image class
This constructor initializes a new Image object by copying the width, height, and channel properties of the given
Image object. It then constructs a new 3D vector pixel and populates it with the pixel values of the given object.
Note that this constructor performs a deep copy of the pixel data to ensure that any modifications to the pixel data
of the new object does not affect the original object.
@param old_obj The object to be copied.
*/
Image::Image(const Image & old_obj): width(old_obj.width), height(old_obj.height), channel(old_obj.channel)
{
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
    // Construct 3-D vector pixel:
    for (int i = 0; i < old_obj.height; i++) {
        for (int j = 0; j < old_obj.width; j++) {
            for (int k = 0; k < old_obj.channel; k++) {
                p[i][j][k] = (uint8_t) old_obj.pixel[i][j][k];
            }
        }
    }
    this->pixel = p;
}

/**
@brief The Image destructor.
This destructor is responsible for freeing the memory used by the Image object.
*/
Image::~Image() {
}

/**
@brief Write the image to a file path in PNG format.
@param path: A string representing the file path.
@throws runtime_error if the image writing operation fails.
*/
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

/**
@brief Print the size of the image in the format "(width, height, channel)".
*/
void Image::printSize() {
    cout << "Image size (w, h, c): (" << this->width << ", " << this->height << ", " << this->channel << ")" << endl;
}

/**
@brief Creates a new image with padding around the edges of the original image.
@param padding An integer value representing the amount of padding to add around the edges of the image.
@return A new Image object with the specified amount of padding added around the edges.
*/
Image Image::pad(int padding) {
    Image new_img = Image(*this);
    // Set padded size
    new_img.height = this->height + 2*padding;
    new_img.width = this->width + 2*padding;
    // Construct a new image with padded size
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
    // Copy pixels form old image to padded image
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

/**
@brief Constructs an Image object with the specified width, height, and number of channels.
The constructor initializes the Image object with the specified width, height, and number of channels.
It also creates a 3-dimensional pixel vector with dimensions (height x width x channel) to store the image data.
@param w The width of the image.
@param h The height of the image.
@param c The number of color channels in the image.
The constructor initializes the Image object with the specified width, height, and number of channels.
It also creates a 3-dimensional pixel vector with dimensions (height x width x channel) to store the image data.
*/
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

/**
@brief Compares this image with another image for equality.
@param other The image to be compared with.
@return true if the images are equal in size and pixel values, false otherwise.
*/
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
