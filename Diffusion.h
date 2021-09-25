#ifndef DIFFUSIONHEADERDEF
#define DIFFUSIONHEADERDEF

class Diffusion{
double L;
double courant;
double nu;
double delx;
double delt;
int nx;
int nt;

	public:
		Diffusion();
		Diffusion(double,double,double,int,int);
		void GetVal(int*,int*);
		void PrintVal();
		double* initCond(double*);
		double* XVector(double*);
		double* FinDiff(double*);
		void WriteSol(double*,double*,std::string);
		


};




#endif
