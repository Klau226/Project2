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
#define MAX_LENGTH 5

char* learn_kbr();
void insert_kbr(char* concept,char* sentence,int used);
void list_display();

int main(){
	char *concept=NULL,*sentence=NULL;
	int desicion;
	printf("press 1 if you want to learn something\n");
	printf("press 0 if you want to print the list\n");
	scanf("%d",&desicion);
	getchar();
	while(desicion!=0){
		if (desicion==1){
			concept = learn_kbr();
			sentence = learn_kbr();
			insert_kbr(concept,sentence,0);
			//learnSentence_kbr();	
		}
		printf("press 1 if you want to learn something\n");
		printf("press 0 if you want to print the list\n");
		scanf("%d",&desicion);
		getchar();
	}
	//insert_kbr(concept,sentence,0);
	list_display();
}

char* learn_kbr(){
	char *user_string = NULL,*tmp = NULL;
    	int size = 0, index = 0;
    	int ch = EOF;

	printf("Type the concept:\n");
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

/*void learnSentence_kbr(){
	char *sentence=NULL, *tmp = NULL;
    	int size = 0, index = 0;
    	int ch = EOF;
	printf("Type the sentence:\n");
    while (ch) {
        ch = getc(stdin);

        // Check if we need to stop. 
        if (ch == EOF || ch == '\n')
            ch = 0;

        // Check if we need to expand. 
        if (size <= index) {
            size += MAX_LENGTH;
            tmp = realloc(sentence, size);
            if (!tmp) {
                free(sentence);
                sentence = NULL;
                break;
            }
            sentence = tmp;
        }

        // Actually store the thing. 
        sentence[index++] = ch;
    }

    printf("the string is :%s",sentence);
}*/


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
