EXE = main
OBJECTS = Model.o Interval.h Bitio.o Compressor.o Decompressor.o main.o

CXXFLAGS += -std=c++11 -Wall

all: $(EXE)
Model.o: Model.h Interval.h
Interval.o: Interval.h
Bitio.o: Bitio.h
Compressor.o: Compressor.h Model.h Interval.h Bitio.h
Decompressor.o: Decompressor.h Model.h Interval.h Bitio.h


$(EXE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@


.PHONY: all clean distclean
clean:
	$(RM) *.o
distclean: clean
	$(RM) $(EXE)
