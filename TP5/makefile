CC = gcc
BUILD_FOLDER := build
exec = bal_1 bal_2 bal_3s bal_3c bal_4s bal_4c bal_5s bal_5c
lib = -lpthread

all : $(addprefix $(BUILD_FOLDER)/,$(exec))


$(BUILD_FOLDER)/bal_1 : bal_1.c
	$(CC) $^ -o $@

$(BUILD_FOLDER)/bal_2 : bal_2.c
	$(CC) $^ -o $@

$(BUILD_FOLDER)/bal_3c : bal_3c.c
	$(CC) $^ -o $@

$(BUILD_FOLDER)/bal_3s : bal_3s.c
	$(CC) $^ -o $@

$(BUILD_FOLDER)/bal_4c : bal_4c.c
	$(CC) $^ -o $@ $(lib)

$(BUILD_FOLDER)/bal_4s : bal_4s.c
	$(CC) $^ -o $@ $(lib)


$(BUILD_FOLDER)/bal_5c : bal_5c.c
	$(CC) $^ -o $@ $(lib)

$(BUILD_FOLDER)/bal_5s : bal_5s.c
	$(CC) $^ -o $@ $(lib)

clean :
	rm $(BUILD_FOLDER)/*
