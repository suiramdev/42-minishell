# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 22:19:57 by mnouchet          #+#    #+#              #
#    Updated: 2023/05/21 17:00:32 by mnouchet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
## ########################################################################## ## 
#   INGREDIENTS																  ##
## ########################################################################## ##
# LIBS			libraries to be used
# LIBS_TARGET	libraries to be built
# INCS			header file locations
#
# SRCS_DIR		source directory
# SRCS			source files
#
# BUILD_DIR		build directory
# OBJS			object files
#
# CC			compiler
# CFLAGS		compiler flags
# CPPFLAGS		preprocessor flags
# LDFLAGS		linker flags
# LDLIBS		libraries name

LIBS		:= ft					\
			   readline
LIBS_TARGET	:= libs/libft/libft.a

INCS		:= includes				\
			   libs/libft

SRCS_DIR	:= srcs
SRCS		:= main.c					\
			   types/command.c			\
			   types/env.c				\
			   types/token.c			\
			   utils/error.c			\
			   utils/signal.c			\
			   utils/str.c				\
			   utils/pipes.c			\
			   utils/env.c				\
			   utils/path.c				\
			   utils/exec/redirs.c		\
			   utils/exec/pipeline.c	\
			   utils/exec/exec.c		\
			   builtins/cd.c			\
			   builtins/echo.c			\
			   builtins/env.c			\
			   builtins/exit.c			\
			   builtins/export.c		\
			   builtins/pwd.c			\
			   builtins/unset.c

SRCS		:= $(SRCS:%=$(SRCS_DIR)/%)

BUILD_DIR	:= .build
OBJS		:= $(SRCS:$(SRCS_DIR)/%.c=$(BUILD_DIR)/%.o)

CC			:= cc
CFLAGS		:= -g3 -Wall -Wextra -Werror	
CPPFLAGS    := $(INCS:%=-I%)
LDFLAGS     := $(addprefix -L,$(dir $(LIBS_TARGET)))
LDLIBS      := $(addprefix -l,$(LIBS))

## ########################################################################## ##
#   UTENSILS																  ##
## ########################################################################## ##
# RM			force remove
# MAKEFLAGS		make flags
# DIR_UP		duplicate directory tree

RM          := rm -f
MAKEFLAGS   += --silent --no-print-directory
DIR_DUP     = mkdir -p $(@D)

## ########################################################################## ##
#   RECIPES																	  ##
## ########################################################################## ##
# all			default goal
# $(NAME)		link .o -> archive
# %.o			compilation .c -> .o
# clean			remove .o
# fclean		remove .o + binary
# re			remake default goal

all: $(NAME)

$(LIBS_TARGET):
	echo "→ Compiling $(@F)"
	$(MAKE) -C $(@D)

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c
	echo "→ Compiling $<"
	$(DIR_DUP)
	$(CC) $(CFLAGS) -c $< -o $@ $(CPPFLAGS)

$(NAME): $(LIBS_TARGET) $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDLIBS) $(LDFLAGS)
	echo "\033[0;32m✓ $@ READY\033[0m"

bonus: all

clean:
	echo "→ Removing objects"
	$(RM) $(OBJS)

fclean: clean
	echo "→ Removing binaries"
	$(RM) $(NAME)

re: fclean all

.PHONY: re
