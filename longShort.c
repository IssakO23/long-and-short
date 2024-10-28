#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  

// conv to uppercase and write to the first dest file
void function1(char *line, FILE *outFile1) 
{
    for (int i = 0; line[i] != '\0'; i++) 
    {
        // conv to uppercase using toupper()
        line[i] = toupper(line[i]);  
    }
    // write the conv line to the file
    fprintf(outFile1, "%s", line);  
}

// conv line to lowercase and write to the second dest file
void function2(char *line, FILE *outFile2) 
{
    for (int i = 0; line[i] != '\0'; i++) 
    {
        line[i] = tolower(line[i]);  
    }
    fprintf(outFile2, "%s", line);  
}

int main(int argc, char *argv[])
{
    // check if the correct number of command-line arguments is provided
    if (argc != 4)
    {
        printf("Error: Must supply a source file and two output files.\n");
        exit(1);  
    }

    // dec file paths from command-line arguments
    char *srcFile = argv[1];      
    char *outFile1 = argv[2];    
    char *outFile2 = argv[3];     

    // open the source file for reading
    FILE *input = fopen(srcFile, "r");
    if (!input)
    {
        printf("Error: Could not open file '%s' for reading.\n", srcFile);
        exit(1);
    }

    // open the first output file for writing
    FILE *out1 = fopen(outFile1, "w");
    if (!out1)
    {
        printf("Error: Could not open file '%s' for writing.\n", outFile1);
        fclose(input);  
        exit(1);
    }

    // open the second output file for writing
    FILE *out2 = fopen(outFile2, "w");
    if (!out2)
    {
        printf("Error: Could not open file '%s' for writing.\n", outFile2);
        fclose(input);  
        fclose(out1);  
        exit(1);
    }

    // buffer for reading lines assuming its like 8.1 and 255 chars
    char line[256];
    // count lines
    int lines1 = 0;  
    int lines2 = 0;  

    // read through the source file line by line
    while (fgets(line, sizeof(line), input) != NULL)
    {
        // check the length of the line
        if (strlen(line) <= 20)
        {
            // Ccll function1 to convert the line to uppercase and write to outFile1
            function1(line, out1);
            lines1++; 
        }
        else
        {
            // call function2 to convert the line to lowercase and write to outFile2
            function2(line, out2);
            lines2++;  
        }
    }

    // print the num of lines written to each output file
    printf("%d lines written to %s\n", lines1, outFile1);
    printf("%d lines written to %s\n", lines2, outFile2);

    // close all open files
    fclose(input);
    fclose(out1);
    fclose(out2);

    return 0;
}