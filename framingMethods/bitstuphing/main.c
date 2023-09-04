#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>


void decodeBitStuffedFrame(char* frame){
    char decodedFrame[100];

    int onesCount = 0 ; 
    for(int i = 8; i < strlen(frame)-8;i++){
        if(frame[i]=='0'){
            strcat(decodedFrame,"0");
            onesCount = 0 ; 
        }
        if(frame[i]=='1'&&onesCount +1 == 5){
            strcat(decodedFrame,"1");
            i++;//skip the stuffed zero
        }
        if(frame[i] == '1'){
            strcat(decodedFrame,"1");
            onesCount++;
        }
    }

    printf("\n\ndecoded frame:%s\n\n",decodedFrame);
}


int main(){
   char myframe[100] ;
    
    printf("enter the no of bits of data of data you want to send:");
    int payloadLength;
    scanf("%d",&payloadLength);
    
    //now we have the payload length
    strcat(myframe,"0111110 ");
    int consecOnes = 0 ;
    char currentBit;
    for (int i = 0; i < payloadLength; i++)
    {
        printf("\nmyframe:%s\n",myframe);
        getchar();
        scanf("%c",&currentBit);
        printf("\ncurrent bit:%c\n",currentBit);
        if(currentBit=='1'){
            strcat(myframe,"1");;
            consecOnes++;
            if(consecOnes==5){
                strcat(myframe,"0");
            
            consecOnes = 0 ;
            }
        }
        else {
            strcat(myframe,"0");
            consecOnes = 0 ; 
            
        }

       
       

    }
    strcat(myframe," 01111110");
    printf("\nThe frame after bit stuffing will be: %s",myframe);

    decodeBitStuffedFrame(myframe);
    


}
