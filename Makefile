#------------------------------------------------------
# Makefile for C/C++ Program
#------------------------------------------------------
# Target: a.out
# Authour: H. Watanabe
#------------------------------------------------------

#TARGET=baseline_throughput
#TARGET=prediction_dontcache_throughput
TARGET=clock_sim

#------------------------------------------------------
# Default Parameters
#------------------------------------------------------

CC=g++
#OPT=-w
#OPT=-Wall -O2
OPT=-Wall -O2 -DSTREAM_SIZE_PREDICTION
#OPT=-Wall -ggdb -pg -O0 -fno-inline
#OPT=-Wall -m32
#OPT=-Wall -g -ggdb -O0 -fno-inline
#OPT=-Wall -g -ggdb -pg
#OPT=-Wall -g
INC=-I./ -I/usr/local/boost_1_69_0/include/boost
LIB=

#------------------------------------------------------
# Compile Option
#------------------------------------------------------

-include makefile.opt

#------------------------------------------------------
# Definition
#------------------------------------------------------

.SUFFIXES:.cpp .hpp .c .o .h

#---
# Source Files
#---

SRC=$(shell ls *.cpp)
HED=$(shell ls *.hpp)
OBJ=$(SRC:.C=.o)

#------------------------------------------------------
# rules
#------------------------------------------------------

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OPT) -o $(TARGET) $(OBJ) $(INC)

.c.o:
	$(CC) $(OPT) -c $< $(INC)
.cc.o:
	$(CC) $(OPT) -c $< $(INC)
.C.o:
	$(CC) $(OPT) -c $< $(INC)
.cpp.o:
	$(CC) $(OPT) -c $< $(INC)

dep:
	g++ -MM -MG $(SRC) >makefile.depend

clean:
	rm -f $(TARGET) $(TARGET).exe
	rm -f *.o *.obj
	rm -f *~ *.~*

tag:
	ctags $(SRC) $(HED)

#--------------------------------------------------
-include makefile.depend
