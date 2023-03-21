# include <string>
# include <vector>
# include <dirent.h>
# include <algorithm>
# include "volume.h"

using namespace std;

Volume::Volume(string root_dir) {
    this->root_dir = root_dir;
    this->img_num = 0;

    cout << "reading root dir ... root is: " << root_dir << endl; 
    struct dirent *ptr;    
    DIR *dir;
    string PATH = this->root_dir;
    dir=opendir(PATH.c_str()); 
    // cout << "file name list: "<< endl;
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

void Volume::preload() {
    for (int i = 0; i < this->img_num; i++) {
        this->data.push_back(FImage(this->files[i]));
    }
}

void Volume::unload() {
    this->data.resize(0);
}