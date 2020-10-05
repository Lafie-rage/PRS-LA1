CC = gcc
exec = test_fork test_thread test_thread2_1 test_thread2_2 test_thread3_1 test_thread3_2 test_caractere test_mutex1 test_mutex2 test_mutex3
lib_thread = -lpthread

all : $(exec)

test_fork : test_fork.c
	$(CC) $^ -o $@

test_thread :  test_thread.c
	$(CC) $^ -o $@ $(lib_thread)

test_thread2_1 : test_thread2_1.c
	$(CC) $^ -o $@ $(lib_thread)

test_thread2_2 : test_thread2_2.c
	$(CC) $^ -o $@ $(lib_thread)

test_thread3_1 : test_thread3_1.c
	$(CC) $^ -o $@ $(lib_thread)

test_thread3_2 : test_thread3_2.c
	$(CC) $^ -o $@ $(lib_thread)

test_caractere : test_caractere.c
	$(CC) $^ -o $@ $(lib_thread)

test_mutex1 : test_mutex1.c
	$(CC) $^ -o $@ $(lib_thread)

test_mutex2 : test_mutex2.c
	$(CC) $^ -o $@ $(lib_thread)

test_mutex3 : test_mutex3.c
	$(CC) $^ -o $@ $(lib_thread)

clean :
	rm $(exec)
