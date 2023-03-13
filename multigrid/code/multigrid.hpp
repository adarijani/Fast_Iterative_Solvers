#ifndef MULTIGRIDHEADERDEFF
#define MULTIGRIDHEADERDEFF

double** AllocateMemory(int m,int n);
void DeallocateMemory(double** A,int m,int n);
double myf(int i, int j,double h);
double analytical(int i, int j,double h);
void smoother(double** u,double** f,int N,int nu);
double** Restr(double** u,int N);
double** Prolong(double** uc,int Nc);
void Multigrid(double** u,double** f,int N,int gamma,int nu1,int nu2);

#endif
