#include <unistd.h>
#include <sys/types.h>
# include <wait.h> 

int main(){
    pid_t pid= fork();

    if (pid==0){
        //Processo-Filho
        write(STDOUT_FILENO,"world !\n",8);

    }else{
        //Processo-Pai
        write(STDOUT_FILENO,"Hello ",6);     
    }
    return 0;

}

/*5a
pid_t pid= fork();

    if (pid==0){
        //Processo-Filho
        write(STDOUT_FILENO,"Hello ",6);
    }else{
        //Processo-Pai
        int i;
        wait(&i);
        write(STDOUT_FILENO,"world !\n",8);     
    }
    return 0;
*/