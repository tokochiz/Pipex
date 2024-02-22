NAME = pipex.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(INC_DIR)
INC_DIR = includes

SRC_DIR = srcs
SRC_FILES = pipex.c \
			error.c
			
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

FUN_DIR = functions
FUN_FILES = ft_putstr.c \
			ft_strncmp.c 

FUNS = $(addprefix $(FUN_DIR)/, $(FUN_FILES))

OBJS = $(FUNS:.c=.o) $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re