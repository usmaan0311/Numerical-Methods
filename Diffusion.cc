#include<iostream>
#include<cmath>
#include<cassert>
#include<string>
#include<fstream>
#include"Diffusion.h"



Diffusion::Diffusion()
{

L=2.0;
courant = 0.2;
nu=0.3;
nt=201;
nx=201;
delx = L/(nx - 1);
delt = (delx*delx*courant)/((nu));

}
Diffusion::Diffusion(double L, double courant, double nu,int nx, int nt)
{
this->nx=nx;
this->nt=nt;
this->L=L;
this->courant=courant;
this->nu=nu;
delx = L/(this->nx - 1);
delt = (delx*delx*this->courant)/((this->nu));

}

void Diffusion::GetVal(int* nx, int* nt)
{
*nx=this->nx;
*nt=this->nt;

}


void Diffusion::PrintVal()
{

	std::cout<<"L\t:\t"<<L<<std::endl;
	std::cout<<"nx\t:\t"<<nx<<std::endl;
	std::cout<<"nt\t:\t"<<nt<<std::endl;
	std::cout<<"courant\t:\t"<<courant<<std::endl;
	std::cout<<"nu\t:\t"<<nu<<std::endl;
	std::cout<<"delx\t:\t"<<delx<<std::endl;
	std::cout<<"delt\t:\t"<<delt<<std::endl;
	std::cout<<"simulation time\t:\t"<<delt*nt<<std::endl;

}


double* Diffusion::initCond(double* A0)
{

	for(int i=0; i<nx; i++)
	{
		if(i*delx>0.75 && i*delx<1.25)
		{
		A0[i]=2.0;
		}
		else
		{
		A0[i]=1.0;

		}
		

	}

return A0;

}

double* Diffusion::XVector(double* X)
{
for(int i=0; i<nx; i++)
{

	X[i]=i*delx;


}

return X;

}


double* Diffusion::FinDiff(double* A)
{
double* mat = new double [nx];

for(int i=0; i<nt;i++)
{
	int k=0;
	while(k<nx)
	{
	mat[k]=A[k];
	k++;
	} 

	for(int j=1; j<nx-1; j++)
	{

		A[j] = mat[j] + (nu*(delt)/(delx*delx))*(mat[j+1] - 2*mat[j] + mat[j-1]);
		std::cout<<"A["<<i<<"]\t:\t"<<A[i]<<"\t"<<"mat["<<i<<"]\t:\t"<<mat[i]<<std::endl;

	}



}
delete [] mat;

return A;

}



void Diffusion::WriteSol(double* A,double* X,std::string strg)
{

	std::ofstream writeA(strg);
	writeA.precision(10);
	writeA.setf(std::ios::scientific);
	assert(writeA.is_open());

	for(int i=0; i<nx;i++)
	{

		writeA<<X[i]<<" "<<A[i]<<"\n";


	}
writeA.close();


}
