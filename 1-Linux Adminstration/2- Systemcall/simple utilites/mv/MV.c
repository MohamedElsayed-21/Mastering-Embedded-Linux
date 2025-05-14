#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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

    dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644 );  // 0644
    if (dest_fd < 0) 
    {
        perror("open destination");
        close(src_fd); // to close the file descriptor which created from the previos step.
        exit(EXIT_FAILURE);
    }

    char buff[COUNT];
    ssize_t bytesRead;
    while ((bytesRead = read(src_fd, buff, COUNT)) > 0)
     {
        ssize_t bytesWritten = write(dest_fd, buff, bytesRead);
        if ( bytesWritten != bytesRead ) 
        {
            perror("write");
            close(src_fd);
            close(dest_fd);
            exit(EXIT_FAILURE);
        }
    }

    if (bytesRead < 0) 
    {
        perror("read");
        close(src_fd);
        close(dest_fd);
        exit(EXIT_FAILURE);
    }
    
     // Remove the source file to complete the "move"
    if (unlink(argv[1]) != 0) 
    {
        perror("unlink (delete source)");
        exit(EXIT_FAILURE);
    }
    
    
    close(src_fd);
    close(dest_fd);
    return 0;
}

