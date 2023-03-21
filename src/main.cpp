# include <iostream>
# include <vector>
# include <string>
# include <sys/stat.h>
# include "image.h"
# include "filter.h"


using namespace std;

void apply(Image img, string filter_name, string output_path) {

    string file_type = ".png";
    Image res;

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
        res = edgeDetection(img, method);
    }
    // Rerun process if filter name specified was invalid
    else {
        cout << "\nInvalid argument - please re-enter filter:\n";
        cin >> filter_name;
        apply(img, filter_name, output_path);
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
        apply(res, filter_name, output_path);
    }
}

int main() {

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
    cout << "\nWhat filter would you like to apply?\n";
    string filter_name, output_path;
    cin >> filter_name;
    output_path = output_folder + "/" + filter_name;
    apply(img, filter_name, output_path);

    cout << "\nThanks for using the Monte-Carlo filtering tool!\n";

    // Filter box3x3("./filter/box3x3.txt");
    // Filter gaussian3x3("./filter/gaussian3x3.txt");
    // Filter box5x5("./filter/box5x5.txt");
    // Filter sobelx("./filter/sobelx.txt");
    // Filter prewittx("./filter/prewittx.txt");
    // box3x3.apply(img).write("../Output/box_gracehopper.png");
    // gaussian3x3.apply(img).write("../Output/gau_gracehopper.png");
    // box5x5.apply(img).write("../Output/box5_gracehopper.png");
    // sobelx.apply(box3x3.apply(grayScale(img))).write("../Output/sobelx_gracehopper.png");
    // prewittx.apply(box3x3.apply(grayScale(img))).write("../Output/prewittx_gracehopper.png");
    // sobel(grayScale(img)).write("../Output/sobel_gracehopper.png");
    // prewitt(grayScale(img)).write("../Output/prewitt_gracehopper.png"); 
    // edgeDetection(grayScale(img)).write("../Output/sobel_gracehopper.png"); 
    // edgeDetection(grayScale(img), "sobel").write("../Output/sobel_gracehopper.png"); 
    // edgeDetection(grayScale(img), "scharr").write("../Output/scharr_gracehopper.png"); 
    // edgeDetection(img, "prewitt").write("../Output/prewitt_gracehopper.png"); 
    // edgeDetection(img, "roberts_cross").write("../Output/roberts_cross_gracehopper.png"); 
    // imageBlur(img, "gaussian", 7).write("../Output/gaussian7_gracehopper.png"); 
    // imageBlur(img, "median", 3).write("../Output/median3_gracehopper.png"); 
    // imageBlur(img, "box", 5).write("../Output/box5_gracehopper.png"); 
    // imageBlur(img, "boox", 5).write("../Output/typo_gracehopper.png"); 
    return 0;
}