from subprocess import call

#21 test cases addressing all of these fields
cases = [0 for i in range(12)]
cases[0] = "ReturnError1"
cases[1] = "ReturnError2"
cases[2] = "ReturnError3"
cases[3] = "ReturnError4"
cases[4] = "ReturnError5"
cases[5] = "ReturnError6"
cases[6] = "ReturnError7"
cases[7] = "ReturnError8"
cases[8] = "ReturnError9"
cases[9] = "ReturnError10"
cases[10] = "ReturnError11"
cases[11] = "ReturnError12"

for i in cases:
    call(["./lexer", i+".java", i+".txt"])
