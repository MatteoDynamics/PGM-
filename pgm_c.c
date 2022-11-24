#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#pragma pack(1)
#define file_name_size 1000
/**
 * @brief struct image PGM called pgm_image
 * 
 */
typedef struct PGM
{
   char type[3];
   int width;
   int height;
   int max;
   int **data;
}pgm_image;
//
/**
 * @function that ignores comments and whitetypes
 *
 * @param file
 */

void ignore_comments(FILE *file)
{
    int a;
    char row[100];
    while((a=fgetc(file))!=EOF && isspace(a));
    if (a=='#')
    {
        fgets(row, sizeof(row),file);
        ignore_comments(file);
    }
    else fseek(file,-1,SEEK_CUR);
}
/**
 * @function reading data into struct pgm_image
 *
 * @param pgm pointer to struct pgm_image
 * @param filename name of file
 */

void allocate_data(pgm_image*pgm, const char*filename)
{
    FILE* pgm_file = fopen(filename, "r");
    if(pgm_file == NULL)
    {
        printf("couldnt find the file\n");
        exit(-1);
    }
    ignore_comments(pgm_file);
    fscanf(pgm_file, "%s" , pgm->type);
    //if(ok==0)
   // {
    //    fseek(pgm_file,1,SEEK_CUR);
   // }
    if(strcmp(pgm->type, "P2"))
    {
        printf("worng type of file\n");
        exit(-1);
    }
    ignore_comments(pgm_file);

    fscanf(pgm_file, "%d %d", &(pgm->width), &(pgm->height));
    ignore_comments(pgm_file);

    fscanf(pgm_file, "%d", &(pgm->max));
    ignore_comments(pgm_file);

    pgm->data = malloc(pgm->height * sizeof(unsigned int*));

    for (int i = 0; i < pgm->height; i++) 
    {
            pgm->data[i]= malloc(pgm->width* sizeof(unsigned int));
            if (pgm->data[i] == NULL) 
            {
                printf("malloc failed\n");
                exit(-1);
            }
            
    }

    /**
     * @brief reading data into dynamicly allocated array 
     */
    
    for (int i = 0; i < pgm->height; i++)
            {
                for(int j=0; j< pgm->width; j++)
                {
                ignore_comments(pgm_file);
                fscanf(pgm_file,"%d", &(pgm->data[i][j]));
                ignore_comments(pgm_file);
                }
            }
    fclose(pgm_file);
}



char * file_name_input()
{
    printf("please type in file name:   ");
    char *name, c;
    int i = 0;
    name = (char*)malloc(1*sizeof(char));
    if(name==NULL)
    {
        printf("Wrong!");
        exit(-1);
    }
    while(c = getc(stdin),c!='\n' && c!=EOF)
    {
      name[i] = c;
      i++;
      realloc(name,i*sizeof(char));
      if(name==NULL)
    {
        printf("Wrong!");
        exit(-1);
    }
    }
    name[i] = '\0';
   // for (int j=0; j<i; j++)
   // printf("%c", name[j]);
    return name;

}
void allocate_array()
{

}

void print_context(pgm_image * pgm)
{
    printf("type = %s\n", pgm->type);
    printf("width = %d\n", pgm->width);
    printf("height = %d\n", pgm->height);
    printf("max = %d\n", pgm->max);
    for (int i = 0 ; i<pgm->height; i++)
    {
        for (int j=0 ; j< pgm->width; j++)
        {
            printf("%d ", pgm->data[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    pgm_image* pgm = malloc(sizeof(struct PGM));
    char *filename = file_name_input();
    allocate_data(pgm,filename);
    print_context(pgm);
    //allocate_array();
    


}