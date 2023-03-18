# pragma once
# include <string>
# include <vector>
# include "image.h"

// Color correction filters:
Image grayScale(Image img);
Image colorBalance(Image img);

// Image blur filters
Image boxBlur(Image img);
Image gaussianBlur(Image img);


// Filter class
class Filter {
    public:
        // constructor:
        Filter(std::string kernel_path);

        // kernel container
        int kernel_size;
        int padding_size;
        std::vector<std::vector<int> > kernel;
        // perform operation: apply filter to img
        Image apply(Image img);

};

// 1. Padding
// 2. Filter readin
// 3. Apply filter

