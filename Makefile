CC 			= g++
FLAGS		= -Og

main: 	main.o
	$(CC) $(FLAGS) main.o -o main 

clean:
	$(RM) main main.o