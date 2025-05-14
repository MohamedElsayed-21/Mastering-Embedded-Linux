#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int main(int argc, char *argv[]) {
  


   if (argc == 1)
   {           
      write(STDOUT_FILENO, "\n", 1);
      return 0;
    }
   if (argc == 2 && strcmp(argv[1], "--help") == 0)
    {
        printf ("the usage is: %s <args to print> \n ",argv[0] );
        return -1 ;
    }
 

    for (int i = 1; i < argc; i++) {
        write(STDOUT_FILENO, argv[i], strlen(argv[i]));
        if (i < argc - 1) {
            write(STDOUT_FILENO, " ", 1);
        }
    }


     write(STDOUT_FILENO, "\n", 1);
     return 0 ; 
}
