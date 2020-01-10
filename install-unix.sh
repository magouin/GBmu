make -C MacosX
rcc -o Qt/unix_resources.rcc -binary Qt/unix_resources.qrc
qmake Qt
make
