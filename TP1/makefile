CC = gcc

all : get_pid_ppid infinite_loop disable_ctr_c callback_on_signal fork exo_synthese

fork : fork_3.1 fork_3.1.3 fork_3.1.5

get_pid_ppid : get_pid_ppid.c
	$(CC) $^ -o $@

infinite_loop : infinite_loop.c
	$(CC) $^ -o $@

disable_ctr_c : disable_ctr_c.c
	$(CC) $^ -o $@

callback_on_signal : callback_on_signal.c
	$(CC) $^ -o $@

fork_3.1 : fork_3.1.c
	$(CC) $^ -o $@

fork_3.1.3 : fork_3.1.3.c
	$(CC) $^ -o $@

fork_3.1.5 : fork_3.1.5.c
	$(CC) $^ -o $@

exo_synthese : exo_synthese.c
	$(CC) $^ -o $@
