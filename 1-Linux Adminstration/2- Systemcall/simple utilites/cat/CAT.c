#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define COUNT 100

int main(int argc, char* argv[]) {
    if (argc != 2) {
        char error_msg[100];  
        snprintf(error_msg, sizeof(error_msg), "Usage: %s <file-name>\n", argv[0]);  
        write(2, error_msg, strlen(error_msg));  
        exit(-1);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        write(2, "The file does not exist\n", strlen("The file does not exist\n"));
        exit(-2);
    }

    char buff[COUNT];
    ssize_t Chars;
    while ((Chars = read(fd, buff, COUNT)) > 0) {
        if (write(1, buff, Chars) < 0) {
            write(2, "Write failed\n", strlen("Write failed\n"));
            exit(-3);
        }
    }

    close(fd);
    return 0;
}

