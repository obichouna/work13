#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
  int fd[2];
  int fdd[2];

  //Making two pipes
  pipe(fd);
  pipe(fdd);

  //Forking one child process
  int f = fork();

  //The parent writes the data into the pipe
  if (f){
    close(fd[0]);
    int x = 64;
    write(fd[1], &x, sizeof(x));
    printf("Parent sending %d\n", x);
  }

  //The child reads the data, performs an operation, and writes it
  if(!f){
    close(fd[1]);
    int x;
    read(fd[0], &x, sizeof(x));
    x = x + x/2;
    close(fdd[0]);
    write(fdd[1], &x, sizeof(x));
    printf("Child performed operation, and now sending back \n");
  }

  //Finally, the parent reads the new value from the child
  if(f){
    close(fdd[1]);
    int x;
    read(fdd[1], &x, sizeof(x));
    printf("Parent received a new value of: %d \n", x);
  }
}
