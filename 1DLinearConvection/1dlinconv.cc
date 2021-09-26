#include<iostream>
#include<cmath>
#include<fstream>
#include<cassert>


/********* du/dt + c*du/dx = 0 ***********************************************
 *********                     ***********************************************
 *********u_{i}^{n+1} = u_{i}^{n} -c*del(t)/del(x)*(u_{i}^{n} - u_{i-1}^{n})**
 *****************************************************************************
 *****************************************************************************/
double* IC(int,double);
double* findiff(double*,double,double,double,int,int);

int main(int argc, char* argv[])
{
int nx=201,nt=201;
double dx, dt, L=2.0, c=1.0, courantNo=0.5;

nx=atoi(argv[1]);
nt=atoi(argv[2]);

double* u=new double [nx];
double* x=new double [nx];
double* u0=new double [nx];

dx=L/(nx -1);
dt=courantNo*dx/c; // c*dt/dx <=1 courant condition , otherwise solution will become unstable

u0=IC(nx,dx);
#pragma omp parallel 
for(int i=0;i<nx;i++)
{
x[i]=i*dx;

}
std::ofstream write_ic("wave.dat");
write_ic.precision(10);
write_ic.setf(std::ios::scientific);
assert(write_ic.is_open());
for(int i=0; i<nx;i++)
{

write_ic<<x[i]<<" "<<u0[i]<<"\n";


}
write_ic.close();

u=findiff(u0,dx,dt,c,nx,nt);
std::ofstream sol("solution.dat");
sol.precision(10);
sol.setf(std::ios::scientific);
assert(sol.is_open());
for(int i=0; i<nx;i++)
{
sol<<x[i]<<" "<<u[i]<<"\n";

}
sol.close();


delete [] u;
delete [] x;
delete [] u0;

return 0;
}

double* IC(int nx, double dx)
{double* mat=new double [nx];
double z=0;
#pragma omp parallel for
	for(int i=0; i<nx;i++)
	{
		z=i*dx;
		if((z>0.5) && (z<1.0))
		{
			mat[i]=2.0;


		}
		else
		{

		mat[i]=1;

		}
		

	}
return mat;

}

double* findiff(double* u, double dx, double dt, double c, int nx, int nt)
{
double* mat=new double [nx];

#pragma openmp parallel for
for(int i=0;i<nt;i++)
{
	for(int k=0;k<nx;k++)
	{
		mat[k]=u[k];

	}

	for(int j=1;j<nx;j++)
	{

		u[j] = mat[j] - c*dt/dx*(mat[j] - mat[j-1]);
	//	u[j] = mat[j] - (c*dt/(2*dx))*(mat[j] - mat[j-2]);
		std::cout<<"u["<<j<<"] =\t"<<u[j]<<"\t mat["<<j<<"] =\t"<<mat[j]<<std::endl;

	}



}



return u;

}

