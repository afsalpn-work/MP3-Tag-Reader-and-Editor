#include<stdio.h>
#include<string.h>

#include "myFun.h"

int main(int argcount, char * arg[])
{

    
    char ch;

    // For Debugging

    // FILE * fptr1 = fopen("audio.mp3","r+");
    // int bytesRead;
    // char buffer[4096];
    // bytesRead = fread(buffer, 1, 200, fptr1);
    // {
    //    // printf("%d\n",bytesRead);
    //     fwrite(buffer, 1, 200, stdout);
    // }
    // fclose(fptr1);

    // return 0;

    if(!strcmp("-v",arg[1]))
    {
        FILE * fptr = fopen(arg[2],"r+");
        if((strstr(arg[2],".mp3"))==NULL)
        {
            perror("Not an mp3 file");
            return 0;
        }
        if(!checkFile(fptr))  // Checcking ID3 and Version
        {
            return 0;  // Return zero if file tag and version are different
        }

        rewind(fptr);
    
        fseek(fptr,10,SEEK_SET);

        readDetails(fptr);

        fclose(fptr);
        
    }
    else if(!strcmp("-e",arg[1]))
    {
        if((strstr(arg[4],".mp3"))==NULL)
        {
            perror("Not an mp3 file");
            return 0;
        }
        
        FILE * fptr = fopen(arg[4],"r+");

        if(!checkFile(fptr))  // Checcking ID3 and Version
        {
            return 0;  // Return zero if file tag and version are different
        }

        if(!strcmp(arg[2],"-t"))
        {
            printf(RED"New Title : %s\n"RESET,arg[3]);
            editFile(fptr,"TIT2",arg[3]);
        }
        else if(!strcmp(arg[2],"-a"))
        {
            printf(RED"New Artist Name : %s\n"RESET,arg[3]);
            editFile(fptr,"TPE1",arg[3]);
        }
        else if(!strcmp(arg[2],"-A"))
        {
            printf(RED"New Album : %s\n"RESET,arg[3]);
            editFile(fptr,"TALB",arg[3]);
        }
        else if(!strcmp(arg[2],"-y"))
        {
            printf(RED"New Year : %s\n"RESET,arg[3]);
            editFile(fptr,"TYER",arg[3]);
        }
        else if(!strcmp(arg[2],"-m"))
        {
            printf(RED"New Content : %s\n"RESET,arg[3]);
            editFile(fptr,"TCON",arg[3]);
        }
        else if(!strcmp(arg[2],"-c"))
        {
            printf(RED"New Comment : %s\n"RESET,arg[3]);
            editFile(fptr,"COMM",arg[3]);
        }
        
        int bytesRead;
        char buffer[4096];
        rewind(fptr);
        FILE * fptr2=fopen("test.mp3","r");
        while ((bytesRead = fread(buffer, 1, sizeof(buffer), fptr2)) > 0)
        {
            fwrite(buffer, 1, bytesRead, fptr);
        }
        fclose(fptr);
        fclose(fptr2);
    }
    else if(!strcmp("--help",arg[1]))
    {
        viewHelpMenu();
    }
    else 
    {
        printf(RED"Invalid Command.\n"RESET);
    }

}