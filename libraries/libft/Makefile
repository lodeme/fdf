NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra
SRC = \
	ft_strlen.c \
	ft_isalpha.c \
	ft_isalnum.c \
	ft_isdigit.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_strncmp.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_atoi.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strnstr.c \
	ft_bzero.c \
	ft_memset.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memchr.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_itoa.c \
	ft_split.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c
BONUS_SRC = \
	ft_lstnew.c \
	ft_lst_last.c \
	ft_lst_size.c \
	ft_lstadd_back.c \
	ft_lstadd_front.c \
	ft_lstclear.c \
	ft_lstdelone.c \
	ft_lstiter.c \
	ft_lstmap.c
OBJ = $(SRC:%.c=obj/%.o)
BONUS_OBJ = $(BONUS_SRC:%.c=bonus_obj/%.o)

all: obj $(NAME)

bonus: all bonus_obj $(BONUS_OBJ)
	ar rs $(NAME) $(BONUS_OBJ)

obj:
	mkdir -p obj

bonus_obj:
	mkdir -p bonus_obj

obj/%.o: %.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

bonus_obj/%.o: %.c | bonus_obj
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -rf obj bonus_obj

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
