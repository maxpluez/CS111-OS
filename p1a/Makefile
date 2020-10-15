lab1a: lab1a.c
	gcc -Wall -Wextra -g -O0 lab1a.c -o lab1a

.PHONY: clean dist

dist:
	@tar -zcvf lab1a-205171726.tar.gz lab1a.c Makefile README

clean:
	@rm -f lab1a
	@rm -f lab1a-205171726.tar.gz
