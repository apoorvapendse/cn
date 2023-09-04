#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main()
{
    int bytesCount;
    char myframe[100];
    strcat(myframe,"FLAG");
    printf("enter the number of bytes you want to trasmit: ");
    scanf("%d",&bytesCount);
    getchar();
    char currentByte[9];


    for(int byte = 0 ; byte < bytesCount ; byte++)
    {
        printf("\n\n");
        strcpy(currentByte,"");
    for(int i = 1 ; i <= 8 ; i++){
        printf("Enter the %d bit of the %d byte: ",i,byte);
        scanf("%c",&currentByte[i-1]);
        getchar();
    }

    printf("\ncurrentBYTE:%s\n",currentByte);
    if(!strcmp("01111110",currentByte)){
        printf("flag byte encounterd\n");
        strcat(myframe,"ESC");
    strcat(myframe,currentByte);
    }
    else{

    strcat(myframe,currentByte);
    }

    }

    strcat(myframe,"FLAG");

    printf("Transmitted string after byte stuffing with flag byte:\n");
    printf("%s",myframe);

}