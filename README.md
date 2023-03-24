# 🖥️ Image Processing Tool: Team Monte-Carlo

This program has been designed to enable quick and easy image modifications via a command line interface.

## 🔎 About

This C++ can be used to apply a range of image filters and orthographic projections to an input 2D image or 3D data volume.
It contains a main function which reads an image or data volume, asks the user which filter or projection to apply, calls separate functions for the appropriate filter and/or projections, and saves the new image with the filter/projection applied. It will work with any arbitrary image/data volume size.


## 🧪 User Instructions (TBC)

To run the program use the following commands:

*(They must be exectued under the src directory and use g++-12 to compile)*

**Compile**
```bash
make
```

**Run**
```bash
make run
```
If you wish to use  g++ then
```bash
make run -f makefile_g++
```

**Clean objective files**
```bash
make clean
```

Once running, the program is interacted with via entries into the command line. These are fairly self explantory, with guidance on options provided throughout, so will not be detailed here.

If processing a 2D image, the high level flow is as follows:
* Enter image name (note the image much be saved in the Image folder)
* Choose type of filter to be applied
* Enter any additional parameters required
* Image is processed and saved
* The user has the option to apply another filter on top of the output

Output images are saved in the filter of their name, in the output folder. Their name corresponds to the filter applied, and if multiple filters have been applied, these will be concatenated together.

If processing a 3D image, the high level flow is as follows:
* Enter which processing procedure to carry out, eg: Gaussian3D, Median 3D, Projection, Slicing ...
* Choose which dataset to use (could be predownloaded datasets or userdefined)
* Choose parameters to apply, eg: kernel size, slicing range ...
* The operation is then applied and save the output to a folder.


## 📖 Documentation

Html documentation is available in the `Documentation` folder, including details of all functions and classes, and how they should be used, as well as the contents of this README.md.

This has been generated with Doxygen and can be viewed in your browser through the `index.html` file.


## ✅ Testing (TBC)

The `test.cpp` file contains tests for all functions and can be used to check the programs operation on your system. 

This can be run by navigating to the src directory and running:

```bash
make runtest
```


## 📁 Code Structure (TBC)

*For further details please refer to the documentation.*
```
main.cpp (main source code)
tests.cpp (test code)
makefile (make file that controls the generation of the program)
makefile_g++ (alternative make file)
|- build (objective files)
    |- fastImage.o
    |- filter.o
    |- filter3d.o
    |- helper.o
    |- image.o
    |- projection.o
    |- slice.o
    |- volume.o
|- include (header files)
    |- fastImage.h
    |- filter.h
    |- filter3d.h
    |- helper.h
    |- image.h
    |- projection.h
    |- stb_image_write.h
    |- stb_image.h
    |- slice.h
    |- volume.h
|- source (source code)
    |- fastImage.cpp
    |- filter.cpp
    |- filter3d.cpp
    |- helper.cpp
    |- image.cpp
    |- projection.cpp
    |- slice.cpp
    |- volume.cpp
```

## 👤 Authors

Zepeng Chen	- acse-zc522

Ruichen Ding - acse-rd422

Georgie Mercer - edsml-gm1722

Chunyang Wang - acse-cw17222

Lizzie Withers - edsml-lcw22


## 📃 License

[MIT](https://choosealicense.com/licenses/mit/)