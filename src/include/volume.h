# pragma once
# include <vector>
# include <string>
# include "fastImage.h"

class Volume {
    public:
        int img_num;

        std::vector<std::string> files;
        std::string root_dir;
        
        std::vector<FImage> data;

        Volume(std::string root_dir);
        // preload all images into memory;
        void preload();
        void unload();
        
};