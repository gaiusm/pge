#
#  mxmstack - maintain a stack
#

class stack:
    #
    #  __init__ - constructor for stack created empty with optional error handler, error.
    #

    def __init__ (self, error = None):
        self.error = error
        self.contents = []

    #
    #  push - pushes tok onto our stack.
    #

    def push (self, tok):
        self.contents += [tok]


    #
    #  pop - returns removes and returns the top of stack.
    #

    def pop (self):
        if self.contents == []:
            if self.error != None:
                self.error('should never be popping from an empty stack')
            return None
        else:
            top = self.contents[-1]
            if len(self.contents) == 1:
                self.contents = []
            else:
                self.contents = self.contents[:-1]
            return top
