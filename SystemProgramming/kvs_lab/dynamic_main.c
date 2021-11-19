#include "kvs.h"

int main()
{
	// 1. create KVS
	kvs_t* kvs = open();

	if(!kvs) {
		printf("Failed to open kvs\n");
		return -1;
	}

	// 2. put data 
	FILE *fp = fopen("student.dat", "r");
	
	if(!fp) {
		printf("Failed to open file\n");
		return -1;
	}

	while(!feof(fp)){
		char key[100];
		char *value = (char*)malloc(sizeof(char)*100);

		if (fscanf(fp, "%s %s\n", key, value) < 0){
			printf("Failed to read data\n");
			exit(-1);
		}

		if (put(kvs, key, value) < 0){
			printf("Failed to put data\n");
			exit(-1);
		}	
	}

	fclose(fp);

	fp = fopen("student.dat", "r");

	if(!fp){
		printf("Failed to open file\n");
		return -1;
	}

	while(!feof(fp)){
		char key[100]	;
		char *value = (char*)malloc(sizeof(char)*100);
		char *rvalue;
		
		if (fscanf(fp, "%s %s\n", key, value) < 0){
			printf("Failed to read data\n");
			exit(-1);
		}

		if(!(rvalue = get(kvs, key))){
			printf("Failed to get data\n");
			exit(-1);
		}

		printf("get: %s, %s\n", key, rvalue);
		
	}

	fclose(fp);

	close(kvs);

	return 0;

}	
