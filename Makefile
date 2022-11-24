
# VARIABLES

NAME		= minishell

SRC_DIR		= src/
OBJ_DIR		= obj/
LIB_DIR		= libft
LIB			= libft/libft.a

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g -I./include -MMD -MP

RM			= rm -rf
AR			= ar rcs
SAN			= -fsanitize=address -g
READL		= -lreadline

# SOURCES

SRC_FILES 	=	0_utils/main \
				0_utils/init \
				0_utils/free \
				0_utils/msg \
				0_utils/init \
				0_utils/signal \
				0_utils/signal_pars \
				1_lexer/lexer \
				1_lexer/lexer_utils \
				1_lexer/lexer_pars \
				1_lexer/lex_lst \
				2_parser/pre_parser \
				2_parser/pre_parser_utils \
				2_parser/parser \
				2_parser/parsing_types \
				2_parser/parsing_utils \
				2_parser/get_heredoc \
				3_expander/get_env \
				3_expander/expander \
				3_expander/expander_utils \
				3_expander/expander_lst \
				3_expander/expand_heredoc \
				3_expander/add_to_env \
				3_expander/post_expander \
				4_executer/executer \
				4_executer/exec_utils \
				4_executer/set_exec \
				4_executer/pipes \
				4_executer/child_exec \
				5_builtins/is_builtin \
				5_builtins/exit_cmd \
				5_builtins/env_cmd \
				5_builtins/unset_cmd \
				5_builtins/pwd_cmd \
				5_builtins/echo_cmd \
				5_builtins/cd_cmd \
				5_builtins/export_cmd \
				5_builtins/export_no_args \
				5_builtins/export_utils \


ALL_DIRS	=	$(OBJ_DIR) \
				$(OBJ_DIR)/0_utils \
				$(OBJ_DIR)/1_lexer \
				$(OBJ_DIR)/2_parser \
				$(OBJ_DIR)/3_expander \
				$(OBJ_DIR)/4_executer \
				$(OBJ_DIR)/5_builtins \

C_FILES		=	$(addsuffix .c, $(SRC_FILES))
SRCS 		=	$(addprefix $(SRC_DIR), $(C_FILES))
OBJS 		=	$(addprefix $(OBJ_DIR), $(C_FILES:.c=.o))
DEPS		=	$(OBJS:.o=.d)


# 	MANDATORY
all: 		obj $(NAME)

$(NAME):	$(LIB) $(OBJS)
			$(CC) $(CFLAGS) $^ -o $@ $(LIB) $(READL)
			@echo "$(GREEN)$(NAME) compiled !$(DEF_COLOR)"

$(OBJ_DIR)%.o: 	$(SRC_DIR)%.c
			$(CC) $(CFLAGS) -c -o $@ $<
			@echo "$(BLUE)Creating object file -> $(WHITE)$(notdir $@)... $(RED)[Done]$(NOC)"

$(LIB):
			@echo "$(MAGENTA)Creating libft files...$(DEF_COLOR)"
			make -C ./libft

# 	RULES
obj:
			@mkdir -p $(ALL_DIRS)

clean:
			@$(RM) $(OBJ_DIR)
			@echo "$(BLUE)$(NAME) object files cleaned!$(DEF_COLOR)"

fclean:		
			@make clean
			@$(RM) $(NAME)
			@$(RM) $(NAME_BONUS)
			@$(RM) $(LIB)

re:			
			@make fclean
			@make all
			@echo "$(GREEN)Cleaned and rebuilt everything for $(NAME)!$(DEF_COLOR)"

.PHONY: all clean fclean re	

-include $(DEPS)

# COLORS

NOC = \033[0m
BOLD = \033[1m
UNDERLINE = \033[4m
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
