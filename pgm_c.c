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
   char * filename;
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
    }data_base[*number_of_pgm].filename = malloc(strlen(filename) + 1);
  strcpy(data_base[*number_of_pgm].filename, filename);
    ignore_comments(pgm_file);
    fscanf(pgm_file, "%s" , data_base[*number_of_pgm].type);
    if(strcmp(data_base[*number_of_pgm].type, "P2"))
    {
        printf("worng type of file\n");
        return 1;
    }
    ignore_comments(pgm_file);

    fscanf(pgm_file, "%d %d", &(data_base[*number_of_pgm].width), &(data_base[*number_of_pgm].height));
    ignore_comments(pgm_file);

    fscanf(pgm_file, "%d", &(data_base[*number_of_pgm].max));
    ignore_comments(pgm_file);

    data_base[*number_of_pgm].data = malloc(data_base[*number_of_pgm].height * sizeof(unsigned int*));

    for (int i = 0; i < data_base[*number_of_pgm].height; i++) 
    {
            data_base[*number_of_pgm].data[i]= malloc(data_base[*number_of_pgm].width* sizeof(unsigned int));
            if (data_base[*number_of_pgm].data[i] == NULL) 
            {
                printf("malloc failed\n");
                return 1;
            }
            
    }

    /**
     * @brief reading data into dynamicly allocated data_base 
     */
    
    for (int i = 0; i < data_base[*number_of_pgm].height; i++)
            {
                for(int j=0; j< data_base[*number_of_pgm].width; j++)
                {
                ignore_comments(pgm_file);
                fscanf(pgm_file,"%d", &(data_base[*number_of_pgm].data[i][j]));
                ignore_comments(pgm_file);
                }
            }
    fclose(pgm_file);
    *number_of_pgm = *number_of_pgm+1;
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

void print_context(pgm_image * data_base, int number_of_pgm)
{
    number_of_pgm = number_of_pgm-1;
    printf("type = %s\n", data_base[number_of_pgm].type);
    printf("width = %d\n", data_base[number_of_pgm].width);
    printf("height = %d\n", data_base[number_of_pgm].height);
    printf("max = %d\n", data_base[number_of_pgm].max);
    for (int i = 0 ; i<data_base[number_of_pgm].height; i++)
    {
        for (int j=0 ; j< data_base[number_of_pgm].width; j++)
        {
            printf("%d ", data_base[number_of_pgm].data[i][j]);
        }
        printf("\n");
    }
}

void allocate_tab(pgm_image * data_base, int * number_of_pgm)
{
    *number_of_pgm = *number_of_pgm +1;
    //printf("number = %d", *number_of_pgm);
    data_base = realloc(data_base,sizeof(pgm_image)*(*number_of_pgm));
    if (data_base==NULL)
    {
        printf("Couldnt allocate a memory");
        *number_of_pgm =*number_of_pgm -1;
        return 1;
    }
    *number_of_pgm = *number_of_pgm -1;
    printf("size of struct = %d", *number_of_pgm);
}
void menu(int *option)
{   
    printf("\n 1.ADD PGM\n2.DELETE PGM\n3.SHOW LIST PGM\n4.CHOOSE PGM\n");
    printf("\nType in what you d like to do:  ");
    scanf("%d",&*option);
    
}

void delete_pgm(pgm_image * data_base, int *number_of_pgm)
{
    int index;
    printf("Type in number to delete: ");
    scanf("%d", &index);
    printf("number = %d",*number_of_pgm);
    if (index < 0 || index > *number_of_pgm)
    {
        printf("Error: invalid index\n");
        return 0;
    }
    index = index -1;
    printf("\n index = %d\n", index);

    // Shift all elements after the index-th element one position to the left
    for (int i = index; i < *number_of_pgm - 1; i++) 
    {
        data_base[i] = data_base[i + 1];
    }

    // Resize the array by one element
    *number_of_pgm = *number_of_pgm - 1;
    data_base = realloc(data_base, sizeof(pgm_image) * (*number_of_pgm));
    if (data_base == NULL)
    {
        printf("Error: realloc failed\n");
        return 0;
    }
}

void print_pgm_list(pgm_image *data_base, int number_of_pgm)
{
    printf("List of PGM images:\n");
    for (int i = 0; i < number_of_pgm; i++)
    {
        //printf("Image %d: %s\n", i + 1, data_base[i].name);
    }
}
void menu2(int *option2)
{
    printf("\n1) rotate 90 degree \n2) histogram\n 3) negative\n 4) noise\n 5) filter\n");
    printf("Type in what you want to do:    ");
    scanf("%d", &*option2);
    
}
void working_file(int *number_of_pgm)
{   int a;
    printf("Podaj plik roboczy:  ");
    scanf("%d", &a);
    *number_of_pgm = a-1;
}

void rotate90(pgm_image * data_base, int *number_of_pgm)
{
    int ** temp;
    temp = malloc(data_base[*number_of_pgm].height*sizeof(int*));
    for (int i =0; i<data_base[*number_of_pgm].width ;i++)
    {
    temp[i]= malloc(data_base[*number_of_pgm].width*sizeof(int));
    }
    for (int i = 0; i < data_base[*number_of_pgm].height; i++) 
    {
    for (int j = 0; j < data_base[*number_of_pgm].width; j++) 
    {
        temp[j][data_base[*number_of_pgm].height - 1 - i] = data_base[*number_of_pgm].data[i][j];
    }
}
for (int i = 0; i < data_base[*number_of_pgm].height; i++) 
    {
    for (int j = 0; j < data_base[*number_of_pgm].width; j++) 
    {
       data_base[*number_of_pgm].data[i][j] = temp[i][j];
    }
}
//print
printf("number of pgm = %d\n", *number_of_pgm);
 for (int i = 0 ; i<data_base[*number_of_pgm].height; i++)
    {
        for (int j=0 ; j< data_base[*number_of_pgm].width; j++)
        {
            printf("%d ", data_base[*number_of_pgm].data[i][j]);
        }
        printf("\n");
    }
}

int *histogram(pgm_image * data_base, int *number_of_pgm)
{
    int histogram[data_base[*number_of_pgm].max+1];
for (int i = 0; i < data_base[*number_of_pgm].max+1; i++) {
  histogram[i] = 0;
}
     for (int i = 0 ; i<data_base[*number_of_pgm].height; i++)
    {
        for (int j=0 ; j< data_base[*number_of_pgm].width; j++)
        {
            int number = data_base[*number_of_pgm].data[i][j];
            histogram[number]++;
        }
    }
    for (int i =0; i<data_base[*number_of_pgm].max+1; i++)
    {
        printf(" ammount[%d] = %d", i, histogram[i]);
    }
    return histogram;
}

int main()
{
    int option=0;int option2 = 0;int number_of_pgm=0;pgm_image * pgm; pgm_image *data_base=NULL; int *histogram_num;
    do{
    menu(&option);
    printf("option = %d", option);
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
        number_of_pgm = number_of_pgm +1;
        data_base = realloc(data_base,sizeof(struct PGM)*number_of_pgm);
        if (data_base==NULL)
    {
        printf("Couldnt allocate a memory");
            number_of_pgm =number_of_pgm -1;
        return 1;
    }
        number_of_pgm = number_of_pgm -1;
       // allocate_tab(data_base, &number_of_pgm);
        printf("\nobraz[%d]\n", number_of_pgm);
        allocate_data(data_base, filename, &number_of_pgm);
        //number_of_pgm = 0;
        print_context(data_base, number_of_pgm);
        
        }break;


        /**
         * @brief DELETE ADDED FILES
         * 
         */
        case 2:
        {
            delete_pgm(data_base, &number_of_pgm);
            
        }break;


        /**
         * @brief SHOW ADDED FILES
         * 
         */
        case 3:
        {   for(int i=0; i<number_of_pgm; i++)
            printf("Filename: %s\n", data_base[0+i].filename);
             //print_pgm_list(data_base, number_of_pgm);
        }break;


        /**
         * @brief CHOOSE ACTIVE FILE TO MODIFY IT
         * 
         */
        case 4:
        {
            working_file(&number_of_pgm);
            do{
            menu2(&option2);
            switch(option2)
            {
                /**
                 * @brief ROTATION 90*
                 * 
                 */
                case 1: 
                {
                    rotate90(data_base, &number_of_pgm);
                }
                case 2:
                {
                    histogram_num = histogram(data_base, &number_of_pgm);
                }

                case 3:
                {

                }

                case 4:
                {

                }

                case 5:
                {

                }
            }
            }while(option2 ==1 || option2 ==2 || option2 ==3 || option2 ==4 || option2 == 5);
        }break;

        case 5:
        {
        printf("Quitting");
        for(int i=0; i<number_of_pgm; i++)
            free(data_base[0+i].filename);
        return 1;
        }break;
        
    }
    }while(option==1 || option==2 || option==3);
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