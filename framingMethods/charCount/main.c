#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

int main(){
    char myframe[100];
    while(1){
        int currFrameLen;
        printf("Enter the length of the current frame: ");
        scanf("%d",&currFrameLen);
        getchar();

        if(currFrameLen==-1){
            printf("\nThe final string is:%s",myframe);
            return 0 ;
        }
        char framelen[2] ;
        sprintf(framelen,"%d",currFrameLen);
        strcat(myframe,framelen);



        for(int i = 1 ; i < currFrameLen ; i++){
            char currentBit;
            printf("Enter bit no %d for current Frame: ",i);
            scanf("%c",&currentBit);
            getchar();
            char mystr[2];
            mystr[0] = currentBit;
            strcat(myframe,mystr);

        }

    }
}