SRC=Diff.cc Diffusion.cc

TAR=Diff.exe

CXX=g++ -Wall -O3 -o

$(TAR): $(SRC)
	$(CXX) $(TAR) $(SRC)

plot:
	python DiffPlot


clean:
	$(RM) *.exe *.dat ~* *~
