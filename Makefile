NAME    = philo
CC = gcc
INC = philo.h
CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread -g
RM = rm -rf

SRCS    =	philo.c \
			philofill.c \
			looping.c \
			looper.c \
			ex.c \


OBJS = $(SRCS:.c=.o)

Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) ${CFLAGS} $(OBJS) -o $(NAME)
	@echo $(B)philo is created

%.o: %.c $(INC)
	@echo $(R)Complining [$<]
	@$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@$(RM) $(OBJS)
	@echo $(R)Removed [$(OBJS)]

fclean: clean
	@$(RM) $(NAME)
	@echo $(R)Removed [$(NAME)]

re: fclean all

.PHONY: all, clean, fclean, re
