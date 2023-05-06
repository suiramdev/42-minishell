SRCS				=			srcs/main/main.c  \
								srcs/parsing/create_linked_list.c \
								srcs/parsing/parsing.c \
								srcs/parsing/handle_file.c \
								srcs/parsing/heredoc.c \
								srcs/utils/free.c \
								srcs/utils/parsing_utils.c \
								srcs/utils/list_utils.c \
								srcs/utils/signals.c

NAME				=			minishell

CC					=			cc

CFLAGS				=			-Wall -Wextra -Werror

OBJS				=			$(SRCS:.c=.o)

all					:			$(NAME)

$(NAME)				:			$(OBJS)
								make -C libft/ && mv libft/libft.a .
								$(CC) -g -o $(NAME) $(OBJS) -lreadline libft.a
								@echo "===== minishell has been created ====="

clean				:
								make clean -C libft/
								rm -rf $(OBJS)
								@echo "===== temporary files has been deleted ====="

fclean				: 			clean
								rm -rf $(NAME) libft.a
								@echo "===== minishell has been deleted ====="

re					:			fclean all

.PHONY				:			all bonus clean fclean re
								@echo "===== minishell created, deleted and re-created done ====="

