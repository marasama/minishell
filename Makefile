NAME	:= minishell
CC		:= gcc
INCLUDE	:= minishell.h
CFLAGS	:= -ggdb -I $(INCLUDE) -I ./libft/libft.h
LIBFT	= libft
FLAGS	= -Wall -Wextra -Werror -g

SRC		:=	check_builtin.c \
			echo_env.c \
			export_unset.c \
			cd.c \
			utils2.c \
			check.c \
			check_utils.c \
			dup2_fd.c \
			exec_free.c \
			exec_free2.c \
			exec.c \
			run_execve.c \
			run_execve1.c \
			expander.c \
			create_files_utils.c \
			create_files.c \
			heredoc_utils.c \
			heredoc.c \
			lexer.c \
			exit.c \
			main.c \
			parser.c \
			parser_utils.c \
			signal.c \
			expander_utils.c \
			utils.c \
			exec_utils.c

OBJ		:= $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling..."
	@make -C $(LIBFT)
	@cp libft/libft.a .
	@printf "\e[35mLIBFT: \e[32mDONE \e[0m\n"
	@$(CC) $(FLAGS) $(CFLAGS) $(OBJ) libft.a -lreadline -o $@
	@printf "\e[35mMINISHELL: \e[32mDONE\e[0m\n"

.c.o:
	@${CC} ${FLAGS} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
	@echo "Cleaning..."
	@make clean -C $(LIBFT)
	@rm -rf libft.a
	@rm -rf $(OBJ)

fclean: clean
	@rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
