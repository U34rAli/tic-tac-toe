# OSX


clang++ -L./osx/lib/ -lSDL2 -I./osx/include/ main.cpp -framework OpenGL


# Windows

cl /EHsc /Iwindows\include /c main.cpp

and then link with:

link /SUBSYSTEM:CONSOLE /LIBPATH:windows\lib\x64 main.obj SDL2.lib SDL2main.lib /NODEFAULTLIB:libcmtd.lib opengl32.lib shell32.lib