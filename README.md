# 🖥️ Image Processing Tool: Team Monte-Carlo

This program has been designed to enable quick and easy image modifications via a command line interface.

## 🔎 About

This C++ can be used to apply a range of image filters and orthographic projections to an input 2D image or 3D data volume.
It contains a main function which reads an image or data volume, asks the user which filter or projection to apply, calls separate functions for the appropriate filter and/or projections, and saves the new image with the filter/projection applied. It will work with any arbitrary image/data volume size.


## 🧪 User Instructions (TBC)

(all command have to be executed under src directory use g++-12 to compile)

+ To run the main program: `make run`
+ Complie program: `make`
+ Clean objective files: `make clean`
+ Run minimal demo: `make demo`
+ Run unit test: `make runtest`

(if you wish to use  g++)
+ run `make run -f makefile_g++`

## 📖 Documentation

Html documentation is available in the `Documentation` folder, including details of all functions and classes, and how they should be used, as well as the contents of this README.md.

This has been generated with Doxygen and can be viewed in your browser through the `index.html` file.


## ✅ Testing

The `test.cpp` file contains tests for all functions and can be used to check the programs operation on your system. 

This can be run by navigating to the src directory and running:

```bash
make runtest
```


## 📁 Code Structure (TBC)

```
main.cpp (main source code)
makefile (make file that controls the generation of the program)
|- build (objective files)
    |- image.o
    |- filter.o
    |- *.o
|- include (header files)
    |- filter.h
    |- image.h
    |- *.h
|- source (source code)
    |- filter.cpp
    |- image.cpp
    |- *.cpp
|- io-demo (minimal demo here)
    |- minimal.cpp
```

## 👤 Authors

Zepeng Chen	- acse-zc522

Ruichen Ding - acse-rd422

Georgie Mercer - edsml-gm1722

Chunyang Wang - acse-cw17222

Lizzie Withers - edsml-lcw22


## 📃 License

[MIT](https://choosealicense.com/licenses/mit/)