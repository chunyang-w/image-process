/* Group: Monte Carlo
Members: Zepeng Chen    | acse-zc522
         Ruichen Ding   | acse-rd422
         Georgie Mercer | edsml-gm1722
         Chunyang Wang  | acse-cw17222
         Lizzie Withers | edsml-lcw22
*/

# include <iostream>
# include <vector>
# include <string>
# include <sys/stat.h>
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


/**
@brief Applies a 2D image filter to the input image img and saves the output to the specified output_path.
The user can enter "help" to print available filter options. The user is also given the option to apply
multiple filters sequentially to the output image (note the result will be saved after each filter).
@param img The input image to be filtered
@param filter_name The name of the filter to be applied
@param output_path The path where the output image should be saved
@return None
*/
void apply_2d(Image img, string filter_name, string output_path) {

    string file_type = ".png";
    Image res;

    // Option to print out filter options
    if (filter_name == "help") {
        output_path.resize(output_path.size() - 4); //Remove 'help' from file name
        cout << "\nFilter options:\ngrayscale\ncolour_balance\n";
        cout << "brightness\nhistogram_equalisation\nblur\nedge_detection\n\nPlease enter one of the above:\n";
        cin >> filter_name;
        output_path = output_path + filter_name;
    }
    // Apply grayscale filter
    if (filter_name == "grayscale") {
        res = grayScale(img);
    } 
    // Apply colour balance
    else if (filter_name == "colour_balance") {
        res = colourBalance(img);
    } 
    // Apply brightness adjustment
    else if (filter_name == "brightness") {

        cout << "\nSpecify optional brightness value in the range -255 to 255, or enter 0 for automatic adjustment:\n";
        int strength ;
        cin >> strength;
        if (strength == 0) {
            res = Brightness(img);}
        else if ((strength > 255) | (strength < -255)) {
            cout << "Invalid value - performing automatic adjustment instead";
            res = Brightness(img);}
        else {
            res = Brightness(img, strength);
        }
    }
    // Apply histogram equalisation
    else if (filter_name == "histogram_equalisation") {
        res = histogramEqualisation(img);
    }
    // Apply blur
    else if (filter_name == "blur") {

        // Allow user to specify blur method
        cout << "\nSpecify method (median/box/gaussian):\n";
        bool accepted = false;
        string strmethod;
        int method;
        while (accepted != true) {
            cin >> strmethod;
            if (strmethod == "median") {method = 1;
            accepted = true;}
            else if (strmethod == "box") {method = 2;
            accepted = true;}
            else if (strmethod == "gaussian") {method = 3;
            accepted = true;}
            else {cout << "Invalid argument - check method specified\n";};
        }
        // Allow user to specify blur kernel size
        cout << "\nSpecify kernel size:\n";
        int size;
        accepted = false;
        while (accepted != true) {
            cin >> size;
            if (size%2 != 1) {
            cout << "\nInvalid argument - kernel size must be odd number, please re-enter:\n";}
            else {accepted = true;}
        }
        output_path = output_path + "_" + strmethod + to_string(size);
        res = imageBlur(img, method, size);
    }
    // Apply edge detection
    else if (filter_name == "edge_detection")  {

        // Allow user to specify method
        cout << "\nSpecify method (sobel/prewitt/scharr/roberts_cross):\n";
        string strmethod;
        bool accepted = false;
        int method;
        while (accepted != true) {
            cin >> strmethod;
            if (strmethod == "sobel") {method = 1;
            accepted = true;}
            else if (strmethod == "prewitt") {method = 2;
            accepted = true;}
            else if (strmethod == "scharr") {method = 3;
            accepted = true;}
            else if (strmethod == "roberts_cross") {method = 4;
            accepted = true;}
            else {cout << "\nInvalid argument - please re-enter method:\n";};
        }
        output_path = output_path + "_" + strmethod;
        res = edgeDetection(img, method);
    }
    // Rerun process if filter name specified was invalid
    else {
        cout << "\nInvalid argument - please re-enter filter:\n";
        cin >> filter_name;
        size_t rootPosition = output_path.find_last_of("/");
        output_path.erase(rootPosition, output_path.length() - rootPosition);
        output_path = output_path + "/" + filter_name;
        apply_2d(img, filter_name, output_path);
    }

    // Save resultant image
    res.write(output_path + file_type);

    // Check if the user wants to apply an additional filter on top of their output
    string again;
    cout << "\nWould you like to apply another filter on top of this? (Y/N)\n";
    cin >> again;
    if ((again == "Y") | (again == "y") |(again == "Yes") | (again == "yes")) {
        cout << "\nWhat filter would you like to apply?\n";
        cin >> filter_name;
        output_path = output_path + "_" + filter_name;
        apply_2d(res, filter_name, output_path);
    }
}

int main(){

    // It is the full API to use the Monte-Carlo tools, and it has following characteristics:
    // 1. It is a command line interface
    // 2. It is a menu driven program
    // 3. It is a program that can be used to process 2D image and 3D volume

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
            // Let user choose image to be processed
            cout << "Enter name of image to process (e.g. 'gracehopper.png' - ensure this image is saved in the 'Images' folder) \n";
            string image_name, image_path;
            Image img;
            bool imported = false;
            while (imported == false) {
                try {
                    cin >> image_name;
                    image_path = "../Images/" + image_name;
                    Image new_img(image_path);
                    img = new_img;
                    imported = true;}
                catch (runtime_error) {
                    cout << "No image found, please re-enter name:\n";
                }
            } 

            // Ensure correct output folder exists, and if not create it
            string output_folder;
            size_t dotPosition = image_name.find_last_of(".");
            if (dotPosition != string::npos) {
                image_name.erase(dotPosition, image_name.length() - dotPosition);
            }
            output_folder = "../Output/" + image_name;
            int status = mkdir(output_folder.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

            // Let user choose type of image processing
            cout << "\nWhat filter would you like to apply? (Enter 'help' for a list of options)\n";
            string filter_name, output_path;
            cin >> filter_name;
            output_path = output_folder + "/" + filter_name;
            apply_2d(img, filter_name, output_path);

            cout << "\n2D filter finished\n";

        }
        else if(data_type == 2){
            while(process){
                // choose the process type
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
                        // judge whether the input is a number
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
                            // set the gaussian kernel size here
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
                    cout << "Thank you for using our program" << endl;
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
}
