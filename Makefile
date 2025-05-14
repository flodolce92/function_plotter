# =============================================================================
# Colors for Output
# =============================================================================
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
RED			=	\033[0;31m
BLUE		=	\033[0;34m
RESET		=	\033[0m

# =============================================================================
# Directories and Files
# =============================================================================
SRCS_DIR	=	src
OBJS_DIR	=	obj
LIB_DIR		=	lib
MLX_DIR		=	$(LIB_DIR)/mlx_linux
LIBFT_DIR	=	$(LIB_DIR)/libft

SRC			=	main.c \
				free_all.c \
				init.c \
				hooks.c
SRCS		=	$(addprefix $(SRCS_DIR)/, $(SRC))
OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRC:.c=.o))

# =============================================================================
# Compiler and Flags
# =============================================================================
NAME		=	draw
CC			=	gcc
CFLAGS		=	#-Wall -Wextra -Werror
RM			=	rm -f
INCLUDES	=	-I/usr/include -I$(MLX_DIR) -O3 -I$(LIBFT_DIR)
MLX_FLAGS	=	-L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz
LIBFT_FLAGS	=	-L$(LIBFT_DIR) -lft

# =============================================================================
# Rules
# =============================================================================
# Default rule: Build the executable
all:			$(NAME)

# Create the object directory
$(OBJS_DIR):
				@echo "$(YELLOW)Creating object directory...$(RESET)"
				@mkdir -p $(OBJS_DIR)

# Compile source files into object files
$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c | $(OBJS_DIR)
				@echo "$(BLUE)Compiling $<...$(RESET)"
				@$(CC) $(CFLAGS) -c -g $< -o $@ $(INCLUDES)

# Link object files to create the executable
$(NAME):		$(OBJS_DIR) $(OBJS)
				@echo "$(YELLOW)Compiling mlx_linux...$(RESET)"
				@make --no-print-directory -C ./$(MLX_DIR) > /dev/null 2>&1
				@echo "$(YELLOW)Compiling libft...$(RESET)"
				@make --no-print-directory -C ./$(LIBFT_DIR) > /dev/null 2>&1
				@echo "$(GREEN)Compilation complete!$(RESET)"
				@echo "$(GREEN)Linking objects and creating $(NAME)...$(RESET)"
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS) $(LIBFT_FLAGS)

# Clean object files
clean:
				@echo "$(RED)Cleaning object files...$(RESET)"
				@$(RM) $(OBJS)
				@$(RM) -r $(OBJS_DIR)
				@echo "$(RED)Cleaning mlx_linux and libft...$(RESET)"
				@make --no-print-directory -C ./$(MLX_DIR) clean > /dev/null 2>&1
				@make --no-print-directory -C ./$(LIBFT_DIR) clean > /dev/null 2>&1

# Clean object files and remove the executable
fclean:			clean
				@echo "$(RED)Removing executable...$(RESET)"
				@$(RM) $(NAME)
				@echo "$(RED)Removing libft.a...$(RESET)"
				@make --no-print-directory -C ./$(LIBFT_DIR) fclean > /dev/null 2>&1

# Rebuild the project from scratch
re:				fclean all

# Run the norminette
norm:
				@echo "$(BLUE)Running norminette...$(RESET)"
				@norminette $(SRCS) $(SRCS_DIR)/so_long.h

# Run the test
test:			all
				@./$(NAME) ./maps/test1.ber

# Run the bonus test
bonus:			all
				@./$(NAME) ./maps/enemy_map.ber

# =============================================================================
# Phony Targets
# =============================================================================
.PHONY:			all clean fclean re norm test bonus
