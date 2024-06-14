NAME	= philo

CC			= gcc -fsanitize=thread -g
CFLAGS		= -Wall -Werror -Wextra
RM			= rm -rf

LIBFT = ./libft_full/libft.a
LIBFT_PATH = ./libft_full

PHILO_SRC		= philo.c / threads.c /

PHILO_OBJ		= $(PHILO_SRC:.c=.o)

PHILO = philo

all: libft $(PHILO) 

libft:
	@$(MAKE) -C $(LIBFT_PATH)

$(PHILO): $(PHILO_OBJ)
	$(CC) $(CFLAGS) -o $(PHILO) $(PHILO_OBJ) $(LIBFT)

clean:
	$(RM) $(PHILO_OBJ)
	@$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
		$(RM) $(PHILO_OBJ)
		$(RM) $(PHILO)
		@$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

# .PHONY rule in order to avoid relinking
.PHONY: all clean fclean re libft
