#include<stdio.h>
//#include<conio.h>
#include<stdlib.h>
#define MAX_VM 20
int i,j,k,a,b,u,v,n,ne=1;
int min,mincost=0,cost[MAX_VM][MAX_VM],parent[MAX_VM],MST[MAX_VM][MAX_VM]={0};
int find(int);
int uni(int,int);
int VM_num, flow_num;
void main()
{
	FILE *traffic,*flow;

    //Read the traffic matrix data (1: Read the traffic matrix data)
    traffic = fopen("compress_matrix.txt","r");
	flow = fopen("flow.txt","w");       
    fscanf(traffic, "%d \n", &VM_num);
    fprintf(flow,"%d \n",VM_num-1);
    if (VM_num > MAX_VM) {
        printf("VM number exceeds maximum VM number %d \n", MAX_VM); 
        exit(1);
    } 

 
 	printf("\n\n\tImplementation of Kruskal's algorithm\n\n");

	


 	for(i=1;i<=VM_num;i++){
  		for(j=1;j<=VM_num;j++){
  			fscanf(traffic,"%d",&cost[i][j]);
   			//scanf("%d",&cost[i][j]);
   			if(cost[i][j]==0)
    			cost[i][j]=-1;
  		}
  		fscanf(traffic,"\n");
 	}
 
 	printf("\nThe edges of Maximum Cost Spanning Tree are\n\n");
 	while(ne<VM_num){
  		for(i=1,min=-1;i<=VM_num;i++){
   			for(j=1;j<=VM_num;j++){
    			if(cost[i][j]>min){
     				min=cost[i][j];
     				a=u=i;
     				b=v=j;
    			}
   			}
  		}
  		u=find(u);
  		v=find(v);
  		if(uni(u,v)){
   			printf("\n%d edge (%d,%d) =%d\n",ne++,a,b,min);
   			fprintf(flow,"%d  %d  %d\n",a,b,min);
   			MST[a][b] = min;
   			mincost +=min;
  		}
   
  		cost[a][b]=cost[b][a]=-1;
 	}
 	//printf("\n\tMinimum cost = %d\n",mincost);
 	getch();
 
 	FILE *Mst;
 	Mst = fopen("MST.txt","w");
 	fprintf(Mst,"%d \n",VM_num);
 	for (i=1;i<=VM_num;i++){
 		for (j=1;j<=VM_num;j++){
 			printf("%6d",MST[i][j]);
 			fprintf(Mst,"%6d",MST[i][j]);
		 }
			printf("\n");
			fprintf(Mst,"\n");
	 }
}
int find(int i){
 	while(parent[i])
  		i=parent[i];
 
 	return i;
}

int uni(int i,int j){
 	if(i!=j){
  		parent[j]=i;
  		return 1;
 	}
 	return 0;
}
