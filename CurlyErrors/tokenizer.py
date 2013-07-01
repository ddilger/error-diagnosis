from subprocess import call

#21 test cases addressing all of these fields
cases = [0 for i in range(21)]
cases[0] = "JavaCurly1"
cases[1] = "JavaCurly2"
cases[2] = "JavaCurly3"
cases[3] = "JavaCurly4"
cases[4] = "JavaCurly5"
cases[5] = "JavaCurly6"
cases[6] = "JavaCurly7"
cases[7] = "JavaCurly8"
cases[8] = "JavaCurly9"
cases[9] = "JavaCurly10"
cases[10] = "JavaCurly11"
cases[11] = "JavaCurly12"
cases[12] = "JavaCurly13"
cases[13] = "JavaCurly14"
cases[14] = "JavaCurly15"
cases[15] = "JavaCurly16"
cases[16] = "JavaCurly17"
cases[17] = "JavaCurly18"
cases[18] = "JavaCurly19"
cases[19] = "JavaCurly20"
cases[20] = "JavaCurly21"

for i in cases:
    call(["./lexer", i+".java", i+".txt"])
