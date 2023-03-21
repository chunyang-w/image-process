# pragma once

# include "image.h"
# include "volume.h"
# include "fastimage.h"

using namespace std;

Volume gaussian3d(Volume voxel, int kernel_size, string dest_path);
Volume median3d(Volume voxel, int kernel_size, std::string dest_path);
