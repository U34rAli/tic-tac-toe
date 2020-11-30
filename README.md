# OSX

To build the examples simple run:

```
make
```

Then you can run:

```
build/shapes
```

```
build/splat
```

clang++ -std=c++17 -L./osx/lib/ -lSDL2 -lSDL2_ttf -lSDL2_image -lfreetype -lpng -lwebp -ltiff -ljpeg -lbz2 -lz -I./osx/include/ -I./osx/include/SDL2/ -I./include ./SDL_FontCache.o src/context.cpp src/app.cpp examples/splat.cpp -framework OpenGL

We need to build font cache

clang -c -I./osx/include/ -I./osx/include/SDL2/  -I./include src/SDL_FontCache.c

# Windows

cl /EHsc /Iwindows\include /c main.cpp

and then link with:

link /SUBSYSTEM:CONSOLE /LIBPATH:windows\lib\x64 main.obj SDL2.lib SDL2main.lib /NODEFAULTLIB:libcmtd.lib opengl32.lib shell32.lib