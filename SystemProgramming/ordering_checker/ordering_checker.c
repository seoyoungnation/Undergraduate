

#include <stdio.h>


typedef unsigned char *bytep;

int main(){
	int val = 0x00000001;
	bytep valp = (bytep) &val;

	if (valp[0])
		printf("Little endian\n");

	else
		printf("Big endian\n");

	return 0;

}
