
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#define MAX_LINE 50

int main(void){
    

    mkfifo("/tmp/fifo_chg", 0644);

    int fd= open("/tmp/fifo_chg", O_RDONLY | O_NONBLOCK);

    int n_read = 0;
    double time = 10;
    char name[MAX_LINE], line[MAX_LINE];

    while(clock() / CLOCKS_PER_SEC < time){
        
        n_read = read(fd,name, MAX_LINE);

        if(n_read > 0){
            sprintf(line, "CHEGOU %s\n", name);
            write(STDOUT_FILENO, line, strlen(line));
            n_read = 0;
            memset(name, 0,sizeof(name));
        }

    }
    return 0;
}