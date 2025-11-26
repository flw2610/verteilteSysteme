#include <stdio.h>
#include <sys/sem.h>
#include <sys/ipc.h>

int main(){

  for(int i=1; i<=3; i++){
  int res = fork(); 
  if(res ==0){
    printf("kind(pid: %d) wurde erzeugt in loop(i: %d)\n",getpid(),i);
    fflush(stdout);

    for(int i=0; i<3; i++){
      kritischerBereich();
    }
    nichtKritischerBereich();
  }
  else if(res == -1){
      perror("hier ist ein fehler passiert");
      exit(1);
    }
  }  
  return 0;
}

void P(int semid){
  struct sembuf p ={0, -1, 0};
  semop(semid,&p,1);
}

void V(int semid){
  struct sembuf v={0, 1, 0};
  semop(semid, &v, 1);
}

int kritischerBereich(){
  key_t key = ftok("semfile",'A');
  int semid = semget(key, 1, 0666);

  P(semid);
  printf("Prozess %d betritt kritischen Bereich\n",getpid());
  fflush(stdout);

  sleep(1);

  printf("Prozess %d verlässt kritischen Bereich\n",getpid());
  fflush(stdout);
  V(semid);
}

int nichtKritischerBereich(){
  printf("Prozess %d betritt nicht-kritischen Bereich\n",getpid());
  fflush(stdout);

  sleep(1);

  printf("Prozess %d verlässt nicht-kritischen Bereich\n",getpid());
  fflush(stdout);
}
