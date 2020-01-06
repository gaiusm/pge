#
#  mxmout
#


#
#  printf - keeps C programmers happy :-)
#

def printf (format, *args):
    print(str(format) % args, end=' ')


#
#  printHeader - prints out the leading inputFile:lineno: for an error message.
#

def printHeader (inputFile, lineno):
    printf("%s:%d:", inputFile, lineno)


