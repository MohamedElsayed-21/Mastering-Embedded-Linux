#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define COUNT 100

int main(int argc, char* argv[]) {
    int src_fd, dest_fd;

    if (argc != 3 || strcmp(argv[1], "--help") == 0)
    {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    src_fd = open(argv[1], O_RDONLY);
    if (src_fd < 0) 
    {
        perror("open source");
        exit(EXIT_FAILURE);
    }

    dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);  // 0644
    if (dest_fd < 0) 
    {
        perror("open destination");
        close(src_fd); // to close the file descriptor which created from the previos step.
        exit(EXIT_FAILURE);
    }

    char buff[COUNT];
    ssize_t Chars;
    while ((Chars = read(src_fd, buff, COUNT)) > 0)
     {
        if (write(dest_fd, buff, Chars) != Chars) 
        {
            perror("write");
            close(src_fd);
            close(dest_fd);
            exit(EXIT_FAILURE);
        }
    }

    if (Chars < 0) 
    {
        perror("read");
    }

    close(src_fd);
    close(dest_fd);
    return 0;
}

