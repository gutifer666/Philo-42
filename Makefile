NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c philosopher.c utils.c
OBJ = $(SRC:.c=.o)
LIBS = -lpthread

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all