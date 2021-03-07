#Marcos Cerdán Amat 20518142-A
set terminal png
set output "quickSort.png"

set xlabel "size of arrays"
set ylabel "Million of program steps"
set xtics ("2¹⁵" 32768, "2²º" 1048576, "2²¹" 2097152)

set title  "QuickSort"

#Grafica 1
plot "qs-vs-hs.Msteps" using 1:2 with lines title "random arrays",\
     "qs-vs-hs.Msteps" using 1:4 with lines title "sorted arrays",\
     "qs-vs-hs.Msteps" using 1:6 with lines title "reverse sorted arrays"


set output "heapSort.png"
set title "HeapShort"

#Grafica 2
plot "qs-vs-hs.Msteps" using 1:3 with lines title "random arrays",\
     "qs-vs-hs.Msteps" using 1:5 with lines title "sorted arrays",\
     "qs-vs-hs.Msteps" using 1:7 with lines title "reverse sorted arrays"

set output "qs-vs-hs-RA.png"
set title "QuickSort versus HeapShort (random arrays)"

    y(x)=a*x*log(x) + b 
    fitFunction="fitting Quicksort time values"
    fit y(x) "qs-vs-hs.Msteps" using 1:2 via a,b

    y2(x)=a*x*log(x) + b
    fitFunction2="fitting HeapShort time values"
    fit y2(x) "qs-vs-hs.Msteps" using 1:3 via a,b

#Grafica 3
plot "qs-vs-hs.Msteps" using 1:2 with lines title "QuickSort",\
     "qs-vs-hs.Msteps" using 1:3 with lines title "HeapShort",\
     y(x) title fitFunction,\
     y2(x) title fitFunction2

set output "qs-vs-hs-SA.png"
set title "Quicksort versus HeapShort (sorted arrays)"

    y3(x)=a*x*log(x) + b
    fitFunction3="fitting Quicksort time values"
    fit y3(x) "qs-vs-hs.Msteps" using 1:4 via a,b

    y4(x)=a*x*log(x) + b
    fitFunction4="fitting HeapShort time values"
    fit y4(x) "qs-vs-hs.Msteps" using 1:5 via a,b

#Grafica 4
plot "qs-vs-hs.Msteps" using 1:4 with lines title "QuickSort",\
     "qs-vs-hs.Msteps" using 1:5 with lines title "HeapShort",\
     y3(x) title fitFunction3,\
     y4(x) title fitFunction4

set output "qs-vs-hs-RSA.png"
set title "Quicksort versus HeapShort (reverse-sorted arrays)"

    y5(x)=a*x*log(x) + b
    fitFunction5="fitting Quicksort time values"
    fit y5(x) "qs-vs-hs.Msteps" using 1:6 via a,b

    y6(x)=a*x*log(x) + b
    fitFunction6="fitting HeapShort time values"
    fit y6(x) "qs-vs-hs.Msteps" using 1:7 via a,b

#Grafica 5
plot "qs-vs-hs.Msteps" using 1:6 with lines title "QuickSort",\
     "qs-vs-hs.Msteps" using 1:7 with lines title "HeapShort",\
     y5(x) title fitFunction5,\
     y6(x) title fitFunction6


