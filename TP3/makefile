CC = gcc
BUILD_FOLDER := build
exec = q1 q3 barbier_01 barbier_02 barbier_03 barbier_04
lib = -lpthread

all : $(addprefix $(BUILD_FOLDER)/,$(exec))


$(BUILD_FOLDER)/q1 : q1.c
	$(CC) $^ -o $@ $(lib)

$(BUILD_FOLDER)/q3 : q3.c
	$(CC) $^ -o $@ $(lib)

$(BUILD_FOLDER)/barbier_01: barbier_01.c
	$(CC) $^ -o $@ $(lib)

$(BUILD_FOLDER)/barbier_02: barbier_02.c
	$(CC) $^ -o $@ $(lib)

$(BUILD_FOLDER)/barbier_03: barbier_03.c
	$(CC) $^ -o $@ $(lib)

$(BUILD_FOLDER)/barbier_04: barbier_04.c
	$(CC) $^ -o $@ $(lib)

clean :
	rm $(BUILD_FOLDER)/*
