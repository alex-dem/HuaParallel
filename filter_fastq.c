#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAXLINE 100
#define WinLen 10
#define WinThres 20
#define min(X, Y) (((X) < (Y)) ? (X) : (Y))

int main(int argc,char **argv)
{

  int i;

// Malloc for a 2-dimensional array of strings with
// 4 lines and MAXLINE of characters per line
  char ** line;
  line=(char**)malloc(sizeof(char*)*4 );
  for(i=0;i<4;i++)
    line[i]=(char*)malloc(sizeof(char)*MAXLINE );

// Open the file given from CLI
  FILE * fp= fopen(argv[1], "r");

   size_t len = 0;


// read line-by-line the 4 lines of the file
// and store each in the array named line
  for(i=0;i<4;i++)
  {
    getline(&line[i], &len, fp);
  }

// The number of nucleotides in the second line
// or equally in the last line
  int MaxLen=strlen(line[1])-1;
  printf("Number of Nucelotides %d:\n", MaxLen);

  // length of line[1] and line[3] MUST be equally
  if (strlen(line[3])!=strlen(line[1]))
  {
    printf("ERROR Lines 2 and 4 have different length\n");
    exit(-1);
  }


  float Qual=0;

  //for (i=0;i<MaxLen;i++)
  //printf("%c %d\n",line[3][i],line[3][i]-33);

// start and end position of the window
  int start=0;
  int end=start+WinLen;

Qual=WinThres+1;
// slide the window while
// the end position has not reached the end of the line
// and the Quality is above the minimum threshold
  while ((end<=MaxLen)&&Qual>WinThres)
  {
  //  printf("%c %d\n",line[3][start],line[3][start]-33);
    printf("Window at position (%d,%d)\n",start,end-1);

    Qual=0;
    for (int k=start;k<end;k++)
      Qual+=line[3][k]-33;
    printf("Accumulated Qual=%f \t Mean Qual=%f \n",Qual,Qual/WinLen);
    Qual/=WinLen;

//slide the window by one position to the right
    start++;
    end=start+WinLen;
  }
  start--;
  printf("Nucelotides after position %d have mean window quality under %d\n",start,WinThres);

// trim out the filter positions from
// the second and the last lines up to
  strncpy(line[1],line[1],start);
  line[1][start]='\0';
  strncpy(line[3],line[3],start);
  line[3][start]='\0';

//print the filtered fastq
  printf("%s",line[0] );
  printf("%s\n",line[1] );
  printf("%s",line[2] );
  printf("%s\n",line[3] );


// free the allocated memory
  for (i=0;i<4;i++)
    free(line[i]);
  free(line);

  //close the file opened
  fclose(fp);

  exit(0);

}
