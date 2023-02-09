all:

s_cat:
	gcc s_cat.c ../common/parcer.c -o s21_cat

debug:
	gcc s_cat.c ../common/parcer.c -o s21_cat -g

test:
	bash ./tests/test.sh

check:
	python3 ../../materials/linters/cpplint.py --extensions=c *.c *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

leaks:
	leaks --atExit -- ./s21_cat tests/new

clean:
	rm s21_cat
