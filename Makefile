# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/01 14:28:59 by acesar-l          #+#    #+#              #
#    Updated: 2022/04/04 20:08:59 by acesar-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= so_long

GREEN		= \033[0;32m
RED		= \033[0;31m
RESET		= \033[0m

REMOVE		= rm -rf

CC		= clang

STANDARD_FLAGS	= -Wall -Wextra -Werror
MINILIBX_FLAGS	= -lmlx -lXext -lX11 -lm 

LIBFT 		= libraries/Libft/libft.a
LIBFT_PATH	= libraries/Libft

SRC_DIR 	= ./sources
OBJ_DIR 	= ./objects

SOURCES		= 	sources/so_long.c				\
			sources/check_command_line_arguments.c		\
			sources/check_for_invalid_map_parameters.c	\
			sources/check_map.c				\
			sources/check_map_parameters.c			\
			sources/error_msg.c				\
			sources/init_game.c				\
			sources/init_map.c				\
			sources/init_vars.c				\
			sources/set_start_position.c			\
			sources/strlen_line.c

OBJECTS		= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

${LIBFT}:
		make bonus -C ${LIBFT_PATH}
		@echo

all:		${NAME}

${NAME}:	${LIBFT} $(OBJ_DIR) ${OBJECTS}
		@echo
		@echo "$(NAME): $(GREEN)${NAME} was created$(RESET)"
		${CC} -o ${NAME} ${SOURCES} ${LIBFT} ${STANDARD_FLAGS} ${MINILIBX_FLAGS}
		@echo

clean:
		make clean -C ${LIBFT_PATH}
		@echo
		@echo "$(NAME): $(RED)object files were deleted$(RESET)"
		${REMOVE} ${OBJECTS}
		@echo

fclean:	
		make fclean -C ${LIBFT_PATH}
		@echo "$(NAME): $(RED)object files were deleted$(RESET)"
		${REMOVE} ${OBJ_DIR}
		@echo
		@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"
		${REMOVE} ${NAME}

re:		fclean all

.PHONY:		all clean fclean re
