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
        // deconstructor
        ~Image();

        // variables
        int width, height, channel;
        std::vector<std::vector<std::vector<unsigned char>>> pixel;

        // member function
        // write Image to destination path;
        void write(std::string path);
        void printSize();
};