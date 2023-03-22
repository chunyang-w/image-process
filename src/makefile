# specify compiler
CXX = g++-12

# include path
EXTRA_PATH = ./include/
INCLUDES = -I $(EXTRA_PATH)
INC = $(INCLUDES)

SRCDIR := ./source
SRCS := $(wildcard $(SRCDIR)/*.cpp)

OBJ_DIR := ./build
OBJS := $(patsubst ./source%.cpp, ./build%.o, $(SRCS))

INPUTS := ./build/image.o ./build/volumn.o ./build/slice.o ./build/projection.o ./build/filter.o ./build/filter3d.o ./build/fastImage.o ./build/helper.o

main: main.o $(INPUTS)
	$(CXX) $(INC) $^ -o $@ -w

main.o: main.cpp
	$(CXX) $(INC) -c $^ -o $@ -w

./build/image.o: ./source/image.cpp
	$(CXX) $(INC) -c $^ -o $@ -w

./build/filter.o: ./source/filter.cpp
	$(CXX) $(INC) -c $^ -o $@ -w

./build/projection.o: ./source/projection.cpp
	$(CXX) $(INC) -c $^ -o $@ -w

./build/slice.o: ./source/slice.cpp
	$(CXX) $(INC) -c $^ -o $@ -w

./build/volumn.o: ./source/volume.cpp
	$(CXX) $(INC) -c $^ -o $@ -w

./build/filter3d.o: ./source/filter3d.cpp
	$(CXX) $(INC) -c $^ -o $@ -w

./build/fastImage.o: ./source/fastImage.cpp
	$(CXX) $(INC) -c $^ -o $@ -w

./build/helper.o: ./source/helper.cpp
	$(CXX) $(INC) -c $^ -o $@ -w

demo: ./io-demo/minimal.cpp
	$(CXX) $(INC) $^ -o $@  -w
	@./demo

test: test.o $(INPUTS)
	$(CXX) $(INC) $^ -o $@ -w

test.o: test.cpp
	$(CXX) $(INC) -c $^ -o $@ -w

.PHONY: runtest
runtest:
	@make clean
	@make test
	@echo ""
	@echo "======= RUNNING PROGRAM ======="
	@echo ""
	@./test
	@echo ""
	@echo "======= RUNNING FINISH ======="

.PHONY: run
run:
	@make clean
	@make
	@echo ""
	@echo "======= RUNNING PROGRAM ======="
	@echo ""
	@./main
	@echo ""
	@echo "======= RUNNING FINISH ======="


.PHONY: clean
clean:
	rm -f ./build/*.o
	rm -f *.o


.PHONY: nimg
nimg:
	@echo ""
	@echo "No out put image can survive this! Kill Kill Kill!"
	@rm -f ../Output/*.png
	@echo ""
	@echo ":-P done!"
	@echo ""

# main: $(OBJS) main.o 
# 	$(CXX) $(INC) $^ -o $@ -w
# 	@./main

# main.o: main.cpp
# 	$(CXX) $(INC) -c $^ -o $@ -w

# $(OBJS): %.o: %.cpp
# 	$(CXX) $(INC) -c $< -o $@  -w