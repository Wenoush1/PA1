#include <stdio.h>

int findNumber(long long position,long long numSystem){
  char possChars[40]="0123456789abcdefghijklmnopqrstuvwxyz";
  char *refPtr=&possChars[numSystem-1];
  char *number[100];
  int increase =1;
  int remainder=0;
  for (size_t i = 0; i < 100; i++)
    {
      number[i]=&possChars[0];
    }
  
  for (int i = 1; i <= position; i+= increase)
    {
        remainder=position-i;
        /*if (increase>remainder)
        {
            break;
        }*/
        
        number[0]++;
        for (int j = 0; j < increase; j++)
        {
            if (number[j]>refPtr)
            {
                number[j]=&possChars[0];
                number[j+1]++;
                if (j+1==increase)
                {
                   increase++;
                }
                
            }
        }
        
        
        
           
    }
    
    for (int i = increase-1; i >= 0; i--)
    {
        printf("%c",*number[i]);
    }
    printf("\n");
    return remainder;
   
}


int main(void){
    long long position=-1;
    int numSystem,positionInNum,err;
    printf("Pozice a soustava:\n");
    err=0;
    
    while (scanf(" %lld",&position) == 1  && position>=0 )
    {
        if (scanf(" %d",&numSystem) !=1 || numSystem > 36 || numSystem < 2)
        {
            err=1;
            break;
        }
        
        positionInNum = findNumber(position,numSystem);
        printf("%*c\n",positionInNum+1,'^');
    }
    
    if (!feof(stdin)||err)
    {
        printf("Nespravny vstup.\n");
        return 1;
    }

    return 0;
}