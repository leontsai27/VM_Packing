#include<stdio.h>

#define MAX_VM 50
#define Capacity 12
#define Bandwidth 24


int a,b,u,v,i,j;
int VM_Matrix[MAX_VM][MAX_VM] ={0};         // original traffic matrix
int tmp[MAX_VM][MAX_VM]={0};             // record traffic matrix after operation
int compress_Matrix[MAX_VM][MAX_VM]={0};
void merge (void);
void compress(void);
int sum (int ,int ,int);
int VM_CAPS[MAX_VM] = {0};  // Original node capacity
int check[MAX_VM] ={0};                                 // This is the array to record the node which have been merge in. 0 is nothing. 

int VM_num,flow_num,caps_num;
void main()
{
	FILE *TM,*caps;
	TM = fopen("flow_matrix.txt", "r");
	caps = fopen("original_capacity.txt","r");
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
		printf("%4d",VM_CAPS[i]);
	} 
	printf("\n\n\n");
   
	merge();
	FILE *MER,*Update_caps;
	MER = fopen("First_Merge_flows.txt","w");                  //Merge完後,將第一階段完成的traffic matrix 輸出 
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

		compress();
} 

void compress (){
	int i,j;
	int mp[MAX_VM]={0};
	int temp[MAX_VM]={0}; 
	int count = 0;
	FILE *compress,*cpress_array;
	compress = fopen("compress_matrix.txt","w");
	cpress_array = fopen("compress_array.txt","w");                  
	
	for(i=1;i<=VM_num;i++){
		for(j=1;j<VM_num;j++){
			if(VM_Matrix[i][j]!=0){
				printf("\n(%d,%d)\n",i,j);
				count = count + 1;
				mp[i] = count;
				temp[count] = i;
				break;
				}	
		}
	}
	fprintf(compress,"%d \n",count);
	fprintf(cpress_array,"%d \n",count);
//	printf("\n\n%d\n\n",count);
	
	for(i=1;i<=VM_num;i++){
	//	printf("%4d",mp[i]);
		for(j=1;j<=VM_num;j++){
			if(VM_Matrix[i][j]!=0){
				compress_Matrix[mp[i]][mp[j]] = VM_Matrix[i][j];
			//	printf("(%d,%d)\n",mp[i],mp[j]);
			}
			
		}
		
	}
	printf("\n");
	for(i=1;i<=count;i++){
		//	printf("%4d",temp[i]);
		for(j=1;j<=count;j++){
			fprintf(compress,"%6d",compress_Matrix[i][j]);
		}
		fprintf(compress,"\n");
	}
	
	for(i=1;i<=count;i++){
			fprintf(cpress_array,"%4d",temp[i]);
	}
	
}

//--------------------------------------------- Start the Maximun spanning tree generating
void merge (){
	int i,cmp,temp,temp1,temp2;
	int arr[MAX_VM]= {0};
	int x[MAX_VM] = {0};
	int y[MAX_VM] = {0};
	FILE *TFS;
	TFS = fopen("sorted_flows.txt","r");
	fscanf(TFS,"%d \n",&flow_num);
	for(i=0;i<flow_num;i++){
		fscanf(TFS, "%d %d %d",&arr[i],&x[i],&y[i] );        //讀取排序的data 
	} 
	again:
	for(i=0;i<flow_num;i++){
	
	

		if(arr[i]==0){break;}
	//printf("%d VM[%d][%d]\n",arr[i],x[i],y[i] );
	
		cmp = sum(arr[i],x[i],y[i]);                         //3: if m_ij shows that the VM pairs VM i and VM j can be merged under the constraints C and B  
//	printf("%d\n\n",cmp);


		if(cmp==1){                                          //if the VM pair are able to merge from the below is the merging action. (4:merge VMs i and j with i,j =>V into a super VM and the super VM ID is i
                                                         //(using the smaller ID to represent, this case is ID I < ID j)
                                                         //5:compute the traffic matrix by adding the traffic which correlated with j into i
                                                         //6:update  M)
			int j;
			int k=0;
	
			for(j=1;j<VM_num+1;j++){
				VM_Matrix[x[i]][j] = VM_Matrix[x[i]][j] + VM_Matrix[y[i]][j]; 
				VM_Matrix[y[i]][j] = 0; 
				VM_Matrix[x[i]][y[i]] = 0; 
		
			}
		
			for(j=1;j<VM_num+1;j++){
			
				VM_Matrix[j][x[i]] = VM_Matrix[j][x[i]] + VM_Matrix[j][y[i]]; 
				VM_Matrix[j][y[i]] = 0;
			}
			printf("node %d combine in %d\n\n",y[i],x[i]);	
	
	
			for(i=1; i<=VM_num; i++){
				for(j=1; j<=VM_num; j++){
	    			if(VM_Matrix[i][j]>0){
						arr[k] = VM_Matrix[i][j];
						x[k] = i;
						y[k] = j;
						k++;  
					//	printf("%2d %2d %2d\n",arr[k],x[k],y[k]);
	    			}
        		}
    		}
    	    
    		for( i = 0; i < flow_num; i++) {
        		for( j = i; j < flow_num; j++) {
            		if( arr[j] > arr[i] ) {
                		temp = arr[j];
                		arr[j] = arr[i];
                		arr[i] = temp;
                		temp1 = x[j];
                		x[j] = x[i];
                		x[i] = temp1;
                		temp2 = y[j];
                		y[j] = y[i];
                		y[i] = temp2;
            		}
            
            		else if( arr[j] == arr[i] ){
            			if( x[j] < x[i] ){
            				temp = arr[j];
                			arr[j] = arr[i];
                			arr[i] = temp;
                			temp1 = x[j];
                			x[j] = x[i];
                			x[i] = temp1;
                			temp2 = y[j];
                			y[j] = y[i];
                			y[i] = temp2;
						}
						if( x[j] == x[i]){
							if(y[j] < y[i]){
								temp = arr[j];
                				arr[j] = arr[i];
                				arr[i] = temp;
                				temp1 = x[j];
                				x[j] = x[i];
                				x[i] = temp1;
                				temp2 = y[j];
                				y[j] = y[i];
                				y[i] = temp2;	
							}
						}
					}
        		}
    		}	
    		goto again;
		}
	
	}
	
	
	
	
	
	fclose(TFS);
	
} 


//This function is checking that the VM i and VM j are enable to merge.
int sum (int arr, int x, int y){
	int i,j;
	int sumx = 0;
	int sumy = 0;
//	if(check[x]!=0){x = check[x];}
//	if(check[y]!=0){y = check[y];}
	for(j=1;j<VM_num+1;j++){
		sumx = sumx + VM_Matrix[x][j] + VM_Matrix[j][x];
		sumy = sumy + VM_Matrix[y][j] + VM_Matrix[j][y];
	}
	//printf("x:%d sum:%d y:%d sum:%d\n",x,sumx,y,sumy);
	
	if( (VM_CAPS[x]+VM_CAPS[y] ) <= Capacity && ((sumx + sumy) - 2*(VM_Matrix[x][y])) <= Bandwidth && VM_Matrix[x][y] > 0){ //This is the constrain of the capacity and the bandwidth.
		VM_CAPS[x] = VM_CAPS[x] + VM_CAPS[y];
		VM_CAPS[y] = 0;
		return 1;
	}
	
	else return 0;
	
	
}

	
	

