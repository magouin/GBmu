make -C MacosX
rcc -binary Qt/resources.qrc -o Qt/resources.rcc
qmake Qt
make
