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

void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
 
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
 
void printArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

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

        // msgrcv to receive message 
        msgrcv(msgid, &message, sizeof(message), 1, 0); 
        
        //display the message 
        printf("Data Received is :\n");
            for(int i = 0; i<SIZE; i++) {
                printf("%d ", message.mesg_text[i]);
            }
        
        insertionSort(message.mesg_text, SIZE);

        printf("\nSorted Array is :\n");
        printArray(message.mesg_text, SIZE);
           
        //to destroy the message queue 
        msgctl(msgid, IPC_RMID, NULL);

        FILE *fptr;

        if((fptr = fopen("PID.txt", "w")) == NULL) {
            perror("file_open");
        }

        for(int i = 0; i<SIZE; i++) {
            fprintf(fptr, "%d ", message.mesg_text[i]);
        }
        fclose(fptr);
    }
}

int main() { 
    pthread_t tid;
    pthread_create(&tid, NULL, perform_work, NULL);
    pthread_join(tid, NULL);
    return 0; 
} 