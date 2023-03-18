# pragma once
#include <iostream>
#include <string>
#include <vector>
#include "stb_image.h"
#include "stb_image_write.h"


class Image {
    public:
        // constructor
        Image(std::string path);
        // copy constructor: make deep copy
        Image(const Image & old_obj);
        // deconstructor
        ~Image();

        // variables
        int width, height, channel;
        // 3 dimensional vector: first dimesion: width; second dimension: height;
        // third dimension: channel
        std::vector<std::vector<std::vector<unsigned char>>> pixel;

        // member function
        // write Image to destination path;
        void write(std::string path);
        // print Image size;
        void printSize();
        // padding function
        Image pad(int padding);
};