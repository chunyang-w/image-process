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

using namespace std;

int main() {

    int w, h, c;
    unsigned char* data;

    // Read in image file
    data = stbi_load("../Images/gracehopper.png", &w, &h, &c, 0);
    if (data != NULL) {
        // Print image size to screen
        cout << "Image loaded with size " << w << " x " << h << " with " << c << " channel(s)." << std::endl; 
    } else {
        cout << "Image load failed" << endl;
    }

    for (unsigned char* p = data; p != data + (w*h*c/2); p += c) {
            *p = (uint8_t) 0;
            *(p+1) = (uint8_t) 0;
            *(p+2) = (uint8_t) 0;
    } 

    // Save image to new filename
    int success = stbi_write_png("../Output/gracehopperx.png", w, h, c, data, 0);

    if (success == 0) {
        cout << "writing failed" << endl;
    } else {
        cout << "writing success" << endl;
    }

    // Deallocate memory
    stbi_image_free(data);

    return 0;
}