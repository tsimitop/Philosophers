################################################################################
#								CONSTANTS									   #
################################################################################
CC = cc
DEBUG = -g
CFLAGS = -Wall -Wextra -Werror
LDFLAGS := -lpthread

################################################################################
#								PHILO MANDATORY								   #
################################################################################

NAME = philo
SRC =	main.c\
		parse.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@echo "Building $(NAME)"
	@$(CC) $(DEBUG) $^ $(LDFLAGS) -o $@
	@echo "\033[34m$(NAME) built successfully!\033[0m"

$(OBJ) : %.o : %.c
	@echo "Building $(OBJ)"
	@$(CC) -c $(CFLAGS) $(LDFLAGS) $< -o $@
	@echo "Built $(OBJ)"

clean :
	@echo "Removing $(OBJ)"
	@rm -f $(OBJ)
	@echo "Removed $(OBJ)"

fclean : clean
	@echo "Removing $(NAME)"
	@rm -f $(NAME)
	@echo "Removed $(NAME)"

re : fclean all

.PHONY :
	all clean fclean re