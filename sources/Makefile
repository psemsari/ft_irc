# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/26 21:56:29 by fdidelot          #+#    #+#              #
#    Updated: 2022/02/27 16:31:59 by bemoreau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-----------------------------------------------#
################# PROG_NAME #####################
#-----------------------------------------------#
NAME = ircserv

#-----------------------------------------------#
################## COMPILO ######################
#-----------------------------------------------#
CXX = clang++

#-----------------------------------------------#
################### PATHS #######################
#-----------------------------------------------#
PATH_HEAD	=	./headers/
PATH_SRCS	=	./sources/
PATH_OBJS	=	./objects/

#-----------------------------------------------#
################## SOURCES ######################
#-----------------------------------------------#
SRCS =		main.cpp							\
			Server.cpp							\
			Command.cpp							\
			User.cpp							\
			Channel.cpp							\
			cmdPass.cpp							\
			cmdNick.cpp							\
			cmdCap.cpp							\
			cmdMode.cpp							\
			cmdJoin.cpp							\
			cmdPing.cpp							\
			cmdPrivmsg.cpp						\
			cmdUser.cpp							\
			cmdPart.cpp							\
			cmdQuit.cpp							\
			cmdOper.cpp							\
			cmdMotd.cpp							\
			cmdList.cpp							\
			cmdKill.cpp             \
			cmdKick.cpp							\
			cmdWho.cpp							\
			cmdWhois.cpp            \
			cmdNotice.cpp						\
			cmdTopic.cpp						\
			cmdInvite.cpp

vpath %.cpp $(PATH_SRCS)

#-----------------------------------------------#
################## HEADERS ######################
#-----------------------------------------------#
HEADERS		=	Server.hpp						\
				Command.hpp						\
				User.hpp						\
				Channel.hpp

vpath %.hpp $(PATH_HEAD)

#-----------------------------------------------#
################## OBJECTS ######################
#-----------------------------------------------#
OBJS = $(addprefix $(PATH_OBJS), $(SRCS:.cpp=.o))


#-----------------------------------------------#
################### FLAGS #######################
#-----------------------------------------------#
CXXFLAGS =	-Wall -Wextra -Werror -std=c++98
ifeq ($(d), 0)
CXXFLAGS	+= -g3
CXXFLAGS	+= -Wpadded
CXXFLAGS	+= -fsanitize=address,undefined
endif
ifeq ($(d), 1)
	CXXFLAGS	+= -g
endif

#-----------------------------------------------#
################# CPPFLAGS ######################
#-----------------------------------------------#
CPPFLAGS	+=	-I $(PATH_HEAD)					\
# Multiple header directories
#CPPFLAGS	+= $(foreach DIR, $(HDRS_DIRS), $(addprefix -I , $(DIR)))
#

#-----------------------------------------------#
################# LIBRARIES #####################
#-----------------------------------------------#
ifeq ($(d), 0)
	LDFLAGS		+= -fsanitize=address,undefined
endif

#-----------------------------------------------#
################### RULES #######################
#-----------------------------------------------#

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDLIBS) $(CXXFLAGS) -g3

$(PATH_OBJS)%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(CPPFLAGS)

$(OBJS): Makefile $(HEADERS) | $(PATH_OBJS)

$(PATH_OBJS):
	mkdir $@

clean:
	rm -rf $(PATH_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
