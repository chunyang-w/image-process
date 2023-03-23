/* Group: Monte Carlo
Members: Zepeng Chen    | acse-zc522
         Ruichen Ding   | acse-rd422
         Georgie Mercer | edsml-gm1722
         Chunyang Wang  | acse-cw17222
         Lizzie Withers | edsml-lcw22
*/

# pragma once
# include <string>
# include <vector>
# include "image.h"

// Colour correction filters
// Example usage::
//      Image img = grayScale(img);
//      img.write(string path);
Image grayScale(Image img);
Image colourBalance(Image img);
Image Brightness(Image img);
Image Brightness(Image img, int brightness);
Image histogramEqualisation(Image img);


// Image blur filters
Image imageBlur(Image img, int method, int kernel_size);


// Edge-detection filters
Image edgeDetection(Image img, int method);


// Filter class
// Example usage
//      Filter myNxNfilter = Filter(path_to_filter);
//      myNxNfilter.apply(img);
class Filter {
    public:

        // Edge detection constructor:
        Filter(char* optr);

        // Gaussian contructor
        Filter(int kernel_size);

        // kernel container
        int kernel_size;
        int padding_size;
        std::vector<std::vector<double> > kernel;
        // perform operation: apply filter to img
        Image apply(Image img);

};
