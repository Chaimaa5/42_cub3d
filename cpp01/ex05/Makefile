NAME = main
CC = clang++
FLAGS = -Wall -Werror -Wextra
SRC = main.cpp Harl.cpp

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

fclean:
	rm -f $(NAME)
re: fclean all