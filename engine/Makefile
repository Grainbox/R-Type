##
## EPITECH PROJECT, 2023
## raytracer
## File description:
## Makefile for raytracer
##

NAME 		=  	engine

LIB_NAME	=	libengine

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	COMPILER 	= 	clang++ -std=c++17
else ifeq ($(UNAME_S),Linux)
    COMPILER	=	g++
else
    $(error "Système d'exploitation non supporté")
endif

SRC_MAIN	=	src/main.cpp

SRC			=	src/Engine.cpp          \

LIB_OUT_DIR =	./shared_libs

OBJ_MAIN    =   $(SRC_MAIN:.cpp=.o)

OBJ			=	$(SRC:.cpp=.o)

INCLUDE		=	-I ./include/ -I ./include/**/ -I ./include/ECS/**/

CXX_FLAGS 	= 	-Wall -Wextra -std=c++17

SFML		=	-lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

LIBS		=	\

TOTAL_FILES = 	$(words $(SRC))

counter 	=	0

all:		$(NAME)

COMPLETE_TEXT:
			@$(ECHO) $(BOLD) $(BLUE)"BUILD COMPELTED 🏗️"

CLEAN_TEXT:
			@$(ECHO) $(BOLD) $(BLUE)"CLEANING 🧹"

$(NAME): 	$(OBJ)	$(OBJ_MAIN)
			@$(COMPILER) -o $(NAME) $(OBJ) $(OBJ_MAIN) $(CXX_FLAGS) $(INCLUDE) $(LIBS) $(SFML)
			@make -s COMPLETE_TEXT

shared_lib: $(OBJ)
		@mkdir -p $(LIB_OUT_DIR)
		@$(COMPILER) -fPIC -shared -o $(LIB_OUT_DIR)/$(LIB_NAME).so $(OBJ) $(CXX_FLAGS) $(INCLUDE) $(SFML)
		@$(COMPILER) -shared -o $(LIB_OUT_DIR)/$(LIB_NAME).dll $(OBJ) $(CXX_FLAGS) $(INCLUDE) $(SFML)

%.o: %.cpp
			$(eval counter=$(shell echo $$(($(counter)+1))))
			$(eval percentage=$(shell echo $$((($(counter) * 100) /\
            $(TOTAL_FILES)))))
			@printf "$(PYELLOW)$(PBOLD)↦🔹[%s] ($(percentage)%%)$(PRESET)" "$(subst $(shell pwd)/,,$<)"
			@$(COMPILER) -fPIC -c $(CXX_FLAGS) $(INCLUDE) $< -o $@
			@printf "\r$(PGREEN)$(PBOLD)↦🔹[%s] ($(percentage)%%)$(PRESET)\n" "$(subst $(shell pwd)/,,$<)"

clean:
			@make -s CLEAN_TEXT
			@rm -f $(OBJ)
			@rm -f $(OBJ_MAIN)
			@rm -f $(LIB_OUT_DIR)/$(LIB_NAME).*

fclean:		clean
			@rm -f $(NAME)

re:			fclean	all

debug:		CXX_FLAGS += -g3 -ggdb
debug:		re
			@printf "$(PYELLOW)$(PBOLD) ⚠ Debug mode ON$(PRESET)\n"
			@printf "\033[1m\033[37mflags: $(CXX_FLAGS)\033[0m\n\n"

ECHO    		=       /bin/echo -e
DEFAULT 		=       "\033[00m"

DEFAULT 		=       "\e[0m"
BOLD    		=       "\e[1m"
DIM     		=       "\e[2m"
UNDLN   		=       "\e[4m"
SHINE   		=       "\e[5;37m"
RODE    		=       "\e[9;37m"

BLACK   		=       "\e[30m"
RED     		=       "\e[31m"
GREEN   		=       "\e[32m"
YELLOW  		=       "\e[33m"
BLUE    		=       "\e[34m"
MAGEN   		=       "\e[35m"
CYAN    		=       "\e[36m"
WHITE   		=       "\e[1;37m"

LIGHT_RED       =       "\e[91m"
LIGHT_GREEN     =       "\e[92m"
LIGHT_YELLOW    =       "\e[93m"
LIGHT_BLUE      =       "\e[94m"
LIGHT_MAGEN     =       "\e[95m"
LIGHT_CYAN      =       "\e[96m"

PGREEN = \033[32m
PYELLOW = \033[33m
PRESET = \033[0m
PBOLD = \033[1m