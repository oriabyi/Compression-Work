.PHONY: all clean fclean re

NAME		:=	client

SRC_D		:=	src/
SRC_DI		:=	includes/
SHARED_P	:=	../generalDir/
SHARED_D	:=	$(SHARED_P)src/
SHARED_DI	:=	$(SHARED_P)includes/
OBJ_D		:=	.obj/

CLANGPP		:=	clang++

CFLAGS		:=	-Wall -Wextra -Werror -std=c++11
BFLAGS		:=	-lboost_system

IBFLAG		:=	-I /Users/ariabyi/.brew/Cellar/boost/1.68.0/include/
LBFLAG		:=	-L /Users/ariabyi/.brew/Cellar/boost/1.68.0/lib

IFLAGS		:=	-I $(SRC_DI)Client.class.hpp -I $(SHARED_DI)Header.Class.hpp -I $(SHARED_DI)Stats.Class.hpp -I $(SHARED_DI)general.hpp

SRC_F		:=	client Client.Class clientHeaderClassFunctions

SHARED_F	:=	Header.Class Stats.Class general

HDRS		:=	$(wildcard $(SRC_DI)*.hpp) $(wildcard $(SHARED_DI)*.hpp)
SRCS		:=	$(addprefix $(SRC_D), $(addsuffix .cpp, $(SRC_F)))
SRCS		+=	$(addprefix $(SHARED_D), $(addsuffix .cpp, $(SHARED_F)))
OBJS		:=	$(addprefix $(OBJ_D), $(SRCS:%.cpp=%.o))

all: $(NAME)

$(NAME): $(OBJ_D) $(OBJS)
	$(CLANGPP) $(IFLAGS) $(CFLAGS) $(BFLAGS) $(IBFLAG) $(LBFLAG) $(wildcard $(OBJ_D)$(SRC_D)*.o) -o $(NAME)
	@ echo "client: done"
$(OBJ_D):
	mkdir -p $(OBJ_D)$(SRC_D)
$(OBJ_D)%.o: %.cpp $(HDRS)
	$(CLANGPP) $(IFLAGS) $(IBFLAG) $(CFLAGS) -g -c -o $(shell echo "$@" | sed -e "s|$(SHARED_P)||g") -c $<

clean:
	@ rm -rf $(OBJ_D)
	@ echo "client: objects removed"
fclean: clean
	@ rm -f $(NAME) 
	@ echo "client: binary removed"
re: fclean all
