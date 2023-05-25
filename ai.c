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

#define LEARN_THIS  "learn this > "
#define C ">"
#define S ":"
#define GPT "ChatGpt$ "
#define USER "User$ "
#define MAX_LENGTH 5

void learn(char* user_string);
char* learn_kbr();
void insert_kbr(char* concept,char* sentence,int used);
void sortlist();
void list_display();

int main(){
	char *user_string=NULL,*sentence=NULL,*test;
	char *c,*s,*sstring=NULL,*sstring1=NULL;
	int desicion;
	int i=0;
	char* variables[3];
	printf("press 1 if you want to learn something\n");
	printf("press 0 if you want to print the list\n");
	scanf("%d",&desicion);
	getchar();
	while(desicion!=0){
			user_string = learn_kbr();
			test = strstr(user_string,LEARN_THIS);
			if(test){
				learn(user_string);
			}
		
		printf("press 1 if you want to learn something\n");
		printf("press 0 if you want to print the list\n");
		scanf("%d",&desicion);
		getchar();
	}
	/*printf ("unsorted list : \n");
	list_display();
	sortlist();
	printf ("sorted list : \n");*/
	list_display();
}

void learn(char* user_string){
	char* token = NULL,*variables[2];
	int i=0;
	
	token = strtok(user_string,">:");
			
	while( token != NULL ) {
		variables[i]=token;
		i++;
      		token = strtok(NULL,">:");
   	}
   	//for(i=0;i<3;i++){
   	//	printf("variables %d: %s\n",i,variables[i]);
   	//}
   	insert_kbr(variables[1],variables[2],0);
   	i=0;
}

char* learn_kbr(){
	char *user_string = NULL,*tmp = NULL;
    	int size = 0, index = 0;
    	int ch = EOF;

	printf("%s ",USER);
    while (ch) {
        ch = getc(stdin);

        /* Check if we need to stop. */
        if (ch == EOF || ch == '\n')
            ch = 0;

        /* Check if we need to expand. */
        if (size <= index) {
            size += MAX_LENGTH;
            tmp = realloc(user_string, size);
            if (!tmp) {
                free(user_string);
                user_string = NULL;
                break;
            }
            user_string = tmp;
        }

        /* Actually store the thing. */
        user_string[index++] = ch;
    }

    return user_string;
}


void sortlist(){
	gtpList *current = NULL, *index = NULL;  
    char* temp=NULL;  
    //Check whether list is empty  
    if(head == NULL) {  
    	printf("Memory allocation failed \n");
        return;  
    }  
    else {  
        //Current will point to head  
        for(current = head; current->next != NULL; current = current->next) {  
            //Index will point to node next to current  
            for(index = current->next; index != NULL; index = index->next) {  
                //If current's data is greater than index's data, swap the data of current and index  
        
                if(strcmp(current->concept,index->concept)>0){
                    temp = current->concept;  
                    current->concept = index->concept;  
                    index->concept = temp; 
                     
                    temp = current->sentence;
                    current->sentence = index->sentence;
                    index->sentence = temp;
                }  
            }  
        }  
    }  

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
		strcpy(new->learnedFrom,"kbr");
		new->prev = NULL;
		new->next = NULL;
		head = new;
	}
	else{
		new->concept = concept;
		new->sentence = sentence;
		strcpy(new->learnedFrom,"kbr");
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
