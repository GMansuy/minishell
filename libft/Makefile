#Standard

NAME		=	libft.a
INCLUDES	=	include
SRCS_DIR 	=	src/
OBJS_DIR	=	obj/
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -I
RM			=	rm -rf
AR			=	ar rcs

#Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

#Sources

FTIS_DIR	=	ft_is/
FTIS		=	ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint ft_islexerchar

FTMEM_DIR	=	ft_mem/
FTMEM		=	ft_bzero ft_calloc ft_memchr ft_memcmp ft_memmove ft_memset ft_memcpy

FTPUT_DIR	=	ft_put/
FTPUT		=	ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd

FTTO_DIR	=	ft_to/
FTTO		=	ft_atoi ft_itoa ft_tolower ft_toupper ft_olditoa

FTSTR_DIR	=	ft_str/
FTSTR		=	ft_split ft_strchr ft_strdup ft_striteri ft_strjoin \
				ft_strlcat ft_strlcpy ft_strlen ft_strmapi ft_strncmp \
				ft_strnstr ft_strrchr ft_strtrim ft_substr \
				ft_oldstrdup ft_oldsplit

FTLST_DIR	=	ft_lst/
FTLST		=	ft_lstadd_back ft_lstadd_front ft_lstclear ft_lstdelone \
				ft_lstiter ft_lstlast ft_lstmap ft_lstnew ft_lstsize

PRINTF_DIR	=	printf/
PRINTF		=	args_cspdi  args_ux  display_args  ft_printf  read_arg

GNL_DIR		=	gnl/
GNL			=	get_next_line get_next_line_utils magic_gnl magic_gnl_utils

ALLOC_DIR	=	alloc/
ALLOC		=	magic_malloc magic_free magic_branch

FLEX_DIR	=	flex_print/
FLEX		=	ft_dec_fd ft_hex_fd	ft_str_fd flex_print

SRC_FILES+=$(addprefix $(FTIS_DIR),$(FTIS))
SRC_FILES+=$(addprefix $(FTMEM_DIR),$(FTMEM))
SRC_FILES+=$(addprefix $(FTPUT_DIR),$(FTPUT))
SRC_FILES+=$(addprefix $(FTTO_DIR),$(FTTO))
SRC_FILES+=$(addprefix $(FTSTR_DIR),$(FTSTR))
SRC_FILES+=$(addprefix $(FTLST_DIR),$(FTLST))
SRC_FILES+=$(addprefix $(PRINTF_DIR),$(PRINTF))
SRC_FILES+=$(addprefix $(GNL_DIR),$(GNL))
SRC_FILES+=$(addprefix $(ALLOC_DIR),$(ALLOC))
SRC_FILES+=$(addprefix $(FLEX_DIR),$(FLEX))

SRCS 		= 	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS 		= 	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRC_FILES)))

###

OBJSF		=	.cache_exists

all:		$(NAME)

$(NAME):	$(OBJS)
			$(AR) $(NAME) $(OBJS)
			ranlib $(NAME)
			@echo "$(GREEN)Libft compiled!$(DEF_COLOR)"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(OBJSF)
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJSF):
			mkdir -p $(OBJS_DIR)
			mkdir -p $(OBJS_DIR)$(FTIS_DIR)
			mkdir -p $(OBJS_DIR)$(FTMEM_DIR)
			mkdir -p $(OBJS_DIR)$(FTPUT_DIR)
			mkdir -p $(OBJS_DIR)$(FTTO_DIR)
			mkdir -p $(OBJS_DIR)$(FTSTR_DIR)
			mkdir -p $(OBJS_DIR)$(FTLST_DIR)
			mkdir -p $(OBJS_DIR)$(GNL_DIR)
			mkdir -p $(OBJS_DIR)$(PRINTF_DIR)
			mkdir -p $(OBJS_DIR)$(ALLOC_DIR)
			mkdir -p $(OBJS_DIR)$(FLEX_DIR)

clean:
			$(RM) $(OBJS_DIR)
			$(RM) $(OBJSF)
			@echo "$(BLUE)libft objects files cleaned!$(DEF_COLOR)"

fclean:		
			@make clean
			$(RM)  $(NAME)
			@echo "$(CYAN)libft executable files cleaned!$(DEF_COLOR)"

re:			
			@make fclean 
			@make all
			@echo "$(GREEN)Cleaned and rebuilt everything for libft!$(DEF_COLOR)"

norm:
	norminette $(SRCS) $(INCLUDES) | grep -v Norme -B1 || true

.PHONY:		all clean fclean re norm

.SILENT:
