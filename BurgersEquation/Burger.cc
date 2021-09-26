#include<iostream>
#include<cmath>
#include<cassert>
#include<fstream>
#include<string>
#include"Burger.h"


Burger::Burger(int nx=201, int nt=201){

this->nx=nx;
this->nt=nt;
dx=L/(this->nx - 1);
dt=courant*(dx*dx)/nu;


}
double Burger::Diff(double (Burger::*f)(double,double), double x, double t, double h=1e-10)
{

	return ( (this->*f)(x + h,t) - (this->*f)(x - h,t) )/(2*h);


}

double* Burger::InitCond(double* u0, double* X){

	for(int i=0; i<nx; i++)
	{

		u0[i] = -2*nu*Diff(&(Burger::Phi),X[i],0)/(Burger::Phi(X[i],0)) + 4;

	}

	return u0;
}

double* Burger::XVector(double* X)
{
	for(int i=0; i<nx; i++)
	{	
		X[i]=i*dx;

	}

	return X;

}

double Burger::Phi(double x, double t)
{

	return exp( -pow((x - 4*t),2)/( 4*nu*(t + 1) ) ) + exp( -pow( (x - 4*t - 2*M_PI),2  )/(4*nu*(t + 1))  ) ;


}


double* Burger::FinDiff(double* A)
{

double* mat = new double [nx];

for(int i=0; i<nt; i++)
{	int k=0;
	while(k<nx)
	{
		mat[k]=A[k];
		k++;

	}
		for(int j=1; j<nx; j++)
		{

			//solve
			A[j] = mat[j] - mat[j]*(dt/dx)*(mat[j] - mat[j-1]) + nu*(dt/(dx*dx))*(mat[j+1] -2*mat[j] + mat[j-1]);

			//update with periodic boundary condition
			A[0] = mat[0] - mat[0]*(dt/dx)*(mat[0] - mat[nx-1]) + nu*(dt/(dx*dx))*(mat[1] -2*mat[0] + mat[nx-1]);
			
			
			A[nx-1] = mat[nx-1] - mat[nx-1]*(dt/dx)*(mat[nx-1] - mat[nx-2]) + nu*(dt/(dx*dx))*(mat[0] -2*mat[nx-1] + mat[nx-2]);



		}





}

delete [] mat;

return A;

}


void Burger::WriteSol(double* A, double* X, std::string strg)
{

	std::ofstream WriteA(strg);
	WriteA.precision(10);
	WriteA.setf(std::ios::scientific);
	assert(WriteA.is_open());
	for(int i=0; i<nx; i++)
	{

		WriteA<<X[i]<<" "<<A[i]<<"\n";



	}

	WriteA.close();



}
