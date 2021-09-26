#include<iostream>
#include"Diffusion2D.h"

int main(int argc, char* argv[])
{
	double Tl=20.0, Th=100.0;
	int nx=atoi(argv[1]), ny=atoi(argv[2]), nt=atoi(argv[3]);
	
	double** A = new double* [ny];
	for(int i=0; i<ny; i++)
	{

		A[i] = new double [nx]; 

	}

	Diffusion2D diff2(Tl, Th, nx, ny, nt);
	
	A=diff2.InitCond(A);
	double* X=new double [nx];
	double* Y=new double [ny];
	
	X=diff2.XVec(X);
	Y=diff2.YVec(Y);

	diff2.WriteSol(A, X, Y, "initial.dat");

	A=diff2.FinDiff(A);

	diff2.WriteSol(A, X, Y, "solution.dat");

for(int i=0; i<ny; i++)
{
	delete [] A[i];
}
delete [] A;
delete [] X;
delete [] Y;


return 0;
}
