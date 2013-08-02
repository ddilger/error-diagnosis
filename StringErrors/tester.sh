#Runs all available test cases of the string diagnoser

none="No error"
echo ""
multiline="Multiline error"
odd="Odd number of quotation marks"

file="StrError.java"
echo ""
echo $file " expected error: " $none
./diagnoser $file

file="StrError1.java"
echo ""
echo $file " expected error: " $odd
./diagnoser $file

file="StrError2.java"
echo ""
echo $file " expected error: " $multiline
./diagnoser $file

file="StrError3.java"
echo ""
echo $file " expected error: " $multiline
./diagnoser $file

file="StrError4.java"
echo ""
echo $file " expected error: " $multiline
./diagnoser $file

file="StrError5.java"
echo ""
echo $file " expected error: " $none
./diagnoser $file

file="StrError6.java"
echo ""
echo $file " expected error: " $none
./diagnoser $file

file="StrError7.java"
echo ""
echo $file " expected error: " $none
./diagnoser $file

file="StrTest1.java"
echo ""
echo $file " expected error: " $odd
./diagnoser $file

file="StrTest2.java"
echo ""
echo $file " expected error: " $none
./diagnoser $file

file="StrTest3.java"
echo ""
echo $file " expected error: " $odd
./diagnoser $file

file="StrTest4.java"
echo ""
echo $file " expected error: " $none
./diagnoser $file

file="MultilineTest1.java"
echo ""
echo $file " expected error: " $multiline
./diagnoser $file

file="MultilineTest2.java"
echo ""
echo $file " expected error: " $multiline
./diagnoser $file

file="MultilineTest3.java"
echo ""
echo $file " expected error: " $multiline
./diagnoser $file