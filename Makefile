
CC ?= clang

INCPATH = ./Includes
SRCPATH = ./Sources

CFLAGS = -I $(INCPATH) -Wall -Wextra
DBGFLAGS = -ggdb3 -DDEBUG
NDBGFLAGS = -DNDEBUG
OFLAGS = -O3
LDFLAGS = -lutil

SRC = $(wildcard $(SRCPATH)/*.c)
OBJ = $(SRC:.c=.o)

RM = rm -vf

TARGET = myscript

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
