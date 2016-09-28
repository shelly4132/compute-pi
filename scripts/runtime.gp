reset
set ylabel 'time(sec)'
set xlabel 'N'
set style fill solid
set title 'perfomance comparison'
set term png enhanced font 'Verdana,10'
set output 'runtime.png'
set logscale x 2
set datafile separator ","

plot "result_clock_gettime.csv" using 1:2 smooth csplines title 'baseline', \
'' using 1:3 smooth csplines title 'openMP(2)', \
'' using 1:4 smooth csplines title 'openMp(4)', \
'' using 1:5 smooth csplines title 'AVX', \
'' using 1:6 smooth csplines title 'AVX_unroll'
