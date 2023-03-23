/* Group: Monte Carlo
Members: Zepeng Chen    | acse-zc522
         Ruichen Ding   | acse-rd422
         Georgie Mercer | edsml-gm1722
         Chunyang Wang  | acse-cw17222
         Lizzie Withers | edsml-lcw22
*/

# pragma once
# include <string>
# include "fastImage.h"
# include "volume.h"

// slice volume form start-th(included) img to end-th(not included) img (index start from 0).
// then write the image to the path. (if not exist, create a specific path)
// axis = 0: slice the voxel along z axis, the image has shape (x,y)
// axis = 1: slice the voxel along y axis, the image has shape (x,z)
// axis = 2: slice the voxel along y axis, the image has shape (y,z)
Volume slice(Volume voxel, int start, int end, int axis, std::string path);