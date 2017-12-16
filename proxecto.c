/* 
 * File:   bib_test.c
 * Author: Uxio
 *
 * Created on December 15, 2017, 5:48 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "polinom.h"

/*
 * 
 */
int exceso(int count){
    
    if(count>49){
        count=0;
        printf("Excedeuse o limite de polinomios gardados comezaran a reescribirse empezando polo máis vello\n");
    }
    return(count);
    
}

int check(int k,int count){
    if(k>=count){
                k=0;
                printf("Como non elixiches un polinomio valido usarase f1(x)\n");
            }
    return(k);
}
int comp(int a){
    int sel;
    if(a>1){
        printf("Escolle unha opcion\n");
        printf("[0]-Operar cun novo polinomio e un dos xa existentes\n");
        printf("[calquera outro valor]-Operar con dous polinomios xa existentes\n");
        scanf("%d",&sel);
    }
    else{
        sel=0;
    }
    
    return(sel);
}

  
int main(){
    
    int op=1,count=0,select,a,b,ab;
    char *m1,*m2,*m3,*m4;
    struct Pol* c[50],inv;
    float resultado,pto;
    
    inv.co=(float *)malloc(sizeof(float));
    inv.i=0;
   *(inv.co) = -1;
   
    printf("Escribe o primeiro polinomio\n");
    c[0]=read();
    count++;
    printf("Polinomio gardado con exito como f%d(x)\n",count);
    
    while(op){
        
    printf("Que operacion queres realizar?\n");
    printf("[1]-Crear novo polinomio\n");
    printf("[2]-Ver mis polinomios\n");
    printf("[3]-Sumar polinomios\n");
    printf("[4]-Restar polinomios\n");
    printf("[5]-Dividir polinomios\n");
    printf("[6]-Multiplicar polinomios\n");
    printf("[7]-Derivar polinomio\n");
    printf("[8]-Integrar polinomio\n");
    printf("[9]-Calculo da area baixo o polinomio entre dous puntos\n");
    printf("[10]-Avaliar polinomio nun punto\n");
    printf("[0]-Rematar execucion\n");
    scanf("%d",&op);
    
    switch(op){
        
        case 1:
            c[count]=read();
            count=exceso(count);
            count++;
            printf("Polinomio gardado con exito como f%d(x)\n",count);
            break;
            
        case 2:
            for(int i=0;i<count;i++){
                printf("f%d(x)=",i+1);
                write(c[i]);                        
            }
            break;
            
        case 3:
            select=comp(count);
            if(select){
               printf("Escribe o subindice do 1º polinomio que queres usar\n");
                scanf("%d",&b);
                b--;
                b=check(b,count);
                printf("Escribe o subindice do 2º polinomio que queres usar\n");
                scanf("%d",&a);
                a--;
                a=check(a,count);
            }
            else{
                printf("Introduce o novo polinomio que vas sumar\n");
                c[count]=read();
                count=exceso(count);
                a=count;
                count++;
                printf("Polinomio gardado con exito como f%d(x)\n",count);
                printf("Escribe o subindice do polinomio xa gardado que queres usar\n");
                scanf("%d",&b);
                b--;
                b=check(b,count);
            }
            printf("Suma \n");
            c[count]=sum(*c[a],*c[b]);
            count=exceso(count);
            count++;
            write(c[count-1]);
            printf("Polinomio suma gardado en f%d(x)\n",count);
        
            break;   
        
        case 4:
            
            select=comp(count);
            if(select){
               printf("Escribe o subindice do minuendo\n");
                scanf("%d",&a);
                a--;
                a=check(a,count);
                printf("Escribe o subindice do sustraendo\n");
                scanf("%d",&b);
                b--;
                b=check(b,count);
            }
            else{
                printf("Introduce o polinomio sustraendo \n");
                c[count]=read();
                count=exceso(count);
                b=count;
                count++;
                printf("Polinomio gardado con exito como f%d(x)\n",count);
                printf("Escribe o subindice do polinomio xa gardado que queres usar de minuendo\n");
                scanf("%d",&a);
                a--;
                a=check(a,count);
            }
            printf("Resta \n");
            c[count]=sum(*c[a],*mul(inv,*c[b]));
            count=exceso(count);
            count++;
            write(c[count-1]);
            printf("Polinomio diferencia gardado en f%d(x)\n",count);
            
            break;
            
        case 5:
            select=comp(count);
            if(select){
               printf("Escribe o subindice do dividendo\n");
                scanf("%d",&b);
                b--;
                b=check(b,count);
                printf("Escribe o subindice do divisor\n");
                scanf("%d",&a);
                a--;
                a=check(a,count);
            }
            else{
                printf("Introduce o  polinomio divisor \n");
                c[count]=read();
                count=exceso(count);
                a=count;
                count++;
                printf("Polinomio gardado con exito como f%d(x)\n",count);
                printf("Escribe o subindice do polinomio xa gardado que vas usar de dividendo\n");
                scanf("%d",&b);
                b--;
                b=check(b,count);
            }
            printf("División \n");
            c[count]=divi(*c[b],*c[a]);
            count=exceso(count);
            count++;
            write(c[count-1]);
            printf("Polinomio cociente gardado en f%d(x)\n",count);
            break;
            
        case 6:
            select=comp(count);
            if(select){
               printf("Escribe o subindice do 1º termo\n");
                scanf("%d",&b);
                b--;
                b=check(b,count);
                printf("Escribe o subindice do 2º termo\n");
                scanf("%d",&a);
                a--;
                a=check(a,count);
            }
            else{
                printf("Introduce o polinomio non gardado que queres usar \n");
                c[count]=read();
                count=exceso(count);
                a=count;
                count++;
                printf("Polinomio gardado con exito como f%d(x)\n",count);
                printf("Escribe o subindice do polinomio xa gardado que queres usar\n");
                scanf("%d",&b);
                b--;
                b=check(b,count);
            }
            printf("Producto \n");
            c[count]=mul(*c[b],*c[a]);
            count=exceso(count);
            count++;
            write(c[count-1]);
            printf("Polinomio producto gardado en f%d(x)\n",count);
            
            break;
            
        case 7: //derivar polinomio
           
            printf("Escolle unha opcion\n");
            printf("[0]-Derivar un novo polinomio\n");
            printf("[calquera outro valor]-Derivar un dos polinomios xa existentes\n");
            scanf("%d",&select);
            if(select){
                
               printf("Escriba o subindice do polinomio\n");
                scanf("%d",&b);
                b--;
                b=check(b,count);
                ab=b;
            
            }
            else{
                
                printf("Introduza o polinomio non gardado que queres usar \n");
                c[count]=read();
                count=exceso(count);
                a=count;
                count++;     
                ab=a;
            
            }  
        
        printf("Derivada\n");
            c[count]=der(*c[ab]);
            count=exceso(count);
            count++;
            write(c[count-1]);   
            printf("Polinomio derivado gardado en f%d(x)\n",count);
            
                break;
        
        case 8:     //integrar polinomio
        
            printf("Escolle unha opcion\n");
            printf("[0]-Integrar un novo polinomio\n");
            printf("[calquera outro valor]-Integrar un dos polinomios xa existentes\n");
            scanf("%d",&select);
            if(select){
                
                printf("Escriba o subindice do polinomio\n");
                scanf("%d",&a);
                a--;
                a=check(b,count);     
                

            }
            else{
                
                printf("Introduza o polinomio non gardado que queres usar \n");
                c[count]=read();
                count=exceso(count);
                a=count;
                count++;     
               
            } 
            
            printf("Integral\n");
            c[count]=integral(*c[a]);
            count=exceso(count);
                count++;
                write(c[count-1]);   
                printf("Primitiva do polinomio gardado en f%d(x)\n",count);
                
            break;
         
        case 9:
            
            printf("Escolle unha opcion\n");
            printf("[0]-Calcular area para un novo polinomio\n");
            printf("[calquera outro valor]-Calcular area para un dos polinomios xa existentes\n");
            scanf("%d",&select);
             int p1,p2;
             float ar;
             
            if(select){
                
                printf("Escriba o subindice do polinomio\n");
                scanf("%d",&b);
                b--;
                b=check(b,count);      
                
           
              
            }
            else{
                
                printf("Introduza o polinomio non gardado que queres usar \n");
                c[count]=read();
                count=exceso(count);
                b=count;
                count++;     

            } 
             
                printf("Escriba o primeiro punto    ");
                scanf("%d",&p1);
                printf("Escriba o segundo punto     ");
                scanf("%d",&p2);
                
                ar=intdef(c[b],p1,p2);
                printf("Area entre a curva e o eixo x = %f\n",ar);
                
                
            break;
            
        case 10:
                     
                printf("Escriba o subindice do polinomio\n");
                scanf("%d",&b);
                b--;
                b=check(b,count);
                
                printf("Escriba o punto no que desexe avaliar a funcion");
                scanf("%f",&pto);
                
            resultado=aval(*c[b],pto) ;
            
            printf("O valor do polinomio nese punto é %f \n",resultado);            
            
            break;
            
        case 0:
                
             return (EXIT_SUCCESS);
    }
    }
   
}
