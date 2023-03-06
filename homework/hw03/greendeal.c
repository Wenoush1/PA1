#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */
const int DAYS_IN_MONTH [13]={31,28,31,30,31,30,31,31,30,31,30,31};
const int NUMBERS[11][8]={
  {1,1,1,1,1,1,0},//0
  {0,1,1,0,0,0,0},//1
  {1,1,0,1,1,0,1},//2
  {1,1,1,1,0,0,1},//3
  {0,1,1,0,0,1,1},//4
  {1,0,1,1,0,1,1},//5
  {1,0,1,1,1,1,1},//6
  {1,1,1,0,0,0,0},//7
  {1,1,1,1,1,1,1},//8
  {1,1,1,1,0,1,1} //9

};
int isLeap(int y)
{
  
  if (y%4==0)
  {
    if (y%100==0)
    {
      if (y%400==0)
      {
        if (y%4000==0)
        {
          return 0;
        }
        return 1;
      }
      return 0;
    }
    return 1;
  }
  return 0;
}
int convertMtoD(int m,int d,int y)
{
  for (int i = 1 ; i <= m; i++)
  {
    if (i==2 && isLeap(y))
    {
      d+=29;
    }
    else
    {
      d+=DAYS_IN_MONTH[i-1];
    }
    
    
  }
  
  return d;

}
long int convertToMin(int y,int m,int d,int h,int i)
{

  d+=y*365.25;
  d= convertMtoD(m,d,y);
  i += (h*60)+(d*1440);
  return i;

}
int validInput(int y1, int m1, int d1, int h1, int i1,int y2, int m2, int d2, int h2, int i2){
  if (!(y1>=1600 && y2>=1600))
  {
    return 0;
  }
  if (!(m1>0 && m1<13 && m2>0 && m2<13))
  {
    return 0;
  }
  if (d1>DAYS_IN_MONTH[m1-1]||d2>DAYS_IN_MONTH[m2-1])
  {
    
    if ((m1==2&&isLeap(y1)&&d1<=29) || (m2==2&&isLeap(y2)&&d2<=29))
    {
      return 1;
    }
    return 0;
  }
  if (!(h1>=0 && h1<25 && h2 >=0 && h2<25))
  {
    return 0;
  }
  if (!(i1>=0&& i1<60 && i2 >= 0 && i2<60))
  {
    return 0;
  }
  if (convertToMin(y1,m1,d1,h1,i1)>convertToMin(y2,m2,d2,h2,i2))
  {
    return 0;
  }
  
  return 1;
}
int energyConsumption ( int y1, int m1, int d1, int h1, int i1,int y2, int m2, int d2, int h2, int i2, long long int * consumption )
{
  int diff,counter;
  *consumption=0;
  if (!(validInput(y1,m1,d1,h1,i1,y2,m2,d2,h2,i2)))
  {
    return 0;
  }
  if (convertToMin(y1,m1,d1,h1,i1)==convertToMin(y2,m2,d2,h2,i2))
  {
    (*consumption)=0;
    return 1;
  }
  diff = convertToMin(y2,m2,d2,h2,i2)*60 - convertToMin(y1,m1,d1,h1,i1)*60;
  while (diff>=86400)
  {
    diff-=86400;
    (*consumption)+=292886;
  }
  if (h1!=h2&&diff<3600)
  {
    for (size_t i = 0; i < 8; i++)
    {
      if (NUMBERS[(h2/10)%10][i]!=NUMBERS[(h1/10)%10][i])
      {
          (*consumption)++;
      }
        
    }
      
      
    for (size_t i = 0; i < 8; i++)
    { 
      if (NUMBERS[h2%10][i]!=NUMBERS[h1%10][i])
      {
          (*consumption)++;
      }
        
    }
    
  }
  counter=h1;
  while (diff>=3600)
  {
    
    if (counter==23)
    {
      (*consumption)+=6;
      counter=0;
    }
    else
    {
      if (((counter+1)/10)!=(counter/10))
      {
        for (size_t i = 0; i < 8; i++)
        {
          if (NUMBERS[((counter+1)/10)%10][i]!=NUMBERS[((counter)/10)%10][i])
          {
            (*consumption)++;
          }
        
        }
      
      }
      for (size_t i = 0; i < 8; i++)
      { 
        if (NUMBERS[(counter+1)%10][i]!=NUMBERS[(counter)%10][i])
        {
          (*consumption)++;
        }
        
      }
      counter++;
    }
      
    diff-=3600;
    (*consumption)+=12200;
  }
  
  
  counter=i1;
  while (diff>=60)
  {
    
    if (counter==59)
    {
      *consumption+=5;
      counter=0;
    }
    
    
    else
    {
      if (((counter+1)/10)!=(counter/10))
      {
        for (size_t i = 0; i < 8; i++)
        {
          if (NUMBERS[((counter+1)/10)][i]!=NUMBERS[((counter)/10)][i])
          {
            (*consumption)++;
          }
        
        }
      
      }
      for (size_t i = 0; i < 8; i++)
      {
        if (NUMBERS[(counter+1)%10][i]!=NUMBERS[(counter)%10][i])
        {
          (*consumption)++;
        }
        
      }

      counter++;


    }
    diff-=60;
    (*consumption)+=200;
  }
  printf("%lld\n",*consumption);
  return 1;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  long long int consumption;
  for (size_t i = 0; i < 12; i++)
  {
    printf("%d\n",DAYS_IN_MONTH[i]);
  }
  
  /*assert ( energyConsumption ( 2021, 11,  1, 12,  0, 2021, 10,  1, 12,  0, &consumption ) == 0 );
  assert ( energyConsumption ( 2021, 10, 32, 12,  0, 2021, 11, 10, 12,  0, &consumption ) == 0 );
  assert ( energyConsumption ( 2100,  2, 29, 12,  0, 2100,  2, 29, 12,  0, &consumption ) == 0 );
  assert ( energyConsumption ( 2400,  2, 29, 12,  0, 2400,  2, 29, 12,  0, &consumption ) == 1 && consumption == 0LL );
  assert ( energyConsumption ( 2021, 10,  1, 12,  0, 2021, 10,  1, 12,  0, &consumption ) == 1 && consumption == 0LL );
  assert ( energyConsumption ( 2021, 10,  1,  0,  0, 2021, 10,  3,  0,  0, &consumption ) == 1 && consumption == 585772LL );
  assert ( energyConsumption ( 2020, 2,  28,  0,  0, 2020, 2,  29,  0,  0, &consumption ) == 1 && consumption == 292886LL );
  assert ( energyConsumption ( 2021, 10,  1,  0,  0, 2021, 10,  1, 12,  0, &consumption ) == 1 && consumption == 146443LL );
  assert ( energyConsumption ( 2021, 10,  1, 13, 15, 2021, 10,  1, 18, 45, &consumption ) == 1 && consumption == 67116LL );
  assert ( energyConsumption ( 2021, 10,  1,  0, 15, 2021, 10,  1,  0, 25, &consumption ) == 1 && consumption == 2035LL );
  assert ( energyConsumption ( 2021, 10,  1, 12,  0, 2021, 10,  1, 12,  1, &consumption ) == 1 && consumption == 204LL );
  assert ( energyConsumption ( 2021, 10,  1, 13, 0, 2021, 10,  2, 11, 0, &consumption ) == 1 && consumption == 268479LL );
  assert ( energyConsumption ( 2021, 10,  1, 13, 15, 2021, 10,  2, 11, 20, &consumption ) == 1 && consumption == 269497LL );
  assert ( energyConsumption ( 2021,  1,  1, 13, 15, 2021, 10,  5, 11, 20, &consumption ) == 1 && consumption == 81106033LL );
  assert ( energyConsumption ( 2024,  1,  1, 13, 15, 2024, 10,  5, 11, 20, &consumption ) == 1 && consumption == 81398919LL );*/
  assert ( energyConsumption ( 1900,  1,  1, 13, 15, 1900, 10,  5, 11, 20, &consumption ) == 1 && consumption == 81106033LL );
  assert ( energyConsumption ( 2021, 12,  1, 12,  0, 2021, 12,  1, 12,  1, &consumption ) == 1 && consumption == 204LL );
  assert (  energyConsumption ( 2000, 12, 26, 0, 0, 2000, 12, 31, 0, 0, &consumption ) == 1 && consumption == 1464430LL );
  assert ( energyConsumption ( 2021, 10,  1, 12,  0, 2021, 10,  1, 12,  1, &consumption ) == 1 && consumption == 204LL );
  assert ( energyConsumption ( 2400,  2, 29, 12,  0, 2400,  2, 29, 12,  0, &consumption ) == 1 && consumption == 0LL );
  return 0;
}
#endif /* __PROGTEST__ */
