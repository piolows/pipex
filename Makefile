NAME	= pipex
CC		= cc
FLAGS	= -Wall -Wextra -Werror
LIBFT	= libft/ft_split.c libft/ft_strlen.c libft/ft_putstr_fd.c libft/ft_strdup.c \
			libft/ft_strlcpy.c libft/ft_strncmp.c libft/ft_putendl_fd.c
GNL		= get_next_line/get_next_line_bonus.c get_next_line/get_next_line_utils_bonus.c
SRCS	= mandatory/pipex.c mandatory/path.c mandatory/utils.c mandatory/processes.c $(LIBFT)
BSRCS	= bonus/pipex_bonus.c bonus/path_bonus.c bonus/utils_bonus.c bonus/here_doc_bonus.c bonus/processes_bonus.c $(LIBFT) $(GNL)
OBJS	= $(SRCS:.c=.o)
BOBJS	= $(BSRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

bonus: $(BOBJS)
	$(CC) $(FLAGS) $(BOBJS) -o $(NAME)

clean:
	rm -f $(OBJS) $(BOBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
