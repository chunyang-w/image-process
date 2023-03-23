/* Group: Monte Carlo
Members: Zepeng Chen    | acse-zc522
         Ruichen Ding   | acse-rd422
         Georgie Mercer | edsml-gm1722
         Chunyang Wang  | acse-cw17222
         Lizzie Withers | edsml-lcw22
*/

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