#include <pthread.h>
#include <stdio.h>

void* run(void* arg){
printf("Thread is running!\n");
return NULL;
}

int main() {
pthread_t t;
pthread_create(&t, NULL, run, NULL);
pthread_join(t, NULL);
return 0;
}
