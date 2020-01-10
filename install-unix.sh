make -C MacosX
rcc -o Qt/resources.rcc -binary Qt/unix_resources.qrc
qmake Qt
make
