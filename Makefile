NAME = philo
NAME_B = philo_bonus

FC = fc
LC = lc

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes -g #-fsanitize=thread -g3 




SRC = ./utils/main.c\
			./utils/set_data.c\
			./utils/philo.c\
			./utils/utils.c\
			./utils/create_philo.c\
			./utils/libft.c
OBJ = $(SRC:.c=.o)

SRC_B = ./bonus/main_bonus\
				./bonus/philo_bonus\
				./bonus/set_data_bonus\
				./bonus/utils_bonus\
				./bonus/libft
OBJ_B = $(SRC_B:=.o)




all:
	$(call compile_target,$(NAME),all)

bonus:
	$(call compile_target,$(NAME_B),bonus)

clean:
	$(call compile_target,$(LC),clean)

fclean:
	$(call compile_target,$(FC),fclean)

re: fclean all




$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(NAME_B): $(OBJ_B)
	$(CC) $(CFLAGS) $(OBJ_B) -o $(NAME_B)

$(FC):
	rm -fr $(OBJ) $(OBJ_B) $(NAME) $(NAME_B)

$(LC):
	rm -fr $(OBJ) $(OBJ_B)





define compile_target
@if [ "$2" = "bonus" ] || [ "$2" = "all" ]; then \
	if make -q $1; then \
	    echo "$1 is up to date."; \
			exit 0; \
	fi; \
fi; \
bash -c ' \
MK="make $1"; \
LOGFILE=$$(mktemp); \
$$MK >$$LOGFILE 2>&1 & MK_PID=$$!; \
echo -n "Compiling $2"; \
while kill -0 $$MK_PID 2>/dev/null; do \
    for i in {1..3}; do \
        echo -n "."; \
        sleep 0.7; \
    done; \
    echo -ne "\rCompiling $2    \rCompiling $2 "; \
done; \
wait $$MK_PID; \
STATUS=$$?; \
if [ $$STATUS -ne 0 ]; then \
    echo -e "\n$2 failed. See the output below:"; \
    cat $$LOGFILE; \
else \
    echo -e "\r$2 finished.    "; \
fi; \
rm -f $$LOGFILE; \
'; 
endef




.PHONY: all bonus clean fclean re 
.SECONDARY:
