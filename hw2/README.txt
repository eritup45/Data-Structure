Struct:
	int dir: record the direction (for variable next)
	int row: record the row in the maze
	int col: record the col

Function:
	getMaze: read maze.txt and build 1's wall outside.
	movea: right > down > up > left
	moveb: left > up > down > right
	stackpush: top++, and write next's data in stack
	stackpop: return stack, and top--
	addq: add stack into the result

Main:
	Move like the description.
	When everytime the rat move one step, mark the step.
	If the rat can't move anymore, go back to the last step, 
	and try moving again.
	Record the result in variable "result".	

Detail:
	line 26: Since I declare movement *next, it's necessary to malloc first.
	line 55: When everytime the rat move one step, mark the step.


1. how to compile your program
	After execution, the program will produce "result.txt". 
	It contains the output of the homewok.
	The output is first ratA, and then ratB.
	If one has finished, the other would still print out its output until it reaches its end.
2. what problem you met
	(1) Since I set my variable "next" as "movement *next", and I forget to malloc "next", I keep meeting segmentation fault, 
	which make me spend lots of time finding the error.
	(2) I also spend lots of time on the rat, walking around the maze.
	I'm thinking where and when should I mark the maze.