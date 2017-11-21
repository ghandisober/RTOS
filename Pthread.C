/*                	   German Jordanian University                      *
 * 			Department of Computer Engineering                  *
 *                       CE 705: Real Time Systems                          *
 *          Program demonstrating the use of pthread_create ()              * 
 *                                                                          *
 ****************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg);          //thread function  
char message[] = "Hello World";           

int main()
{
  int retVal;
  pthread_t a_thread;                       //pthread object
  void *thread_result;                      //pointer to result

  retVal = pthread_create(&a_thread,NULL,thread_function,(void *)message);
  if(retVal != 0)
    {
      perror("Thread creation failed\n");
      exit(EXIT_FAILURE);
    }

  printf("Waiting for thread to finish...\n");

  retVal = pthread_join(a_thread,&thread_result); //waiting for the thread
  if(retVal != 0)                                 //to join
    {
      perror("Thread join failed\n");
      exit(EXIT_FAILURE);
    } 

  printf("Thread joined, it returned %s",(char *)thread_result); //print the 
                                                        //return value    
  printf("Message is now %s",message);
  exit(EXIT_SUCCESS);
}
    
void *thread_function(void *arg)
{
  printf("Thread function is running. Argument was %s\n",(char *)arg);
  sleep(1);
  strcpy(message,"Bye\n");
  pthread_exit("Thank you for the CPU time\n");  
}
  




