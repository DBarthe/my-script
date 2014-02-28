##
## Makefile for myscript in /home/common/Dev/tek2/Unix/PSU_2013_myscript
## 
## Made by Barthelemy Delemotte
## Login   <delemo_b@epitech.net>
## 
## Started on Fri Feb 28 19:39:29 2014 Barthelemy Delemotte
## Last update Fri Feb 28 19:48:29 2014 Barthelemy Delemotte
##

CC ?= clang

INCPATH = ./Includes
SRCPATH = ./Sources

CFLAGS = -I $(INCPATH) -Wall -Wextra
DBGFLAGS = -ggdb3 -DDEBUG
NDBGFLAGS = -DNDEBUG
OFLAGS = -O3
LDFLAGS = -lutil

SRC = 	$(SRCPATH)/error.c \
	$(SRCPATH)/exit.c \
	$(SRCPATH)/main.c \
	$(SRCPATH)/master.c \
	$(SRCPATH)/mypty.c \
	$(SRCPATH)/myscript.c \
	$(SRCPATH)/options.c \
	$(SRCPATH)/print.c \
	$(SRCPATH)/sighandlers.c \

OBJ = $(SRC:.c=.o)

RM = rm -vf

TARGET = my_script

ifeq ($(DEBUG), 1)
CFLAGS += $(DBGFLAGS)
else
CFLAGS += $(NDBGFLAGS) $(OFLAGS)
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(TARGET)

re: fclean all
