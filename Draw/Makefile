
ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs)
ROOTGLIBS     = $(shell root-config --glibs)

all:  Draw.cc 

Draw.o: Draw.cc 
	$(CXX) $(CXXFLAGS) -pg -c -g Draw.cc  $(ROOTCFLAGS) -lSpectrum 

Draw: Draw.o
	$(CXX) -pg -o Draw Draw.o $(ROOTLIBS) $(ROOTGLIBS) -lSpectrum

