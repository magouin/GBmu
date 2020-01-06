make -C MacosX
make clean -C MacosX
qmake Qt
make
make clean 
rm -rf Makefile