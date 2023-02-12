all:

wincat:
	gcc main.c wincat.c ../common/parcer.c -o wincat

debug:
	gcc main.c wincat.c ../common/parcer.c -o wincat -g

test:
	bash ./tests/test.sh

check:
	python3 ../../materials/linters/cpplint.py --extensions=c *.c *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

clean:
	rm wincat
