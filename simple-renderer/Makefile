FLTK_INCLUDE = `fltk-config --cxxflags`
FLTK_LIBS = `fltk-config --ldflags`

INCLUDE  =  $(FLTK_INCLUDE) -I./math/numerical -I./math/euclidean -I./renderer -I./structures -I.
CXXFLAGS = -g -Wall $(INCLUDE) 
LIBS = $(FLTK_LIBS) 

OBJS =  raylite.o \
        ./math/euclidean/euclidean.o \
        ./math/euclidean/transformation.o \
        ./renderer/camera.o \
        ./renderer/engine.o \
        ./renderer/object.o \
        ./renderer/parser.o \
        ./renderer/renderer.o \
        ./renderer/triangle.o \
        ./renderer/viewport.o

TARGET =	raylite

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
