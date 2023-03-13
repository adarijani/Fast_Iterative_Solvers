multigrid.o:multigrid.cpp multigrid.hpp
	g++ -c -std=c++11 -O3 multigrid.cpp

main.o:main.cpp multigrid.hpp
	g++ -c -std=c++11 -O3 main.cpp

main:multigrid.o main.o
	g++ -o main main.o multigrid.o

clean:
	        rm *.o
