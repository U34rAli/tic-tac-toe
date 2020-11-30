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

cl /EHsc /Iwindows/include /Iinclude /Iwindows/include/SDL2 /c .\src\app.cpp .\src\context.cpp .\examples\shapes.cpp .\src\SDL_FontCache.c

link /SUBSYSTEM:CONSOLE /LIBPATH:windows\lib\x64 shapes.obj .\context.obj .\app.obj .\SDL_FontCache.obj SDL2.lib SDL2main.lib /NODEFAULTLIB:libcmtd.lib opengl32.lib shell32.lib SDL2_ttf.lib SDL2_image.lib freetype.lib
