NAME = philo
NAME_B = philo_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes -g -fsanitize=thread -g3 

SRC = ./utils/main.c\
			./utils/philo2.c\
			./utils/philo.c\
			./utils/utils.c\

OBJ = $(SRC:.c=.o)

SRC_B = ./bonus/bonus.c\

OBJ_B = $(SRC_B:.c=.o)

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

bonus: $(NAME_B)

$(NAME_B): $(OBJ_B)
	$(CC) $(CFLAGS) $(OBJ_B) -o $(NAME_B)

clean:
	rm -fr $(OBJ)
	rm -fr $(OBJ_B)

fclean: clean
	rm -fr $(NAME)
	rm -fr $(NAME_B)

re: fclean all

.PHONY: all bonus clean fclean re
