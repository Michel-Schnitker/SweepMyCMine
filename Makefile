#CFLAGS = -g -Wextra -Wall -Wno-long-long -pedantic-errors
CFLAGS = -g -Wextra -Wall -O3
STANDART = -std=c99
TARGET = sweepMyCMine

LIB += -lncurses

INC = -I code/library/include \
	-I code/minesweeper/include \
	-I code/solver/include \
	-I code/tests/include \
	-I code/tui/include

SRC += code/main.c \
	$(wildcard code/library/src/*.c) \
	$(wildcard code/minesweeper/src/*.c) \
	$(wildcard code/solver/src/*.c) \
	$(wildcard code/tests/src/*.c) \
	$(wildcard code/tui/src/*.c)

output: $(SRC)
	clang $(STANDART) $(SRC) $(LIB) $(INC) $(CFLAGS) -o $(TARGET)

clean clear:
	rm $(TARGET)

run:
	./$(TARGET)

debug:
	gdb ./$(TARGET) -ex "so gdbHelper"
