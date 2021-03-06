NAME = minishell

CC = gcc -Werror -Wall -Wextra 
# -g -fsanitize=address

FILE = main.c \
		make_node.c \
		make_redirect.c \
		change_input.c \
		make_env.c

OBJS = $(FILE:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(MAKE) -C ./libft all
	$(CC) $(OBJS) -lreadline -L./libft -lft -o $(NAME)

%.o : %.c
	$(CC) -c $< -o $@

clean :
	@$(MAKE) -C ./libft clean
	rm -rf $(OBJS)

fclean :
	make clean
	@$(MAKE) -C ./libft fclean
	rm -rf $(NAME)

re :
	make fclean
	make all

.PHONY: all clean fclean re