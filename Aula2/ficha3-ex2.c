#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

void simula_processamento();

int main() { 
  int r, i, status; 

  r = fork(); //cria novo processo. Novo processo executa o mesmo programa (a partir do fork).O valor de retorno, no processo inicial ("pai"), é o PID do novo processo ("filho"). O valor de retorno para o filho é 0.
  printf("pid = %d, ppid = %d\n", getpid(), getppid()); 
  sleep(1); 
  srandom(getpid()); 

  if(r==0) //Condição verdadeira apenas no processo filho...
  { 
    //...e portanto, apenas o processo filho executa código seguinte
    for(i=0;i<20;++i) { 
      simula_processamento(); 
      printf("%d ",i); 
      fflush(stdout); 
    } 
    exit(1); //Termina processo (neste caso, o processo filho)
  }  

  //Entretanto, o processo pai também já está a executar este código
  for(i=20;i<40;++i) { 
    simula_processamento(); 
    printf("%d ",i); 
    fflush(stdout); 
  } 

  r = wait(&status); //Processo inicial ("pai") aguarda que o filho termine
  printf("\n"); 
  if(WIFEXITED(status)) 
    printf("Valor de retorno de (%d): %d\n", r, WEXITSTATUS(status)); 
  else 
    printf("Filho (%d) terminou de forma anormal\n", r); 

  return 0; 
} 



//Apenas uma função para consumir tempo de CPU. 
//Usa a função random() para não consumir sempre o mesmo tempo (ajustar NELEM para alterar tempos de execução).
#define NELEM 64 
void simula_processamento() { 
  int i,j; 
  double d1[NELEM]; 
  for(i=0;i<random();++i) { 
    for(j=0;j<NELEM;++j) 
      d1[j]=d1[j]*1.1; 
  } 
}
