# pragma once
# include "image.h"

class Filter {
    public:
        // Color correction filters:
        static Image grayScale(Image img);
        static Image colorBalance(Image img);

        // Image blur filters
        static Image boxBlur(Image img);
        static Image gaussianBlur(Image img);
};