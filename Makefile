NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror  -I./includes -I$(LIBFT_SRC) -g -fsanitize=thread -g3 

LIBFT_SRC = ./lib/libft
LIBFT = $(LIBFT_SRC)/libft.a

SRC = ./utils/philo.c\

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_SRC)

clean:
	make -C $(LIBFT_SRC) clean
	rm -fr $(OBJ)

fclean: clean
	make -C $(LIBFT_SRC) fclean
	rm -fr $(NAME)

re: fclean all

.PHONY: all clean fclean re
