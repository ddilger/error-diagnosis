#Should include line errors in the report of what's expected
#Not really a difference between the insufficient close and unterminated block error,
#except with arrays

#Guide to test areas:
#Surplus {
#Surplus }
#Insufficient {
#Insufficient }
#Unterminated block
#Unterminated array
#Multiple errors in one file
#No error

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
        print("Expected error: Excess open curly error")
    if error == ErrType.SurplusClose:
        print("Expected error: Excess close curly error")
    if error == ErrType.InsufficientOpen:
        print("Expected error: Missing open curly error")
    if error == ErrType.UnterminatedBlock:
        print("Expected error: Unterminated Block error")
    if error == ErrType.InsufficientClose:
        print("Expected error: Missing close curly Error")
    if error == ErrType.UnterminatedArray:
        print("Expected error: Missing close token")
#        print("Expected error: Unterminated Array error")
    if error == ErrType.MultipleErr:
        print("Expected error: Multiple errors")
    if error == ErrType.NoErr:
        print("Expected error: No Error")

#21 test cases addressing all of these fields

errors = [0 for i in range(21)]
errors[0] = ("JavaCurly1.txt", ErrType.NoErr)
errors[1] = ("JavaCurly2.txt", ErrType.SurplusOpen)
errors[2] = ("JavaCurly3.txt", ErrType.SurplusClose)
errors[3] = ("JavaCurly4.txt", ErrType.NoErr)
errors[4] = ("JavaCurly5.txt", ErrType.SurplusOpen)
errors[5] = ("JavaCurly6.txt", ErrType.SurplusClose)
errors[6] = ("JavaCurly7.txt", ErrType.NoErr)
errors[7] = ("JavaCurly8.txt", ErrType.SurplusOpen)
errors[8] = ("JavaCurly9.txt", ErrType.SurplusClose)
errors[9] = ("JavaCurly10.txt", ErrType.SurplusOpen)
errors[10] = ("JavaCurly11.txt", ErrType.SurplusClose)
errors[11] = ("JavaCurly12.txt", ErrType.NoErr)
errors[12] = ("JavaCurly13.txt", ErrType.SurplusOpen)
errors[13] = ("JavaCurly14.txt", ErrType.UnterminatedBlock)
errors[14] = ("JavaCurly15.txt", ErrType.InsufficientOpen)
errors[15] = ("JavaCurly16.txt", ErrType.UnterminatedBlock)
errors[16] = ("JavaCurly17.txt", ErrType.NoErr)
errors[17] = ("JavaCurly18.txt", ErrType.UnterminatedArray)
errors[18] = ("JavaCurly19.txt", ErrType.InsufficientOpen)
errors[19] = ("JavaCurly20.txt", ErrType.MultipleErr)
errors[20] = ("JavaCurly21.txt", ErrType.MultipleErr)


for i in errors:
    print "Executing file ", i[0] 
    expected(i[1])
    call(["./curly_diagnoser", i[0]])
    print("")
    
