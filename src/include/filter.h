# pragma once
# include <string>
# include <vector>
# include "image.h"

// std::string sobelx_path = "./filter/sobelx.txt";
// std::string sobely_path = "./filter/sobely.txt";

// Color correction filters
// Example usage::
//      Image img = grayScale(img);
//      img.write(string path);
Image grayScale(Image img);
Image colorBalance(Image img);
Image Brightness(Image img);
Image Brightness(Image img, int brightness);
Image histogramEqualisation(Image img);
Image histogramEqualisationRGB(Image img);


// Edge-detection filters
Image sobel(Image img);
Image prewitt(Image img);


// Filter class
// Example usage
//      Filter myNxNfilter = Filter(path_to_filter);
//      myNxNfilter.apply(img);
class Filter {
    public:
        // constructor:
        Filter(std::string kernel_path);

        // kernel container
        int kernel_size;
        int padding_size;
        std::vector<std::vector<double> > kernel;
        // perform operation: apply filter to img
        Image apply(Image img);

};

