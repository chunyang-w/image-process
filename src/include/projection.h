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
# include "volume.h"
# include "fastimage.h"

using namespace std;

FImage max_projection(Volume voxel);
Image min_projection(Volume voxel);
Image ave_projection(Volume voxel);
FImage Z_projection(Volume voxel);
FImage X_projection(Volume voxel);
FImage choose_projection(Volume voxel);
