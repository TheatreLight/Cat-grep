all:

wingrep:
	gcc main.c wingrep.c wingrep_patterns.c ../common/parcer.c -o wingrep

debug:
	gcc main.c wingrep.c wingrep_patterns.c ../common/parcer.c -o wingrep -g

check:
	python3 ../../materials/linters/cpplint.py --extensions=c *.c *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

leaks:
	leaks --atExit -- ./wingrep -e all -e it grep_tests/new grep_tests/old

clean:
	rm wingrep
