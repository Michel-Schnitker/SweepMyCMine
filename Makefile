CFLAGS = -g -Wall
TARGETS = sweepMyCMine

PAK += -lncurses

SRC += code/main.c

output: $(SRC)
	clang -std=c99 $(SRC) $(PAK) $(CFLAGS) -o $(TARGETS)

clean clear:
	rm $(TARGETS)

run:
	./$(TARGETS)

debug:
	gdb ./$(TARGETS) -ex "so gdbHelper"