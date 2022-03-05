all:

s21_grep:
	gcc s21_grep.c s21_grep_patterns.c ../common/parcer.c -o s21_grep

debug:
	gcc s21_grep.c s21_grep_patterns.c ../common/parcer.c -o s21_grep -g

test:
	bash ./grep_tests/test.sh

check:
	python3 ../../materials/linters/cpplint.py --extensions=c *.c *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

leaks:
	leaks --atExit -- ./s21_grep -e all -e it grep_tests/new grep_tests/old

clean:
	rm s21_grep
