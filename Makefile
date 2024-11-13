NAME = philo

NAME_B = philo_bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror -I./includes -g #-fsanitize=thread -g3 

SRC = ./utils/main.c\
			./utils/set_data.c\
			./utils/philo.c\
			./utils/utils.c\
			./utils/create_philo.c\
			./utils/libft.c

OBJ = $(SRC:.c=.o)

SRC_B = ./bonus/main_bonus.c\
				./bonus/philo_bonus.c\
				./bonus/set_data_bonus.c\
				./bonus/utils_bonus.c\
				./bonus/libft.c

OBJ_B = $(SRC_B:.c=.o)

all:
	@if make -q $(NAME); then \
            echo "$(NAME) is up to date."; \
        else \
            bash -c ' \
            MK="make $(NAME)"; \
            LOGFILE=$$(mktemp); \
            $$MK >$$LOGFILE 2>&1 & MK_PID=$$!; \
            echo -n "Compiling"; \
            while kill -0 $$MK_PID 2>/dev/null; do \
                for i in {1..3}; do \
                    echo -n "."; \
                    sleep 0.5; \
                done; \
                echo -ne "\rCompiling   \rCompiling"; \
            done; \
            wait $$MK_PID; \
            STATUS=$$?; \
            if [ $$STATUS -ne 0 ]; then \
                echo -e "\nCompilation failed. See the output below:"; \
                cat $$LOGFILE; \
            else \
                echo -e "\rCompiling finished.    "; \
            fi; \
            rm -f $$LOGFILE; \
            '; \
    fi

bonus:
	@if make -q $(NAME_B); then \
            echo "$(NAME_B) is up to date."; \
        else \
            bash -c ' \
            MK="make $(NAME_B)"; \
            LOGFILE=$$(mktemp); \
            $$MK >$$LOGFILE 2>&1 & MK_PID=$$!; \
            echo -n "Compiling Bonus"; \
            while kill -0 $$MK_PID 2>/dev/null; do \
                for i in {1..3}; do \
                    echo -n "."; \
                    sleep 0.5; \
                done; \
                echo -ne "\rCompiling Bonus   \rCompiling Bonus"; \
            done; \
            wait $$MK_PID; \
            STATUS=$$?; \
            if [ $$STATUS -ne 0 ]; then \
                echo -e "\nCompilation failed. See the output below:"; \
                cat $$LOGFILE; \
            else \
                echo -e "\rCompiling finished.    "; \
            fi; \
            rm -f $$LOGFILE; \
            '; \
    fi

clean:
	@bash -c ' \
            MK="rm -fr $(OBJ) $(OBJ_B)"; \
            LOGFILE=$$(mktemp); \
            $$MK >$$LOGFILE 2>&1 & MK_PID=$$!; \
            echo -n "clean"; \
            while kill -0 $$MK_PID 2>/dev/null; do \
                for i in {1..3}; do \
                    echo -n "."; \
                    sleep 0.5; \
                done; \
                echo -ne "\rclean   \rclean"; \
            done; \
            wait $$MK_PID; \
            STATUS=$$?; \
            if [ $$STATUS -ne 0 ]; then \
                echo -e "\nclean failed. See the output below:"; \
                cat $$LOGFILE; \
            else \
                echo -e "\rclean finished.    "; \
            fi; \
            rm -f $$LOGFILE; \
            '

fclean:
	@bash -c ' \
            MK="rm -fr $(OBJ) $(OBJ_B) $(NAME) $(NAME_B)"; \
            LOGFILE=$$(mktemp); \
            $$MK >$$LOGFILE 2>&1 & MK_PID=$$!; \
            echo -n "Full clean"; \
            while kill -0 $$MK_PID 2>/dev/null; do \
                for i in {1..3}; do \
                    echo -n "."; \
                    sleep 0.5; \
                done; \
                echo -ne "\rFull clean   \rFull clean"; \
            done; \
            wait $$MK_PID; \
            STATUS=$$?; \
            if [ $$STATUS -ne 0 ]; then \
                echo -e "\nFull clean failed. See the output below:"; \
                cat $$LOGFILE; \
            else \
                echo -e "\rFull clean finished.    "; \
            fi; \
            rm -f $$LOGFILE; \
            '

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(NAME_B): $(OBJ_B)
	$(CC) $(CFLAGS) $(OBJ_B) -o $(NAME_B)

re: fclean all

.PHONY: all bonus clean fclean re 

.SECONDARY:
