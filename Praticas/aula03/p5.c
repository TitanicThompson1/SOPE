#include <unistd.h>
#include <sys/types.h>
#include <wait.h> 

int main(){
    pid_t pid= fork();

    if (pid==0){
        //Processo-Filho
        
        if(fork() == 0){
            write(STDOUT_FILENO,"friends!\n",9);
        }else{
            write(STDOUT_FILENO,"my ",3);
        }
    }else{
        //Processo-Pai
        write(STDOUT_FILENO,"Hello ",6);     
    }
    return 0;

}