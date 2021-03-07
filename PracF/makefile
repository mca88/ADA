#Marcos Cerdán Amat 20518142-A

OPTS = -Wall -O3 -std=c++0x

all: maxsum-bb filter

maxsum-bb: maxsum-bb.cc
	g++ ${OPTS} maxsum-bb.cc -o maxsum-bb

filter: filter.cc
	g++ ${OPTS} filter.cc -o filter

tar: maxsum-bb.cc
	tar cvfz 20518142A.tar.gz maxsum-bb.cc makefile memoria.pdf

clean: 
	rm maxsum-bb filter 