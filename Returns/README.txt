The finding returns problem isn't fixed yet.

There are three attempts in this folder: 
--return_diagnoser1.c represents an attempt in the same stack-based way
as the solution in CurlyErrors.

--return_diagnoser2.c represents an attempt to use a recursive-descent
parser to diagnose the error. It's promising, but it may be too
complicated a solution, since the diagnoser can assume the program was
more or less following Java's grammar.

--return_diagnoser3.c is a simpler version of return_diagnoser2, which
  is still based on recursion and using the stack frame to keep track
  of a hierarchy of data, but it doesn't check the type of blocks
  against a grammar. (So a method declaration could be inside an if
  statement, but there's no reason the diagnoser needs to catch
  this). It works by "chains". A link in the chain represents a
  block in a method. A link can itself be made up of a chain of
  sub-blocks. A function analyzes the chain to diagnose the block. If
  one link has a return, then it expects all links to have it, or the
  block is flagged. Some chains, like methods with return declarations,
  get automatic flaggings, which need to be erased by good returns.
