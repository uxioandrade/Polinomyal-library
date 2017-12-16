/* 
 * File:   ex_final.c
 * Author: Juan & Uxio
 * Version: 1
 * Created on November 15, 2017, 9:58 AM
 * 
 * Biblioteca polinomios
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float powe(float a,float b){
    
    float power;
    power=1;
    for (int i=0;i<b;i++){
        power *=a;
    }
    return(power);
}

struct Pol{
    
    int i; //grao
    float *co; //coeficiente
  
};

struct Pol *crear(int n){   //n debe ser un enteiro positivo
    
    struct Pol *p=NULL;
    
    p=(struct Pol*)malloc(sizeof(struct Pol));
    
    if (p==NULL){
        
        printf("Erro");
        exit(1);
    
    }
    
    p->co=(float*)malloc((n+1)*sizeof(float));
    
        if (p==NULL){
            
        printf("Erro");
        exit(1);
        
    }
    
    p->i=n;
    
    return(p);
    
}   //p é o enderezo de memoria no montón da estructura do polinomio (co vector de coeficientes baleiro)

struct Pol *read(){ //TRUE
    
    struct Pol *c=NULL;
    int n;
    
    printf("De que grao é o polinomio? \n");
    scanf("%d",&n);
    
    if (n<0){
        printf("Erro, o grao do polinomio debe ser positivo");
        exit(1);
    }
    
    c=crear(n);
            
    printf("Introduza os coeficientes de cada termo do polinomio \n");
    
    for (int i=0; i<=n; i++){
        printf("[]x^%d ",i);
        scanf("%f",&c->co[i]);
    }  

    
    return(c); //devolve o enderezo de memoria no montón do polinomio cos seus coeficientes, no cal o termo x^n debe ser distinto de 0
}

void write(struct Pol *c){ //c debe ser un punteiro de polinomios con algún termo distinto de 0
    
   
   int count=0;
   
    for(int i=c->i; i>1; i--){
        
       if(c->co[i]==1.00){
           printf("x^%d ",i);
           count += 1;
           if(c->co[i-1]>0.00) printf(" + ");
       }
       else if(c->co[i]!=0.00 || c->co[i]!=-0.00){
           printf("%.2fx^%d",c->co[i],i);
           count += 1;
           if(c->co[i-1]>0.00) printf(" + ");
       }     
       else printf(" ");
    } 
   
  if(c->co[1]!=0.00){
      if(c->co[1]==1.00){
           printf("x");
           count += 1;
       }
      else{
      printf(" %.2fx ",c->co[1]);
      }
  }
  if(c->co[0]>0.00){
      printf("+ %.2f \n",c->co[0]);
  }
  else if(c->co[0]<0.00){
      printf(" %.2f \n",c->co[0]);
  }
  else if(count==0){
      printf("0 \n");
  }
  else{
      printf(" \n");
  }
   
}


float aval(struct Pol c,float p){   //c ten que ser unha estrutura tipo pol, e un float calquera que sexa o punto no que se desexe avaliar o polinomio.
    
    float res;
    int n;
    n=c.i;
    
    if(p==0){
        res=c.co[0];
    }
    else{
    for (int i=n;i>=0;i--){
        
        res += c.co[i] * powe(p,i);
     
    }
    }
    
    return(res);
    
} //res é o enteiro resultante de sumar o valor de sustituír o x polo p en cada termo.


struct Pol *der(struct Pol c){  //c debe ser unha estrutura de polinomios
     
    struct Pol *d=NULL;
    int n;
    
    n=c.i-1;
    
    d=crear(n);
    
    for (int i=c.i;i>=1;i--){
        
      d->co[i-1] = c.co[i]*i;
      
    }
    
    return(d); //d é un punteiro de polinomios resultante de derivar o polinomio c
}


struct Pol *sum(struct Pol c,struct Pol v){ //c e v deben ser dúas estruturas de polinomios
    
    struct Pol *s=NULL;
    int n,m,min,max, aux;
    
    n=c.i;
    m=v.i;
    aux=0;
    
    if (n<=m){          //comprobamos cal é o de maior grao
        min=n;
        max=m;
        aux=1;
    }
    else{
        min=m;
        max=n;
    }
    
    s = crear(max);
    
    for (int i=0;i<=max;i++){
        
        if(i<=min){
        s->co[i] = c.co[i] + v.co[i];
        continue;
        }
        else if (aux==1){
            s->co[i] = v.co[i];
        }
        else{
            s->co[i] = c.co[i];
        }
    }
  
    return(s); //s é o enderezo de memoria do polinomio resultante da suma dos polinomio c e v
}

struct Pol *mul(struct Pol c,struct Pol v){ //c e v deben ser dúas estruturas de polinomios
    
    struct Pol *p=NULL;
    int aux,n,m;
    
    n=c.i;
    m=v.i;
    
    p=crear(m+n);
    
    for (aux=0;aux<=(m+n);aux++){
        
        for(int i=0;i<=m;i++){
            
            for(int j=0;j<=n;j++){
                
                    if (j+i==aux){
                        p->co[aux] += c.co[j]  * v.co[i];
                    }
                }
        }
    }
    
    return(p);  //s é o enderezo de memoria do polinomio resultante da multiplicación dos polinomios c e v
    
}

struct Pol *divi(struct Pol dendo, struct Pol dor){ //dendo e dor deben ser dúas estruturas de polinomios. o coeficiente do termo de maior grao de dor debe ser distinto de 0.
    
    struct Pol *pq=NULL; //cociente
    //struct Pol *pr=NULL; //resto
    struct Pol inv; //polinomio grao 1 cuxo único termo é -1,
    struct Pol *aux1=NULL; 
    struct Pol *aux2=NULL;
    struct Pol *aux3=NULL;

    inv.co=(float *)malloc(sizeof(float));
   
   
    if(inv.co==NULL){
        printf("Erro");
        exit(1);
    }
   
   inv.i=0;
   *(inv.co) = -1;
   
    int n,m;
    
    n=dendo.i;
    m=dor.i;
    
    if (n-m<0){
        
        printf("Erro, o grao do dividendo debe ser maior que o do divisor");
        struct Pol *cero;
        cero=(struct Pol*)malloc(sizeof(struct Pol));
        cero->i=0;
        cero->co=(float*)malloc(sizeof(float));
        *(cero->co)=0;
        
        return (cero);
        
    }
    
    pq=crear(n-m);
    
    pq->i=n-m;
    
    for (int i=0;i<=(n-m);i++){
        pq->co[i] = 0;
    }
     
    for (int i=n;i>=m;i--){
               
        pq->co[i-m] = dendo.co[i] / dor.co[m];
        
        for(int j=m;j>=0;j--){
            dendo.co[i-m+j]-=dor.co[j]*pq->co[i-m];
        }
        
    }
    
    free(inv.co);
      
    return(pq);//Devolvese o enderezo do polinomio cociente resultante de dividir dendo entre dor
}


struct Pol *integral(struct Pol c){//c debe ser unha estrutura de polinomios con sus dos campos con al menos un elemento     
    struct Pol *in;
    
    in = (struct Pol *)malloc(sizeof(struct Pol));
    
    in->co = (float *)malloc((c.i+2)*sizeof(float));
    
    for (int i=c.i+1;i>=1;i--){
        
      in->co[i] = c.co[i-1]/i;
      
    }
    
    in->i=c.i+1;
    in->co[0]=0;
    return(in);//d é un punteiro de polinomios resultante de integrar o polinomio c
}

float intdef(struct Pol *c,float a,float b){//c debe ser unha estrutura de polinomios con sus dos campos con al menos un elemento , a y b deben ser dos numeros entre los que se va a calcular el area    
    struct Pol *integ;
    float x,y;
    integ=integral(*c);
    x=aval(*integ,a);
    y=aval(*integ,b);
    
    return(fabs(x-y));//devolvese o un float >=0 (unha area non  pode ser negativa)
}

