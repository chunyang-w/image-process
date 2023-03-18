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

    int count = 0;

    // Save image to new filename
    int success = stbi_write_png("../Output/gracehopperx.png", w, h, c, data, 0);

    if (success == 0) {
        cout << "writing failed" << endl;
    } else {
        cout << "writing success" << endl;
    }

    // Deallocate memory
    stbi_image_free(data);

    // make fake
    int w_test = 512, h_test = 513, c_test = 4;
    unsigned char *test = new unsigned char[w_test*h_test*c_test];
    cout << "here" << endl;
    for (unsigned char* p = test; p != test + (w_test*h_test*c_test); p += c_test) {
        // cout <<(count % w_test)  << endl;
            *p = (uint8_t) 40;
            *(p+1) = (uint8_t) 200;
            *(p+2) = (uint8_t) 12;  
            *(p+3) = (uint8_t) 255;
            // if ((count % w_test) < 20) {
            //     *p = (uint8_t) 0;
            //     *(p+1) = (uint8_t) 0;
            //     *(p+2) = (uint8_t) 0;
            //     // *(p+3) = (uint8_t) 0;
            // }
            count++;
    } 
    // Save image to new filename
    success = stbi_write_png("../Images/fake.png", w_test, h_test, c_test, test, 0);

    if (success == 0) {
        cout << "writing test failed" << endl;
    } else {
        cout << "writing test success" << endl;
    }

    // Deallocate memory
    stbi_image_free(test);
    return 0;
}