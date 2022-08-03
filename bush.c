#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
char *a[128];
char l[1024];
void sighand(int no){signal(SIGINT, sighand); fflush(stdout);}
void sp(char *l){
  const char s[128] = " ";
  char *tok;
  tok = strtok(l,s);
  for (int i = 0; tok != NULL; i++){
    a[i] = tok;
    tok = strtok(NULL, s);
   }
}
int ex(char *l, char **a){
  if(strcmp(a[0],"exit")==0){exit(0);}
  pid_t pid = fork();
  if (!pid){
    if (execvp(a[0], a) == -1){
      puts("cant find command");
      exit(0);
    }
  }
  return 0;
}
int main(void){
  signal(SIGINT, sighand);
  while(1){
    if(!fgets(l,1024,stdin)) return 0;
    l[strlen(l)-1] = 0;
    sp(l);
    ex(l, a);
  }
}
