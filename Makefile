
ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs)
ROOTGLIBS     = $(shell root-config --glibs)

all:  converter.cc 

converter.o: converter.cc 
	$(CXX) $(CXXFLAGS) -pg -c -g converter.cc  $(ROOTCFLAGS) -lSpectrum 

converter: converter.o
	$(CXX) -pg -o converter converter.o $(ROOTLIBS) $(ROOTGLIBS) -lSpectrum

