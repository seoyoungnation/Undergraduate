#include <stdio.h>
#include <stdlib.h>

extern void matrix(int** A, int** B, int** C, int index[]);

int main(){
	int i = 0 ;
	int j = 0 ;
	int k = 0 ;

	int ArraySize[3];
	int idx = 0;
	
	//setting s, u, v
	printf("\nInput values of s, u, v : ");

	while(idx < 3){
		ArraySize[idx] = getchar() - '0';
		idx++;
	}	
	getchar();

	// memory allocation of A, B, C
	int** A = (int**)malloc(sizeof(int) * ArraySize[0]);
	int** B = (int**)malloc(sizeof(int) * ArraySize[1]);
	int** C = (int**)malloc(sizeof(int) * ArraySize[0]);

	for (idx=0; idx < ArraySize[0]; idx++)
		A[idx] = (int*)malloc(sizeof(int) * ArraySize[1]);
	for (idx=0; idx < ArraySize[2]; idx++){
		B[idx] = (int*)malloc(sizeof(int) * ArraySize[2]);
		C[idx] = (int*)malloc(sizeof(int) * ArraySize[2]);
	}


	//setting matrix A and B as input	
	printf("\nInput value of A : ");
	for(i=0; i < ArraySize[0]; i++){
		for(j=0; j < ArraySize[1]; j++){       
			*(A[i]+j) = getchar()-'0';
		}
	}
	j=0; i=0;
	getchar();
		
	printf("\nInput value of B : ");
	for(j=0; j < ArraySize[1]; j++){
		for(k=0; k < ArraySize[2]; k++){       
			*(B[j]+k) = getchar()-'0';
		}
	}
	getchar();
	k=0; j=0;	
		
	//print matrices
	printf("\nArray A \n");
	for(i=0; i < ArraySize[0]; i++){
		for(j=0; j < ArraySize[1]; j++){  
		printf("%d ",*(A[i]+j));
		}
		printf("\n");	
	}
	i=0;
	j=0;
		
	printf("Array B \n");
	for(j=0; j < ArraySize[1]; j++){
		for(k=0; k < ArraySize[2]; k++){   
		printf("%d ",*(B[j]+k));
		}
		printf("\n");	
	}
	j=0;
	k=0;
				
	matrix( A, B, C, ArraySize);
	
	//print result
	printf("Array C after Operating : \n");
	for(i=0; i < ArraySize[0]; i++){
		for(k=0; k < ArraySize[2]; k++){  
		printf("%d ",*(C[i]+k));
		}
		printf("\n");	
	}
	
	//memory deallocation
	free(A); free(B); free(C);
	return 0;
}
