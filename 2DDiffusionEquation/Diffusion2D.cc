#include<iostream>
#include<fstream>
#include<cassert>
#include<string>
#include"Diffusion2D.h"



Diffusion2D::Diffusion2D(double Tl, double Th, int nx, int ny, int nt)
{


	this->Tl=Tl;
	this->Th=Th;
	this->nx=nx;
	this->ny=ny;
	this->nt=nt;
	dx=Lx/(nx -1);
	dy=Ly/(ny -1);
	dt=courant*std::min(dx,dy)*std::min(dx,dy)/alpha;


}
double** Diffusion2D::InitCond(double** A)
{


	for(int i=0; i<ny;i++)
	{
		for(int j=0; j<nx; j++)
		{
		
			if(i==0)
			{

				A[i][j]=Th;

			}
			else if(j==0)
			{


				A[i][j]=Th;

			}
			else
			{
			A[i][j]=20.0;
			}

		}


	}

return A;

}

double* Diffusion2D::XVec(double* X)
{
for(int i=0;i<nx;i++)
{

	X[i]=i*dx;

}


return X;
}



double* Diffusion2D::YVec(double* Y)
{
for(int i=0;i<ny;i++)
{

	Y[i]=i*dy;

}


return Y;
}

double** Diffusion2D::FinDiff(double** A)
{

double** mat=new double* [ny];

for(int i=0; i<ny;i++)
{


	mat[i]=new double [nx];


}


for(int k=0; k<nt; k++)
{

for(int i=0; i<ny; i++)
{

	for(int j=0; j<nx; j++)
	{

		mat[i][j]=A[i][j];


	}


}

for(int i=1; i<ny-1; i++)
{
	for(int j=1; j<nx-1; j++)
	{

		A[i][j]=mat[i][j] + (alpha*dt/(dx*dx))*( mat[i+1][j] - 2*mat[i][j] + mat[i-1][j] ) + \
			(alpha*dt/(dy*dy))*( mat[i][j+1] -2*mat[i][j] + mat[i][j-1]  );

		A[i][nx-1]=A[i][nx-2];
		A[ny-1][j]=A[ny-2][j];



	}




}

}

for(int i=0; i<ny;i++)
{

delete [] mat[i];


}

delete [] mat;



return A;
}


void Diffusion2D::WriteSol(double** A, double* X, double* Y, std::string strg)
{

	std::ofstream WriteA(strg);
	WriteA.precision(10);
	WriteA.setf(std::ios::scientific);
	assert(WriteA.is_open());
	for(int i=0; i<nx; i++)
	{for(int j=0; j<ny; j++)
		{
	
		WriteA<<X[i]<<" "<<Y[i]<<" "<<A[i][j]<<"\n";

		}
	}
	WriteA.close();
}


