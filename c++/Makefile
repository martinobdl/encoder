EXE = main
OBJECTS = Model.o Write_bit.o Compressor.o main.o Decompressor.o Read_bit.o

CXX = g++

CXXFLAGS += -std=c++11 -Wall

all: $(EXE)
Model.o: Model.h Interval.h
Write_bit.o: Write_bit.h
Read_bit.o: Read_bit.h
Compressor.o: Compressor.h Model.h Interval.h Write_bit.h
Decompressor.o: Decompressor.h Model.h Interval.h Read_bit.h


$(EXE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@


.PHONY: all clean distclean
clean:
	$(RM) *.o
distclean: clean
	$(RM) $(EXE)
