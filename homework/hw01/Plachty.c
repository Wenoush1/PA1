 #include <stdio.h>
 
 double area(double fHeight2 ,double fWidth2 , double sHeight2 , double sWidth2, double overlap2)
 {
    double vAmount,hAmount;
    vAmount=1;
    hAmount=1;
    if (fHeight2<sHeight2)
    {
        hAmount=(sHeight2-overlap2)/(fHeight2-overlap2);
    }
    if (fWidth2<sWidth2)
    {
        vAmount=(sWidth2-overlap2)/(fWidth2-overlap2);
    }
    /*printf("%.40lf\n",vAmount);
    printf("%.40lf\n",hAmount);*/
    
    if (hAmount-(int)hAmount>0+(hAmount*0.00000001))
    {
        hAmount=(int)hAmount+1;
    }
    if (vAmount-(int)vAmount>0+(vAmount*0.00000001))
    {
        vAmount=(int)vAmount+1;
    }
    /*
    printf("%lf\n",vAmount);
    printf("%lf\n",hAmount);
    printf("%lf\n",hAmount*vAmount);*/
    return (vAmount*hAmount);

 }

 int main(void){ 
    double fHeight , fWidth , sHeight , sWidth , overlap,vAmount,hAmount;
    overlap = 0.0;
    printf("Velikost latky:\n");
    if(scanf(" %lf %lf",&fHeight,&fWidth)!=2||fHeight<=0||fWidth<=0)
    {
        printf("Nespravny vstup.\n");
        return 1;
    }
    printf("Velikost plachty:\n");
    
    if(scanf(" %lf %lf",&sHeight,&sWidth)!=2||sHeight<=0||sWidth<=0)
    {
        printf("Nespravny vstup.\n");
        return 1;
    } 
    
    if (!((fWidth>=sWidth&&fHeight>=sHeight)||(fHeight>=sWidth&&fWidth>=sHeight)))
    {
        printf("Prekryv:\n");
        if (scanf(" %lf",&overlap)!=1||overlap<0)
        {  
            printf("Nespravny vstup.\n");
            return 1;
        }
        if ((overlap>fWidth&&fWidth!=sWidth)||(overlap>fHeight&&fHeight!=sHeight))
        {
            printf("Nelze vyrobit.\n");
            return 1;
        }
        
        
        
    }
    vAmount=area(fHeight,fWidth,sHeight,sWidth,overlap);
    hAmount=area(fWidth,fHeight,sHeight,sWidth,overlap);
    /*printf("%lf\n",vAmount);
    printf("%lf\n",hAmount);*/
    
    if (hAmount>=vAmount || hAmount<0 )
    {
        printf("Pocet kusu latky: %.0f\n",vAmount);
    }
    else
    {
        printf("Pocet kusu latky: %.0f\n",hAmount);
    }
    
    
    


    return 0;
 }
