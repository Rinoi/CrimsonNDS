NAME	=	sharedPal

SRC	= 	src/main.cpp 		\

OBJ	=	$(SRC:.cpp=.o)

CXX	=	g++

CXXFLAGS =	-I./include -std=c++11 -W -Wall -Wextra -g

LDFLAGS =	-lsfml-system -lsfml-window -lsfml-graphics

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS) $(LDFLAGS)

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:		fclean all
