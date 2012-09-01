Chapter 8 - The UNIX System Interface
====================================

8.1 File Descriptors
-------------------

Since input and output involving keyboard and screen is so common, special arrangements exist to make this convenient. When the command interpreter (the `shell`) runs a program, three files are open, with file descriptors 0, 1, and 2, called the standard input, the standard output, and the standard error. If a program reads 0 and writes 1 and 2, it can do input and output without worrying about opening files.


8.2 Low Level I/O - Read and Write
---------------------------------

Input and output uses the `read` and `write` system calls

    :::c
    int n_read = read(int fd, char *buf, int n);
    int n_written = write(int fd, char *buf, int n);

Each call returns a count of the number of bytes transferred.

A program that copy anything to anything:

[copy_input_to_output.c]()

Use read to construct higher-level `get_char()`:

[my_get_char.c]()


