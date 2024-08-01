RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
END_COLOR = \033[0m
BOLD_GREEN = \033[1;32m
BOLD_YELLOW = \033[1;33m
END = \033[0m

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
SRCS =	ft_strdup.c ft_isdigit.c ft_atoi.c ft_bzero.c ft_isalpha.c ft_isascii.c ft_isprint.c\
		ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strlcat.c ft_strlcpy.c ft_strlen.c\
		ft_tolower.c ft_toupper.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_isalnum.c ft_memcmp.c\
		ft_memchr.c ft_substr.c ft_itoa.c ft_strjoin.c ft_calloc.c ft_putstr_fd.c ft_putnbr_fd.c\
		ft_putchar_fd.c ft_putendl_fd.c ft_strtrim.c ft_striteri.c ft_strmapi.c ft_split.c\
		ft_printf.c ft_putnbr.c ft_itoaprintf.c ft_printf_utils.c ft_putstr.c ft_puthex.c\
		ft_putptr.c ft_typefinder.c ft_putunsigned.c get_next_line_bonus.c get_next_line_utils_bonus.c\
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c\
		ft_lstdelone.c ft_lstmap.c ft_lstiter.c ft_lstclear.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

clean:
	@rm -rf $(OBJS) $(BONUS_OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
