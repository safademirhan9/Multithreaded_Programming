#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#define SIZE 10

struct mesg_buffer { 
    long mesg_type; 
    int mesg_text[SIZE]; 
} message;


void *perform_work(void *arguments) {
    key_t key; 
    int msgid;
    pthread_mutex_t lock;

    while(1) {
        pthread_mutex_lock(&lock);
        // ftok to generate unique key 
        key = ftok("progfile", 65);

        // msgget creates a message queue 
        // and returns identifier 
        msgid = msgget(key, 0666 | IPC_CREAT);
        message.mesg_type = 1;

        srand(time(0));
        for(int i = 0; i<SIZE; i++) {
            message.mesg_text[i] = rand()%1000;
        }

        msgsnd(msgid, &message, sizeof(message), 0);

        // display the message 
        printf("Data Sent is :\n");
        for(int i = 0; i<SIZE; i++) {
            printf("%d ", message.mesg_text[i]);
        }
        printf(" ");

        const char* fileName = "PID.txt";
        FILE *fptr;

        // if((fptr = fopen(fileName, "r")) == NULL) {
        //     perror("file not created yet!");
        // }
        
        // char sortedArray;
        // while ((sortedArray == fgetc(fptr)) != EOF) {
        //     printf("Sorted Array: %c ", sortedArray);
        // }
        // fclose(fptr);
    }
}

int main() { 
    pthread_t tid;
    pthread_create(&tid, NULL, perform_work, NULL);
    pthread_join(tid, NULL);
    return 0; 
} 