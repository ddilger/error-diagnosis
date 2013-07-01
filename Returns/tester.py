#NOTE: not entirely sure that this tester is perfect...

#Guide to test areas:
#No potential return error
#Potential return error

#Causes:
#Loop
#if statement
#switch statement
#loop possibly not terminating
# (more details like no else?)

from subprocess import call

class ErrType:
    SurplusOpen = 1
    SurplusClose = 2
    InsufficientOpen = 3
    InsufficientClose = 8
    UnterminatedBlock = 4
    UnterminatedArray = 5
    MultipleErr = 6
    NoErr = 7
    
def expected(error):
    if error == ErrType.SurplusOpen:
        print("Expected error: Surplus { (Open curly) Error")
    if error == ErrType.SurplusClose:
        print("Expected error: Surplus } (Close curly) Error")
    if error == ErrType.InsufficientOpen:
        print("Expected error: Insufficient { Error")
    if error == ErrType.UnterminatedBlock:
        print("Expected error: Unterminated Block error")
    if error == ErrType.UnterminatedArray:
        print("Expected error: Unterminated Array error")
    if error == ErrType.MultipleErr:
        print("Expected error: Multiple errors")
    if error == ErrType.NoErr:
        print("Expected error: No Error")

#21 test cases addressing all of these fields

errors = [0 for i in range(21)]
errors[0] = ("JavaCurly1.java", ErrType.NoErr)
errors[1] = ("JavaCurly2.java", ErrType.SurplusOpen)
errors[2] = ("JavaCurly3.java", ErrType.SurplusClose)
errors[3] = ("JavaCurly4.java", ErrType.NoErr)
errors[4] = ("JavaCurly5.java", ErrType.SurplusOpen)
errors[5] = ("JavaCurly6.java", ErrType.SurplusClose)
errors[6] = ("JavaCurly7.java", ErrType.NoErr)
errors[7] = ("JavaCurly8.java", ErrType.SurplusOpen)
errors[8] = ("JavaCurly9.java", ErrType.SurplusClose)
errors[9] = ("JavaCurly10.java", ErrType.SurplusOpen)
errors[10] = ("JavaCurly11.java", ErrType.SurplusClose)
errors[11] = ("JavaCurly12.java", ErrType.NoErr)
errors[12] = ("JavaCurly13.java", ErrType.SurplusOpen)
errors[13] = ("JavaCurly14.java", ErrType.UnterminatedBlock)
errors[14] = ("JavaCurly15.java", ErrType.InsufficientOpen)
errors[15] = ("JavaCurly16.java", ErrType.InsufficientClose)
errors[16] = ("JavaCurly17.java", ErrType.NoErr)
errors[17] = ("JavaCurly18.java", ErrType.UnterminatedArray)
errors[18] = ("JavaCurly19.java", ErrType.InsufficientOpen)
errors[19] = ("JavaCurly20.java", ErrType.UnterminatedArray)
errors[20] = ("JavaCurly21.java", ErrType.MultipleErr)


for i in errors:
    print("Executing file ", i[0])
    expected(i[1])
    call(["./curly2", i[0]])
    print("")
    
