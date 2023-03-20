# pragma once
# include <string>
# include <vector>
# include "image.h"
# include "volume.h"
using namespace std;

Image max_projection(Volume voxel);
Image min_projection(Volume voxel);
Image ave_projection(Volume voxel);
Image Z_projection(Volume voxel);
