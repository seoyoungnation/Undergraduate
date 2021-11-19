#include "kvs.h"

char* get(kvs_t* kvs, const char* key)
{
	node_t *currNode = (node_t*)malloc(sizeof(node_t));
	currNode = kvs->db;

	while(currNode!=NULL){
		if(strcmp(currNode->key, key) == 0){
			return currNode->value;
		}
		currNode = currNode->next;
	}

	char* value = (char*)malloc(sizeof(char)*100);

	if(!value){
		printf("Failed to malloc\n");
		return NULL;
	}

	strcpy(value, "deadbeaf");
	return value;

}
