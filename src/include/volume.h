# pragma once
# include <vector>
# include <string>
# include "image.h"

class Volume {
    public:
        int total_img;
        int img_num;

        std::vector<std::string> files;
        std::string root_dir;
        Volume(std::string root_dir);
};