msbuild .\Windows\Gbmu.sln
qmake Qt
mingw32-make.exe
mingw32-make.exe clean
Remove-Item Makefile
Remove-Item .qmake.stash