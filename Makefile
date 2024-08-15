NAME	=  philo

CC			= gcc -fsanitize=thread -g
CFLAGS		= -Wall -Werror -Wextra
RM			= rm -rf

LIBFT = ./libft_full/libft.a
LIBFT_PATH = ./libft_full

SRC		= main.c init_info.c utils.c run_philo.c init_mutex.c actions.c

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

# .PHONY rule in order to avoid relinking
.PHONY: all clean fclean re libft


# gcc -fsanitize=thread -g
# gcc -fsanitize=thread --help -g

# TSAN_OPTIONS=second_deadlock_stack=1 ./philo 5 800 200 200

# ***problems***
# WARNING: ThreadSanitizer: lock-order-inversion (potential deadlock) (pid=225396)
#  Cycle in lock order graph: M8 (0x7b34000000a0) => M4 (0x7b3400000000) => M5 (0x7b3400000028) => M6 (0x7b3400000050) => M7 (0x7b3400000078) => M8
# solution: the circle mutex due to the round table, need to  put to 0 the fork_lock when it's the last philosopher turn to pick the fork
#
#
# in philo_alive: it was costantly repeating "died": solved inverting the if conditions;
#
#