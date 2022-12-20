#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
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
    if(data_base[*number_of_pgm].filename == NULL)
    {
        printf("\nMalloc Failed!");
        return 1;
    }
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
    if(data_base[*number_of_pgm].data == NULL)
    {
        printf("\nMalloc Failed!");
        return 1;
    }

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
        printf("malloc failed!");
        return 1;
    }
    while(c = getc(stdin),c!='\n' && c!=EOF)
    {
      name[i] = c;
      i++;
      realloc(name,i*sizeof(char));
      if(name==NULL)
    {
        printf("realloc failed!");
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
    printf("\n 1.ADD PGM\n2.DELETE PGM\n3.SHOW LIST PGM\n4.CHOOSE PGM\n6.QUIT\n");
    while (1) {
    printf("Type in what you want to do:    ");
    if (scanf("%d", &*option) == 1) {
      break;
    } else {
      printf("Invalid input, please try again.\n");
      while (getchar() != '\n');
    }
  }
    
}

/**
 * @brief 
 * 
 * @param data_base 
 * @param number_of_pgm 
 */
void delete_pgm(pgm_image * data_base, int *number_of_pgm)
{
    int index;
    while (1) {
    printf("Type in number to delete: ");
    if (scanf("%d", &index) == 1) {
      break;
    } else {
      printf("Invalid input, please try again.\n");
      while (getchar() != '\n');
    }
  }
    //printf("number = %d",*number_of_pgm);
    if (index < 0 || index > *number_of_pgm)
    {
        printf("Error: invalid index\n");
        return 0;
    }
    index = index -1;
    //printf("\n index = %d\n", index);

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

/**
 * @brief 
 * 
 * @param option2 
 */
void menu2(int *option2)
{
    printf("\n1) rotate 90 degree \n2) histogram\n 3) negative\n 4) noise\n 5) filter\n6)quit");
     while (1) {
    printf("Type in what you want to do:    ");
    if (scanf("%d", &*option2) == 1) {
      break;
    } else {
      printf("Invalid input, please try again.\n");
      while (getchar() != '\n');
    }
  }
    
}

/**
 * @brief 
 * 
 * @param number_of_pgm 
 */
void working_file(int *number_of_pgm)
{   int a;
    while (1) {
    printf("\nPodaj plik roboczy:  ");
    if (scanf("%d", &a) == 1) {
      break;
    } else {
      printf("Invalid input, please try again.\n");
      while (getchar() != '\n');
    }
  }
    *number_of_pgm = a-1;
}

/**
 * @brief 
 * 
 * @param data_base 
 * @param number_of_pgm 
 */
void rotate90(pgm_image * data_base, int *number_of_pgm)
{
    int ** temp;
    temp = malloc(data_base[*number_of_pgm].height*sizeof(int*));
    if(temp == NULL)
    {
        printf("\nmalloc failed!");
        return 1;
    }
    for (int i =0; i<data_base[*number_of_pgm].width ;i++)
    {
    temp[i]= malloc(data_base[*number_of_pgm].width*sizeof(int));
    if(temp[i] == NULL)
    {
        printf("\nmalloc failed!");
        return 1;
    }
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
printf("number of pgm = %d\n", *number_of_pgm);
 for (int i = 0 ; i<data_base[*number_of_pgm].height; i++)
    {
        for (int j=0 ; j< data_base[*number_of_pgm].width; j++)
        {
            printf("%d ", data_base[*number_of_pgm].data[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < data_base[*number_of_pgm].height; i++) {
    free(temp[i]);
  }
  free(temp);
}

/**
 * @brief 
 * 
 * @param data_base 
 * @param number_of_pgm 
 * @return int* 
 */
int *histogram(pgm_image * data_base, int *number_of_pgm)
{
    int * histogram = malloc((data_base[*number_of_pgm].max+1) * sizeof(int));
    if(histogram == NULL)
    {
        printf("\nmalloc failed!");
        return 1;
    }
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
        printf(" ammount[%d] = %d ", i, histogram[i]);
    }
    return histogram;
}

/**
 * @brief 
 * 
 * @param data_base 
 * @param histogram_num 
 * @param number_of_pgm 
 */
void read_to_excel(pgm_image * data_base,int * histogram_num, int *number_of_pgm)
{
    FILE *file = fopen("histogram.csv", "w");
    if (file = NULL)
    {
        return 1;
    }
    for (int i=0; i<data_base[*number_of_pgm].max+1; i++)
    {
        fprintf(file, "%d", histogram_num[i]);
    }
}

/**
 * @brief 
 * 
 * @param data_base 
 * @param number_of_pgm 
 */
void negative(pgm_image * data_base, int *number_of_pgm)
{
    int ** temp;
    temp = malloc(data_base[*number_of_pgm].height*sizeof(int*));
    if(temp == NULL)
    {
        printf("\nmalloc failed!");
        return 1;
    }
    for (int i =0; i<data_base[*number_of_pgm].width ;i++)
    {
    temp[i]= malloc(data_base[*number_of_pgm].width*sizeof(int));
    if(temp[i] == NULL)
    {
        printf("\nmalloc failed!");
        return 1;
    }
    }
    for (int i = 0; i < data_base[*number_of_pgm].height; i++) 
    {
    for (int j = 0; j < data_base[*number_of_pgm].width; j++) 
        {
        temp[i][j] = data_base[*number_of_pgm].max - data_base[*number_of_pgm].data[i][j];
        }
    }

    for (int i = 0; i < data_base[*number_of_pgm].height; i++) 
    {
    for (int j = 0; j < data_base[*number_of_pgm].width; j++) 
    {
       data_base[*number_of_pgm].data[i][j] = temp[i][j];
    }
    }
    printf("\n");
    for (int i = 0 ; i<data_base[*number_of_pgm].height; i++)
    {
        for (int j=0 ; j< data_base[*number_of_pgm].width; j++)
        {
            printf("%d ", data_base[*number_of_pgm].data[i][j]);
        }
        printf("\n");
    }
     for (int i = 0; i < data_base[*number_of_pgm].height; i++) {
    free(temp[i]);
  }
  free(temp);
}


/**
 * @brief 
 * 
 * @param data_base 
 * @param number_of_pgm 
 */
void noise(pgm_image * data_base, int *number_of_pgm)
{
    srand(time(NULL));
    int a;
    while (1) {
    printf("type probability to noise: ");
    if (scanf("%d", &a) == 1) {
      break;
    } else {
      printf("Invalid input, please try again.\n");
      while (getchar() != '\n');
    }
  }
    for (int i = 0; i < data_base[*number_of_pgm].height; i++) 
    {
    for (int j = 0; j < data_base[*number_of_pgm].width; j++) 
        {
            int r = rand()%100+1;
            if(r<=a)
            {
                int random_max_low = rand()%2;
                if(random_max_low==0)
                {
                data_base[*number_of_pgm].data[i][j] = data_base[*number_of_pgm].max;
                }
                else data_base[*number_of_pgm].data[i][j] = 0;
            }
        }
    }
    printf("\n");
    for (int i = 0 ; i<data_base[*number_of_pgm].height; i++)
    {
        for (int j=0 ; j< data_base[*number_of_pgm].width; j++)
        {
            printf("%d ", data_base[*number_of_pgm].data[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief 
 * 
 * @param data_base 
 * @param number_of_pgm 
 */
void median_filter(pgm_image * data_base, int *number_of_pgm)
{
    int ** temp;
    int size =5;
    int kernel[size];
    temp = malloc(data_base[*number_of_pgm].height*sizeof(int*));
    if(temp == NULL)
    {
        printf("\nmalloc failed!");
        return 1;
    }
    for (int i =0; i<data_base[*number_of_pgm].width ;i++)
    {
    temp[i]= malloc(data_base[*number_of_pgm].width*sizeof(int));
    if(temp[i] == NULL)
    {
        printf("\nmalloc failed!");
        return 1;
    }
    }
    for (int i = 0; i < data_base[*number_of_pgm].height; i++) 
    {
    for (int j = 0; j < data_base[*number_of_pgm].width-4; j++) 
        {   
            for (int k =0; k<size; k++)
            {
            kernel[k] = data_base[*number_of_pgm].data[i][k+j];
            }
            bubble_sort(kernel,size);
            
            data_base[*number_of_pgm].data[i][2+j] = kernel[2];
           
        }
        
    }
    for (int i = 0 ; i<data_base[*number_of_pgm].height; i++)
    {
        for (int j=0 ; j< data_base[*number_of_pgm].width; j++)
        {
            printf("%d ", data_base[*number_of_pgm].data[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < data_base[*number_of_pgm].height; i++) {
    free(temp[i]);
  }
  free(temp);
}

/**
 * @brief 
 * 
 * @param array 
 * @param size 
 */
void bubble_sort(int array[], int size)
{
    for(int i=0; i<size-1; i++)
    {
        for(int j=0; j<size-i-1; j++)
        {
            if(array[j] > array[j+1])
            {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}

int main()
{
    int option=0;int option2 = 0;int number_of_pgm=0;pgm_image * pgm; pgm_image *data_base=NULL; int *histogram_num;
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
        number_of_pgm = number_of_pgm +1;
        data_base = realloc(data_base,sizeof(struct PGM)*number_of_pgm);
        if (data_base==NULL)
    {
        printf("Couldnt allocate a memory");
            number_of_pgm =number_of_pgm -1;
        return 1;
    }
        number_of_pgm = number_of_pgm -1;
        printf("\nobraz[%d]\n", number_of_pgm);
        allocate_data(data_base, filename, &number_of_pgm);
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
            printf("\nFilename: %s\n", data_base[0+i].filename);
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
                }break;
                case 2:
                {
                    histogram_num = histogram(data_base, &number_of_pgm);
                    //read_to_excel(data_base,histogram_num, &number_of_pgm);
                }break;

                case 3:
                {
                    negative(data_base, &number_of_pgm);
                }break;

                case 4:
                {
                    noise(data_base, &number_of_pgm);
                }break;

                case 5:
                {
                    median_filter(data_base, &number_of_pgm);
                }break;
                case 6:
                {
                    printf("quitting");
                    for (int i = 0; i < number_of_pgm; i++) {
  // Free the dynamically allocated filename string
  free(data_base[i].filename);

  // Free the dynamically allocated data array
  for (int j = 0; j < data_base[i].height; j++) {
    free(data_base[i].data[j]);
  }
  free(data_base[i].data);
}

// Free the dynamically allocated array of structures
free(data_base);
printf("\nfree memory!");
                }break;
            }
            }while(option2 ==1 || option2 ==2 || option2 ==3 || option2 ==4 || option2 == 5);
        }break;

        case 5:
        {
        printf("quitting");
                    for (int i = 0; i < number_of_pgm; i++) {
  // Free the dynamically allocated filename string
  free(data_base[i].filename);

  // Free the dynamically allocated data array
  for (int j = 0; j < data_base[i].height; j++) {
    free(data_base[i].data[j]);
  }
  free(data_base[i].data);
}

// Free the dynamically allocated array of structures
free(data_base);
printf("\nfree memory!");
        }break;
        
    }
    }while(option==1 || option==2 || option==3);
}