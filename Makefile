# Project settings
NAME = minishell
CC = cc
ARCH := $(shell uname -m)
OS := $(shell uname -s)
INCLUDE = -I src/execution -I include -I src/parsing -I libft -I src/execution/builtins

ifneq ($(ARCH), x86_64)
	CFLAGS = -arch $(ARCH) -Wall -Wextra -Werror
else
	CFLAGS = -Wall -Wextra -Werror
endif

# For MacOS lreadline from brew is mandatory.
ifeq ($(OS), Linux)
	READLINE_LIB = -lreadline
else
	READLINE_DIR = $(shell brew --prefix readline)
	READLINE_LIB =	-I$(READLINE_DIR)/include/			\
					-L$(READLINE_DIR)/lib/				\
					-lreadline
endif

DEBUG_FLAGS = -g
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

LIBS = $(LIBFT) $(READLINE_LIB)

SRCS =	src/main.c							\
		src/utils.c							\
		src/env/env.c						\
		src/env/env_utils.c					\
		src/env/env_utils2.c				\
		src/env/env_print_utils.c			\
		src/signal/signal.c					\
		src/parsing/p_parse.c				\
		src/parsing/p_token.c				\
		src/parsing/p_cmd_list.c			\
		src/parsing/p_expansion.c			\
		src/parsing/p_mem_cleaner.c			\
		src/parsing/p_parse_utils.c			\
		src/parsing/p_parse_helpers.c		\
		src/parsing/p_cmd_list_helpers.c	\
		src/execution/e_path.c				\
		src/execution/e_pipes.c				\
		src/execution/e_builtin.c			\
		src/execution/e_execute.c			\
		src/execution/e_external.c			\
		src/execution/e_exec_pipes.c		\
		src/execution/e_redirections.c		\
		src/execution/e_heredoc.c			\
		src/execution/builtins/e_cd.c		\
		src/execution/builtins/e_cd_utils.c	\
		src/execution/builtins/e_echo.c		\
		src/execution/builtins/e_exit.c		\
		src/execution/builtins/e_pwd.c		\
		src/execution/builtins/e_env.c		\
		src/execution/builtins/e_unset.c	\
		src/execution/builtins/e_export.c
OBJS = $(SRCS:.c=.o)

all: libft_check $(LIBFT) $(NAME)

libft_check:
ifneq ($(wildcard $(LIBFT_DIR)),)
	@echo "Libft found!"
else
	@echo "Libft not found, downloading library from https://github.com/Db1zz/libft"
	git clone https://github.com/Db1zz/libft libft
	rm -rf ./libft/.git
endif

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(SRCS)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(SRCS) $(LIBS) $(INCLUDE) -o $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean:
	rm -f $(NAME) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re