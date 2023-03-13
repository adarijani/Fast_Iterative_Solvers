#include <iostream>
#include <cmath>
#include <fstream>
#include "multigrid.hpp"

int main(int argc, char const *argv[]) {
  double r_knot=0.0;
  int n=atoi(argv[1]);
  int M=atoi(argv[2]);
  int nu1=atoi(argv[3]);
  int nu2=atoi(argv[4]);
  int gamma=2;

  std::cout << "***************************" << '\n';
  std::cout << "config is:" << '\n';
  std::cout << "n=" << n << ",M=" << M << ",nu1=" << nu1;
  std::cout << ",nu2=" << nu2 << ",gamma=" << gamma << '\n';
  int N=pow(2,n);
  int Nc=pow(2,n-1);
  double h=1./(double)(N);
  double h2=h*h;

  double** u=AllocateMemory(N+1,N+1);
  double** f=AllocateMemory(N+1,N+1);

  for (size_t i = 0; i < N+1; i++) {
    for (size_t j = 0; j < N+1; j++) {
      f[i][j]=myf(i,j,h);
      if (abs(f[i][j])>r_knot) {
        r_knot=abs(f[i][j]);
      }
    }
  }

  std::ofstream write("data");
  for (size_t m = 0; m < M; m++) {
    Multigrid(u,f,N,gamma,nu1,nu2);
    double maxres=0.0;
    double resij=0.0;
    for (size_t i = 1; i < N; i++) {
      for (size_t j = 1; j < N; j++) {
        resij=f[i][j]+(u[i+1][j]-2*u[i][j]+u[i-1][j]+u[i][j+1]-2*u[i][j]+u[i][j-1])/h2;
        if (abs(resij)>maxres) {
          maxres=abs(resij);
        }
      }
    }
    maxres=maxres/r_knot;
    write<<m<<"\t"<<maxres<<"\n";
  }
  write.close();
  std::cout << "***************************" << '\n';
  std::cout << "data are written to file." << '\n';
  std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$" << '\n';
  DeallocateMemory(u,N+1,N+1);
  DeallocateMemory(f,N+1,N+1);
  return 0;
}
