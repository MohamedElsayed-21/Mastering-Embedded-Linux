#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define PATH_MAX 100

int main() {
    char buf[PATH_MAX];

    if (getcwd(buf, sizeof(buf)) != NULL) {
        if (write(1, buf, strlen(buf)) < 0) {
            exit(-1);
        }
        write(1, "\n", 1); // Print a newline after the path
    } else {
        perror("getcwd() error");
        exit(-2);
    }

    return 0;
}


