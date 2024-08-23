NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror  -I./includes -g -fsanitize=thread -g3 

SRC = ./utils/main.c\
			./utils/philo.c\
			./utils/utils.c\

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -fr $(OBJ)

fclean: clean
	rm -fr $(NAME)

re: fclean all

.PHONY: all clean fclean re
