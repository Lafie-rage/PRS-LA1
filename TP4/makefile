CC=gcc -Wall
BUILD_DIR=build
lib=-lpthread
exe = shm_e1 shm_e2 shm_e3 shm_e4 shm_e5 shm_srv shm_cli

all : $(addprefix $(BUILD_DIR)/, $(exe))

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/shm_e1: shm_e1.c
	$(CC) $^ -o $@

$(BUILD_DIR)/shm_e2: shm_e2.c
	$(CC) $^ -o $@

$(BUILD_DIR)/shm_e3: shm_e3.c
	$(CC) $^ -o $@

$(BUILD_DIR)/shm_e4: shm_e4.c
	$(CC) $^ -o $@ $(lib)

$(BUILD_DIR)/shm_e5: shm_e5.c
	$(CC) $^ -o $@ $(lib)

$(BUILD_DIR)/shm_srv: shm_srv.c
	$(CC) $^ -o $@ $(lib)

$(BUILD_DIR)/shm_cli: shm_cli.c
	$(CC) $^ -o $@ $(lib)

clean:
	rm build/*
