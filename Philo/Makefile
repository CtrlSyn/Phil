NAME = philo

SRC_NAME = parsing.c main.c fetching.c simulation.c 

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3 #fsanitize=address

OBJ_NAME = $(SRC_NAME:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_NAME)
	$(CC) $(CFLAGS) $(OBJ_NAME) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	@rm -f $(OBJ_NAME)
fclean: clean
	@rm -f $(NAME)

re: fclean all
