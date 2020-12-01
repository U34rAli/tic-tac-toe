CC = clang++
LD = clang++
CPPFLAGS = -std=c++17 -I./osx/include/ -I./osx/include/SDL2/  -I./include
CFLAGS = -I./osx/include/ -I./osx/include/SDL2/  -I./include
LDFLAGS = -L./osx/lib/ -lSDL2 -lSDL2_ttf -lSDL2_image -lfreetype -lpng -lwebp -ltiff -ljpeg -lbz2 -lz -framework OpenGL

ROOTDIR = ./

LIBDIR=S(ROOTDIR)/osx/lib

CP = cp
ECHO = echo

BUILD_DIR = build

C_SOURCES = src/SDL_FontCache.c
CPP_SOURCES = src/app.cpp src.cpp/context.cpp

OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))
vpath %.cpp examples

OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR)
	$(ECHO) compiling $<
	$(CC) -c $(CPPFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(ECHO) compiling $<
	clang -c $(CFLAGS) $< -o $@

all: $(BUILD_DIR)/splat $(BUILD_DIR)/shapes $(BUILD_DIR)/sprite

$(BUILD_DIR)/splat: $(OBJECTS) $(BUILD_DIR)/splat.o Makefile
	$(ECHO) linking $<
	$(CC) -L./osx/lib/ -lSDL2 -lSDL2_ttf -lSDL2_image -lfreetype -lpng -lwebp -ltiff -ljpeg -lbz2 -lz -framework OpenGL -o $@ $(OBJECTS) build/splat.o
	# $(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(BUILD_DIR)/splat.o
	$(ECHO) success

$(BUILD_DIR)/shapes: $(OBJECTS) $(BUILD_DIR)/shapes.o Makefile
	$(ECHO) linking $<
	$(CC) -L./osx/lib/ -lSDL2 -lSDL2_ttf -lSDL2_image -lfreetype -lpng -lwebp -ltiff -ljpeg -lbz2 -lz -framework OpenGL -o $@ $(OBJECTS) build/shapes.o
	# $(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(BUILD_DIR)/splat.o
	$(ECHO) success

$(BUILD_DIR)/sprite: $(OBJECTS) $(BUILD_DIR)/sprite.o Makefile
	$(ECHO) linking $<
	$(CC) -L./osx/lib/ -lSDL2 -lSDL2_ttf -lSDL2_image -lfreetype -lpng -lwebp -ltiff -ljpeg -lbz2 -lz -framework OpenGL -o $@ $(OBJECTS) build/sprite.o
	# $(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(BUILD_DIR)/splat.o
	$(ECHO) success

#######################################
# clean up
#######################################
clean:
	-rm -fR .dep $(BUILD_DIR)

#######################################
# dependencies
#######################################
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)


.PHONY: clean all