CC = gcc
CFLAGS = -Wall -o
#LDFLAGS = -lssl -lcrypto -pthread  # Add this line to link against OpenSSL libraries

riscv: src/main.c
	$(CC) $(CFLAGS) riscv-simulator src/main.c src/instructions.c #$(LDFLAGS)  # Include LDFLAGS here

clean:
	rm -f riscv-simulator