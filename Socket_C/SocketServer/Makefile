CC = gcc
CFLAGS = -Wall -Wextra -I..
OBJ = main.o ../socket_utils.o
TARGET = server

all: $(TARGET)

$(TARGET): $(OBJ)
	@$(CC) -o $@ $^

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@


clean:
	@rm -f $(OBJ) $(TARGET)
	@echo "Cleaned client build files."

