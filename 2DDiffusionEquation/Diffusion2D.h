#ifndef DIFFUSION2DHEADERDEF
#define DIFFUSION2DHEADERDEF

#include<string>

class Diffusion2D{
	double alpha=1e-4;
	double Lx=0.01;
	double Ly=0.01;
	double courant=0.25;
	double Th;
	double Tl;
	double dx;
	double dy;
	double dt;
	int nx;
	int ny;
	int nt;
	
	public:
	Diffusion2D(double,double,int,int,int);
	double** InitCond(double**);
	double* XVec(double*);
	double* YVec(double*);
	double** FinDiff(double**);
	void WriteSol(double**,double*,double*,std::string);



};



#endif
