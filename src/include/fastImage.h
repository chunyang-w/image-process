# pragma once
#include <iostream>
#include <string>
#include <vector>
#include "stb_image.h"
#include "stb_image_write.h"


// Encapsulated Image class
// Major feature: 
// 1. use [i][j][k] selector to select k-th channel on the i-th row of the j-th column
//      (on img.pixel menber)
// 2. support writing with img.write(path_to_write)
// 3. support img.printSize() to print out image shape

class FImage {
    public:
        // constructor
        FImage(){}
        FImage(std::string path);
        FImage(int h, int w, int c);
        FImage(const FImage &old_obj);
        // // copy constructor: make deep copy
        // FImage(const FImage & old_obj);
        // deconstructor
        ~FImage();

        // variables
        int width, height, channel;
        // variable for memory occupied measured in byte
        // pointer to the starting point of the pixel
        unsigned char* pixel;

        // member function
        // get pixel at i-th row j-th col and z-th channel
        unsigned char getPixel(int i, int j, int k);
        // get pixel at i-th row j-th col and z-th channel
        void setPixel(int i, int j, int k, unsigned char val);
        // write Image to destination path;
        void write(std::string path);
        // print Image size;
        void printSize();
        // padding function
        FImage pad(int padding);
        bool operator==(FImage& x);
};