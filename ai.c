#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

void reply(char* concept,int search);
void learn(char* user_string);
char* learn_kbr();
void insert_kbr(char* concept,char* sentence,int used);
void sortlist();
int search(char* stringToSearch); 
void list_display();

int main(){
	char *user_string=NULL,*sentence=NULL,*test;
	char *c,*s,*sstring=NULL,*sstring1=NULL;
	int desicion;
	int i=0;
	char* variables[3];
	
	srand(time(NULL));	
	//printf("press 1 if you want to learn something\n");
	//printf("press 0 if you want to print the list\n");
	//scanf("%d",&desicion);
	printf("%s Hi, i dont have time to chat go away\n",GPT);
	//getchar();
	do{
			printf("%s ",USER);
			user_string = learn_kbr();
			
			test = strstr(user_string,LEARN_THIS);
			if(test){
				learn(user_string);
				sortlist();
			}
			else{
				printf("Type 0 if you want to exit\n");
			}
			printf("%s ",USER);
		//printf("press 1 if you want to learn something\n");
		//printf("press 0 if you want to print the list\n");
		scanf("%d",&desicion);
	}while(desicion!=0);
	/*printf ("unsorted list : \n");
	list_display();
	sortlist();
	printf ("sorted list : \n");*/
	//searched = search("klaudio manofi");
	//printf("the search has searched: %d\n",searched);
	
	list_display();
}

void reply(char *concept,int search){
	int i=0,j=0;
	char *learn_first[5]={"Learnig about","","WOW!","Ok then","Well i guess"};
	char *learn_second[4]={"was interesting.","was good,can you leave alone me now?",".",",but why though?"};
	char *sheKnows_first[4]={"You think i am stupid?","Eh? are you drunk?","Go see a doctor","Please!"};
	char *sheKnows_second[4]={"i already know this.","i know that! you have taught me this,fool","pfff let it go,you are just stupid","stop teaching me things that i know!"};
	//gtpList *new=NULL;
	if (search != 1){
		i = rand()%5;
		j = rand()%4;
		printf("%s%s%s\n",learn_first[i],concept,learn_second[j]);
	}
	else if(search == 1){
		i = rand()%4;
		j = rand()%4;
		printf("%s%s%s\n",sheKnows_first[i],concept,sheKnows_second[j]);
	}
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
   	insert_kbr(variables[1],variables[2],0);
   	i=0;
}

char* learn_kbr(){
	char *user_string = NULL,*tmp = NULL;
    	int size = 0, index = 0;
    	int ch = EOF;

	//printf("%s ",USER);
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
	int searched;
	gtpList *new = NULL;
	new = (gtpList*)malloc(sizeof(gtpList));
	searched = search(concept);
	if(searched != 1){
	//searched = search(new->concept);
		if(new == NULL){
			printf("Memory allocation failed \n");
			exit(0);
		}
		if(head == NULL){
			new->concept = concept;
			new->sentence = sentence;
			strcpy(new->learnedFrom,"kbr");
			new->timesUsed = used;
			new->prev = NULL;
			new->next = NULL;
			head = new;
		}
		else{
			new->concept = concept;
			new->sentence = sentence;
			strcpy(new->learnedFrom,"kbr");
			new->timesUsed = used;
			new->prev = NULL;
			new->next = head;
			head->prev = new;
			head = new;
		}
		printf("Node inserted \n");
		//searched = search(concept);
	}
	
	reply(concept,searched);
}


int search(char* data) {
   int pos = 0;
   gtpList *current=NULL;
   if(head==NULL) {
      printf("Linked List not initialized");
      return 0;
   } 

   current = head;
   while(current!=NULL) {
      pos++;
      if(strcmp(current->concept,data)==0) {
         printf("%s found at position %d\n", data, pos);
         return 1;
      }

      if(current->next != NULL)
         current = current->next;
      else
         break;
   }

   printf("%s does not exist in the list\n", data);
   return 2;
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
