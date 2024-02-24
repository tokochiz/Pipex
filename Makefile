NAME = pipex.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(INC_DIR)
INC_DIR = includes

SRC_DIR = srcs
SRC_FILES = pipex.c \
			error.c \
			
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

LIBFT = libft/libft.a

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(LIBFT): 
	make -C libft 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re