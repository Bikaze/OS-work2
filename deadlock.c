#include <stdio.h>
#include <unistd.h>
void releaseLock(int lockNum);
void getLock(int lockNum);
void process1();
void process2();
void process3();
// lock prototypes 

int locks[3];

void process1() {
  // Acquire Lock 1
  getLock(1);  
  printf("Process 1: Acquired Lock 1\n");
  process2();
  
  // Try acquiring Lock 2
  getLock(2); 
  printf("Process 1: Acquired Lock 2\n");

  // Critical section    
  
  // Release locks
  releaseLock(2);
  releaseLock(1);  
}


void process2() {

  // Acquire Lock 2  
  getLock(2);
  printf("Process 2: Acquired Lock 2\n");
  process3();  

  // Try to acquire Lock 3
  getLock(3);
  printf("Process 2: Acquired Lock 3\n");

  // Critical section

  // Release Locks    
  releaseLock(3);
  releaseLock(2);   
}

void process3() {  

  // Acquire Lock 3
  getLock(3);
  printf("Process 3: Acquired Lock 3\n");

  // Try to acquire Lock 1 
  getLock(1);
  printf("Process 3: Acquired Lock 1\n");

  // Critical section
  
  // Release Locks
  releaseLock(1);
  releaseLock(3);  
}

void init_locks() {
   // Initialize all locks as free
   for(int i=0; i<3; i++){
      locks[i] = 1; 
   }
}

void getLock(int lockNum) {
   // Try to acquire lock 
   while(locks[lockNum-1] == 0) {
      // Lock not free, wait
      sleep(1); 
   }
   // Acquired lock
   locks[lockNum-1] = 0;  
}

void releaseLock(int lockNum) {

   // Release lock  
   locks[lockNum-1] = 1; 

}

int main() {
  
  init_locks();
  
  // Launch processes
  process1();
  return 0;
}