/* Group: Monte Carlo
Members: Zepeng Chen    | acse-zc522
         Ruichen Ding   | acse-rd422
         Georgie Mercer | edsml-gm1722
         Chunyang Wang  | acse-cw17222
         Lizzie Withers | edsml-lcw22
*/

# include "helper.h"
# include <iostream>
# include <string>
# include <sys/stat.h>

using namespace std;

/**
@brief Swaps two elements in an array.
This function takes an array of 8-bit unsigned integers, and swaps the elements at the given indices.
@param arr The array to be modified.
@param l The index of the first element to be swapped.
@param r The index of the second element to be swapped.
*/
void swap(uint8_t arr[], int l, int r) {
    uint8_t temp = arr[l];
    arr[l] = arr[r];
    arr[r] = temp;
}

/**
@brief Partition an array of unsigned 8-bit integers around a pivot element.
@param arr - the array to be partitioned
@param l - the index of the leftmost element
@param r - the index of the rightmost element
@return the index of the pivot element after partitioning
*/
int partition(uint8_t arr[], int l, int r) {
    int pivot = arr[l];
    int count = 0;
    for (int i = l + 1; i <= r; i++) {
        if (arr[i] <= pivot)
            count++;
    }
    int pivotIdx = l + count;
    swap(arr[pivotIdx], arr[l]);
    int i = l; int j = r;
    while (i < pivotIdx && j > pivotIdx) {
        while (arr[i] <= pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i < pivotIdx && j > pivotIdx)
            swap(arr[i++], arr[j--]);
    }
    return pivotIdx;
}
 
/**
@brief Sorts an array of unsigned 8-bit integers in non-descending order using the Quick Sort algorithm.
@param arr The array to be sorted.
@param l The starting index of the subarray to be sorted.
@param r The ending index of the subarray to be sorted.
*/
void quickSort(uint8_t arr[], int l, int r) {
    if (l >= r)
        return;
    int p = partition(arr, l, r);
    quickSort(arr, l, p - 1);
    quickSort(arr, p + 1, r);
}

/**
@brief Converts an integer to an 8-bit binary string representation.
@param count the integer to be converted
@return the 8-bit binary string representation of the integer
*/
string num2string(int count) {
    string num_output = to_string(count);
    string eight_bit = "";
    for (int i = 0; i < 8 - num_output.length(); i++) {
        eight_bit += "0";
    }
    eight_bit = eight_bit + num_output;
    return eight_bit;
}

/**
@brief Creates a folder at the specified path if it doesn't already exist.
The function first checks if the folder already exists. If it does, it prints a message to console.
If it does not exist, it attempts to create the folder and set the appropriate permissions.
If the folder creation fails, a runtime error is thrown.
@param path The path of the folder to be created.
@throw runtime_error if the folder cannot be created.
*/
void createFolder(std::string path) {
    struct stat sb;
    if (stat(path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode)) {
        cout << "Path exists" << endl;
    } 
    else {
        cout << "creating the path" << endl;
        int success = mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if (success != 0) {
            cout << "Creat path failed";
            throw runtime_error("not able to create path");
        }
    }
}