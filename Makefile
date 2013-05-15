CC=clang++
# ARCH=-arch i386 
ARCH=
DEBUGFLAGS=-g
DEFINES=-D_LARGE_FILES -D__WXDEBUG__ -DHAVE_TYPE_TRAITS
CFLAGS=-std=c++11 -stdlib=libc++ -Wall -fmessage-length=0 $(ARCH) $(DEBUGFLAGS) $(DEFINES)
#WXCPPFLAGS=-I/usr/local/Cellar/wxmac/2.9.4.0/lib/wx/include/osx_cocoa-unicode-2.9 -I/usr/local/Cellar/wxmac/2.9.4.0/include/wx-2.9 -I/usr/local/include/wx-2.9 -DHAVE_TYPE_TRAITS
WXCPPFLAGS=$(shell wx-config --cxxflags --unicode --debug)
LDFLAGS=-stdlib=libc++ $(ARCH) $(DEBUGFLAGS)
WXLDFLAGS=$(shell wx-config --libs --unicode --debug)
SOURCES=Source/biosim_app.cpp Source/biosim_gui.cpp Source/biosim_gui_impl.cpp Source/creature.cpp Source/image.cpp Source/model.cpp Source/sim_area_widget.cpp Source/world_map.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=sim

goal : all

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(WXCPPFLAGS) $(LDFLAGS) $(WXLDFLAGS) $(SOURCES) -o $(EXECUTABLE)

all: $(SOURCES) $(EXECUTABLE) mat 
	mv $(EXECUTABLE)* Build
clean : 
	rm -rf $(EXECUTABLE)* $(OBJECTS) ./Build/*

#$(EXECUTABLE): $(OBJECTS) 
old:
	$(CC) $(LDFLAGS) $(WXLDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $(WXCPPFLAGS) $< -o $@

mat :
	mkdir -p ./Build
	cp -R ./Material/* ./Build

