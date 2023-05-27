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
#define READ_THIS "read this >"
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
void file_kbr();
void learn_file(char* file_string);

int main(){
	char *user_string=NULL,*sentence=NULL,*kbr,*file;
	char *c,*s,*sstring=NULL,*sstring1=NULL;
	int desicion;
	int i=0;
	
	srand(time(NULL));	
	printf("Type exit if you want to end the programm and to print the list\n");
	printf("%s Hi, i dont have time to chat go away\n",GPT);
	//file_kbr();
	//getchar();
	do{
		printf("%s ",USER);
		user_string = learn_kbr();
		kbr = strstr(user_string,LEARN_THIS);
		file = strstr(user_string,READ_THIS);				    			
		if(kbr){
			learn(user_string);
			sortlist();
			//list_display();
		}
		else if(file){
			learn_file(user_string);
		}
	}while(strcmp(user_string,"exit")!=0);
	list_display();
}

void reply(char *concept,int search){
	int i=0,j=0;
	char *learn_first[5]={"Learnig about","","WOW!","Ok then","Well i guess"};
	char *learn_second[4]={"was interesting.","was good,can you leave me alone now?",".",",but why though?"};
	char *sheKnows_first[4]={"You think i am stupid?","Eh? are you drunk?","Go see a doctor","Please!"};
	char *sheKnows_second[4]={"i already know this.","i know that! you have taught me this,fool","pfff let it go,you are just stupid","stop teaching me things that i know!"};
	//gtpList *new=NULL;
	if (search != 1){
		i = rand()%5;
		j = rand()%4;
		printf("%s %s%s%s\n",GPT,learn_first[i],concept,learn_second[j]);
	}
	else if(search == 1){
		i = rand()%4;
		j = rand()%4;
		printf("%s %s%s%s\n",GPT,sheKnows_first[i],concept,sheKnows_second[j]);
	}
}

void learn(char* user_string){
	char* token = NULL;
	char* variables[3];
	int i=0;

	token = strtok(user_string,">:");
	while( token != NULL ) {
      		token = strtok(NULL,">:");
		if (token!=NULL){
			variables[i]=token;
			i++;
		}
   	}		
   	insert_kbr(variables[0],variables[1],0);
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
	//printf("%s%s\n",concept,sentence);	
	new = (gtpList*)malloc(sizeof(gtpList));
	searched = search(concept);
	if(searched != 1){
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
	}
	
	reply(concept,searched);
}

void file_kbr(){
	FILE *fptr;
	long str_length;
	char *str;

	// Open the file.
	fptr = fopen("/home/klaudio/Downloads/wikipedia_100.txt" , "rb");

	// Get the size of the file.
	fseek(fptr, 0, SEEK_END);
	str_length = ftell(fptr);
	rewind(fptr);

	// Allocate memory to contain the whole file including the null byte.
	str = calloc(str_length + 1, sizeof(char)); // +1 for null byte.

	// Read the contents of the file into the buffer.
	//fread(str, 1, str_length, fptr);
	while(fgets(str,str_length, fptr))
	{
    		str[strcspn(str, "\n")] = '\0';
		if (strcmp(str, "\n") == 0) break;
	}

	// Null terminate the string.
	str[str_length] = '\0';

	// Close the file.
	fclose(fptr);

	// Print the contents of the file.
	printf("%s", str);
	//learn_file(str);


	/*FILE *file1=NULL;
	char *buffer;
	buffer = (char*)malloc(sizeof(char));
	
	file1 = fopen("/home/klaudio/Downloads/wikipedia_100.txt","r");
	if (file1 == NULL){
		printf("no such file");
		return;
	}
	fscanf(file1,"%s",buffer = learn_file());
	printf("1 : %s\n", buffer );
	
	fgets(buffer, 255, (FILE*)file1);
   	printf("2: %s\n", buffer );
   	
   	fgets(buffer, 255, (FILE*)file1);
   	printf("3: %s\n", buffer );
   	fclose(file1);*/

}

void learn_file(char* file_string){
	FILE *fptr;
	long str_length;
	char *str,*final_str;
	char* token = NULL;
	char* variables[2];
	char* variables1[2];
	char* sstring = NULL;
	char* sstring2 = NULL;
	char sstring1[256]={"/home/klaudio/Downloads/"};
	int i=0;

	token = strtok(file_string,">:");
	while( token != NULL ) {
      		token = strtok(NULL,">:");
		if (token!=NULL){
			//printf("first token: %s i: %d\n",variables[i],i);
			variables[i]=token;
			i++;
			//printf("second token: %s i: %d\n",token,i);
			//printf("%s %s\n",variables[0],variables[1]);
		}
   	}
   	printf("first token: %s %s \n",variables[0],variables[1]);		
   	//insert_kbr(variables1[0],variables1[1],0);
   	i=0;
   	
   	sstring = variables[0];
   	printf("the path is: %s\n",sstring);
   	sstring = strcat(sstring1,sstring);
   	if (sstring == NULL){
   		printf("wrong input \n");
   		return;
   	}
   	
   	 printf("the string is: %s\n",sstring);
   	// Open the file.
	fptr = fopen(sstring,"rb");
	if (fptr == NULL){
		printf("No such file");
		return;
	}
	
	fseek(fptr, 0, SEEK_END);
	str_length = ftell(fptr);
	rewind(fptr);

	// Allocate memory to contain the whole file including the null byte.
	str = calloc(str_length + 1, sizeof(char)); // +1 for null byte.
	final_str = calloc(str_length + 20, sizeof(char));
	// Read the contents of the file into the buffer.
	//fread(str, 1, str_length, fptr);
	while(fgets(str,str_length, fptr))
	{
    		str[strcspn(str, "\n")] = '\0';
		if (strcmp(str, "\n") == 0) break;
	}

	// Null terminate the string.
	str[str_length] = '\0';

	// Close the file.
	fclose(fptr);
	
	printf("First string:    %s", str);
	strcat(final_str,"read this > ");
	strcat(final_str,str);
	printf("Second String:    %s", final_str);
	
	token = strtok(final_str,">:");
	while( token != NULL ) {
      		token = strtok(NULL,">:");
		if (token!=NULL){
			//printf("first token: %s i: %d\n",token,i);
			variables1[i]=token;
			i++;
			//printf("second token: %s i: %d\n",token,i);
			//printf("%s %s\n",variables[0],variables[1]);
		}
   	}
   	printf("tokened: %s %s \n",variables1[0],variables1[1]);		
   	insert_kbr(variables1[0],variables1[1],0);
   	i=0;
	
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
