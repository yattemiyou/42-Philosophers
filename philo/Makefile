# （参考）
# https://zenn.dev/keitean/articles/aaef913b433677
NAME = philo

INCLUDE = -I.

SRCDIR = ./
SRCS = main.c
SRCS += fork.c
SRCS += philosopher.c
SRCS += simulation.c
SRCS += util.c

OBJS = $(addprefix $(SRCDIR),$(SRCS:%.c=%.o))

CC = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -g

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $*.o

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

valgrind: $(NAME)
	valgrind --leak-check=full ./$(NAME) 4 310 200 100

.PHONY: all clean fclean re valgrind