# 🖥️ C++ Group Project: Team Monte-Carlo

## Programme instructions:

(all command have to be executed under src directory)

+ To run the main program: `make run`
+ Complie program: `make`
+ Clean objective files: `make clean`
+ Run minimal demo: `make demo`

##🔎 Project source code director explained
src
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

