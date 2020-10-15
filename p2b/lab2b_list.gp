#! /usr/bin/gnuplot
#
# purpose:
#	 generate data reduction graphs for the multi-threaded list project
#
# input: lab2b_list.csv
#	1. test name
#	2. # threads
#	3. # iterations per thread
#	4. # lists
#	5. # operations performed (threads x iterations x (ins + lookup + delete))
#	6. run time (ns)
#	7. run time per operation (ns)
#
# output:
#	lab2_list-1.png ... cost per operation vs threads and iterations
#	lab2_list-2.png ... threads and iterations that run (un-protected) w/o failure
#	lab2_list-3.png ... threads and iterations that run (protected) w/o failure
#	lab2_list-4.png ... cost per operation vs number of threads
#
# Note:
#	Managing data is simplified by keeping all of the results in a single
#	file.  But this means that the individual graphing commands have to
#	grep to select only the data they want.
#
#	Early in your implementation, you will not have data for all of the
#	tests, and the later sections may generate errors for missing data.
#

# general plot parameters
set terminal png
set datafile separator ","

# how many threads/iterations we can run without failure (w/o yielding)
set title "List-1: Operations per Second vs Number of Threads"
set xlabel "Threads"
set logscale x 2
set ylabel "Operations per second"
#set logscale y 10
set output 'lab2b_1.png'

plot \
     "< grep 'list-none-m,[0-9]*,1000,1,' lab2b_list.csv" using ($2):(1000000000)/($7) \
	title 'Mutex' with linespoints lc rgb 'red', \
     "< grep 'list-none-s,[0-9]*,1000,1,' lab2b_list.csv" using ($2):(1000000000)/($7) \
	title 'Spin-lock' with linespoints lc rgb 'green'
	
set title "List-2: Wait For Lock Time (Mutex) vs Number of Threads"
set xlabel "Threads"
set logscale x 2
set ylabel "Time"
#set logscale y 10
set output 'lab2b_2.png'

plot \
     "< grep 'list-none-m,[0-9]*,1000,1,' lab2b_list.csv" using ($2):($8) \
	title 'avg-wait-time' with linespoints lc rgb 'red', \
	 "< grep 'list-none-m,[0-9]*,1000,1,' lab2b_list.csv" using ($2):($7) \
	title 'avg-operation-time' with linespoints lc rgb 'blue'

set title "List-3: Threads and Iterations that run without failure"
set xlabel "Threads"
set logscale x 2
set xrange [0.75:]
set ylabel "Successful Iterations"
set logscale y 10
set output 'lab2b_3.png'
# note that unsuccessful runs should have produced no output
plot \
     "< grep 'list-id-none' lab2b_list.csv" using ($2):($3) \
	title 'no protection' with points lc rgb 'green', \
	 "< grep 'list-id-m' lab2b_list.csv" using ($2):($3) \
	with points lc rgb "blue" ps 2 title "mutex", \
	 "< grep 'list-id-s' lab2b_list.csv" using ($2):($3) \
	with points lc rgb "red" title "spin lock"
	
set title "List-4: Throughput vs Number of Threads (for different number of lists) With Mutex"
set xlabel "Threads"
set logscale x 2
set ylabel "Operations per second"
#set logscale y 10
set output 'lab2b_4.png'

# grep out only single threaded, un-protected, non-yield results
plot \
     "< grep 'list-none-m,[0-9]*,1000,1,' lab2b_list.csv" using ($2):(1000000000)/($7) \
	title '1 list' with linespoints lc rgb 'red', \
     "< grep 'list-none-m,[0-9]*,1000,4' lab2b_list.csv" using ($2):(1000000000)/($7) \
	title '4 list' with linespoints lc rgb 'green', \
	 "< grep 'list-none-m,[0-9]*,1000,8' lab2b_list.csv" using ($2):(1000000000)/($7) \
	title '8 list' with linespoints lc rgb 'blue', \
	 "< grep 'list-none-m,[0-9]*,1000,16' lab2b_list.csv" using ($2):(1000000000)/($7) \
	title '16 list' with linespoints lc rgb 'yellow'
	
set title "List-5: Throughput vs Number of Threads (for different number of lists) With Spin Lock"
set xlabel "Threads"
set logscale x 2
set ylabel "Operations per second"
#set logscale y 10
set output 'lab2b_5.png'

# grep out only single threaded, un-protected, non-yield results
plot \
     "< grep 'list-none-s,[0-9]*,1000,1,' lab2b_list.csv" using ($2):(1000000000)/($7) \
	title '1 list' with linespoints lc rgb 'red', \
     "< grep 'list-none-s,[0-9]*,1000,4' lab2b_list.csv" using ($2):(1000000000)/($7) \
	title '4 list' with linespoints lc rgb 'green', \
	 "< grep 'list-none-s,[0-9]*,1000,8' lab2b_list.csv" using ($2):(1000000000)/($7) \
	title '8 list' with linespoints lc rgb 'blue', \
	 "< grep 'list-none-s,[0-9]*,1000,16' lab2b_list.csv" using ($2):(1000000000)/($7) \
	title '16 list' with linespoints lc rgb 'yellow'
