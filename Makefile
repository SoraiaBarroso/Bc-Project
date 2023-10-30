CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = my_bc.c lexer_system_1.c lexer_system_2.c error_management.c math_parsing.c math_postfix_calc.c
TARGET = my_bc

all : $(TARGET)

$(TARGET) : $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f *.o

fclean: clean
	rm -f $(TARGET)

re: fclean all