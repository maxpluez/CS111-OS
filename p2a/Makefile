LAB = lab2a
ID = 205171726
OUTPUT = lab2_add.csv lab2_list.csv
GRAPHS = lab2_add-1.png lab2_add-2.png lab2_add-3.png lab2_add-4.png lab2_add-5.png lab2_list-1.png lab2_list-2.png lab2_list-3.png lab2_list-4.png
SCRIPTS = lab2_add.gp lab2_list.gp
TARBALL=$(LAB)-$(ID).tar.gz

build: lab2_add.c lab2_list.c SortedList.c
	gcc -Wall -Wextra -pthread -g -O0 lab2_add.c -o lab2_add
	gcc -Wall -Wextra -pthread -g -O0 lab2_list.c SortedList.c -o lab2_list

test_add: lab2_add
	@./lab2_add --threads=12 --iterations=10000

test_add_y: lab2_add
	@./lab2_add --threads=12 --iterations=10000 --yield

test_add_m: lab2_add
	@./lab2_add --threads=12 --iterations=10000 --sync=m

test_add_s: lab2_add
	@./lab2_add --threads=12 --iterations=1000 --sync=s

test_add_c: lab2_add
	@./lab2_add --threads=12 --iterations=10000 --sync=c

test_add_m_y: lab2_add
	@./lab2_add --threads=12 --iterations=10000 --sync=m --yield

test_add_s_y: lab2_add
	@./lab2_add --threads=12 --iterations=1000 --sync=s --yield

test_add_c_y: lab2_add
	@./lab2_add --threads=12 --iterations=10000 --sync=c --yield

test_list: lab2_list
	@./lab2_list --threads=12 --iterations=32

test_list_y: lab2_list
	@./lab2_list --threads=12 --iterations=32 --yield=idl

test_list_m_y:
	@./lab2_list --threads=12 --iterations=32 --yield=idl --sync=m

test_list_s_y:
	@./lab2_list --threads=12 --iterations=32 --yield=idl --sync=s

tests: build
	@./lab2_add --threads=2 --iterations=10 --yield > lab2_add.csv
	@./lab2_add --threads=2 --iterations=20 --yield >> lab2_add.csv
	@./lab2_add --threads=2 --iterations=40 --yield >> lab2_add.csv
	@./lab2_add --threads=2 --iterations=80 --yield >> lab2_add.csv
	@./lab2_add --threads=2 --iterations=100 --yield >> lab2_add.csv
	@./lab2_add --threads=2 --iterations=1000 --yield >> lab2_add.csv
	@./lab2_add --threads=2 --iterations=10000 --yield >> lab2_add.csv
	@./lab2_add --threads=2 --iterations=100000 --yield >> lab2_add.csv
	@./lab2_add --threads=4 --iterations=10 --yield >> lab2_add.csv
	@./lab2_add --threads=4 --iterations=20 --yield >> lab2_add.csv
	@./lab2_add --threads=4 --iterations=40 --yield >> lab2_add.csv
	@./lab2_add --threads=4 --iterations=80 --yield >> lab2_add.csv
	@./lab2_add --threads=4 --iterations=100 --yield >> lab2_add.csv
	@./lab2_add --threads=4 --iterations=1000 --yield >> lab2_add.csv
	@./lab2_add --threads=4 --iterations=10000 --yield >> lab2_add.csv
	@./lab2_add --threads=4 --iterations=100000 --yield >> lab2_add.csv
	@./lab2_add --threads=8 --iterations=10 --yield >> lab2_add.csv
	@./lab2_add --threads=8 --iterations=20 --yield >> lab2_add.csv
	@./lab2_add --threads=8 --iterations=40 --yield >> lab2_add.csv
	@./lab2_add --threads=8 --iterations=80 --yield >> lab2_add.csv
	@./lab2_add --threads=8 --iterations=100 --yield >> lab2_add.csv
	@./lab2_add --threads=8 --iterations=1000 --yield >> lab2_add.csv
	@./lab2_add --threads=8 --iterations=10000 --yield >> lab2_add.csv
	@./lab2_add --threads=8 --iterations=100000 --yield >> lab2_add.csv
	@./lab2_add --threads=12 --iterations=10 --yield >> lab2_add.csv
	@./lab2_add --threads=12 --iterations=20 --yield >> lab2_add.csv
	@./lab2_add --threads=12 --iterations=40 --yield >> lab2_add.csv
	@./lab2_add --threads=12 --iterations=80 --yield >> lab2_add.csv
	@./lab2_add --threads=12 --iterations=100 --yield >> lab2_add.csv
	@./lab2_add --threads=12 --iterations=1000 --yield >> lab2_add.csv
	@./lab2_add --threads=12 --iterations=10000 --yield >> lab2_add.csv
	@./lab2_add --threads=12 --iterations=100000 --yield >> lab2_add.csv
	@./lab2_add --threads=2 --iterations=100 >> lab2_add.csv
	@./lab2_add --threads=2 --iterations=1000 >> lab2_add.csv
	@./lab2_add --threads=2 --iterations=10000 >> lab2_add.csv
	@./lab2_add --threads=2 --iterations=100000 >> lab2_add.csv
	@./lab2_add --threads=8 --iterations=100 >> lab2_add.csv
	@./lab2_add --threads=8 --iterations=1000 >> lab2_add.csv
	@./lab2_add --threads=8 --iterations=10000 >> lab2_add.csv
	@./lab2_add --threads=8 --iterations=100000 >> lab2_add.csv
	@./lab2_add --threads=1 --iterations=10 >> lab2_add.csv
	@./lab2_add --threads=1 --iterations=20 >> lab2_add.csv
	@./lab2_add --threads=1 --iterations=40 >> lab2_add.csv
	@./lab2_add --threads=1 --iterations=80 >> lab2_add.csv
	@./lab2_add --threads=1 --iterations=100 >> lab2_add.csv
	@./lab2_add --threads=1 --iterations=1000 >> lab2_add.csv
	@./lab2_add --threads=1 --iterations=10000 >> lab2_add.csv
	@./lab2_add --threads=1 --iterations=100000 >> lab2_add.csv
	@./lab2_add --threads=2 --iterations=10000 --yield --sync=m >> lab2_add.csv
	@./lab2_add --threads=4 --iterations=10000 --yield --sync=m >> lab2_add.csv
	@./lab2_add --threads=8 --iterations=10000 --yield --sync=m >> lab2_add.csv
	@./lab2_add --threads=12 --iterations=10000 --yield --sync=m >> lab2_add.csv
	@./lab2_add --threads=2 --iterations=10000 --yield --sync=c >> lab2_add.csv
	@./lab2_add --threads=4 --iterations=10000 --yield --sync=c >> lab2_add.csv
	@./lab2_add --threads=8 --iterations=10000 --yield --sync=c >> lab2_add.csv
	@./lab2_add --threads=12 --iterations=10000 --yield --sync=c >> lab2_add.csv
	@./lab2_add --threads=2 --iterations=1000 --yield --sync=s >> lab2_add.csv
	@./lab2_add --threads=4 --iterations=1000 --yield --sync=s >> lab2_add.csv
	@./lab2_add --threads=8 --iterations=1000 --yield --sync=s >> lab2_add.csv
	@./lab2_add --threads=12 --iterations=1000 --yield --sync=s >> lab2_add.csv
	@./lab2_add --threads=1 --iterations=10000 >> lab2_add.csv
	@./lab2_add --threads=2 --iterations=10000 >> lab2_add.csv
	@./lab2_add --threads=4 --iterations=10000 >> lab2_add.csv
	@./lab2_add --threads=8 --iterations=10000 >> lab2_add.csv
	@./lab2_add --threads=12 --iterations=10000 >> lab2_add.csv
	@./lab2_add --threads=1 --iterations=10000 --sync=m >> lab2_add.csv
	@./lab2_add --threads=2 --iterations=10000 --sync=m >> lab2_add.csv
	@./lab2_add --threads=4 --iterations=10000 --sync=m >> lab2_add.csv
	@./lab2_add --threads=8 --iterations=10000 --sync=m >> lab2_add.csv
	@./lab2_add --threads=12 --iterations=10000 --sync=m >> lab2_add.csv
	@./lab2_add --threads=1 --iterations=10000 --sync=s >> lab2_add.csv
	@./lab2_add --threads=2 --iterations=10000 --sync=s >> lab2_add.csv
	@./lab2_add --threads=4 --iterations=10000 --sync=s >> lab2_add.csv
	@./lab2_add --threads=8 --iterations=10000 --sync=s >> lab2_add.csv
	@./lab2_add --threads=12 --iterations=10000 --sync=s >> lab2_add.csv
	@./lab2_add --threads=1 --iterations=10000 --sync=c >> lab2_add.csv
	@./lab2_add --threads=2 --iterations=10000 --sync=c >> lab2_add.csv
	@./lab2_add --threads=4 --iterations=10000 --sync=c >> lab2_add.csv
	@./lab2_add --threads=8 --iterations=10000 --sync=c >> lab2_add.csv
	@./lab2_add --threads=12 --iterations=10000 --sync=c >> lab2_add.csv
	@./lab2_add --threads=1 --iterations=10000 >> lab2_add.csv
	@./lab2_add --threads=2 --iterations=10000 >> lab2_add.csv
	@./lab2_add --threads=4 --iterations=10000 >> lab2_add.csv
	@./lab2_add --threads=8 --iterations=10000 >> lab2_add.csv
	@./lab2_add --threads=12 --iterations=10000 >> lab2_add.csv
	-@./lab2_list --iterations=10 > lab2_list.csv
	-@./lab2_list --iterations=100 >> lab2_list.csv
	-@./lab2_list --iterations=1000 >> lab2_list.csv
	-@./lab2_list --iterations=10000 >> lab2_list.csv
	-@./lab2_list --iterations=20000 >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=1 >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=10 >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=100 >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=1000 >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=1 >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=10 >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=100 >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=1000 >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=1 >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=10 >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=100 >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=1000 >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=1 >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=10 >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=100 >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=1000 >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=1 --yield=i >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=1 --yield=d >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=1 --yield=l >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=1 --yield=id >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=1 --yield=il >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=1 --yield=dl >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=1 --yield=idl >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=2 --yield=i >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=2 --yield=d >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=2 --yield=l >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=2 --yield=id >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=2 --yield=il >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=2 --yield=dl >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=2 --yield=idl >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=4 --yield=i >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=4 --yield=d >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=4 --yield=l >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=4 --yield=id >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=4 --yield=il >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=4 --yield=dl >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=4 --yield=idl >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=8 --yield=i >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=8 --yield=d >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=8 --yield=l >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=8 --yield=id >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=8 --yield=il >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=8 --yield=dl >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=8 --yield=idl >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=16 --yield=i >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=16 --yield=d >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=16 --yield=l >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=16 --yield=id >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=16 --yield=il >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=16 --yield=dl >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=16 --yield=idl >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=32 --yield=i >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=32 --yield=d >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=32 --yield=l >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=32 --yield=id >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=32 --yield=il >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=32 --yield=dl >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=32 --yield=idl >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=1 --yield=i >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=1 --yield=d >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=1 --yield=l >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=1 --yield=id >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=1 --yield=il >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=1 --yield=dl >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=1 --yield=idl >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=2 --yield=i >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=2 --yield=d >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=2 --yield=l >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=2 --yield=id >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=2 --yield=il >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=2 --yield=dl >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=2 --yield=idl >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=4 --yield=i >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=4 --yield=d >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=4 --yield=l >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=4 --yield=id >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=4 --yield=il >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=4 --yield=dl >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=4 --yield=idl >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=8 --yield=i >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=8 --yield=d >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=8 --yield=l >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=8 --yield=id >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=8 --yield=il >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=8 --yield=dl >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=8 --yield=idl >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=16 --yield=i >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=16 --yield=d >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=16 --yield=l >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=16 --yield=id >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=16 --yield=il >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=16 --yield=dl >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=16 --yield=idl >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=32 --yield=i >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=32 --yield=d >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=32 --yield=l >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=32 --yield=id >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=32 --yield=il >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=32 --yield=dl >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=32 --yield=idl >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=1 --yield=i >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=1 --yield=d >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=1 --yield=l >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=1 --yield=id >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=1 --yield=il >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=1 --yield=dl >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=1 --yield=idl >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=2 --yield=i >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=2 --yield=d >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=2 --yield=l >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=2 --yield=id >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=2 --yield=il >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=2 --yield=dl >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=2 --yield=idl >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=4 --yield=i >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=4 --yield=d >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=4 --yield=l >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=4 --yield=id >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=4 --yield=il >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=4 --yield=dl >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=4 --yield=idl >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=8 --yield=i >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=8 --yield=d >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=8 --yield=l >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=8 --yield=id >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=8 --yield=il >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=8 --yield=dl >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=8 --yield=idl >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=16 --yield=i >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=16 --yield=d >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=16 --yield=l >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=16 --yield=id >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=16 --yield=il >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=16 --yield=dl >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=16 --yield=idl >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=32 --yield=i >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=32 --yield=d >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=32 --yield=l >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=32 --yield=id >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=32 --yield=il >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=32 --yield=dl >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=32 --yield=idl >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=1 --yield=i >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=1 --yield=d >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=1 --yield=l >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=1 --yield=id >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=1 --yield=il >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=1 --yield=dl >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=1 --yield=idl >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=2 --yield=i >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=2 --yield=d >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=2 --yield=l >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=2 --yield=id >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=2 --yield=il >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=2 --yield=dl >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=2 --yield=idl >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=4 --yield=i >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=4 --yield=d >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=4 --yield=l >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=4 --yield=id >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=4 --yield=il >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=4 --yield=dl >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=4 --yield=idl >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=8 --yield=i >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=8 --yield=d >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=8 --yield=l >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=8 --yield=id >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=8 --yield=il >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=8 --yield=dl >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=8 --yield=idl >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=16 --yield=i >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=16 --yield=d >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=16 --yield=l >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=16 --yield=id >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=16 --yield=il >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=16 --yield=dl >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=16 --yield=idl >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=32 --yield=i >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=32 --yield=d >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=32 --yield=l >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=32 --yield=id >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=32 --yield=il >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=32 --yield=dl >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=32 --yield=idl >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=32 --yield=idl --sync=m >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=32 --yield=idl --sync=s >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=32 --yield=i --sync=m >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=32 --yield=i --sync=s >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=32 --yield=d --sync=m >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=32 --yield=d --sync=s >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=32 --yield=l --sync=m >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=32 --yield=l --sync=s >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=32 --yield=id --sync=m >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=32 --yield=id --sync=s >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=32 --yield=dl --sync=m >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=32 --yield=dl --sync=s >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=32 --yield=il --sync=m >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=32 --yield=il --sync=s >> lab2_list.csv
	-@./lab2_list --threads=1 --iterations=1000 --sync=m >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=1000 --sync=m >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=1000 --sync=m >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=1000 --sync=m >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=1000 --sync=m >> lab2_list.csv
	-@./lab2_list --threads=16 --iterations=1000 --sync=m >> lab2_list.csv
	-@./lab2_list --threads=24 --iterations=1000 --sync=m >> lab2_list.csv
	-@./lab2_list --threads=1 --iterations=1000 --sync=s >> lab2_list.csv
	-@./lab2_list --threads=2 --iterations=1000 --sync=s >> lab2_list.csv
	-@./lab2_list --threads=4 --iterations=1000 --sync=s >> lab2_list.csv
	-@./lab2_list --threads=8 --iterations=1000 --sync=s >> lab2_list.csv
	-@./lab2_list --threads=12 --iterations=1000 --sync=s >> lab2_list.csv
	-@./lab2_list --threads=16 --iterations=1000 --sync=s >> lab2_list.csv
	-@./lab2_list --threads=24 --iterations=1000 --sync=s >> lab2_list.csv

graphs: tests lab2_add.gp lab2_list.gp
	@gnuplot lab2_add.gp
	@gnuplot lab2_list.gp

clean:
	@rm -f lab2_add
	@rm -f lab2_list
	@rm -f lab2a-205171726.tar.gz

dist: clean graphs README
	-@tar -cvzf $(TARBALL) README Makefile *.c *.h $(OUTPUT) $(GRAPHS) $(SCRIPTS)
