#include<iostream>
#include"Diffusion.h"


int main(int argc, char* argv[])
{
double L=2.0, c=0.2, nu=0.3;
int nx=atoi(argv[1]),nt=atoi(argv[2]);

Diffusion diff(L,c,nu,nx,nt);

//diff.GetVal(&nx, &nt);

double* u=new double [nx];
double* x=new double [nx];

diff.PrintVal();
	
u=diff.initCond(u);
x=diff.XVector(x);
diff.WriteSol(u,x,"initial.dat");

u=diff.FinDiff(u);
diff.WriteSol(u,x,"solution.dat");

delete [] u;
delete [] x;


return 0;
}
