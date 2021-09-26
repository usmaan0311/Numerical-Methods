#include<iostream>
#include"Burger.h"


int main(int argc, char* argv[])
{
int nx=atoi(argv[1]), nt=atoi(argv[2]);

double* X = new double [nx];
double* u = new double [nx];

Burger burj(nx,nt);

X=burj.XVector(X);
u=burj.InitCond(u,X);
burj.WriteSol(u,X,"initial.dat");

u=burj.FinDiff(u);
burj.WriteSol(u,X,"solution.dat");



return 0;
}



