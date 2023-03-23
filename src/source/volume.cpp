/* Group: Monte Carlo
Members: Zepeng Chen    | acse-zc522
         Ruichen Ding   | acse-rd422
         Georgie Mercer | edsml-gm1722
         Chunyang Wang  | acse-cw17222
         Lizzie Withers | edsml-lcw22
*/

# include <string>
# include <vector>
# include <dirent.h>
# include <algorithm>
# include "volume.h"

using namespace std;


/**
@brief Constructs a Volume object given the root directory of the image files.
This constructor initializes a Volume object by reading all PNG image files in the specified directory
and storing their file paths in a vector. The files are sorted by name in ascending order.
@param root_dir A string representing the root directory containing the image files.
@throws std::runtime_error If the directory cannot be read or no PNG files are found.
*/
Volume::Volume(string root_dir) {

    this->root_dir = root_dir;
    this->img_num = 0;

    cout << "reading root dir ... root is: " << root_dir << endl; 
    struct dirent *ptr;    
    DIR *dir;
    string PATH = this->root_dir;
    dir=opendir(PATH.c_str()); 
    while((ptr=readdir(dir))!=NULL) {   
        string file_name = ptr->d_name;
        if (file_name.length()<4)
            continue;
        else if(file_name.substr(file_name.length()-4,file_name.length()) == ".png"){
            this->files.push_back(root_dir + ptr->d_name);
            this->img_num ++;
        }
    }
    sort(this->files.begin(), this->files.end());
    closedir(dir);
}

/**
@brief Preloads the Volume's image data into memory.
This function initializes an FImage object for each PNG file in the Volume's file list and stores them
in a vector for quick access. This can improve performance when working with the Volume's image data
multiple times.
@throws std::runtime_error If any FImage objects fail to be initialized.
*/
void Volume::preload() {
    for (int i = 0; i < this->img_num; i++) {
        this->data.push_back(FImage(this->files[i]));
    }
}

/**
@brief Unloads the Volume's image data from memory.
This function clears the Volume's data vector, which contains all of the FImage objects representing the
Volume's image data. This can free up memory if the Volume's image data is no longer needed.
*/
void Volume::unload() {
    this->data.resize(0);
}