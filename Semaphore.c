/*                	   German Jordanian University                      *
 * 			Department of Computer Engineering                  *
 *                       CE 705: Real Time Systems                          *
 *                Program demonstrating the use of semaphores               * 
 *                                                                          *
 ****************************************************************************/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

extern int errno;

#define SEMKEY 0x20                         //semaphore key
#define PERMS  0666                         //permission flag 


int main()
{
  int semid,pid;
  struct sembuf sop;
  semid = semget(SEMKEY,1,IPC_CREAT|PERMS); //create a semaphore
  if(semid < 0)
    printf("Error in getting semaphore: %s",strerror(errno));
  semctl(semid,0,SETVAL,1);                 //set value 1
  pid = fork();
  if(pid == 0)                              //child process 
    {
      printf("Child :: before semop\n");
      sop.sem_num = 0;
      sop.sem_op = -1;                      //wait untill the value is greater 
      sop.sem_flg = 0;                      //than or equal to 1 and 
      semop(semid,&sop,1);                  //lock the semaphore
      printf("Child :: semaphore locked\n");
      printf("Child :: entering critical section\n");
      sleep(2);                               
      printf("Child :: leaving critical section\n");
      printf("Child :: releasing semaphore\n");
      sop.sem_num = 0;
      sop.sem_op =  1;                      //add 1 to current semaphore value
      sop.sem_flg = 0;
      semop(semid,&sop,1);                  //release the semaphore 
    }
  else
    {
      printf("Parent:: before semop\n");
      sop.sem_num = 0;
      sop.sem_op = -1;                      //wait untill the value is greater 
      sop.sem_flg = 0;                      //than or equal to 1 and 
      semop(semid,&sop,1);                  //lock the semaphore
      printf("Parent:: semaphore locked\n");
      printf("Parent:: entering critical section\n");
      sleep(2);
      printf("Parent:: leaving critical section\n");
      printf("Parent:: releasing semaphore\n");
      sop.sem_num = 0;
      sop.sem_op =  1;                      //add 1 to current semaphore value
      sop.sem_flg = 0;                       
      semop(semid,&sop,1);                  //release semaphore
      wait(0);                              //wait for the child to terminate

      if(semctl(semid,0,IPC_RMID,0) < 0)    //remove the semaphore
        printf("Parent:: error in removing sempahore, %s\n",strerror(errno));
      else
        printf("Parent:: semaphore removed successfully\n");   
      exit(0);
  }
}









