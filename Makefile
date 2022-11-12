# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/15 19:18:05 by ikarjala          #+#    #+#              #
#    Updated: 2022/11/12 22:00:25 by ikarjala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ROOT	:= ./
NAME	:= fractol
BIN		= $(ROOT)$(NAME)

CFUNC	=\
main events app_control draw_util draw_man render sampler fractals gui

SRC_DIR		= $(ROOT)src/
OBJ_DIR		= $(ROOT)obj/
INC_DIR		= $(ROOT) include/ libft/
INC_NAME	= libft/libft.h include/fractol.h include/keysym_macos.h \
			  include/graphics_util.h

SRC			= $(CFUNC:%=$(SRC_DIR)%.c)
OBJ			= $(CFUNC:%=$(OBJ_DIR)%.o)
INCLUDE		= $(addprefix -I , $(INC_DIR))
RM			:= rm -f

LIB_NAME	= libft/libft.a
LIBS		= $(LIBFT) $(MLX)
LIBFT		= -L libft -lft
MLX			= -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

CC			:= clang
CFLAGS		= -Wall -Werror -Wextra -O3
CFSTRICT	= -Wimplicit -Wunused -Wconversion
DBFLAGS		= -g -fsanitize=address

#=== TARGETS ==================================================================
.PHONY: all clean fclean re debug d db so strict W
all: $(NAME)
$(NAME): .buildinfo $(LIB_NAME) $(OBJ) Makefile $(INC_NAME)
	@$(ECHO) $(BMSG_LD)
	@$(CC) -o $(BIN) $(LIBS) $(OBJ)
	@$(ECHO) $(BMSG_FIN)

$(OBJ): $(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@
	@$(ECHO)	" $(GREEN)$<$(CNIL)"

$(LIB_NAME):
	@make -C $(dir $@) all

clean:
	@$(ECHO)	"Cleaning objects..."
	@$(RM)		$(OBJ)
	@$(RM) -d	$(OBJ_DIR)
	@$(RM) .buildinfo
fclean: clean
	@$(ECHO)	"Removing binaries..."
	@$(RM) $(BIN) $(BIN:.a=.so)
re: fclean all

W: strict
strict: CFLAGS += $(CFSTRICT)
strict: BMSG_FORM := --STRICT--
strict: re

d: debug
db: debug
debug: CFLAGS += $(DBFLAGS)
debug: BMSG_FORM := --DEBUG--
debug: re

#=== UTILITY ==================================================================
ECHO	:= echo
.buildinfo:
	@$(ECHO)	$(BMSG_BIN)
	@$(ECHO)	$(BMSG_CC)
	@touch .buildinfo

BMSG_FORM	:= --DEPLOY--
BMSG_BIN	= "$(BLUE)$(NAME) :: $(CYANB)Starting $(BMSG_FORM) build...$(CNIL)"
BMSG_CC		= "$(BLUE)$(NAME) :: $(CNIL)$(CC) $(CFLAGS)"
BMSG_LD		= "$(BLUE)$(NAME) :: $(PURPLEB)Linking: $(CNIL)$(LIBS)"
BMSG_FIN	= "$(BLUE)$(NAME) :: $(GREENB)Build success!$(CNIL)"

CNIL	:=\033[0;0m
RED		:=\033[0;31m
GREEN	:=\033[0;32m
GOLD	:=\033[0;33m
BLUE	:=\033[0;34m
PURPLE	:=\033[0;35m
CYAN	:=\033[0;36m

CYANB	:=\033[1;36m
PURPLEB	:=\033[1;35m
GREENB	:=\033[1;32m

CMD_NORME	= norminette -R CheckForbiddenSourceHeader
norme:
	$(CMD_NORME) $(INC_DIR)*.h $(SRC)*.c
run: $(NAME)
	$(BIN) julia
#==============================================================================
