NAME = Zombie
CC = c++
FLAGS = -Wall -Werror -Wextra -std=c++98
SRC = main.cpp Zombie.cpp randomChump.cpp newZombie.cpp

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

fclean:
	rm -f $(NAME)
re: fclean all