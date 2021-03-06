LAB = lab2b
ID = 205171726
OUTPUT = lab2b_list.csv
GRAPHS = lab2b_1.png lab2b_2.png lab2b_3.png lab2b_4.png lab2b_5.png
SCRIPTS = lab2b_list.gp
TARBALL=$(LAB)-$(ID).tar.gz

build: lab2_list.c SortedList.c
	gcc -Wall -Wextra -pthread -lprofiler -g -O0 lab2_list.c SortedList.c -o lab2_list

test_list: lab2_list
	@./lab2_list --threads=12 --iterations=32

test_list_y: lab2_list
	@./lab2_list --threads=12 --iterations=32 --yield=idl

test_list_m_y:
	@./lab2_list --threads=12 --iterations=32 --yield=idl --sync=m

test_list_s_y:
	@./lab2_list --threads=12 --iterations=32 --yield=idl --sync=s

test_should_succeed:
	-@./lab2_list --threads=1 --iterations=10 --yield=id --lists=4 --sync=s
	-@./lab2_list --threads=1 --iterations=20 --yield=id --lists=4 --sync=s
	-@./lab2_list --threads=1 --iterations=40 --yield=id --lists=4 --sync=s
	-@./lab2_list --threads=1 --iterations=80 --yield=id --lists=4 --sync=s
	-@./lab2_list --threads=4 --iterations=10 --yield=id --lists=4 --sync=s
	-@./lab2_list --threads=4 --iterations=20 --yield=id --lists=4 --sync=s
	-@./lab2_list --threads=4 --iterations=40 --yield=id --lists=4 --sync=s
	-@./lab2_list --threads=4 --iterations=80 --yield=id --lists=4 --sync=s
	-@./lab2_list --threads=8 --iterations=10 --yield=id --lists=4 --sync=s
	-@./lab2_list --threads=8 --iterations=20 --yield=id --lists=4 --sync=s
	-@./lab2_list --threads=8 --iterations=40 --yield=id --lists=4 --sync=s
	-@./lab2_list --threads=8 --iterations=80 --yield=id --lists=4 --sync=s
	-@./lab2_list --threads=12 --iterations=10 --yield=id --lists=4 --sync=s
	-@./lab2_list --threads=12 --iterations=20 --yield=id --lists=4 --sync=s
	-@./lab2_list --threads=12 --iterations=40 --yield=id --lists=4 --sync=s
	-@./lab2_list --threads=12 --iterations=80 --yield=id --lists=4 --sync=s
	-@./lab2_list --threads=16 --iterations=10 --yield=id --lists=4 --sync=s
	-@./lab2_list --threads=16 --iterations=20 --yield=id --lists=4 --sync=s
	-@./lab2_list --threads=16 --iterations=40 --yield=id --lists=4 --sync=s
	-@./lab2_list --threads=16 --iterations=80 --yield=id --lists=4 --sync=s
	-@./lab2_list --threads=1 --iterations=10 --yield=id --lists=4 --sync=m
	-@./lab2_list --threads=1 --iterations=20 --yield=id --lists=4 --sync=m
	-@./lab2_list --threads=1 --iterations=40 --yield=id --lists=4 --sync=m
	-@./lab2_list --threads=1 --iterations=80 --yield=id --lists=4 --sync=m
	-@./lab2_list --threads=4 --iterations=10 --yield=id --lists=4 --sync=m
	-@./lab2_list --threads=4 --iterations=20 --yield=id --lists=4 --sync=m
	-@./lab2_list --threads=4 --iterations=40 --yield=id --lists=4 --sync=m
	-@./lab2_list --threads=4 --iterations=80 --yield=id --lists=4 --sync=m
	-@./lab2_list --threads=8 --iterations=10 --yield=id --lists=4 --sync=m
	-@./lab2_list --threads=8 --iterations=20 --yield=id --lists=4 --sync=m
	-@./lab2_list --threads=8 --iterations=40 --yield=id --lists=4 --sync=m
	-@./lab2_list --threads=8 --iterations=80 --yield=id --lists=4 --sync=m
	-@./lab2_list --threads=12 --iterations=10 --yield=id --lists=4 --sync=m
	-@./lab2_list --threads=12 --iterations=20 --yield=id --lists=4 --sync=m
	-@./lab2_list --threads=12 --iterations=40 --yield=id --lists=4 --sync=m
	-@./lab2_list --threads=12 --iterations=80 --yield=id --lists=4 --sync=m
	-@./lab2_list --threads=16 --iterations=10 --yield=id --lists=4 --sync=m
	-@./lab2_list --threads=16 --iterations=20 --yield=id --lists=4 --sync=m
	-@./lab2_list --threads=16 --iterations=40 --yield=id --lists=4 --sync=m
	-@./lab2_list --threads=16 --iterations=80 --yield=id --lists=4 --sync=m

profile: build
	-@echo ""
	-@echo "Making profile..."
	-@env CPUPROFILE=profileInfo.prof ./lab2_list --threads=12 --iterations=1000 --sync=s
	-@pprof --text ./lab2_list profileInfo.prof > profile.out
	-@rm -f profileInfo.prof

tests: build
	-@echo ""
	-@echo "Running tests and making graphs... (May take a while)"
	-@rm -f lab2b_list.csv
	-@touch lab2b_list.csv
	-@./lab2_list --threads=1 --iterations=1000 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=2 --iterations=1000 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=4 --iterations=1000 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=8 --iterations=1000 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=12 --iterations=1000 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=16 --iterations=1000 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=24 --iterations=1000 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=1 --iterations=1000 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=2 --iterations=1000 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=4 --iterations=1000 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=8 --iterations=1000 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=12 --iterations=1000 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=16 --iterations=1000 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=24 --iterations=1000 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=1 --iterations=1 --yield=id --lists=4 >> lab2b_list.csv
	-@./lab2_list --threads=1 --iterations=2 --yield=id --lists=4 >> lab2b_list.csv
	-@./lab2_list --threads=1 --iterations=4 --yield=id --lists=4 >> lab2b_list.csv
	-@./lab2_list --threads=1 --iterations=8 --yield=id --lists=4 >> lab2b_list.csv
	-@./lab2_list --threads=1 --iterations=16 --yield=id --lists=4 >> lab2b_list.csv
	-@./lab2_list --threads=4 --iterations=1 --yield=id --lists=4 >> lab2b_list.csv
	-@./lab2_list --threads=4 --iterations=2 --yield=id --lists=4 >> lab2b_list.csv
	-@./lab2_list --threads=4 --iterations=4 --yield=id --lists=4 >> lab2b_list.csv
	-@./lab2_list --threads=4 --iterations=8 --yield=id --lists=4 >> lab2b_list.csv
	-@./lab2_list --threads=4 --iterations=16 --yield=id --lists=4 >> lab2b_list.csv
	-@./lab2_list --threads=8 --iterations=1 --yield=id --lists=4 >> lab2b_list.csv
	-@./lab2_list --threads=8 --iterations=2 --yield=id --lists=4 >> lab2b_list.csv
	-@./lab2_list --threads=8 --iterations=4 --yield=id --lists=4 >> lab2b_list.csv
	-@./lab2_list --threads=8 --iterations=8 --yield=id --lists=4 >> lab2b_list.csv
	-@./lab2_list --threads=8 --iterations=16 --yield=id --lists=4 >> lab2b_list.csv
	-@./lab2_list --threads=12 --iterations=1 --yield=id --lists=4 >> lab2b_list.csv
	-@./lab2_list --threads=12 --iterations=2 --yield=id --lists=4 >> lab2b_list.csv
	-@./lab2_list --threads=12 --iterations=4 --yield=id --lists=4 >> lab2b_list.csv
	-@./lab2_list --threads=12 --iterations=8 --yield=id --lists=4 >> lab2b_list.csv
	-@./lab2_list --threads=12 --iterations=16 --yield=id --lists=4 >> lab2b_list.csv
	-@./lab2_list --threads=16 --iterations=1 --yield=id --lists=4 >> lab2b_list.csv
	-@./lab2_list --threads=16 --iterations=2 --yield=id --lists=4 >> lab2b_list.csv
	-@./lab2_list --threads=16 --iterations=4 --yield=id --lists=4 >> lab2b_list.csv
	-@./lab2_list --threads=16 --iterations=8 --yield=id --lists=4 >> lab2b_list.csv
	-@./lab2_list --threads=16 --iterations=16 --yield=id --lists=4 >> lab2b_list.csv
	-@./lab2_list --threads=1 --iterations=10 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=1 --iterations=20 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=1 --iterations=40 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=1 --iterations=80 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=4 --iterations=10 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=4 --iterations=20 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=4 --iterations=40 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=4 --iterations=80 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=8 --iterations=10 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=8 --iterations=20 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=8 --iterations=40 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=8 --iterations=80 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=12 --iterations=10 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=12 --iterations=20 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=12 --iterations=40 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=12 --iterations=80 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=16 --iterations=10 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=16 --iterations=20 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=16 --iterations=40 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=16 --iterations=80 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=1 --iterations=10 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=1 --iterations=20 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=1 --iterations=40 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=1 --iterations=80 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=4 --iterations=10 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=4 --iterations=20 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=4 --iterations=40 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=4 --iterations=80 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=8 --iterations=10 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=8 --iterations=20 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=8 --iterations=40 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=8 --iterations=80 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=12 --iterations=10 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=12 --iterations=20 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=12 --iterations=40 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=12 --iterations=80 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=16 --iterations=10 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=16 --iterations=20 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=16 --iterations=40 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=16 --iterations=80 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=1 --iterations=1000 --lists=4 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=2 --iterations=1000 --lists=4 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=4 --iterations=1000 --lists=4 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=8 --iterations=1000 --lists=4 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=12 --iterations=1000 --lists=4 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=1 --iterations=1000 --lists=8 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=2 --iterations=1000 --lists=8 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=4 --iterations=1000 --lists=8 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=8 --iterations=1000 --lists=8 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=12 --iterations=1000 --lists=8 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=1 --iterations=1000 --lists=16 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=2 --iterations=1000 --lists=16 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=4 --iterations=1000 --lists=16 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=8 --iterations=1000 --lists=16 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=12 --iterations=1000 --lists=16 --sync=m >> lab2b_list.csv
	-@./lab2_list --threads=1 --iterations=1000 --lists=4 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=2 --iterations=1000 --lists=4 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=4 --iterations=1000 --lists=4 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=8 --iterations=1000 --lists=4 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=12 --iterations=1000 --lists=4 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=1 --iterations=1000 --lists=8 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=2 --iterations=1000 --lists=8 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=4 --iterations=1000 --lists=8 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=8 --iterations=1000 --lists=8 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=12 --iterations=1000 --lists=8 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=1 --iterations=1000 --lists=16 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=2 --iterations=1000 --lists=16 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=4 --iterations=1000 --lists=16 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=8 --iterations=1000 --lists=16 --sync=s >> lab2b_list.csv
	-@./lab2_list --threads=12 --iterations=1000 --lists=16 --sync=s >> lab2b_list.csv

graphs: tests lab2b_list.gp
	@gnuplot lab2b_list.gp

clean:
	@rm -f lab2_list
	@rm -f lab2b-205171726.tar.gz

dist: clean profile graphs README
	-@tar -cvzf $(TARBALL) README Makefile *.c *.h $(OUTPUT) $(GRAPHS) $(SCRIPTS) profile.out
