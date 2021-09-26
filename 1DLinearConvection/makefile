TAR=1dlinconv.exe
SRC=1dlinconv.cc
CXX=g++ -Wall -O3 -fopenmp -o

$(TAR):$(SRC)
	$(CXX) $(TAR) $(SRC)
	
plot:
	python conv_plot

clean:
	$(RM) *.exe ~* *~ *.dat *.png



