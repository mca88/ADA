#Marcos Cerdán Amat 20518142-A
set terminal png
set output "pow2.png"

set xlabel "n"
set ylabel "Recursivas"

set xrange [1:100]
set yrange [0:300]

set title  "Coste función 2^n"

plot "pow2.steps" using 1:2 with lines title "ø = (n)", \
     "pow2.steps" using 1:3 with lines title "ø = (2^n)", \
     "pow2.steps" using 1:4 with lines title "ø = (log(n))"




