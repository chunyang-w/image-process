# include <iostream>
# include <vector>
# include "image.h"
# include "filter.h"
# include "volume.h"
# include "projection.h"
# include "fastImage.h"
# include "slice.h"
# include "filter3d.h"

using namespace std;

int main() {
    Volume voxel1("../Scans/fracture/");
    Volume voxel2 = slice(voxel1, 0, 70, 1, "../Output/updownfracture/");
    cout << voxel2.img_num << endl;
}
