#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LAST_MESSAGE 255

int main(void)
{
    
    int msqid;
    char pathname[]="09-2a.c";
    key_t  key;
    int i,len;

    struct mymsgbuf
    {
       long mtype;
       int myint;
    } mybuf;



    /* Create or attach message queue  */
    
    if((key = ftok(pathname,0)) < 0){
      printf("Can\'t generate key\n");
      exit(-1); 
    }
    
    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
       printf("Can\'t get msqid\n");
       exit(-1);
    }


    /* Send information */
    
    for (i = 1; i <= 5; i++){
       
       mybuf.mtype = 1;
       mybuf.myint = i;
       len = 4;
       if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0){
         printf("Can\'t send message to queue\n");
         msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
         exit(-1);
       }
    }    
       
    /* Send the last message */   
       
    mybuf.mtype = LAST_MESSAGE;   
    len         = 0;   
       
    if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0){
       printf("Can\'t send message to queue\n");
       msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
       exit(-1);
    }

    return 0;    
}
