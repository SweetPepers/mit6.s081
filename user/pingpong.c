#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define BUF_SIZE (16)

int main(int argc, char* argv[]){
    int pp[2];  // parent write
    int cp[2]; // child write
    pipe(pp);
    pipe(cp);
    char buf[BUF_SIZE];
    int pid = fork();
    if (pid==0){ // child
        int pid = getpid();
        close(cp[0]);
        read(pp[0], buf, sizeof(buf));
              // 4: received ping
        printf("%d: received %s\n", pid, buf);
        write(cp[1], "pong", 5);
    }else{ // parent
        int pid = getpid();
        close(pp[0]);
        write(pp[1], "ping", 5);
        read(cp[0], buf, sizeof(buf));
        printf("%d: received %s\n", pid, buf);
    }
    exit(0);
}