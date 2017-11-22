#include<stdio.h>

#define MAX_VM 50
#define Capacity 12
#define Bandwidth 24
int a,b,u,v,i,j;
int VM_Matrix[MAX_VM][MAX_VM] ={0};         // original traffic matrix
int tmp[MAX_VM][MAX_VM]={0};             // record traffic matrix after operation
void merge (void);
int sum (int ,int ,int);
int VM_CAPS[MAX_VM] = {0};  // Original node capacity
int check[MAX_VM] ={0};                                 // This is the array to record the node which have been merge in. 0 is nothing. 
int caps_sum[MAX_VM] = {0};
int VM_num,flow_num,caps_num;
void main()
{
	FILE *TM,*caps;
	TM = fopen("First_Merge_flows.txt", "r");
	caps = fopen("Updated_capacity.txt","r");
	fscanf(TM,"%6d",&VM_num);
	fscanf(caps,"%d\n",&caps_num);
	printf("\n");
	printf("\n");
		
	for(i=1;i<VM_num+1;i++){
		for(j=1;j<VM_num+1;j++){
		fscanf(TM,"%6d",&VM_Matrix[i][j]);
		}
		fscanf(TM,"\n");
	} 

	for(i=1;i<=caps_num;i++){
		fscanf(caps,"%d",&VM_CAPS[i]);
	//	printf("%4d",VM_CAPS[i]);
	} 
	printf("\n\n\n");
   
	merge();
	FILE *MER,*Update_caps;
	MER = fopen("Merge_flows.txt","w");                  //Merge完後,將第一階段完成的traffic matrix 輸出 
	Update_caps = fopen("Updated_capacity.txt","w");
	fprintf(MER,"%d \n",VM_num);
	fprintf(Update_caps,"%d \n",caps_num);
	
	for(i=1;i<VM_num+1;i++){
		for(j=1;j<VM_num+1;j++){
		
			if (VM_Matrix[j][i] > VM_Matrix[i][j]){
				VM_Matrix[i][j] = VM_Matrix[j][i];
			}
			else
			VM_Matrix[j][i] = VM_Matrix[i][j];
		
		//	VM_Matrix[j][i] = VM_Matrix[i][j];
			printf("%6d",VM_Matrix[i][j]);
			fprintf(MER,"%6d",VM_Matrix[i][j]);}
			printf("\n");
			fprintf(MER,"\n");
}
	for(i=1;i<=caps_num;i++){
		fprintf(Update_caps,"%6d",VM_CAPS[i]);
	}

} 


//--------------------------------------------- Start the Maximun spanning tree generating
void merge (){
	int i,cmp,arr_num;
	int arr[MAX_VM]= {0};
	int x[MAX_VM] = {0};
	int y[MAX_VM] = {0};
	int cpress[MAX_VM] = {0};
	FILE *TFS,*cpress_array;
	cpress_array = fopen("compress_array.txt","r");
	TFS = fopen("list_array.txt","r");
	fscanf(TFS,"%d \n",&flow_num);
	fscanf(cpress_array,"%d \n",&arr_num);
	for(i=1;i<=arr_num;i++){
		fscanf(cpress_array,"%3d",&cpress[i]);
		//printf("%3d",cpress[i]);
	}
	
	for(i=1;i<=flow_num;i++){
		fscanf(TFS, "%d",&x[i] ); 
		if(i == x[i]){
			caps_sum[ x[i] ] = caps_sum[ x[i] ] + VM_CAPS[ cpress[x[i]] ];
		}
	}
	
	for(i=1;i<=flow_num;i++){
		for(j=i+1;j<=flow_num;j++){
			if(x[j] == x[i] && x[i] != x[i-1]){
				caps_sum[ x[i] ] = caps_sum[ x[i] ] + VM_CAPS[ cpress[x[j]] ];
			}
		}
		
	}
	printf("\n\n");
	
	for(i=1;i<=VM_num;i++){
		printf("%4d",caps_sum[i]);
	}
	printf("\n\n");
	
	for(i=1;i<=flow_num;i++){
		fscanf(TFS, "%d",&x[i] );        //讀取排序的data 
		
		if(i > x[i] && x[i]!=0 && caps_sum[ x[i] ] <= Capacity ){
			int j;
			for(j=1;j<VM_num+1;j++){
				VM_Matrix[ cpress[ x[i] ] ][j] = VM_Matrix[ cpress[ x[i] ] ][j] + VM_Matrix[ cpress[ i ] ][j]; 
				VM_Matrix[ cpress[ i ] ][j] = 0; 
				VM_Matrix[ cpress[ x[i] ] ][i] = 0; 
				
		
				}
		
			for(j=1;j<VM_num+1;j++){
			
				VM_Matrix[j][ cpress[ x[i] ] ] = VM_Matrix[j][ cpress[ x[i] ] ] + VM_Matrix[j][ cpress[ i ] ]; 
				VM_Matrix[j][ cpress[ i ] ] = 0;
				VM_Matrix[j][y[i]] = 0;
				VM_Matrix[ cpress[ x[i] ] ][ cpress[ x[i] ] ] = 0;
				}
			printf("node %d combine in %d\n\n",cpress[ i ],cpress[ x[i] ]);	
			VM_CAPS[cpress[ x[i] ]] = VM_CAPS[cpress[ x[i] ]] + VM_CAPS[cpress[ i ]];
			VM_CAPS[cpress[ i ]] = 0;
		}
		
	}


	
	fclose(TFS);
	
} 





