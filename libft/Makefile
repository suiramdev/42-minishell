# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 10:15:50 by zdevove           #+#    #+#              #
#    Updated: 2023/01/03 09:15:06 by zdevove          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS				=			ft_atoi.c\
								ft_isprint.c\
								ft_putchar_fd.c\
								ft_striteri.c\
								ft_strnstr.c\
								ft_bzero.c\
								ft_itoa.c\
								ft_putendl_fd.c\
								ft_strjoin.c\
								ft_strrchr.c\
								ft_calloc.c\
								ft_memchr.c\
								ft_putnbr_fd.c\
								ft_strlcat.c\
								ft_strtrim.c\
								ft_isalnum.c\
								ft_memcmp.c\
								ft_putstr_fd.c\
								ft_strlcpy.c\
								ft_substr.c\
								ft_isalpha.c\
								ft_memcpy.c\
								ft_split.c\
								ft_strlen.c\
								ft_tolower.c\
								ft_isascii.c\
								ft_memmove.c\
								ft_strchr.c\
								ft_strmapi.c\
								ft_toupper.c\
								ft_isdigit.c\
								ft_memset.c\
								ft_strdup.c\
								ft_strncmp.c\
								get_next_line.c\
								get_next_line_utils.c

SRCS_BONUS			=			ft_lstadd_back.c\
								ft_lstadd_front.c\
								ft_lstclear.c\
								ft_lstdelone.c\
								ft_lstiter.c\
								ft_lstlast.c\
								ft_lstmap.c\
								ft_lstnew.c\
								ft_lstsize.c\

NAME				=			libft.a

FLAGS				=			-Wall -Wextra -Werror

CC					=			cc

OBJ					=			$(SRCS:.c=.o)

OBJ_BONUS			=			$(SRCS_BONUS:.c=.o)

all					:			$(NAME)

$(NAME)				:
								$(CC) $(FLAGS) -c libft.h $(SRCS)
								ar -rc $(NAME) $(OBJ)
								@echo "===== libft has been created ====="

bonus				:			
								$(CC) $(FLAGS) -c libft.h $(SRCS_BONUS) $(SRCS)
								ar -rc $(NAME) $(OBJ_BONUS) $(OBJ)
								@echo "===== libft bonus has been created ====="

clean				:
								rm -rf $(OBJ) $(OBJ_BONUS)
								@echo "===== temporary files had been deleted ====="

fclean				: 			clean
								rm -rf $(NAME)
								@echo "===== libft has been deleted ====="

re					:			fclean all

.PHONY				:			all clean fclean re bonus
								@echo "===== libft created, delete and re-created done ====="
