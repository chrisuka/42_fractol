# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/15 19:18:05 by ikarjala          #+#    #+#              #
#    Updated: 2022/11/08 23:19:56 by ikarjala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ROOT	:= ./
NAME	:= fractol
BIN		= $(ROOT)$(NAME)

CFUNC	=\
main events app_control draw_util draw_man render

SRC_DIR		= $(ROOT)src/
OBJ_DIR		= $(ROOT)obj/
INC_DIR		= $(ROOT) include/ libft/

SRC			= $(CFUNC:%=$(SRC_DIR)%.c)
OBJ			= $(CFUNC:%=$(OBJ_DIR)%.o)
INCNAME		= libft/libft include/fractol include/keysym_macos \
			  include/graphics_util
INCLUDE		= $(addprefix -I , $(INC_DIR))
RM			:= rm -f

EXT_LIBS	= libft/libft.a
LIBS		= $(LIBFT) $(MLX)
LIBFT		= -L libft -lft
MLX			= -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

CFLAGS		= -Wall -Wextra -Werror
DBFLAGS		= -g -fsanitize=address
CFSTRICT	= -Wimplicit
CC			:= clang

#=== TARGETS ====================================================================
.PHONY: all clean fclean re debug d db so strict W
all: $(NAME)
$(NAME): .buildinfo $(EXT_LIBS) $(OBJ) Makefile $(INC:%=%.h)
	@$(ECHO) $(BMSG_AR)
	@$(CC) -o $(BIN) $(CFLAGS) $(OBJ) $(INCLUDE) $(LIBS)
	@$(ECHO) $(BMSG_FIN)
	@touch .buildinfo

$(OBJ): $(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@
	@$(ECHO)	"$(COL_CS) $<$(COL_NUL)"

$(EXT_LIBS):
	@make -C $(dir $@) all

clean:
	@$(ECHO)	"Cleaning objects..."
	@$(RM) $(OBJ)
	@rm -f .buildinfo
fclean: clean
	@$(ECHO)	"Removing binaries..."
	@$(RM) $(BIN) $(BIN:.a=.so)
re: fclean all

W: strict
strict: CFLAGS += $(CFSTRICT)
strict: BMSG_FORM := = STRICT =
strict: re

d: debug
db: debug
debug: CFLAGS += $(DBFLAGS)
debug: BMSG_FORM := = DEBUG =
debug: re

#=== UTILITY ====================================================================
ECHO	:= echo
.buildinfo:
	@$(ECHO)	$(BMSG_BIN)
	@$(ECHO)	$(BMSG_CC)
	@$(ECHO)	$(BMSG_RELINK)

BMSG_BIN	= "$(COL_HL)$(NAME) :: Starting $(BMSG_FORM) build... $(COL_NUL)"
BMSG_FORM	:= = DEPLOY =

BMSG_CC		= "$(COL_HL)$(NAME) :: Using $(CC) with $(CFLAGS) $(COL_NUL)"
BMSG_RELINK	= "$(COL_HL)$(NAME) :: Compiling C objects:"
BMSG_AR		= "$(COL_HL)$(NAME) :: Linking..."
BMSG_FIN	= "$(COL_CS)$(NAME) :: Build success! $(COL_NUL)"

COL_HL		:=\033[0;33m
COL_CS		:=\033[0;32m
COL_NUL		:=\033[0;0m

CMD_NORME	= norminette -R CheckForbiddenSourceHeader
norme:
	$(CMD_NORME) $(INC_DIR)*.h $(SRC)
#==============================================================================
