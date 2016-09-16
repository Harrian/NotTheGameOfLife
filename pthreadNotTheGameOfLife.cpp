#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <queue>

#define NUM_THREADS 8
pthread_mutex_t mutexlock;
class pthreadnode{
  private:
    int ** originalarray;
    int ** destination;
    int rownumber;
    int cols;
  public:
    pthreadnode(int**a,int**b,int c,int d);
    int ** getOriginalArray(void){return originalarray;}
    int ** getDestination(void){return destination;}
    int getRowNumber(void){return rownumber;}
    int getCols(void){return cols;}
};

pthreadnode::pthreadnode(int**a,int**b,int c,int d){
  originalarray=a;
  destination=b;
  rownumber=c;
  cols=d;
}
int SumOfNeighbors(int **a, int b, int c){
  int r=0,i=0,j=0;
  for(i=b-1;i<b+2;i++){
    for(j=c-1;j<c+2;j++)
      r+=a[i][j];
  }
  return r;
}
void *processNextGen(void *param){
  std::queue<pthreadnode *> * jobqueue = (std::queue<pthreadnode *> *)param;
  jobqueue->front();
  pthreadnode * job=NULL;
  int temp=0;
  while(!jobqueue->empty()){
    pthread_mutex_lock(&mutexlock);
    job=jobqueue->front();
    jobqueue->pop();
    pthread_mutex_unlock(&mutexlock);
    if(job!=NULL){
      for(int i=1;i<job->getCols()-1;i++){
        temp=SumOfNeighbors(job->getOriginalArray(),job->getRowNumber(),i);
        if(temp%10==0){
          job->getDestination()[job->getRowNumber()][i]=0;
        }else if(temp<50){
          job->getDestination()[job->getRowNumber()][i]=job->getOriginalArray()[job->getRowNumber()][i]+3;
        }else if(temp>50){
          if(job->getOriginalArray()[job->getRowNumber()][i]>2){
            job->getDestination()[job->getRowNumber()][i]=job->getOriginalArray()[job->getRowNumber()][i]-3;
          }else{
            job->getDestination()[job->getRowNumber()][i]=0;
          }
        }else if(temp>150){
          job->getDestination()[job->getRowNumber()][i]=1;
        }
      }
      delete job;
      job=NULL;
    }
  }
  pthread_exit(NULL);
}
int ** createTwoDArray(int a, int b, int init){
  int i=0,j=0;
  int ** r = (int**)malloc(a * sizeof(int *));
  for(i=0;i<a;i++)
    r[i]=(int*)malloc(b * sizeof(int));
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

void nextGeneration(int ***a,int b, int c){
  int **d=*a;
  int **e=createTwoDArray(b,c,0);
  int temp=0;
  int i=0,j=0;
  std::queue<pthreadnode *> queueofdata;
  for(i=1;i<b-1;i++){
    queueofdata.push(new pthreadnode(d,e,i,c));
  }
  pthread_t tids[NUM_THREADS];
  for(i=0;i<NUM_THREADS;i++){
    pthread_create( &tids[i], NULL, processNextGen, (void *) &queueofdata);
  }
  void*status;
  for (i=0; i < NUM_THREADS; i++)
	{
		pthread_join( tids[i], &status );
  }
  deleteTwoDArray(d,b);
  *a=e;
  return;
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
  pthread_mutex_init(&mutexlock,NULL);
  int **b = createTwoDArray(8,8,20);
  printTwoDArray(b,8,8);
  int i=0;
  for(i=0;i<500;i++){
    nextGeneration(&b,8,8);
  }
  printf("\n");
  printTwoDArray(b,8,8);
  return 0;
}
