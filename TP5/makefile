CC = gcc
BUILD_FOLDER := build
msg_exec = bal_1 bal_2 bal_3s bal_3c bal_4s bal_4c bal_5s bal_5c
anonymous_pipe_exec = tube_1 tube_2 tube_3
named_pipe_exec = tube_srv_n1 tube_cli_n1 tube_srv_n2 tube_cli_n2
pipe_exec = $(anonymous_pipe_exec) $(named_pipe_exec)
exec = $(msg_exec) $(pipe_exec)
lib = -lpthread

all : $(addprefix $(BUILD_FOLDER)/,$(exec))

msg : $(addprefix $(BUILD_FOLDER)/,$(msg_exec))

pipe : $(addprefix $(BUILD_FOLDER)/,$(pipe_exec))

anonymous_pipe : $(addprefix $(BUILD_FOLDER)/,$(anonymous_pipe_exec))

named_pipe : $(addprefix $(BUILD_FOLDER)/,$(named_pipe_exec))

# Mail boxes
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

# Anonymous pipes
$(BUILD_FOLDER)/tube_1 : tube_1.c
	$(CC) $^ -o $@

$(BUILD_FOLDER)/tube_2 : tube_2.c
	$(CC) $^ -o $@

$(BUILD_FOLDER)/tube_3 : tube_3.c
	$(CC) $^ -o $@

# Named pipes
$(BUILD_FOLDER)/tube_srv_n1 : tube_srv_n1.c
	$(CC) $^ -o $@

$(BUILD_FOLDER)/tube_cli_n1 : tube_cli_n1.c
	$(CC) $^ -o $@

$(BUILD_FOLDER)/tube_srv_n2 : tube_srv_n2.c
	$(CC) $^ -o $@

$(BUILD_FOLDER)/tube_cli_n2 : tube_cli_n2.c
	$(CC) $^ -o $@

clean :
	rm $(BUILD_FOLDER)/*
