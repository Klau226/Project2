#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct gList {
 char *concept; // the concept learned
 char *sentence; // the sentence associated with the concept
 int timesUsed; //no of times the concept was used to an answer
 char learnedFrom[5]; //learned either from "file" or "kbrd"
 struct gList *next;
 struct gList *prev;
} gtpList;

gtpList* head = NULL;

#define LEARN_THIS = "learn this >"
#define MAX_LENGTH 1000

void learn_kbr();
void insert_kbr(char* concept,char* sentence,int used);
void list_display();

int main(){
	int desicion;
	printf("press 1 if you want to learn something\n");
	printf("press 0 if you want to print the list\n");
	scanf("%d",&desicion);
	getchar();
	while(desicion!=0){
		if (desicion==1){
			learn_kbr();	
		}
		printf("press 1 if you want to learn something\n");
		printf("press 0 if you want to print the list\n");
		scanf("%d",&desicion);
		getchar();
	}
	
	list_display();
}



void learn_kbr(){
	char* concept,*sentence;
	concept = (char*)malloc((MAX_LENGTH+1)*sizeof(char));
	sentence = (char*)malloc((MAX_LENGTH+1)*sizeof(char));
	if (concept == NULL || sentence == NULL) {
    		printf("Memory allocation failed.\n");
    		exit(1); // or return an error code
	}
	printf("Enter the concept: \n");
	//printf(" \n");
	fgets(concept, MAX_LENGTH, stdin);
	int length_con = strlen(concept);
	if (concept[length_con - 1] == '\n') {
    		concept[length_con - 1] = '\0';
	}
	printf("Enter the sentence: \n");
	fgets(sentence, MAX_LENGTH, stdin);
	int length_sen = strlen(sentence);
	if (sentence[length_sen - 1] == '\n') {
    		sentence[length_sen - 1] = '\0';
	}
	//printf("This is the concept : %s\n",concept);
	//printf("This is the sentence : %s\n",sentence);
	insert_kbr(concept,sentence,0);
	//free(sentence);
	//free(concept);
}

void insert_kbr(char* concept,char* sentence,int used){
	gtpList *new = NULL;
	new = (gtpList*)malloc(sizeof(gtpList));
	
	if(new == NULL){
		printf("Memory allocation failed \n");
		exit(0);
	}
	if(head == NULL){
		new->concept = concept;
		new->sentence = sentence;
		new->prev = NULL;
		new->next = NULL;
		head = new;
	}
	else{
		new->concept = concept;
		new->sentence = sentence;
		new->prev = NULL;
		new->next = head;
		head->prev = new;
		head = new;
	}
	printf("Node inserted \n");
}

void list_display(){
	gtpList *ptr = NULL;
	ptr = head;
	while(ptr!=NULL){
		printf("Concept: %s\n",ptr->concept); 
		printf("Sentence: %s\n",ptr->sentence); 
        	ptr=ptr->next;  
	}
	free(ptr);

}
	

