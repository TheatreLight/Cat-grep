
#1st test: 1 pattern, 1 file
./wingrep coronavirus grep_tests/new > out1
grep coronavirus grep_tests/new > out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "1 test 1 pattern 1 file OK"
else
echo "1 test 1 pattern 1 file FAIL"
fi

rm out1
rm out2

#2nd test: 1 pattern, 7 files
./wingrep a grep_tests/new grep_tests/old grep_tests/18_test_pat grep_tests/19_test_pat grep_tests/forgrep grep_tests/pattern grep_tests/text  > out1
grep a grep_tests/new grep_tests/old grep_tests/18_test_pat grep_tests/19_test_pat grep_tests/forgrep grep_tests/pattern grep_tests/text > out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "2 test 1 pattern 7 files OK"
else
echo "2 test 1 pattern 7 files FAIL"
fi

rm out1
rm out2

#3 test -e: 2 patterns 1 file 
./wingrep -e all -e it grep_tests/new > out1
grep -e all -e it grep_tests/new > out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "3 test -e OK"
else
echo "3 test -e FAIL"
fi

rm out1
rm out2

#4 test -e: 2 patterns 2 files 
./wingrep -e all -e it grep_tests/new grep_tests/old > out1
grep -e all -e it grep_tests/new grep_tests/old > out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "4 test -e OK"
else
echo "4 test -e FAIL"
fi

rm out1
rm out2

#5 test -i 1 pattern 1 file
./wingrep -i health grep_tests/new > out1
grep -i health grep_tests/new > out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "5 test -i OK"
else
echo "5 test -i FAIL"
fi

rm out1
rm out2

#6 test -i 2 pattern 2 files
./wingrep -ie health -e grep grep_tests/new grep_tests/old> out1
grep -ie health -e grep grep_tests/new grep_tests/old> out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "6 test -i OK"
else
echo "6 test -i FAIL"
fi

rm out1
rm out2

#7 test -v 1 pattern 1 file
./wingrep -v health grep_tests/new > out1
grep -v health grep_tests/new > out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "7 test -v OK"
else
echo "7 test -v FAIL"
fi

rm out1
rm out2

#8 test -v 2 patterns 2 files
./wingrep -ve health -e grep grep_tests/new grep_tests/old> out1
grep -ve health -e grep grep_tests/new grep_tests/old> out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "8 test -v OK"
else
echo "8 test -v FAIL"
fi

rm out1
rm out2

#9 test -c 1 pattern 1 file 
./wingrep -c health grep_tests/new > out1
grep -c health grep_tests/new > out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "9 test -c OK"
else
echo "9 test -c FAIL"
fi

rm out1
rm out2

#10 test -c 2 patterns 2 files
./wingrep -ce health -e grep grep_tests/new grep_tests/old> out1
grep -ce health -e grep grep_tests/new grep_tests/old> out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "10 test -c OK"
else
echo "10 test -c FAIL"
fi

rm out1
rm out2

#11 test -l 1 pattern 2 file
./wingrep -l all grep_tests/new grep_tests/old> out1
grep -l all grep_tests/new grep_tests/old> out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "11 test -l OK"
else
echo "11 test -l FAIL"
fi

rm out1
rm out2

#12 test -l 2 patterns 2 files
./wingrep -le health -e grep grep_tests/new grep_tests/old> out1
grep -le health -e grep grep_tests/new grep_tests/old> out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "12 test -l OK"
else
echo "12 test -l FAIL"
fi

rm out1
rm out2

#13 test -n 1 patterns 1 file
./wingrep -n health grep_tests/new > out1
grep -n health grep_tests/new > out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "13 test -n OK"
else
echo "13 test -n FAIL"
fi

rm out1
rm out2

#14 test -n 2 patterns 2 files
./wingrep -ne health -e grep grep_tests/new grep_tests/old> out1
grep -ne health -e grep grep_tests/new grep_tests/old> out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "14 test -n OK"
else
echo "14 test -n FAIL"
fi

rm out1
rm out2

#15 test -o 1 pattern 1 file
./wingrep -o health grep_tests/new > out1
grep -o health grep_tests/new > out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "15 test -o OK"
else
echo "15 test -o FAIL"
fi

rm out1
rm out2

#16 test -o 2 patterns 2 files
./wingrep -oe health -e grep grep_tests/new grep_tests/old> out1
grep -oe health -e grep grep_tests/new grep_tests/old> out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "16 test -o OK"
else
echo "16 test -o FAIL"
fi

rm out1
rm out2

#17 test -h 2 patterns 2 files
./wingrep -he health -e grep grep_tests/new grep_tests/old> out1
grep -he health -e grep grep_tests/new grep_tests/old> out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "17 test -h OK"
else
echo "17 test -h FAIL"
fi

rm out1
rm out2

#18 test -f 2 patterns 2 files
./wingrep -f grep_tests/18_test_pat grep_tests/new grep_tests/old > out1
grep -f grep_tests/18_test_pat grep_tests/new grep_tests/old > out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "18 test -f OK"
else
echo "18 test -f FAIL"
fi

rm out1
rm out2

#19 test -f with -i
./wingrep -if grep_tests/19_test_pat grep_tests/new grep_tests/old> out1
grep -if grep_tests/19_test_pat grep_tests/new grep_tests/old> out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "19 test -f OK"
else
echo "19 test -f FAIL"
fi

rm out1
rm out2

#20 test -f with -v
./wingrep -vf grep_tests/19_test_pat grep_tests/new grep_tests/old> out1
grep -vf grep_tests/19_test_pat grep_tests/new grep_tests/old> out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "20 test -f OK"
else
echo "20 test -f FAIL"
fi

rm out1
rm out2

#21 test -f with -c
./wingrep -cf grep_tests/19_test_pat grep_tests/new grep_tests/old> out1
grep -cf grep_tests/19_test_pat grep_tests/new grep_tests/old> out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "21 test -f OK"
else
echo "21 test -f FAIL"
fi

rm out1
rm out2

#22 test -f with -l
./wingrep -lf grep_tests/19_test_pat grep_tests/new grep_tests/old> out1
grep -lf grep_tests/19_test_pat grep_tests/new grep_tests/old> out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "22 test -f OK"
else
echo "22 test -f FAIL"
fi

rm out1
rm out2

#23 test -f with -n
./wingrep -nf grep_tests/19_test_pat grep_tests/new grep_tests/old> out1
grep -nf grep_tests/19_test_pat grep_tests/new grep_tests/old> out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "23 test -f OK"
else
echo "23 test -f FAIL"
fi

rm out1
rm out2

#24 test -f with -o
./wingrep -of grep_tests/19_test_pat grep_tests/new grep_tests/old> out1
grep -of grep_tests/19_test_pat grep_tests/new grep_tests/old> out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "24 test -f OK"
else
echo "24 test -f FAIL"
fi

rm out1
rm out2

#25 test -sf
echo "      25 test -s start:"
./wingrep it grep_tests/neww
grep it grep_tests/neww

./wingrep -s it grep_tests/neww grep_tests/old> out1
grep -s it grep_tests/neww grep_tests/old> out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "25 test -s OK"
else
echo "25 test -s FAIL"
fi

rm out1
rm out2

#26 combo 1 test
./wingrep -hnie health -e grep grep_tests/new grep_tests/old> out1
grep -hnie health -e grep grep_tests/new grep_tests/old> out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "26 test combo 1 OK"
else
echo "26 test combo 1 FAIL"
fi

rm out1
rm out2

#27 combo 2 test
./wingrep -hvnie health -e grep grep_tests/new grep_tests/old> out1
grep -hvnie health -e grep grep_tests/new grep_tests/old> out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "27 test combo 2 OK"
else
echo "27 test combo 2 FAIL"
fi

rm out1
rm out2

#28 combo 3 test
./wingrep -vce health -e grep grep_tests/new grep_tests/old> out1
grep -vce health -e grep grep_tests/new grep_tests/old> out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "28 test combo 3 OK"
else
echo "28 test combo 3 FAIL"
fi

rm out1
rm out2

#29 combo 4 test
./wingrep -vcnie health -e grep grep_tests/new grep_tests/old> out1
grep -vcnie health -e grep grep_tests/new grep_tests/old> out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "29 test combo 4 OK"
else
echo "29 test combo 4 FAIL"
fi

rm out1
rm out2

#30 combo 5 test
./wingrep -nioe health -e grep grep_tests/new grep_tests/old> out1
grep -nioe health -e grep grep_tests/new grep_tests/old> out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "30 test combo 5 OK"
else
echo "30 test combo 5 FAIL"
fi

rm out1
rm out2

#31 combo 6 test
./wingrep -hnioe health -e grep grep_tests/new grep_tests/old> out1
grep -hnioe health -e grep grep_tests/new grep_tests/old> out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "31 test combo 6 OK"
else
echo "31 test combo 6 FAIL"
fi

rm out1
rm out2

#32 combo 7 test
./wingrep -cnioe health -e grep grep_tests/new grep_tests/old> out1
grep -cnioe health -e grep grep_tests/new grep_tests/old> out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "32 test combo 7 OK"
else
echo "32 test combo 7 FAIL"
fi

rm out1
rm out2

#33 combo 8 test
./wingrep -hniof grep_tests/19_test_pat grep_tests/new grep_tests/old> out1
grep -hniof grep_tests/19_test_pat grep_tests/new grep_tests/old> out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "33 test combo 8 OK"
else
echo "33 test combo 8 FAIL"
fi

rm out1
rm out2

