make main
declare -i n=30
./main 4 "$n" 1 1
mv data n4nu11nu21
echo n4nu11nu21 | python plot.py
echo "plot is generated for n4nu11nu21"
./main 4 "$n" 1 2
mv data n4nu11nu22
echo n4nu11nu22 | python plot.py
echo "plot is generated for n4nu11nu22"
./main 4 "$n" 2 1
mv data n4nu12nu21
echo n4nu12nu21 | python plot.py
echo "plot is generated for n4nu12nu21"
./main 4 "$n" 2 2
mv data n4nu12nu22
echo n4nu12nu22 | python plot.py
echo "plot is generated for n4nu12nu22"
./main 7 "$n" 1 1
mv data n7nu11nu21
echo n7nu11nu21 | python plot.py
echo "plot is generated for n7nu11nu21"
./main 7 "$n" 1 2
mv data n7nu11nu22
echo n7nu11nu22 | python plot.py
echo "plot is generated for n7nu11nu22"
./main 7 "$n" 2 1
mv data n7nu12nu21
echo n7nu12nu21 | python plot.py
echo "plot is generated for n7nu12nu21"
./main 7 "$n" 2 2
mv data n7nu12nu22
echo n7nu12nu22 | python plot.py
echo "plot is generated for n7nu12nu22"
make clean
