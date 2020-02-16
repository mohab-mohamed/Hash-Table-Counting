#include <stdio.h>
#include <stdlib.h>

struct node
{
	long int key;
	long long int value;
	struct node *next;
};

struct arrNode
{
	struct node *head;
	struct node *tail;
};

struct arrNode *array;

long int hashFunction();

int main(int argc, char *argv[]) {

	
	int isUnique = 1;
	long int notUniqueIndex;
	long long int notUniqueValue;
	long long int hex;
	long uniqueAddress = 0; 
	
	if(argc == 1){
		printf("error\n");
		return 0;
	}
	int i ; 
	array = (struct arrNode*) malloc(20000 * sizeof(struct node));
	for( i = 0; i < 20000; i++) {
		array[i].head = NULL;
		array[i].tail = NULL;
	}
	for( i = 0; i <20000; i++ ) {
		struct node *tmp_head =(struct node*)malloc(sizeof(struct node));
		tmp_head->value = -1;
		array[i].head = tmp_head;
	}
	
	FILE *file = fopen(argv[1], "r");
	
	if(file == NULL) {
		printf("error\n");
		return 0;
	}
	
	while (fscanf(file, "%X\n", &hex) != EOF) {
		isUnique = 1;
		for ( i = 0; i < 20000; i++) {
			if(array[i].head->value == hex) {
				isUnique = 0;
				notUniqueIndex = i;
				notUniqueValue = array[i].head->value;
				break;
			}
		}
		if (isUnique == 1) {
			int index = hashFunction(rand());
			
			while(array[index].head->value != -1) {
				index = hashFunction(rand());
			}
			struct node *item = (struct node*)malloc(sizeof(struct node));
			item->value = hex;
			array[index].head = item; 		
		}		
	}
	for (i =0; i < 20000; i++) {
		if(array[i].head->value != -1) {
			uniqueAddress++;
		}
	}
	printf("%i\n", uniqueAddress);
	return 0;
}

long int hashFunction(long int key) {
	
	return (key % 20000);
}
