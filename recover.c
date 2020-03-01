/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 #include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


int main(int argc, char* argv[])
{
    // open raw card
    FILE* file = fopen("card.raw", "r");
 
    
    //holds the number of picture
    int k = 0;
	// for holding the current file
    FILE* current;
    
 	// for formatting the name of files
    char title[16];
    
    
    while(true)
    {   
        // array of bytes for reading into initially.
        uint8_t buffer [512];
        // checks for the end of file, if found breaks out of loop.
        if( (fread(&buffer, 512, 1, file)) == 0 )
        {
            free(current);
            break;
        }
        
        // check if a jpeg signature is found
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2]== 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1) )
        {
            // close current file
            if(k > 0)
            {
                fclose(current);
            }
            //formats title as required
            sprintf(title, "%03d.jpg", k);
            //opens a new file.
            FILE* img = fopen(title, "w");
            current = img;
            if (img == NULL)
            {
                fclose(img);
                fprintf(stderr, "Could not create %s.\n", title);
                return 3;
            }
            // updates the name for next jpg file name.
            k ++;
            
        }
        if (k > 0)
        {
            // writes to the newly created file.
            fwrite(&buffer, 512, 1, current);
        }
        
    }

    // close the card.
    fclose(file);
    return 0;
}
