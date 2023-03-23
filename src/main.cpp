# include <iostream>
# include <vector>
# include "image.h"
# include "filter.h"
# include "volume.h"
# include "projection.h"
# include "fastImage.h"
# include "filter3d.h"
# include <cassert>
# include <random>
# include "slice.h"
# include <filesystem>
# include <sys/stat.h>


using namespace std;

int main(){
    bool enter = true;
    bool process = true;
    bool path_select = true;
    bool judge_kernel = true;
    int data_type;
    int process_type;
    int kernel_size;
    int choose_path;
    

    cout << "Hello, welcome Monte-Carlo tools" << endl;
    while(enter){
        process = true;
        cout << "Please choose the data type you want to process" << endl;
        cout << "1. 2D image" << endl;
        cout << "2. 3D volume" << endl;
        cout << "(Press 9 to quit the program)" << endl;
        string read_path;
        if(!cin >> data_type){
            cin.clear();
            cin.ignore();
            cout << "You enter an invalid character" << endl;
        }
        else{
            cin >> data_type;
        }
        if(data_type == 1){
            process = false;
        }
        else if(data_type == 2){
            while(process){
                path_select = true;
                cout << "please choose process: " << endl;
                cout << "1. Gaussian filter" << endl;
                cout << "2. Median filter" << endl;
                cout << "3. 3d projection" << endl;
                cout << "4. slce the images" << endl;
                cout << "5. return back to data type selectuon" << endl;
                cout << "(Press 9 to quit the program)" << endl;
                if(!cin >> process_type){
                    cin.clear();
                    cin.ignore();
                    cout << "You enter an invalid character" << endl;
                }
                else{
                    cin >> process_type;
                }
                if(process_type == 1 || process_type == 2 || process_type == 3 || process_type == 4){
                    while(path_select){
                        cout << "Please choose the read path" << endl;
                        cout << "1. confuciusornis" << endl;
                        cout << "2. fracture" << endl;
                        cout << "3. personal dataset path" << endl;
                        cout << "4. return back" << endl;
                        cout << "(Press 9 to quit the program)" << endl;
                        if(!cin >> choose_path){
                            cin.clear();
                            cin.ignore();
                            cout << "You enter an invalid character" << endl;
                        }
                        else{
                            cin >> choose_path;
                        }
                        if(choose_path == 1){
                            read_path = "../Scans/confuciusornis/";
                            path_select = false;
                        }
                        else if(choose_path == 2){
                            read_path = "../Scans/fracture/";
                            path_select = false;
                        }
                        else if(choose_path == 3){
                            cout << "Please enter the path" << endl;
                            cin >> read_path;
                            if (filesystem::exists(read_path.c_str()))
                            {
                                cout << "The path is valid" << endl;
                                path_select = false;
                            }
                            else{
                                cout << "The path is invalid" << endl;
                            }
                        }
                        else if(choose_path == 4){
                            path_select = false;
                        }
                        else if(choose_path == 9){
                            return 0;
                        }
                        else{
                            cout << "Please enter a valid number" << endl;
                        }
                    }
                    if ((process_type == 1 || process_type == 2) && choose_path != 4){
                        while(judge_kernel){
                            cout << "Please enter the kernel size" << endl;
                            if(!cin >> process_type){
                                cin.clear();
                                cin.ignore();
                                cout << "You enter an invalid character" << endl;
                            }
                            else{
                                cin >> kernel_size;
                            }
                            if (kernel_size >= 3 && kernel_size % 2 == 1){
                                cout << "The kernel size is valid" << endl;
                                judge_kernel = false;
                            }
                            else{
                                cout << "The kernel size is invalid" << endl;
                                cout << "kernel size should be odd and at least 3" << endl;
                                cout << "Please enter a valid kernel size" << endl;
                            }
                        }
                    }
                    if(process_type == 1 && choose_path != 4){
                        Volume voxel(read_path);
                        Volume voxel2 = gaussian3d(voxel, kernel_size, "../Output/gaussian3d_result/");
                        cout << "Your gaussian filter result is saved in path: " << endl;
                        cout << "../Output/gaussian3d_result/" << endl;
                    }
                    else if(process_type == 2 && choose_path != 4){
                        Volume voxel3(read_path);
                        Volume voxel4 = median3d(voxel3, kernel_size, "../Output/median3d_result/");
                        cout << "Your median filter result is saved in path: " << endl;
                        cout << "../Output/median3d_result/" << endl;
                    }
                    else if(process_type == 3 && choose_path != 4){
                        Volume voxel(read_path);
                        FImage res_img = choose_projection(voxel);
                        res_img.write("../Output/projection_result.png");
                    }
                    else if(process_type == 4 && choose_path != 4){
                        Volume voxel(read_path);
                        int slice_start;
                        int slice_end;
                        int axis;
                        bool judge_axis = true;
                        while(judge_axis){

                            cout << "please enter your start number: " << endl;
                            if (!cin >> slice_start){
                                cin.clear();
                                cin.ignore();
                                cout << "You enter an invalid character" << endl;
                            }
                            else{
                                cin >> slice_start;
                                cin.clear();
                                cin.ignore();
                            }
                            cout << "please enter your end number: " << endl;
                            if (!cin >> slice_end){
                                cin.clear();
                                cin.ignore();
                                cout << "You enter an invalid character" << endl;
                            }
                            else{
                                cin >> slice_end;
                                cin.clear();
                                cin.ignore();
                            }
                            cout << "please enter the axis: " << endl;
                            cout << "0: slice the voxel along z axis, the image has shape (x,y)" << endl;
                            cout << "1: slice the voxel along y axis, the image has shape (x,z)" << endl;
                            cout << "2: slice the voxel along x axis, the image has shape (y,z)" << endl;
                            if(!(cin >> axis)){
                                cin.clear();
                                cin.ignore();
                                cout << "You enter an invalid character" << endl;
                            }
                            else{
                                if(axis == 0 || axis == 1 || axis == 2){
                                    cout << axis << endl;
                                    cout << "The axis is valid" << endl;
                                    slice(voxel, slice_start, slice_end, axis, "../Output/slice_result/");
                                    judge_axis = false;
                                }
                                else{
                                    cout << "The axis is invalid" << endl;
                                    cout << "Please enter a valid axis" << endl;
                                    cin.clear();
                                }
                            }
                        }
                    }
                }
                else if(process_type == 5){
                    process = false;
                }
                else if(process_type == 9){
                    return 0;
                }
                else{
                    cout << "Please enter a valid number" << endl;
                }
            }
        }
        else if(data_type == 9){
            return 0;
        }
        else{
            cout << "Please enter a valid number" << endl;
        }
    }

    return 0;
    }