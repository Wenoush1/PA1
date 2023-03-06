#include <stdio.h> 
#include <stdlib.h>

static int idArray[1000000];
void addId( int id, int * length,int *amountArray)
{
    int count=1;
    
    count=amountArray[id];
    if (count>1)
    {
        printf("> navsteva #%d\n",count);
    }
    else
    {
        printf("> prvni navsteva\n");
    }
    idArray[*length]=id;
    (*length)++;
}
//int * idArray,
void amountOfUniques(int startPos, int endPos,int **array)
{
    int totalAm = (endPos-startPos)+1;
    int count = (endPos-startPos)+1;
    int unique=0;
    if (count>100000)
    {
        count=100000;
    }
    *array=(int *)malloc(count*sizeof(int));
    for (int i = 0; i < count; i++)
    {
        (*array)[i]=-1;
    }
    

    //int amofZeros=0;
    
    
    int help=0;
   for (int i = startPos; i <= endPos; i++)
   {
       for (int j = 0; j < count; j++)
       {
           if (idArray[i]==(*array)[j])
           {
               help=1;
           }         
       }
       if (help==0)
       {
            (*array)[unique]=idArray[i];
            unique++;
       }
       /*if (amofZeros==0&&idArray[i]==0)
       {
           unique++;
           amofZeros++;
       }*/
       
    help=0;
    //totalAm++;
    if (unique==100000)
    {
        break;
    }
    
   }
    free(*array);
    printf("> %d / %d\n",unique,totalAm);
    

}

int main(void){
    char action;
    //,maxElements=0
    int id,resultCode,startPos,endPos,length=0;
    int amountArray[100000]={0};
    int *array=NULL;
    
    
    
    printf("Pozadavky:\n");
    while ((resultCode=scanf(" %c",&action))==1&&(action=='+'||action=='?'))
    {
        if (action=='+')
        {
            if((resultCode=scanf(" %d",&id))!=1||id<0||id>99999||length>1000000)
            {
                break;
            }
            amountArray[id]++;
            //&idArray,,&maxElements
            addId(id,&length,amountArray);
        }
        else
        {
            if ((resultCode=scanf(" %d %d",&startPos,&endPos)!=2)||startPos<0||startPos>length||endPos<startPos||endPos>length-1)
            {
                break;
            }
            //idArray,
            amountOfUniques(startPos,endPos,&array);
        }
        
    }
    if (resultCode!=EOF)
    {
        printf("Nespravny vstup.\n");
        
        return 1;
    }
    return 0;
}