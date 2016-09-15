#include <stdio.h>
#include <stdlib.h>
/*
void deleteTwoDArray(int ***a, int b){
  int ** c= *a;
  for(int i=0;i<b;i++){
//    std::cout<<c[i]<<" "<<i<<std::endl;
    delete [] c[i];
  }
  delete [] c;
  return;
}

int ** createTwoDArray(int b, int c, int init){
  int **a=new int *[b];
  for(int i=0;i<c;i++)
    a[i]=new int[c];
  for(int i=0;i<b;i++){
    for(int j=0;j<c;j++){
        a[i][j]=0;
      }
    }
  if(init!=0){
    for(int i=1;i<b-1;i++){
      for(int j=1;j<c-1;j++){
        if(init==-1){
          a[i][j]=rand()%20;
        }else{
          a[i][j]=init;
        }
      }
    }
  }
  return a;
}

int SumOfNeighbors(int **a, int b, int c){
  int r=0;
  for(int i=b-1;i<b+2;i++){
    for(int j=c-1;j<c+2;j++)
      r+=a[i][j];
  }
  return r;
}

void nextGeneration(int ***a,int b, int c){
  int **d=*a;
  int **e=createTwoDArray(b,c,0);
  int temp=0;
  for(int i=1;i<b-1;i++){
    for(int j=1;j<c-1;j++){
      temp=SumOfNeighbors(d,i,j);
      e[i][j]=temp%10?temp<50?d[i][j]+3:temp>150?1:temp>3?d[i][j]-3:0:0;
    }
  }
  deleteTwoDArray(a,b);
  *a=e;
}
int main(void){
  int **b=createTwoDArray(8,8,-1);
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      std::cout<<b[i][j]<<'\t';
    }
    std::cout<<std::endl;
  }
  nextGeneration(&b,8,8);
  return 0;
}
*/
int ** createTwoDArray(int a, int b, int init){
  int i=0,j=0;
  int ** r = malloc(a * sizeof(int *));
  for(i=0;i<a;i++)
    r[i]=malloc(b * sizeof(int));
  for(i=0;i<a;i++){
    for(j=0;j<b;j++)
      r[i][j]=(!i||i==a-1)||(!j||j==b-1)||(!init)?0:rand()%init;
  }
  return r;
}
void deleteTwoDArray(int ** a, int b){
  int i=0;
  for(i=0;i<b;i++){
    free(a[i]);
  }
  free(a);
  return;
}
int SumOfNeighbors(int **a, int b, int c){
  int r=0,i=0,j=0;
  for(i=b-1;i<b+2;i++){
    for(j=c-1;j<c+2;j++)
      r+=a[i][j];
  }
  return r;
}
void nextGeneration(int ***a,int b, int c){
  int **d=*a;
  int **e=createTwoDArray(b,c,0);
  int temp=0;
  int i=0,j=0;
  for(i=1;i<b-1;i++){
    for(j=1;j<c-1;j++){
      temp=SumOfNeighbors(d,i,j);
      if(temp%10==0){
        e[i][j]=0;
      }else if(temp<50){
        e[i][j]=d[i][j]+3;
      }else if(temp>50){
        if(d[i][j]>2){
          e[i][j]=d[i][j]-3;
        }else{
          e[i][j]=0;
        }
      }else if(temp>150){
        e[i][j]=1;
      }
//      e[i][j]=temp%10?temp<50?d[i][j]+3:temp>150?1:temp>3?d[i][j]-3:0:0;
    }
  }
  deleteTwoDArray(d,b);
  *a=e;
}
void printTwoDArray(int ** a, int b, int c){
  int i=0,j=0;
  for(i=0;i<b;i++){
    for(j=0;j<c;j++)
      printf("%d\t",a[i][j]);
    printf("\n");
  }
  return;
}

int main(void){
  int **b = createTwoDArray(8,8,20);
  printTwoDArray(b,8,8);
  nextGeneration(&b,8,8);
  printf("\n");
  printTwoDArray(b,8,8);
  return 0;
}
