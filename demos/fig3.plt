set term postscript eps enhanced color 		#Output Format monochrome
set output "delete.eps"									#Output File
set size .9,.9										#Canvas Size
#set pointsize 1.75										#Pointer Size (on lines)
#set key font ",18"
#set tics font ",17"
#set xlabel font ",18"
#set ylabel font ",18"

#set for [i=1:8] linetype i dashtype i

#set multiplot layout 1,2								#Grid layout for multiplot

#1st Plot in Grid
#set size .46,.45										#Set Size of plot
#set log y
set xtics ("0" 0, "1" 1, "2" 2, "3" 3)
#set xtics 1.4e-5,.35e-5,2.55e-5
#set ytics ("-1.00e-07" -1.0e-07, "-0.75e-07" -.75e-7, "-0.50e-07" -0.5e-07, "-0.25e-07" -.25e-7, "0" 0, "0.25e-07" .25e-7, "0.50e-07" .50e-07, "0.75e-07" .75e-7, "1.00e-07" 1.0e-07)
#set yrange [-1:1.5]
#set xrange [2.5:6]
set zlabel "temperature"
set xlabel "radius points"
set ylabel "time"
splot 'delete.txt' matrix with lines notitle

#plot \
#"delete.txt" using 2:3 title "1" with lines lt 1 lw 3 lc "red", \
#"delete.txt" using 2:4 title "2" with lines lt 3 lw 5 lc "blue", \
#"delete.txt" using 2:5 title "2" with lines lt 3 lw 5 lc "green", \
#"delete.txt" using 2:6 title "2" with lines lt 3 lw 5 lc "yellow"

#unset multiplot 
