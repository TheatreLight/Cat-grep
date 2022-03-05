
./s21_cat tests/new > out1
cat tests/new > out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "test empty OK"
else
echo "test empty FAIL"
fi

rm out1 out2

./s21_cat -b tests/case_b > out1
cat -b tests/case_b > out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "test -b OK"
else
echo "test -b FAIL"
fi

rm out1 out2

./s21_cat -n tests/case_n > out1
cat -n tests/case_n > out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "test -n OK"
else
echo "test -n FAIL"
fi

rm out1 out2

./s21_cat -s tests/case_s > out1
cat -s tests/case_s > out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "test -s OK"
else
echo "test -s FAIL"
fi

rm out1 out2

./s21_cat -e tests/case_e > out1
cat -e tests/case_e > out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "test -e OK"
else
echo "test -e FAIL"
fi

rm out1 out2

./s21_cat -t tests/case_t > out1
cat -t tests/case_t > out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "test -t OK"
else
echo "test -t FAIL"
fi

rm out1 out2

./s21_cat -E tests/case_upE > out1

string1=$(shasum out1)
string2=$(shasum tests/out3)

x=${string1%out1}
y=${string2%tests/out3}

if [[ $x = $y ]]
then
echo "test -E OK"
else
echo "test -E FAIL"
fi

rm out1

./s21_cat -T tests/case_upT > out1

string1=$(shasum out1)
string2=$(shasum tests/out4)

x=${string1%out1}
y=${string2%tests/out4}

if [[ $x = $y ]]
then
echo "test -T OK"
else
echo "test -T FAIL"
fi

rm out1

./s21_cat -bn tests/big_text > out1
cat -bn tests/big_text > out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "test -bn OK"
else
echo "test -bn FAIL"
fi

rm out1 out2

./s21_cat --number tests/memory_case > out1
if [[ "$OSTYPE" == "linux-gnu"* ]]
then
cat --number tests/memory_case > out2
elif [[ "$OSTYPE" == "darwin"* ]]
then
cat -n tests/memory_case > out2
fi

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "test --number OK"
else
echo "test --number FAIL"
fi

rm out1 out2

./s21_cat --number-nonblank tests/big_text > out1
if [[ "$OSTYPE" == "linux-gnu"* ]]
then
cat --number-nonblank tests/big_text > out2
elif [[ "$OSTYPE" == "darwin"* ]]
then
cat -b tests/big_text > out2
fi


string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "test --number-nonblank OK"
else
echo "test --number-nonblank FAIL"
fi

rm out1 out2

./s21_cat --squeeze-blank tests/case_s > out1
if [[ "$OSTYPE" == "linux-gnu"* ]]
then
cat --squeeze-blank tests/case_s > out2
elif [[ "$OSTYPE" == "darwin"* ]]
then
cat -s tests/case_s > out2
fi

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "test --squeeze OK"
else
echo "test --squeeze FAIL"
fi

rm out1 out2

./s21_cat -nst tests/memory_case > out1
cat -nst tests/memory_case > out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "test memory OK"
else
echo "test memory FAIL"
fi

rm out1 out2

./s21_cat tests/hard_case > out1
cat tests/hard_case > out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "test BONUS OK"
else
echo "test BONUS FAIL"
fi

rm out1 out2

./s21_cat -nse tests/big_text > out1
cat -nse tests/big_text > out2

string1=$(shasum out1)
string2=$(shasum out2)

x=${string1%out1}
y=${string2%out2}

if [[ $x = $y ]]
then
echo "test BONUS2 OK"
else
echo "test BONUS2 FAIL"
fi

rm out1 out2
