make -C MacosX
rcc -o Qt/windows_resources.rcc -binary Qt/windows_resources.qrc
rcc -o Qt/unix_resources.rcc -binary Qt/unix_resources.qrc
qmake Qt
make
