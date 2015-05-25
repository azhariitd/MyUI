
CXX = g++
LINKER = g++ -o


LIBS= -lGL -lglut -lSOIL -lm -lfreetype `freetype-config --libs`
CFLAGS = -Wall -g 
INCLUDE = `freetype-config --cflags`
TARGET =  main

SRCDIR = src
OBJDIR = obj
BINDIR = bin

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)




$(TARGET): $(OBJECTS)
	$(CXX) -o  $@ $(LFLAGS) $(OBJECTS) $(LIBS) 
	@echo "Linking complete!"


$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "Compiled "$<" successfully!"



Clean:
	rm bin/*
	rm main
