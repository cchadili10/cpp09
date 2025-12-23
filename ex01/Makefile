NAME = RPN
CPP = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
SRC = main.cpp RPN.cpp
OBJECTS = $(SRC:.cpp=.o)

all: $(OBJECTS)
	$(CPP) $(FLAGS) $(OBJECTS) -o $(NAME)

%.o: %.cpp  RPN.hpp
	$(CPP) $(FLAGS) -c $< -o $@

clean: 
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all