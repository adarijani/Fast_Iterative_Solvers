#include "multigrid.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <cassert>




double** AllocateMemory(int m,int n){
  double** A;
  A=new double* [m];
  for (size_t i = 0; i < m; i++) {
    A[i]=new double [n];
  }
  for (size_t i = 0; i < m; i++) {
    for (size_t j = 0; j < n; j++) {
      A[i][j]=0.0;
    }
  }
  return A;
}

void DeallocateMemory(double** A,int m,int n){
  for (size_t i = 0; i < m; i++) {
    delete[] A[i];
  }
  delete[] A;
}

double myf(int i, int j,double h){
    return 8.*M_PI*M_PI*sin(2.*M_PI*h*i)*sin(2.*M_PI*h*j);
}

double analytical(int i, int j,double h){
    return sin(2*M_PI*h*i)*sin(2*M_PI*h*j);
}

void smoother(double** u,double** f,int N,int nu){
    double h=1.0/double(N);
    double h2=h*h;
    for(int k=0;k<nu;k++){
        for(int i=1;i<N;i++){
            for(int j=1;j<N;j++){
               u[i][j]=0.25*(h2*f[i][j]+u[i-1][j]+u[i][j-1]+u[i][j+1]+u[i+1][j]);
            }
        }
    }
}

double** Restr(double** u,int N){
    int Nc=N/2;
    double** uc=AllocateMemory(Nc+1,Nc+1);
    for(int i=1;i<Nc;i++){
        int ii=2*i;
        for(int j=1;j<Nc;j++){
            int jj=2*j;
            uc[i][j]=(1.0/16.0)*(u[ii-1][jj-1]+2*u[ii][jj-1]+u[ii+1][jj-1]+2*u[ii-1][jj]+4*u[ii][jj]+2*u[ii+1][jj]+u[ii-1][jj+1]+2*u[ii][jj+1]+u[ii+1][jj+1]);
        }
    }
    return uc;
}

double** Prolong(double** uc,int Nc){
    int N=2*Nc;
    double** u=AllocateMemory(N+1,N+1);
    for(int i=1;i<Nc;i++){
        int ii=2*i;
        for(int j=1;j<Nc;j++){
            int jj=2*j;
            u[ii][jj]+=uc[i][j];
            u[ii+1][jj]+=0.5*uc[i][j];
            u[ii-1][jj]+=0.5*uc[i][j];
            u[ii][jj+1]+=0.5*uc[i][j];
            u[ii][jj-1]+=0.5*uc[i][j];
            u[ii+1][jj+1]+=0.25*uc[i][j];
            u[ii+1][jj-1]+=0.25*uc[i][j];
            u[ii-1][jj+1]+=0.25*uc[i][j];
            u[ii-1][jj-1]+=0.25*uc[i][j];
        }
    }
    return u;
}

void Multigrid(double** u,double** f,int N,int gamma,int nu1,int nu2){
    int Nc=N/2;
    double h=1.0/(double)(N);
    double h2=h*h;
    double H=1.0/(double)(Nc);
    double H2=H*H;

    smoother(u,f,N,nu1);
    double** r=AllocateMemory(N+1,N+1);
    for(int i=1;i<N;i++){
        for(int j=1;j<N;j++){
            r[i][j]=f[i][j]+(u[i+1][j]-2*u[i][j]+u[i-1][j]+u[i][j+1]-2*u[i][j]+u[i][j-1])/h2;
        }
     }

    double** rc=Restr(r,N+1);
    double** ec=AllocateMemory(Nc+1,Nc+1);
    double** rcm=AllocateMemory(Nc+1,Nc+1);
    for (size_t i = 1; i < Nc; i++) {
      for (size_t j = 1; j < Nc; j++) {
        rcm[i][j]=-1.0*rc[i][j];
      }
    }
    if(Nc==2){
        ec[1][1]=0.25*H2*rcm[1][1];
    }
    else{
        for(int i=0;i<gamma;i++){
            Multigrid(ec,rcm,Nc,gamma,nu1,nu2);
        }
    }
    double** el=Prolong(ec,Nc);
    double** temp=AllocateMemory(N+1,N+1);
    for (size_t i = 1; i < N; i++) {
      for (size_t j = 1; j < N; j++) {
        temp[i][j]=u[i][j]-el[i][j];
      }
    }
    smoother(temp,f,N,nu2);
    for (size_t i = 1; i < N; i++) {
      for (size_t j = 1; j < N; j++) {
        u[i][j]=temp[i][j];
      }
    }
    DeallocateMemory(r,N+1,N+1);
    DeallocateMemory(rc,Nc+1,Nc+1);
    DeallocateMemory(ec,Nc+1,Nc+1);
    DeallocateMemory(rcm,Nc+1,Nc+1);
    DeallocateMemory(el,N+1,N+1);
    DeallocateMemory(temp,N+1,N+1);
}
