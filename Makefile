NAME    := fdf
CFLAGS  := -Wextra -Wall -Wunreachable-code -Ofast -g -O0
LIBFT   := ./libraries/libft
LIBMLX  := ./libraries/mlx42
HEADERS := -I ./include -I $(LIBMLX)/include -I ./libraries/get_next_line -I $(LIBFT)
LIBS    := $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a -ldl -lglfw -pthread -lm
SRCS    :=	libraries/get_next_line/get_next_line.c \
			libraries/get_next_line/get_next_line_utils.c \
			source/main.c \
			source/plot_line.c \
			source/load_map.c \
			source/utils.c \
			source/plot_map.c \
			source/init.c \
			source/scale.c \
			source/utils2.c \
			source/ft_xtoi.c \
			source/colors.c \
			source/input.c \
			source/apply.c
OBJ_DIR := obj
SRC_DIRS := $(sort $(dir $(SRCS)))
OBJ_DIRS := $(addprefix $(OBJ_DIR)/,$(SRC_DIRS))
OBJS    := $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: directories libmlx libft $(NAME)

directories:
	@mkdir -p $(OBJ_DIRS)

libft:
	@$(MAKE) -C $(LIBFT)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT) clean
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT) fclean

re: fclean all
