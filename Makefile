CC=cc
FLAGS=-Wall -Werror -Wextra
NAME=pt.click
OBJS=game_creation.c game_read.c printing.c user.c help.c user_interactions.c inventory.c tester.c
LIBS=libby.h

$(NAME): $(OBJS) $(LIBS)
	$(CC) -o $(NAME) $(FLAGS) $(OBJS)

.PHONY: clean re

clean:
	rm $(NAME)

re: clean $(NAME)

