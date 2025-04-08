# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDE = -I./includes -I./libft

# gdb ./minishell
# run
# backtrace

# Directories
OBJ_DIR = ./obj
SRC_DIR = ./src
INCLUDES_DIR = ./includes
LIBFT_DIR = ./libft

# Create necessary directories for build
OBJ_DIRS = $(OBJ_DIR) \
           $(OBJ_DIR)/main \
           $(OBJ_DIR)/lexer_parser \
           $(OBJ_DIR)/environment_management \
           $(OBJ_DIR)/signal_handling

# Source files organization by component

# Main Program Loop
MAIN_SRC = main.c display_command.c display_command_details.c display_redirections.c
MAIN = $(addprefix $(SRC_DIR)/main/, $(MAIN_SRC))
MAIN_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(MAIN))

# Tokenizer & Parser
LEXER_PARSER_SRC = count_command.c \
extract_command.c \
ft_add_io_file.c \
ft_add_redirection.c \
ft_arrange_table.c \
ft_checkforgarbage.c \
ft_check_redirect.c \
ft_create_fullcmd.c \
ft_expand_variable.c \
ft_extract_env_var.c \
ft_free_cmdlist.c \
ft_free_dstr.c \
ft_get_redirection.c \
ft_lexer.c \
ft_many_cmd.c \
ft_many_redirect.c \
ft_parse_input.c \
ft_parser.c \
ft_process_quotes.c \
ft_realloc.c \
ft_removesurplusspaces.c \
ft_resize_string_array.c \
ft_tokenize.c \
handle_expansion.c \
parse_cmd_into_array.c \
tokenize_parse_and_link_commands.c

LEXER_PARSER = $(addprefix $(SRC_DIR)/lexer_parser/, $(LEXER_PARSER_SRC))
LEXER_PARSER_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(LEXER_PARSER))

# Environment Management
ENV_MGMT_SRC = free_list.c ft_create_env_node.c ft_get_envp.c
ENV_MGMT = $(addprefix $(SRC_DIR)/environment_management/, $(ENV_MGMT_SRC))
ENV_MGMT_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(ENV_MGMT))

# Signal Handling
SIGNAL_SRC = signal.c
SIGNAL = $(addprefix $(SRC_DIR)/signal_handling/, $(SIGNAL_SRC))
SIGNAL_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SIGNAL))

# All objects combined
OBJ = $(MAIN_OBJ) $(LEXER_PARSER_OBJ) $(ENV_MGMT_OBJ) $(SIGNAL_OBJ)

# Target executable
NAME = minishell

# External libraries
LIBS = -L$(LIBFT_DIR) -lft -lreadline

# Rules
all: $(NAME)

# Create directories first
$(OBJ_DIRS):
	@mkdir -p $@

# Create object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIRS)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJ)
	@echo "Building libft..."
	@make -C $(LIBFT_DIR)
	@echo "Building minishell..."
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "Build complete!"

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "Clean complete!"

fclean: clean
	@echo "Cleaning executable..."
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "Full clean complete!"

re: fclean all

check-env-dir:
	@if [ -d "$(SRC_DIR)/environment_management" ]; then \
		echo "Directory $(SRC_DIR)/environment_management exists"; \
	else \
		echo "Directory $(SRC_DIR)/environment_management does NOT exist"; \
		echo "Current directory structure:"; \
		find $(SRC_DIR) -type d | sort; \
	fi

check-env-files:
	@echo "Looking for environment management files..."
	@for file in $(ENV_MGMT_SRC); do \
		if [ -f "$(SRC_DIR)/environment_management/$$file" ]; then \
			echo "Found: $(SRC_DIR)/environment_management/$$file"; \
		else \
			echo "MISSING: $(SRC_DIR)/environment_management/$$file"; \
		fi; \
	done

.PHONY: all clean fclean re check-env-dir check-env-files
