#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>

int main(){
  key_t key = ftok("./semfile",'A');
  int semid = semget(key, 1, IPC_CREAT | 0666);
  semctl(semid, 0, SETVAL,1);
  printf("SemID = %d\n",semid);
  return 0;
}
