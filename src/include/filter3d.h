/* Group: Monte Carlo
Members: Zepeng Chen    | acse-zc522
         Ruichen Ding   | acse-rd422
         Georgie Mercer | edsml-gm1722
         Chunyang Wang  | acse-cw17222
         Lizzie Withers | edsml-lcw22
*/

# pragma once

# include "image.h"
# include "volume.h"
# include "fastimage.h"

using namespace std;

Volume gaussian3d(Volume voxel, int kernel_size, string dest_path);
Volume median3d(Volume voxel, int kernel_size, std::string dest_path);
