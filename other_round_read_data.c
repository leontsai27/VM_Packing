#include<stdio.h>
#include<stdlib.h>
//#include<conio.h>

#define MAX_VM 20

int a, b, u, v, i, j, ne=1;
int VM_Matrix[MAX_VM][MAX_VM] ={0};       // original flow matrix
int tmp[MAX_VM][MAX_VM]={0};              // record flow matrix after operation
int VM_num, flow_num;

void main()
{
    //clrscr();
    FILE *traffic;

    //Read the traffic matrix data (1: Read the traffic matrix data)
    traffic = fopen("Merge_flows.txt","r");       
    fscanf(traffic, "%d \n", &VM_num);
    if (VM_num > MAX_VM) {
        printf("VM number exceeds maximum VM number %d \n", MAX_VM); 
        exit(1);
    } 

    flow_num = 0;
    printf("\n Enter the matrix:\n"); 
    //---------------------- Print out the traffic matrix 
    for(i=1; i<VM_num+1; i++){
	for(j=1; j<VM_num+1; j++){
	    fscanf(traffic, "%d", &VM_Matrix[i][j]);
            if (VM_Matrix[i][j] > 0)
                flow_num ++;
	    tmp[i][j] = VM_Matrix[i][j];
	    printf("%6d", tmp[i][j]);
	}
	printf("\n");
	fscanf(traffic, "\n");
    }

    FILE *TF,*TM;

    printf("\n");
    printf("\n");
    TF = fopen("flow_list.txt", "w");  // a list of flows
    fprintf(TF, "%d \n", flow_num/2);  // store flow number first (half?)
   
      //m_ij will be recorded in the data
    TM = fopen("flow_matrix.txt","w"); 
    fprintf(TM,"%d \n", VM_num);
      //為了方便之後的計算,先將traffic matrix 做成上三角矩陣 
    for(i=1; i<VM_num+1; i++){
	for(j=1; j<VM_num+1; j++){
	    fprintf(TM, "%6d", VM_Matrix[i][j]);
            // Make the lower half matrix to all zeros, why?
	    if(VM_Matrix[i][j]>0){
		VM_Matrix[j][i] = 0;
                // store flows in flow_list
	        fprintf(TF, "%6d  %d %d \n", VM_Matrix[i][j], i, j);   
	    }
	    printf("%6d", VM_Matrix[i][j]);
        }
        fprintf(TM,"\n");
        printf("\n");
    } 
    printf("\n\n\n");
} 
