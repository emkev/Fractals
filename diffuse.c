
/* 2016.05.11 pm 23:54 , 

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int height = 5 , width = 5 ;

int random_range(int min , int max)
{
  int r ;

  r = rand() % (max - min) + min ;

  return r ;

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

  srand((unsigned)time(NULL));

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

         srand((unsigned)time(NULL));
         random() % 2  ...

         At the moment , I modified it as :

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

  a = random_range(0 , height - 1) ;
  b = random_range(0 , width - 1) ;
  printf("%d , %d\n" , a , b);
  nearanother(a , b , grid , height , width);
  plot(grid , height , width);

  printf("diffuse finish\n");
  exit(1);
}
