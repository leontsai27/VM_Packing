#include <stdio.h>
#include <stdlib.h>
#define MAX_VM 20
#define Capacity 12
#define Bandwidth 24
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int VM_CAPS[MAX_VM] = {0}; 
int VM_num, flow_num,cpress_num ,cpressarraynum ,caps_num;
int cpress_array[MAX_VM] = {0};
int cpress[MAX_VM][MAX_VM] = {0};
int n1[MAX_VM] = {0};
int n2[MAX_VM] = {0};
int value[MAX_VM] = {0};
int a[MAX_VM][MAX_VM] = {0};
int b[MAX_VM] = {0};
int cksum[MAX_VM] = {0};
int row[MAX_VM] = {0};
int assign[MAX_VM] = {0};
int tmp [MAX_VM] ={0};
void tree (){
	int i,j,k; 
//	printf("\n\n123\n\n");
	for(i=1;i<=VM_num;i++){
		for(j=1;j<=VM_num;j++){
			if(a[i][j]!=0){printf("(%d,%d)=%d\n",i,j,a[i][j]);
				if(b[i]!=0 && b[j]==0)
					{b[j]=b[i];}
				if(b[i]==0 && b[j]!=0)
					{b[i]=b[j];}
				if(b[i]!=0 && b[j]!=0)
					{if(b[i]>b[j])
						{
							for(k=1;k<=VM_num;k++){
								if(b[k]==b[i]){b[k]=b[j];
								//printf("%d\n",k);
								}
								
							}
							b[i]=b[j];
						}
			 		 else if (b[i]<b[j])
			 		 	{
						  for(k=1;k<=VM_num;k++){
								if(b[k]==b[j]){b[k]=b[i];
								//printf("%d %d\n",k,b[k]);
								}
							
							}
						  b[j]=b[i];
						  }
					}
				if(b[i]==0 && b[j]==0)
					{b[j]=i;}
			}
		}
		
	}
	
	for (i=1;i<=VM_num;i++){
	//	printf("%4d",b[i]);
		if(b[i]==0){
			for(j=1;j<=VM_num;j++){
				if(a[i][j]!=0){
					b[i]=b[j];
				}
			}
		}
	}
		printf("\n\n");
	for (i=1;i<=VM_num;i++){
		printf("%4d",b[i]);
		//fprintf(list_array,"%4d",b[i]);
	}
	printf("\n");
}



void checking (){
	int i,j,k;
	int cks;
	
	for(i=1;i<=flow_num;i++){
		a[n1[i]][n2[i]] = 0;
		printf("\n(%d,%d)= 0\n",n1[i],n2[i]);
		tree();
		tree();
		//for(j=1;j<=VM_num;j++){
			cks = checksum();
			printf("\n\n%d\n\n",cks);
		//	getch();
			if (cks ==1){
				goto end;
			}
		//}
		
		for(k=1;k<=VM_num;k++){
					b[k] = 0;
				}
	}
	end:
		printf("end!!!\n\n");
}

int checksum (void){
	int i,j,k;
	int sum=0;
	int caps_sum[MAX_VM] = {0};
	
	for(i=1;i<=caps_num;i++){
		caps_sum[i] = VM_CAPS[i];
	}
	
	for(i=1;i<=VM_num;i++){
			sum = 0;
		for(j=1;j<=VM_num;j++){
			
			
			if(b[j] == b[i]  ){
			//	printf("\n%d\n",b[j]);
				sum = sum + cpress[i][j];
			//	printf("%d\n",sum);
			}
			
		}
		cksum[b[i]] = cksum[b[i]] + row[i] - sum ;
		//printf("%d\n",cksum[i]);
	
	}
	
	
	for(i=1;i<=caps_num;i++){
		for(j=1;j<=caps_num;j++){
			if(b[j] == i && j!=i){
			caps_sum[i] = caps_sum[i] + VM_CAPS[ cpress_array[j] ];
			}
		}
	}
	
	int over =0;
	int notover =0;
	int overcaps = 0;
	int notovercaps = 0;
	for (i=1;i<=VM_num;i++){
		
		if(cksum[i]>Bandwidth || caps_sum[i] > Capacity ){
			over = over + 1;
			printf("\n root %d overload : %d\n",i,cksum[i]);
			cksum[i] = 0;
			
		}
		
		else if (cksum[i] < Bandwidth && cksum[i] > 0 ){ 
			notover = notover + 1;
			printf("\n root %d not overload : %d\n",i,cksum[i]);
			cksum[i] = 0;
			
		} 
	}
	printf("\n overload : %d   not overload : %d",over,notover);
	
	if (notover > 0 && over == 0){
		return 1;
	}
	else
		return 0;

}

void check_caps(){
	int caps_sum[MAX_VM] = {0};
	int i,j;
	int overcaps = 0;
	int notovercaps = 0;

	for(i=1;i<=caps_num;i++){
		caps_sum[i] = VM_CAPS[i];
	}
	
	for(i=1;i<=caps_num;i++){
		for(j=1;j<=caps_num;j++){
			if(b[j] == i && j!=i){
			caps_sum[i] = caps_sum[i] + VM_CAPS[ cpress_array[j] ];
			}
		}
	}
	
	
}

int main(int argc, char *argv[]) {
	FILE *data,*list_array,*flow,*cpress_matrix,*cpressarray,*capacity;
	capacity = fopen("Updated_capacity.txt","r");
	cpressarray = fopen("compress_array.txt","r");
	cpress_matrix = fopen("compress_matrix.txt","r");
	flow = fopen("flow.txt","r");
	data = fopen("MST.txt","r");
	list_array = fopen("list_array.txt","w");
	fscanf(capacity,"%d \n",&caps_num); 
	fscanf(cpressarray,"%d \n",&cpressarraynum);
	fscanf(cpress_matrix,"%d \n",&cpress_num);
	fscanf(data,"%d \n",&VM_num);
	fscanf(flow,"%d \n",&flow_num);
	fprintf(list_array,"%d \n",VM_num);
	int i,j;
	
	for(i=1;i<=caps_num;i++){
		fscanf(capacity,"%d",&VM_CAPS[i]); 
	}
	
	for(i=1;i<=cpressarraynum;i++){
		fscanf(cpressarray,"%d",&cpress_array[i]); 
	}
	
	for(i=1;i<=cpress_num;i++){
		for(j=1;j<=cpress_num;j++){
			fscanf(cpress_matrix,"%d",&cpress[i][j]);
			printf(" %6d",cpress[i][j]);
		}
		printf("\n");
	}
	
	for(i=1;i<=cpress_num;i++){
		for(j=1;j<=cpress_num;j++){
			row[i] = row[i] + cpress[i][j];
		}
		
	}
	
	for(i=1;i<=cpress_num;i++){
		printf("row%d = %d\n",i,row[i]);
	}
	
	for(i=flow_num;i>=1;i--){
		fscanf(flow,"%d %d %d\n",&n1[i],&n2[i],&value[i]);
	}
	
	for(i=1;i<=flow_num;i++){
		printf("%d %d %d\n",n1[i],n2[i],value[i]);
	}
	
	for(i=1;i<=VM_num;i++){
		for(j=1;j<=VM_num;j++){
			fscanf(data,"%d",&a[i][j]);
			printf(" %6d",a[i][j]);
		}
		printf("\n");
	}
	
	checking();
	tree();
	
	for (i=1;i<=VM_num;i++){
		//printf("%4d",b[i]);
		fprintf(list_array,"%4d",b[i]);
	}
	return 0;
}
