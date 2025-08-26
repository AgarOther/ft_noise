# Compilation
CC					=	c++
CFLAGS				=	-Wall -Wextra -Werror -std=c++20 -g -MP -MMD

# Names
NAME				=	noise

# Sources & Includes
SRCS				= 	srcs/main.cpp \
						srcs/maths.cpp \
						srcs/Noise.cpp
LIBS_SRC			=	libs/stb/stb_image.cpp
OBJ_FOLDER			=	objs
INCLUDES			=	-I srcs \
						-I libs/stb

# Objects
OBJS				=	$(patsubst srcs/%, $(OBJ_FOLDER)/%, $(SRCS:.cpp=.o)) \
						$(patsubst libs/%, $(OBJ_FOLDER)/%, $(LIBS_SRC:.cpp=.o))
DEPS				=	$(patsubst srcs/%, $(OBJ_FOLDER)/%, $(SRCS:.cpp=.d)) \
						$(patsubst libs/%, $(OBJ_FOLDER)/%, $(LIBS_SRC:.cpp=.d))

# Custom Makefile Flags
MAKEFLAGS			+=	--no-print-directory --silent

# Custom Colors
PURPLE				=	\033[1;35m
LIGHT_GREEN			=	\033[1;32m
RESET				=	\033[0m

# Custom messages
EXE_DONE			=	@echo "🎉$(PURPLE) $(NAME) compiled! 🎉$(RESET)\n"
ALL_CLEAN			=	@echo "🧹$(LIGHT_GREEN) Project's objects cleaned! 🧹$(RESET)\n"
ALL_FCLEAN			=	@echo "🧹$(LIGHT_GREEN) Project's objects & Executables cleaned! 🧹$(RESET)\n"

# Rules

all :
	@make -j4 $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	$(EXE_DONE)

$(OBJ_FOLDER)/%.o: srcs/%.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_FOLDER)/%.o: libs/%.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean :
	@rm -rf $(OBJ_FOLDER)
	$(ALL_CLEAN)

fclean :
	@rm -f $(NAME)
	@rm -rf $(OBJ_FOLDER)
	$(ALL_FCLEAN)

run: all
	./$(NAME)

re : fclean all

.PHONY: all clean fclean re

-include $(DEPS)
