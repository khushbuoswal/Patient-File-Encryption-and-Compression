CC = gcc
CFLAGS = -Wall -Wextra -g

SRCS = main.c patient.c patient_encryption.c rle_compression.c vigenere_encryption.c
HDRS = patient.h patient_encryption.h rle_compression.h vigenere_encryption.h

EXEC = main.out

all: $(EXEC)

$(EXEC): $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) $(SRCS) -o $(EXEC)

clean:
	rm -f $(EXEC)
