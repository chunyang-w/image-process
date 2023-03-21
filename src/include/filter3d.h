# pragma once

# include "image.h"
# include "volume.h"
# include "fastimage.h"

using namespace std;

FImage filter_3d(Volume voxel);

Volume median3d(Volume voxel, int kernel_size);
