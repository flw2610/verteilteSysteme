#include <stdio.h>

int main(){

  for(int i=1; i<=3; i++){
  int res = fork(); 
  if(res ==0) printf("kind(pid: %d) wurde erzeugt in loop(i: %d)\n",getpid(),i); 
   
  else if(res == -1){
      perror("hier ist ein fehler passiert");
      exit(1);
    }
  else printf("vater(pid: %d) hat kind(pid: %d) erzeugt in loop(i: %d)\n",getpid(),res, i);
  }
  
  return 0;
}


