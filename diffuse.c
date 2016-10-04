
/* 2016.05.11 pm 23:54 , 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int height = 5 , width = 5 ;
/* !!!! option_length ===== speical setting !!!!! */
int option_length = 4 ;
int posx = 0 , posy = 0 ;

/* 2016.10.04 , add the help informations for using friendly  */
char *help_string = "running options :  -heigth  -width  -posx  -posy";

typedef enum opt_type
{
  opt_int , opt_double , opt_string
} opt_type ;

typedef struct option
{
  char *name ;
  opt_type type ;
  int *ptr ;
} option ;

option options[] = {
  { "-height" , opt_int , &height } ,
  { "-width"  , opt_int , &width  } ,
  { "-posx"   , opt_int , &posx   } ,
  { "-posy"   , opt_int , &posy   }
} ;

int random_range(int min , int max)
{
  int r ;

  r = rand() % (max - min) + min ;

  return r ;

}

int another(int x , int y , char **grid)
{
  int nx , ny , i , j ;

  for(i = -1 ; i <= 1 ; i++)
  {
    for(j = -1 ; j <= 1 ; j++)
    {
      if(i == 0 && j == 0) continue ;

      nx = x + i ;
      ny = y + i ;

      nx = (nx < 0) ? (width - 1) : ((nx > width - 1) ? 0 : nx) ;
      ny = (ny < 0) ? (height - 1) : ((ny > height - 1) ? 0 : ny) ;

      if(grid[nx][ny]) 
        return(1);
    } /*  for(j = -1 ; j <= 1 ; j++)  */
  } /*  for(i = -1 ; i <= 1 ; i++)  */

  return(0);

}

void nearanother(int x , int y , char **grid , int height , int width)
{
  int i , j , nx , ny ;

  //printf("x = %d , y = %d\n" , x , y);
  if(grid[x][y] == '*')
  {
    grid[x][y] = '+';

    for(i = -1 ; i <=1 ; i++)
    {
      for(j = -1 ; j <= 1 ; j++)
      {
        if(i == 0 && j == 0) continue ;

        nx = x + i ;
        ny = y + j ;
        nx = (nx < 0) ? 0 : (nx > height) ? height : nx ;
        ny = (ny < 0) ? 0 : (ny > width) ? width : ny ;

        if(grid[nx][ny] == '*')
        {
          grid[nx][ny] = '^' ;
        }

      } /*  for(j = -1   */
    } /*  for(i = -1   */

  } /*  if(grid[x][y] == '*')  */
  else
  {
    printf("no mark\n");
  }
}

void plot(char **grid , int height , int width)
{
  int i , j ;

  for(i = 0 ; i < height ; i++)
  {
    for(j = 0 ; j < width ; j++)
    {
      //printf("i = %d , j = %d\n" , i , j);

      //if(i == 2 && j == 3) grid[i][j] = '-';

      printf("%c" , grid[i][j]);
    }
    printf("\n");
  }
}

int main(int argc , char **argv)
{
  int i , j ;
  int a , b ;
  char **grid ;
  int ar , found , opf ;

  srand((unsigned)time(NULL));

  //posx = random_range(0 , width - 1) ;
  //posy = random_range(0 , height - 1) ;
  //printf("signal p , %d , %d\n" , posx , posy);

  ar = 1 ;
  while(ar < argc)
  {
    found = 0 , opf = 0 ;
    while((!found) && (opf <= option_length - 1))
    {
      /* 2016.10.04 and 10.05 , add the help informations */
      if(strcmp(argv[ar] , "-help") == 0)
      {
        printf("%s\n" , help_string);
        exit(1);
      }
      else if(strcmp(argv[ar] , options[opf].name) == 0)
      {
        switch(options[opf].type)
	{
	case opt_int :
          found = 1 ;
          *(int *)options[opf].ptr = atoi(argv[ar + 1]) ;
          ar += 2 ;
          break ;
	case opt_double :
          found = 1 ;
          *(double *)options[opf].ptr = atof(argv[ar + 1]) ;
          ar += 2 ;
          break ;
	case opt_string :
          found = 1 ;
          *(char **)options[opf].ptr = argv[ar + 1] ;
          ar += 2 ;
          break ;
        default :
          break ;
	}
      }

      opf++ ;

    } /*  while((!found) ...  */

    if(!found)
      ar++ ;

  } /*  while(ar < argc)  */


  printf("signal p-o , %d , %d\n" , posx , posy);

  grid = malloc(sizeof(char *) * height);
  for(i = 0 ; i < height ; i++)
  {
    grid[i] = malloc(sizeof(char) * width);
    for(j = 0 ; j < width ; j++)
    {
      /* if just :
           if(random() % 2 == 1) 
             grid[i][j] = '*';

         AND , other locations of array are not given values , 
         SO , it will result in a error location-value .

         grid[2][3] = '+';

         ****
         ***
         *+*

         ***

         VERY STRANGER !!!

         SO , for this , the WAY is that it must give a init values !!! 

        */


      /* 2016.07.12 am 00:20 . 

         For long time , it fails for randoming here . Old code :

         #include <time.h>
         srand((unsigned)time(NULL));
         random() % 2  ...

         At the moment , I modified it as :

         #include <time.h>
         srand((unsigned)time(NULL));
         rand() % 2  ...

       */
      if(rand() % 2 == 1)
        grid[i][j] = '*' ;
      else
        grid[i][j] = ' ';

    } /* for(j = 0 ; j < width ;  */
  } /* for(i = 0 ; i < height ;  */

  plot(grid , height , width);
  printf("---------\n");

  //a = random_range(0 , height - 1) ;
  //b = random_range(0 , width - 1) ;
  printf("(%d , %d)\n" , posx + 1 , posy + 1) ;
  /*  (x , y) need to exchanged input to functions   */
  nearanother(posy , posx , grid , height , width);
  plot(grid , height , width);

  printf("diffuse finish\n");
  exit(1);
}
