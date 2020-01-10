msbuild .\Windows\Gbmu.sln
rcc -o Qt/resources.rcc -binary Qt/windows_resources.qrc
qmake Qt
mingw32-make.exe
mingw32-make.exe clean
Remove-Item Makefile
Remove-Item .qmake.stash
pause