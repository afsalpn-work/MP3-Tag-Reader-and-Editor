#include<stdio.h>
#include<string.h>

#include "myFun.h"


void convertLittleEndian(int * intbuff)
{
    char * ch=(char*)(intbuff);

// reversing to little endian
    char temp=*ch;
    *(ch)=*(ch+3);
    *(ch+3)=temp;

    temp=*(ch+1);
    *(ch+1)=*(ch+2);
    *(ch+2)=temp;     
}

void readContent(FILE * fptr)
{
        // Reading the size of content
        int size;
        fread(&size,1,4,fptr);

        convertLittleEndian(&size);

        fseek(fptr,3,SEEK_CUR);

        char buffcontent[size];
        fread(buffcontent,1,size-1,fptr);

        for(int i=0;i<size-1;i++)
        {
            putchar(buffcontent[i]);
        }
        printf("\n");
}

// Read Details
void readDetails(FILE * fptr)
{

    printf("-------------------------SELECTED VIEW DETAILS-------------------------\n");
    printf("-----------------------------------------------------------------------\n");
    printf("%55s","MP3 TAG READER AND EDITOR FOR ID3v2\n");
    printf("-----------------------------------------------------------------------\n");

    char buff[5]={0};
    while(strcmp(buff,"COMM"))
    {
        // Reading the TAG
        fread(buff,4,1,fptr);
        
        // Checking Which tag is present
        if(!(strcmp(buff,"TIT2")))
        {
            printf("%-15s : ","TITLE");
        }
        else if(!(strcmp(buff,"TYER")))
        {
            printf("%-15s : ","YEAR");
        }
        else if(!(strcmp(buff,"TALB")))
        {
            printf("%-15s : ","ALBUM");
        }
        else if(!(strcmp(buff,"TPE1")))
        {
            printf("%-15s : ","ARTIST");
        }
        else if(!(strcmp(buff,"TCON")))
        {
            printf("%-15s : ","GENRE");
        }
        else if(!(strcmp(buff,"COMM")))
        {
            printf("%-15s : ","COMMENT");
        }
        else if(!(strcmp(buff,"APIC")))
        {
            printf("%-15s : ","PICTURE");
        }
        readContent(fptr);
    }
    printf("-----------------------------------------------------------------------\n");
}

// Check File 
int checkFile(FILE * fptr)
{
    rewind(fptr);

    // Checking the first 3 bits are ID3
    char check[4]={0};
    fread(check,3,1,fptr);
    if(strcmp("ID3",check))
    {
        perror("Not an ID3 format File");
        return 0;
    }

    // Checking 4 and 5 bits are 03 00
    short int n1;
    fread(&n1,1,2,fptr);
    if(n1!=3)
    {
        printf("Not the required Version\n");
        return 0;
    }
    return 1;
}


// Editing function
void editFile(FILE * fptr, char str[],char buff2[])
{
    rewind(fptr);
    char buffer[4096];
    int bytesRead;
    FILE * fptr2= fopen("test.mp3","w");

    bytesRead = fread(buffer,1,10,fptr);
    fwrite(buffer,1,10,fptr2);

    while(1)
    {
        bytesRead= fread(buffer,1,4,fptr);
        fwrite(buffer,1,4,fptr2);
        buffer[bytesRead]=0;
        int size;

        // If the required tag is present changig the content
        if(!strcmp(str,buffer))
        {
            
            fread(&size,1,4,fptr);
            convertLittleEndian(&size);
    
            int newSize;
            newSize=strlen(buff2);
            newSize++;
            convertLittleEndian(&newSize);
            fwrite(&newSize,1,4,fptr2);
            convertLittleEndian(&newSize);
            newSize--;

            fread(buffer,1,3,fptr);
            fwrite(buffer,1,3,fptr2);

            fseek(fptr,size-1,SEEK_CUR);

            fwrite(buff2,1,newSize,fptr2);

            break;
        }
        fread(&size,1,4,fptr);
        fwrite(&size,1,4,fptr2);
        convertLittleEndian(&size);

        fread(buffer,1,size+2,fptr);
        fwrite(buffer,1,size+2,fptr2);

        //fwrite("Test",1,4,fptr2);
    }

    
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), fptr)) > 0)
    {
        fwrite(buffer, 1, bytesRead, fptr2);
    }

    printf(GREEN"Editing Done . \n"RESET);

    fclose(fptr2);
}

// Help Menu

void viewHelpMenu()
{
    printf("-------------------------HELP MENU-------------------------\n");
    printf("-----------------------------------------------------------------------\n");

    printf("1. -v -> to view mp3 file contents\n");
    printf("2. -e -> to edit mp3 file contents\n");
    printf("         2.1. -t -> to edit song title\n");
    printf("         2.2. -a -> to edit artist name\n");
    printf("         2.3. -A -> to edit album name\n");
    printf("         2.4. -y -> to edit year\n");
    printf("         2.5. -m -> to edit content\n");
    printf("         2.6. -c -> to edit comment\n");

    printf("-----------------------------------------------------------------------\n");
}