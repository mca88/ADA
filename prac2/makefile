#Marcos Cerdán Amat 20518142-A
OPTS = -Wall -O3 -std=c++0x

qs-vs-hs: qs-vs-hs.cc
	g++ ${OPTS} -o qs-vs-hs qs-vs-hs.cc	 

qs-vs-hs.Msteps: qs-vs-hs
	./qs-vs-hs > qs-vs-hs.Msteps

graphs: qs-vs-hs.Msteps qs-vs-hs.gnuplot
	gnuplot qs-vs-hs.gnuplot

all: qs-vs-hs qs-vs-hs.Msteps graphs

tar: qs-vs-hs.cc qs-vs-hs.gnuplot makefile
	tar cvfz 20518142-A.tar.gz qs-vs-hs.cc qs-vs-hs.gnuplot makefile

clean: 
	rm qs-vs-hs qs-vs-hs.Msteps quickSort.png heapSort.png qs-vs-hs-RA.png qs-vs-hs-SA.png qs-vs-hs-RSA.png fit.log *~