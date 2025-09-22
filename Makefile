# ---------------------- Variables ---------------------------------------------

# Executable
NAME = minishell

# Commands
CC = cc
RM            = rm -rf


# Compiling Flags
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR)
LDFLAGS = -lreadline -L$(LIBFT_DIR) -lft

# Directorys
INC_DIR = includes
LIBS_DIR = libs
LIBFT_DIR = $(LIBS_DIR)/libft
OBJ_DIR = obj
SRC_DIR = src

# SRCs Find
SRCS = $(shell find $(SRC_DIR) -name "*.c")

# OBJs Location
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Libft Library
LIBFT = $(LIBFT_DIR)/libft.a

# Colors: use tput when available, otherwise fall back to hardcoded ANSI sequences
# `tput` is POSIX and available in most shells; this makes colors portable across
# bash, sh, dash, fish, zsh, etc. We also provide a fallback to ANSI escapes so
# Make still prints colors if tput isn't present.
TPUT := $(shell command -v tput 2>/dev/null || true)
ifneq ($(TPUT),)
	GREEN := $(shell tput setaf 2)
	RED := $(shell tput setaf 1)
	YELLOW := $(shell tput setaf 3)
	CYAN := $(shell tput setaf 6)
	RESET := $(shell tput sgr0)
else
	GREEN := \033[0;32m
	RED := \033[0;31m
	YELLOW := \033[0;33m
	CYAN := \033[0;36m
	RESET := \033[0m
endif

# ---------------------- Default -----------------------------------------------

all: $(NAME)

# ---------------------- Linking -----------------------------------------------

$(NAME): $(LIBFT) $(OBJS)
	@printf "\n"
	@printf "%b\n" "$(YELLOW)Linking Object Files to make $(NAME)...$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LDFLAGS) -o $(NAME)
	@printf "%b\n" "$(GREEN)Done! Execute ./$(NAME)$(RESET)"

# ---------------------- Compiling ---------------------------------------------

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p "$(dir $@)"
	@printf "%b\n" "$(CYAN)\n Compiling $<... $(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf "%b\n" "$(GREEN)Done Compiling $< $(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# ---------------------- Cleaning ----------------------------------------------

clean:
	@printf "%b\n" "$(CYAN)\n Cleaning Object Files $(RESET)"
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@printf "%b\n" "$(GREEN) Done Cleaning Object Files $(RESET)"


fclean: clean
	@printf "%b\n" "$(RED)Removing executables...$(RESET)"
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@printf "%b\n" "$(GREEN)Done Removing the Executables $(RESET)"

re: fclean all

valgrind:
	valgrind --suppressions=./.supps/readline.supp --leak-check=full --show-leak-kinds=all --track-fds=yes ./minishell

.PHONY: all clean fclean re valgrind
