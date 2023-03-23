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
# include <filesystem>

using namespace std;

void swap(uint8_t arr[], int l, int r) {
    uint8_t temp = arr[l];
    arr[l] = arr[r];
    arr[r] = temp;
}

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
 
void quickSort(uint8_t arr[], int l, int r) {
    if (l >= r)
        return;
    int p = partition(arr, l, r);
    quickSort(arr, l, p - 1);
    quickSort(arr, p + 1, r);
}

string num2string(int count) {
    string num_output = to_string(count);
    string eight_bit = "";
    for (int i = 0; i < 8 - num_output.length(); i++) {
        eight_bit += "0";
    }
    eight_bit = eight_bit + num_output;
    return eight_bit;
}

void createFolder(std::string path) {
    if (filesystem::exists(path.c_str())) {
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