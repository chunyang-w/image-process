// A minimal example file showing how to include the stb image headers,
// and how to read and write image files using these headers.
//
// Compilation with: g++-12 minimal.cpp -o minimal
//
// Written by T.M. Davison (2023)

#include <iostream>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main() {

    int w, h, c;
    unsigned char* data;

    // Read in image file
    data = stbi_load("example.png", &w, &h, &c, 0);

    // Print image size to screen
    std::cout << "Image loaded with size " << w << " x " << h << " with " << c << " channel(s)." << std::endl; 

    // Save image to new filename
    int success = stbi_write_png("output.png", w, h, c, data, 0);

    // Deallocate memory
    stbi_image_free(data);

    return 0;
}