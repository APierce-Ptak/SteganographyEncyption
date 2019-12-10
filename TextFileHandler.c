#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "head.h"


int SIZE;

char *byte_to_binary(int byte)
{
    static char buffer[9];
    buffer[0] = '\0';

    int size;
    for (size = 128; size > 0; size >>= 1)
    {
        strcat(buffer, ((byte & size) == size) ? "1" : "0");
    }

    return buffer;
}

void openTextAsArray()
{
    int placementCounter =0;
    FILE *sourceFile;
    char ch;


    //open the source file in read mode
    sourceFile = fopen(getTextFileName(), "r");
    //error handling
    if (!sourceFile)
    {
            printf("Unable to open the input file!!\n");
            exit(1);
    }
    
    
    
    size_t pos = ftell(sourceFile);
    fseek(sourceFile, 0, SEEK_END);
    size_t file_size = ftell(sourceFile);
    fseek(sourceFile, pos, SEEK_SET);
    SIZE = file_size*8;
    text_data = (bool*) malloc(SIZE);



    //read text from sourceFile, output to the targetFile as binary
    while (!feof(sourceFile))
    {
            //reading one byte of data
            int success = fread(&ch, sizeof(char), 1, sourceFile);
            if(success < 0)
            {
              printf("Read error\n");
              exit(1);
            }
            char* num = byte_to_binary(ch);
            for(int i=0;i<8;i++)
            {
              if ((int)num[i] == 49) //checking for a 1 in ASCII since reading from char*
              {
                text_data[placementCounter] = 1;
              }
              else
              {
                text_data[placementCounter] = 0;
              }
              placementCounter++;
            }
    }

    // close files
    fclose(sourceFile);
    return;
}

int getTextFileSize()
{
  return SIZE;
}
