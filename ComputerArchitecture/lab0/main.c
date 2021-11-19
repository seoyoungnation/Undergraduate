#include <stdio.h>

extern void copyarray(int arr1[], int arr2[], int n);

void printarr(int arr[], int n){
	for(int i = 0; i < n ; i++)
		printf("%d ",arr[i]);
	printf("\n");
}

int main(){
	int arrOri[5] = {2, 6, 3, 7, 5};
	int arrCpy[5] = {0, };
	int num = 5;

	printf("Array Original :");
	printarr(arrOri,num);

	printf("Array Copy :");
	printarr(arrCpy,num);

	copyarray(arrOri, arrCpy, num);

	printf("Array Original :");
	printarr(arrOri,num);

	printf("Array Copy :");
	printarr(arrCpy,num);

	return 0;
}
