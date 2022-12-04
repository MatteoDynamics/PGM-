#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
//* IF YOU NEED TO SAVE AS MUCH MEMORY AS YOU CAN // 
//* #pragma pack(1)
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
 * @param data_base pointer to struct pgm_image
 * @param filename name of file
 */

void allocate_data(pgm_image*data_base, const char*filename, int *number_of_pgm)
{
    FILE* pgm_file = fopen(filename, "r");
    if(pgm_file == NULL)
    {
        printf("couldnt find the file\n");
        *number_of_pgm =*number_of_pgm -1;
        return 1;
    }
    ignore_comments(pgm_file);
    fscanf(pgm_file, "%s" , data_base[0].type);
    if(strcmp(data_base[0].type, "P2"))
    {
        printf("worng type of file\n");
        return 1;
    }
    ignore_comments(pgm_file);

    fscanf(pgm_file, "%d %d", &(data_base[0].width), &(data_base[0].height));
    ignore_comments(pgm_file);

    fscanf(pgm_file, "%d", &(data_base[0].max));
    ignore_comments(pgm_file);

    data_base[0].data = malloc(data_base[0].height * sizeof(unsigned int*));

    for (int i = 0; i < data_base[0].height; i++) 
    {
            data_base[0].data[i]= malloc(data_base[0].width* sizeof(unsigned int));
            if (data_base[0].data[i] == NULL) 
            {
                printf("malloc failed\n");
                return 1;
            }
            
    }

    /**
     * @brief reading data into dynamicly allocated data_base 
     */
    
    for (int i = 0; i < data_base[0].height; i++)
            {
                for(int j=0; j< data_base[0].width; j++)
                {
                ignore_comments(pgm_file);
                fscanf(pgm_file,"%d", &(data_base[0].data[i][j]));
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
        return 1;
    }
    while(c = getc(stdin),c!='\n' && c!=EOF)
    {
      name[i] = c;
      i++;
      realloc(name,i*sizeof(char));
      if(name==NULL)
    {
        printf("Wrong!");
        return 1;
    }
    }
    name[i] = '\0';
    return name;

}

/**
 * @brief FUNCTION PRINTING DATA IN STRUCTURE
 * 
 * @param pgm 
 */

void print_context(pgm_image * data_base)
{
    printf("type = %s\n", data_base[0].type);
    printf("width = %d\n", data_base[0].width);
    printf("height = %d\n", data_base[0].height);
    printf("max = %d\n", data_base[0].max);
    for (int i = 0 ; i<data_base[0].height; i++)
    {
        for (int j=0 ; j< data_base[0].width; j++)
        {
            printf("%d ", data_base[0].data[i][j]);
        }
        printf("\n");
    }
}

void allocate_tab(pgm_image * data_base, int * number_of_pgm)
{
    *number_of_pgm = *number_of_pgm +1;
    //printf("number = %d", *number_of_pgm);
    data_base = realloc(data_base,sizeof(struct PGM)*(*number_of_pgm));
    if (data_base==NULL)
    {
        printf("Couldnt allocate a memory");
        *number_of_pgm =*number_of_pgm -1;
        return 1;
    }
   // printf("size of struct = %d", sizeof(struct PGM));
}
void menu(int *option)
{   
    printf("\n 1.ADD PGM\n2.DELETE PGM\n3.SHOW LIST PGM\n4.CHOOSE PGM\n");
    printf("\nType in what you d like to do:  ");
    scanf("%d",&*option);
    
}

int main()
{
    int option=0;int number_of_pgm=0;pgm_image * pgm; pgm_image *data_base;
    do{
    menu(&option);
    switch(option)
    {
        /**
         * @brief adding new pgm
         * 
         */
        case 1:
        { 
        fflush(stdin);
        char *filename = file_name_input();
        data_base = malloc(sizeof(struct PGM)*0);
        allocate_tab(data_base, &number_of_pgm);
        printf("\nobraz[%d]\n", number_of_pgm-1);
        allocate_data(data_base, filename, &number_of_pgm);
        //print_context(data_base);
        
        }break;


        /**
         * @brief DELETE ADDED FILES
         * 
         */
        case 2:
        {
        
        }break;


        /**
         * @brief SHOW ADDED FILES
         * 
         */
        case 3:
        {
            
        }break;


        /**
         * @brief CHOOSE ACTIVE FILE TO MODIFY IT
         * 
         */
        case 4:
        {
        
        }break;

        case 5:
        {
        printf("Quitting");
        return 1;
        }break;
        
    }
    }while(option==1 || option==2 || option==3 || option==4);
   // pgm_image* pgm = malloc(sizeof(struct PGM));
   // char *filename = file_name_input();
  //  allocate_data(pgm,filename);
    
   // print_context(pgm);
}



/*void ignore_comments(FILE *file)
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
}*/