CC = g++
FLAG = -O2 -g -Wall -DDEBUG -DEXITA
DIRLIB = lib/
DIRINCLUDE = include/
OBJ = TB.o const.o coordin.o\
	  readin.o lattice.o

tb   : $(OBJ)
	$(CC) -o tb $(OBJ) -larmadillo -lgfortran -lpthread
readin.o : $(DIRLIB)readin.cpp
	$(CC) $(FLAG) -c $(DIRLIB)readin.cpp
coordin.o : $(DIRLIB)coordin.cpp
	$(CC) $(FLAG) -c $(DIRLIB)coordin.cpp
const.o : $(DIRLIB)const.cpp
	$(CC) $(FLAG) -c $(DIRLIB)const.cpp
lattice.o : $(DIRLIB)lattice.cpp
	$(CC) $(FLAG) -c $(DIRLIB)lattice.cpp
TB.o : TB.cpp
	$(CC) $(FLAG) -c TB.cpp

.PHONY : clean
clean :
	rm $(OBJ)
