################################################################################
#								CONSTANTS									   #
################################################################################
CC = cc
DEBUG = -g
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread
LDFLAGS := -lpthread

################################################################################
#								PHILO MANDATORY								   #
################################################################################

NAME = philo
SRC =	main.c\
		parse.c\
		time.c\
		utils.c\
		actions.c\
		thread.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@echo "Building $(NAME)"
	@$(CC) $(CFLAGS) $(DEBUG) $^ $(LDFLAGS) -o $@
	@echo "\033[34m$(NAME) built successfully!\033[0m"

$(OBJ) : %.o : %.c
	@$(CC) -c $(CFLAGS) $(DEBUG) $< -o $@
#@echo "Building $(OBJ)"
#@echo "Built $(OBJ)"

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

#windows
# ################################################################################
# #								CONSTANTS									   #
# ################################################################################
# CC = cc
# DEBUG = -g
# CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread
# LDFLAGS := -lpthread

# ################################################################################
# #								PHILO MANDATORY								   #
# ################################################################################

# NAME = philo
# SRC =	main.c\
# 		parse.c\
# 		time.c
# OBJ = $(SRC:.c=.o)

# all : $(NAME)

# $(NAME) : $(OBJ)
# 	@echo "Building $(NAME)"
# 	@$(CC) $(CFLAGS) $(DEBUG) $^ $(LDFLAGS) -o $@
# 	@echo "\033[34m$(NAME) built successfully!\033[0m"

# $(OBJ) : %.o : %.c
# 	@echo "Building $(OBJ)"
# 	@$(CC) -c $(CFLAGS) $(DEBUG) $(LDFLAGS) $< -o $@
# 	@echo "Built $(OBJ)"

# clean :
# 	@echo "Removing $(OBJ)"
# 	@rm -f $(OBJ)
# 	@echo "Removed $(OBJ)"

# fclean : clean
# 	@echo "Removing $(NAME)"
# 	@rm -f $(NAME)
# 	@echo "Removed $(NAME)"

# re : fclean all

# .PHONY :
# 	all clean fclean re