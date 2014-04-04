#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include"tamaki.h"

#define PROCESS 3         // number of process
#define WAIT 5000000    // set wait timer[s]
const unsigned long tamaki_size = sizeof( tamaki_data ) / sizeof( tamaki_data[0] );

int main(void)
{
  char fname[100];
  char sname[100];
  int pid[PROCESS];  
  int i, j;
  FILE *fp;
    
  for( i = 0; i < PROCESS ; i++){
    
    pid[i] = fork();
    if( pid[i] == 0 ){
      fprintf(stdout,"child process %d.\tpid = %d.\tmy ppid = %d \n",i,getpid(),getppid());
      break;
    }else if(pid[i] == -1){
      fprintf(stderr,"fork failed.\n");
    } 
  }

  /* Make Deamon prosess */ 
  
  if( pid[i] != 0 && i == PROCESS ){    
    sleep(1);
    fprintf(stdout, "parents end ...\n");   
    return 0;
  }else{
    
    /* deamon process*/
    setsid();   
    if( fork() ) exit(0);
    printf("Bomb No.%d waiting ....\n",i);
    usleep(WAIT+i*200000);    

    sprintf(fname,"tamaki_out_%d.jpg",i);  
    fp = fopen(fname, "w");
    fwrite(tamaki_data, sizeof(char), tamaki_size, fp);
    fclose(fp);
    sprintf(sname,"open tamaki_out_%d.jpg",i);
      
    for( ; ; ){
      system(sname);
      usleep(500000);
      //system( "PID=`ps x | grep -v grep | grep  \"Preview\"  | awk '{ print $1 }'` ;kill $PID ");       
      //sleep(1);
    }
  }

  return 0;
}
