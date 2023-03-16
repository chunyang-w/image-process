CXX = g++-12

EXTRA_PATH = ./include/
INCLUDES = -I$(EXTRA_PATH)
INC = $(INCLUDES)

main: main.o matrix.o csrmatrix.o
	$(CXX) $^ -o $@ $(INC) -w
	@./main

main.o: main.cpp
	$(CXX) -c $^ -o $@ $(INC) -w

# matrix.o: ../assessment_matrix/Matrix.cpp
# 	$(CXX) -c $(EXTRA_PATH)Matrix.cpp -o $@ $(INC) -g

# csrmatrix.o: ../assessment_matrix/CSRMatrix.cpp
# 	$(CXX) -c $(EXTRA_PATH)CSRMatrix.cpp -o $@ $(INC) -g

demo: ./io-demo/minimal.cpp
	$(CXX) $^ -o $@ $(INC) -w
	@./demo

clean:
	rm -f *.o
