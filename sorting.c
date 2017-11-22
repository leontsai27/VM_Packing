#include <stdio.h>
#include <stdlib.h>
#define MAX_VM 50
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// 2: sort m_ij  with i, j => V in non-increasing order  (此程式是用來排序 m_ij)
int x[MAX_VM]={0};
int y[MAX_VM]={0};
int number[MAX_VM]={0} ;
int flow_num;
int main(int argc, char *argv[]) {
	

	FILE *st,*r;
	st = fopen("flow_list.txt","r");
	r = fopen("sorted_flows.txt","w");             //將排序後的 m_ij輸出 
    int i,j,temp,temp1,temp2;
    
    fscanf(st,"%d",&flow_num);

    
    for(i=0;i<flow_num;i++){
    	fscanf(st,"%d %d %d",&number[i],&x[i],&y[i]);
	//	printf("%d %d %d\n",number[i],x[i],y[i]);
	}
    

    for( i = 0; i < flow_num; i++) {
        for( j = i; j < flow_num; j++) {
            if( number[j] > number[i] ) {
                temp = number[j];
                number[j] = number[i];
                number[i] = temp;
                temp1 = x[j];
                x[j] = x[i];
                x[i] = temp1;
                temp2 = y[j];
                y[j] = y[i];
                y[i] = temp2;
            }
            
            else if( number[j] == number[i] ){
            	if( x[j] < x[i] ){
            		temp = number[j];
                	number[j] = number[i];
                	number[i] = temp;
                	temp1 = x[j];
                	x[j] = x[i];
                	x[i] = temp1;
                	temp2 = y[j];
                	y[j] = y[i];
                	y[i] = temp2;
				}
				if( x[j] == x[i]){
					if(y[j] < y[i]){
						temp = number[j];
                		number[j] = number[i];
                		number[i] = temp;
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
    
    fprintf(r,"%d \n",flow_num);

    for( i = 0; i < flow_num; i++ ) {
    	if(number[i]!=0){
		
        printf("%d %d %d\n", number[i],x[i],y[i]);
    	fprintf(r,"%d %d %d\n",number[i],x[i],y[i]);
     					}
	}


	return 0;
}
