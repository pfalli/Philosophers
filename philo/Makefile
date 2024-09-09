NAME	=  philo

CC			= gcc #-g -lpthread -fsanitize=address
CFLAGS		= -Wall -Werror -Wextra #-g -lpthread -fsanitize=thread
RM			= rm -rf

LIBFT = ./libft_full/libft.a
LIBFT_PATH = ./libft_full

SRC		= main.c init.c utils.c monitor.c actions.c threads.c

OBJ		= $(SRC:.c=.o)

all: libft $(NAME) 

libft:
	@$(MAKE) -C $(LIBFT_PATH)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

clean:
	$(RM) $(NAME_OBJ)
	@$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
		$(RM) $(OBJ)
		$(RM) $(NAME)
		@$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all


#  to avoid relinking
.PHONY: all clean fclean re libft

# valgrind --leak-check=full
# valgrind --tool=helgrind
