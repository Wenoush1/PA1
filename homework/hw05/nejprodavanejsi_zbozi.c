#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int (*Comp)(const void *, const void *);
typedef struct
{
    char name[100];
    int amount;
}TZbozi;
void addToArray(TZbozi ** wares_array,int *max_elements, int *count_in_array,char * ware_name){
    int is_in=1;
    int i,result;
    for (i = 0; i < (*count_in_array); i++)
    {
        result=strcmp((*wares_array)[i].name,ware_name);
        if (result==0)
        {
            is_in=0;
            break;
        }
        
    }
    if (is_in==1)
    {
        if ((*count_in_array)>=(*max_elements))
        {
            (*max_elements)=(*max_elements)*2+4;
            (*wares_array)=(TZbozi *) realloc((*wares_array),(*max_elements)*sizeof((*wares_array)[0]));
        }
        (*wares_array)[(*count_in_array)].amount=1;
        strcpy((*wares_array)[(*count_in_array)].name,ware_name);
        (*count_in_array)++;
    }
    else
    {
        ((*wares_array)[i].amount)+=1;
    }
}
int cmp(const TZbozi * aPtr,const TZbozi * bPtr){

    int a=aPtr->amount, b=bPtr->amount;
    return a==b?0:(b<a? -1 : 1);


}

void mostBought(TZbozi ** wares_array,int number_traced,int count_in_array,char action){

    int same_amount,total_amount=0;
    qsort((*wares_array),count_in_array,sizeof((*wares_array)[0]),(Comp) cmp);
    for (int i = 0; i < number_traced&& i<count_in_array; i++)
    {
        same_amount=0;
        for (int j = i+1; j+1 <= count_in_array; j++)
        {
            if ((*wares_array)[i].amount==(*wares_array)[j].amount)
            {
                same_amount++;
            }
            
        }
        if (same_amount>0)
        {
            for (int j = 0; j <= same_amount; j++)
            {
                if (action=='#')
                {
                    printf("%d.-%d. %s, %dx\n",i+1,i+same_amount+1,(*wares_array)[i+j].name,(*wares_array)[i+j].amount);
                }
                
                
                total_amount+=(*wares_array)[i+j].amount;
            }
            i+=same_amount;
        }
        else
        {
            if (action=='#')
            {
                printf("%d. %s, %dx\n",i+1,(*wares_array)[i].name,(*wares_array)[i].amount);
            } 
            total_amount+=(*wares_array)[i].amount;
        }
 
    }
    
    
    
    printf("Nejprodavanejsi zbozi: prodano %d kusu\n",total_amount);


}

int main(void){
    int number_traced,result_code,max_elements=0,count_in_array=0;
    char action;
    char ware_name[1000]="";
    TZbozi *wares_array = NULL;
    printf("Pocet sledovanych:\n");
    if (scanf("%d",&number_traced)!=1 || number_traced<1)
    {
        printf("Nespravny vstup.\n");
        return 1;
    }
    printf("Pozadavky:\n");
    while ((result_code=scanf(" %c",&action))==1&&(action=='+'||action=='?'||action=='#'))
    {
        if (action=='+')
        {
            
            if (scanf(" %s",ware_name)!=1||strlen(ware_name)>99|| strlen(ware_name)<1)
            {
                break;
            }
            addToArray(&wares_array,&max_elements,&count_in_array,ware_name);

        }
        if (action=='#'||action=='?')
        {
            mostBought(&wares_array,number_traced,count_in_array,action);
        }
        
        
        
        
    }
    if (result_code!=EOF)
    {
        printf("Nespravny vstup.\n");
        free(wares_array);
        return 1;
    }
    
    



    free(wares_array);
    return 0;
}