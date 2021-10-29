#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCK_SIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //Check argument at command-line
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    //Open memory card
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    //DON'T WORRY ABOUT THIS SHIT yet
    BYTE buffer[BLOCK_SIZE];
    int counter = 0;
    char newfile_name[10000];
    FILE *newfile; 
    bool found_jpg = false;

    //Read memory card until end
    while ((fread(buffer, sizeof(BYTE), BLOCK_SIZE, file)) == BLOCK_SIZE)
    {
        //if start of new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //Close previous file
            if (counter != 0)
            {
                fclose(newfile);
            }
            
            //Name, open and write to new file
            sprintf(newfile_name, "%06i.jpg", counter);
            newfile = fopen(newfile_name, "w");
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, newfile);
            
            //Prepare for the next loop
            found_jpg = true;
            counter++;
        }
        else
        {
            //if already found JPEG, keep writing to it
            if (found_jpg)
            {
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, newfile);
            }
        }
    }
    
    //Close files
    fclose(file);
    fclose(newfile);
    
    return 0;
}