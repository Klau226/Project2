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

#define LEARN_THIS  "learn this >"
#define READ_THIS "read this >"
#define FORGET_THIS "forget this >"
#define GPT "ChatGpt$ "
#define USER "User$ "
#define MAX_LENGTH 5


void reply(char* concept,int search);
char* removeWhitespace(char* user_string);
void learn(char* user_string);
char* learn_kbr();
void insert_kbr(char* concept,char* sentence,int used,char* type);
void sortlist();
int search(char* stringToSearch); 
void list_display();
void listdisplay_concept();
void listdisplay_timesUsed();
void display_struct();
void learn_file(char* file_string);
void forget(char* user_string);
void deleteNode(gtpList *del);
char* question(char *user_string);
gtpList* answerTheQuestion(char* keyword,gtpList* prevSearch);

int main(){
	char *user_string=NULL,*sentence=NULL,*kbr,*file,*forget_string,*point,*answer,*keyword,*printConcept,*printTimesUsed,*help,*fortytwo,*print,*print_struct;
	char* questions;
	gtpList *ptr=NULL;
	
	
	FILE *fp;
	fp = fopen("dialogue.txt", "w");
	if(fp == NULL) {
        	printf("file couldn't be opened\n");
        	exit(1);
    	}
	
	srand(time(NULL));	
	printf("Type exit if you want to end the programm and to print the list\n");
	printf("Type Help Me Please to help you with the grammar\n");
	printf("Type Print The List to print the list\n");
	printf("Type Print The Struct to print all the struct\n");
	printf("\n");
	printf("%s Hi, i dont have time to chat go away\n",GPT);
	do{
		printf("%s ",USER);
		user_string = learn_kbr();
		kbr = strstr(user_string,LEARN_THIS);
		file = strstr(user_string,READ_THIS);
		forget_string = strstr(user_string,FORGET_THIS);
		printConcept = strstr(user_string,"What do you know about?");
		printTimesUsed = strstr(user_string,"What do you talk about?");
		point = strstr(user_string,".");
		answer = strstr(user_string,"?");
		help = strstr(user_string,"Help Me Please");
		fortytwo = strstr(user_string,"What is the meaning of Life, The Universe, and Everything?");
		print = strstr(user_string,"Print The List");
		print_struct = strstr(user_string,"Print The Struct");

		fprintf(fp, "\n");
					    			
		if(kbr){
			learn(user_string);		
			sortlist();
			
		}
		else if(file){
			learn_file(user_string);
			sortlist();
		}
		else if(forget_string){
			forget(user_string);
		}
		else if(printConcept){
			listdisplay_concept();
		}
		else if(printTimesUsed){
			listdisplay_timesUsed();
		}
		else if(point){
				reply(user_string,4);
		}
		else if(answer){
			keyword = strstr(user_string,"*");
			if(keyword){
				questions = question(user_string);
				ptr = answerTheQuestion(questions,ptr);
				if (ptr != NULL){
					reply(questions,6);
					printf("%s%s \n",GPT,ptr->sentence);
					fprintf(fp,"%s%s\n",GPT,ptr->sentence);
				}
				else if(ptr == NULL){
					reply(questions,5);
					
				}
				else{
					ptr = NULL;
				}
			}
			else{
				printf("%s If you have a question use '*your question*' \n",GPT);
				fprintf(fp,"%s If you have a question use '*your question*' \n",GPT);
			}
		}
		else if(help){
			printf("\n");
			printf("-----------------------------------------------------------------------------------------------------------------------------------\n");
			printf("~If you want to learn something type: learn this > 'Your Concept': 'Your Sentence'\n");
			printf("~If you want to read from a file type: read this > 'File Name'\n");
			printf("~If you want to delete something type: forget this > 'Concept'\n");
			printf("~If you want to search something type anything you like and the keyword *keyword* that you want to search and '?' or '.' in the end\n");
			printf("~If you want to speak with Chat GPT just end your conversation with '.' or '?'\n");
			printf("~If you want to print the list which prints only the concept type: 'What do you know about?'\n");
			printf("~If you want to print the concept and the times that the concept or the sentence have been used type: 'What do you talk about?'\n");
			printf("Be careful!! there is a file named dialogue.txt in your system and the conversation will be stored(you like it or not)\n");
			printf("-----------------------------------------------------------------------------------------------------------------------------------\n");
			printf("\n");
		}
		else if(fortytwo){
			printf("%s 42\n",GPT);
			fprintf(fp,"%s 42 \n",GPT);
		}
		else if(print){
			list_display();
		}
		else if(print_struct){
			display_struct();
		}
		else{
			printf("%s Type the keywords fool,first time chatting with me? \n",GPT);
			fprintf(fp,"%s Type the keywords fool,first time chatting with me? \n",GPT);
		}
	}while(strcmp(user_string,"So Long, and Thanks for All the Fish")!=0);
	printf("%s Good bye dont come again \n",GPT);
	fprintf(fp,"%s Good bye dont come again \n",GPT);
	list_display();
	fclose(fp);
}

void reply(char *concept,int search){
	int i=0,j=0;
	char *learn_first[5]={"Learnig about","","WOW! i learned","Ok then i learned","Well i guess learning"};
	char *learn_second[5]={"was interesting.","was good,can you leave me alone now?","was a pleasure","was easy,but why though?","was a piece of cake"};
	char *sheKnows_first[5]={"You think i am stupid?","Eh? are you drunk?","Go see a doctor","Please!","Try again"};
	char *sheKnows_second[5]={",i already know this.",",i know that! you have taught me this,fool",",pfff i know that let it go,you are just stupid",",stop teaching me things that i know!",",i know it!"};
	char *deletion_first[5]={"Hmmm i think i remember somethink like ","What is ","i dont understand you what is ","What??? ","Emmm"};
	char *deletion_second[5]={"nhaa its nothing.","i just forgot it.","i dont remember :)","i am so naive.","pfff i have alzheimer"};
	char *point[5] = {"You are right!","Lets do this","If you say so","I dont think so but okay","Let me be please"};
	char *cantFind_first[5]={"I am done ","Try again ","Lookout! ","Cmooon ","Are you serious? "};
	char *cantFind_second[5]={",couldnt find the word.",",there is no such word.",",neither concept nor centence like this.",",search again.",",no word like this."};
	char *found_first[5]={"Hurray! ","Searching..... ","Lets get to work....","Well ","It seems like "};
	char *found_second[5]={",found it!","found it, now let me be","found it, stop bothering me now","found it, and it wasn't easy","ffffound stop now",};
	
	FILE *fp;
	fp = fopen("dialogue.txt", "a");
	if(fp == NULL) {
        	printf("file couldn't be opened\n");
        	exit(1);
        	
    	}
	
	if (search == 2 || search==0){
		i = rand()%5;
		j = rand()%5;
		printf("%s %s %s %s\n",GPT,learn_first[i],concept,learn_second[j]);
		fprintf(fp,"%s %s %s %s\n",GPT,learn_first[i],concept,learn_second[j]);
	}
	else if(search == 1){
		i = rand()%5;
		j = rand()%5;
		printf("%s %s %s %s\n",GPT,sheKnows_first[i],concept,sheKnows_second[j]);
		fprintf(fp,"%s %s %s %s\n",GPT,sheKnows_first[i],concept,sheKnows_second[j]);
	}
	else if(search==3){
		i = rand()%5;
		j = rand()%5;
		printf("%s %s %s %s\n",GPT,deletion_first[i],concept,deletion_second[j]);
		fprintf(fp,"%s %s %s %s\n",GPT,deletion_first[i],concept,deletion_second[j]);
	}
	else if(search == 4){
		i = rand()%5;
		printf("%s %s\n",GPT,point[i]);
		fprintf(fp,"%s %s\n",GPT,point[i]);
	}
	else if(search == 5){
		i = rand()%5;
		j = rand()%5;
		printf("%s %s %s %s\n",GPT,cantFind_first[i],concept,cantFind_second[j]);
		fprintf(fp,"%s %s %s %s\n",GPT,cantFind_first[i],concept,cantFind_second[j]);
	}
	else if(search == 6){
		i = rand()%5;
		j = rand()%5;
		printf("%s %s %s %s\n",GPT,found_first[i],concept,found_second[j]);
		fprintf(fp,"%s %s %s %s\n",GPT,found_first[i],concept,found_second[j]);
	}
}

char* removeWhitespace(char* user_string){
	int i,j;
	int foundWhitespace = 0;
	for (i = 0, j = 0; user_string[i] != '\0'; i++) {
        		if (user_string[i] == ' ' && !foundWhitespace) {
            			foundWhitespace = 1; // Set the flag to indicate that the first white space has been found
        		}
        		else {
            			user_string[j++] = user_string[i];
        		}
    		}
    		//foundWhitespace=0;
    		user_string[j] = '\0';
		return user_string;
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
   	
   	variables[0] = removeWhitespace(variables[0]);
   	variables[1] = removeWhitespace(variables[1]);		
   	insert_kbr(variables[0],variables[1],0,"kbr");
   	
   	i=0;
}

void forget(char* user_string){
	gtpList *current=NULL;
	char* token = NULL;
	char* variables[3];
	char* sstring;
	int i=0;
	
	
	sstring = (char*)malloc(sizeof(user_string)*sizeof(char));
	sstring = user_string;
	sstring = strcat(sstring,": ");
	token = strtok(sstring,">:");
	while( token != NULL ) {
      		token = strtok(NULL,">:");
		if (token!=NULL){
			variables[i]=token;
			i++;
		}
   	}
   	i=0;
   	
   	variables[0] = removeWhitespace(variables[0]);	     
	if(head == NULL) {  
    		printf("%s For real you need a doctor,first time i hear about %s \n",GPT,variables[0]);
        	return;  
    	}   
	current = head;    
	while(current!=NULL) {
      		if(strcasecmp(current->concept,variables[0])==0) {
		 	printf("%s found and deleted\n", variables[0]);
		 	deleteNode(current);
		 	reply(variables[0],3);
		 	return;
		 }
		 current = current->next;	
	}    	

	printf("%s For real you need a doctor,first time i hear about %s \n",GPT,variables[0]);	
}

void deleteNode(gtpList *del){ 
    if (head==NULL){
    	return;
    }

   if(head == del){
   	if(del->next != NULL){
    		head = del->next;
    		head->prev = NULL;
    		free(del);
    		return;
    	}
    	else{
    		head->next = NULL;
    		head->prev = NULL;
    		head = NULL;
    		return;
    		
    	}
    
   }
   gtpList *curr=head;
   if (del->next == NULL) {
   	curr = del->prev;
        curr->next = NULL;
        del = NULL;
        free(del);
        return;
    }

   del->next->prev = del->prev;
   del->prev->next = del->next;
   free(del);
   return;	
}


char* learn_kbr(){
	char *user_string = NULL,*tmp = NULL;
    	int size = 0, i = 0;
    	int ch = EOF;

	//printf("%s ",USER);
    while (ch) {
        ch = getc(stdin);

        /* Check if we need to stop. */
        if (ch == EOF || ch == '\n')
            ch = 0;

        /* Check if we need to expand. */
        if (size <= i) {
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
        user_string[i++] = ch;
    }
	
    return user_string;
}


void sortlist(){
	gtpList *current = NULL, *index = NULL;  
    char* temp=NULL;  
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
void insert_kbr(char* concept,char* sentence,int used,char* type){
	int searched;
	gtpList *new = NULL;
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
			strcpy(new->learnedFrom,type);
			new->timesUsed = used;
			new->prev = NULL;
			new->next = NULL;
			head = new;
		}
		else{
			new->concept = concept;
			new->sentence = sentence;
			strcpy(new->learnedFrom,type);
			new->timesUsed = used;
			new->prev = NULL;
			new->next = head;
			head->prev = new;
			head = new;
		}
	}
	
	reply(concept,searched);
}

void learn_file(char* file_string){
	FILE *fptr;
	char* token = NULL;
	char sstring1[256]={"/home/klaudio/Downloads/"};
	char* variables[1];
	char* variables2[2];
	char* line;
	int i;

	file_string = removeWhitespace(file_string);

	token = strtok(file_string,">");
	i=0;
	while( token != NULL ) {
      		token = strtok(NULL,">");
      		printf("Second token:%s",token);
		if (token!=NULL){
			variables2[i]=token;
			i++;
		}
   	}
	token = NULL;
   	i=0;
	
	variables2[0] = removeWhitespace(variables2[0]);
	fptr = fopen(variables2[0],"r");
	if (fptr == NULL){
		printf("Error opening file \n");

    		return ;
	}
	line = (char*)malloc(1000*sizeof(char));
    	while (fgets(line, 1000, fptr)) {  		
        	token = strtok(line, ":.");
        	variables[i]=strdup(token);
        	i++;
        	while (token != NULL) {
        		token = strtok(NULL, ":.");
			if(token!=NULL){
            			variables[i] = strdup(token); // Allocate memory for the token
            			i++;
            		}
        	}
      
    		variables[0] = removeWhitespace(variables[0]);
    		variables[1] = removeWhitespace(variables[1]);
        	if (variables[0] != NULL && variables[1] != NULL) {
            		insert_kbr(variables[0], variables[1], 0, "file");
        	}
        	variables[0] = NULL;
        	variables[1] = NULL;
        	i = 0;
        }
        token = NULL;
        free(line);
}

char* question(char *user_string){
	char* token = NULL;
	int i=0;
	char* variables[3];
	
	token = strtok(user_string,"**");
	while( token != NULL ) {
      		token = strtok(NULL,"**");
		if (token!=NULL){
			variables[i]=token;
			i++;
		}
   	}
   	variables[0] = removeWhitespace(variables[0]);		
   	i=0;
   	return variables[0];
}

gtpList* answerTheQuestion(char* keyword,gtpList* prevSearch){
	gtpList *current = NULL;



    	if (head == NULL) {
    		printf("Linked List not initialized");
        	return NULL;
    	}
    	if(prevSearch == NULL){
    		current = head;
    		while (current != NULL) {
        		if (strstr(current->concept, keyword) != NULL) {
           			current->timesUsed++;
            			return current;
        		}

        		if (current->next != NULL) {
            			current = current->next;
        		} else {
            			break;
        		}
        		if (strstr(current->sentence, keyword) != NULL) {
            			current->timesUsed++;
            			return current;
        		}

        		if (current->next != NULL) {
            			current = current->next;
        		} else {
            			break;
        		}
        	}
    	}	

    /*else if(prevSearch != NULL){ 
        current = prevSearch;
        while (current != NULL) {
        	if (strstr(current->concept, keyword) != NULL) {
                	current->timesUsed++;
                	return current;
            	}
            	else if (strcmp(current->concept, keyword) < 0) {
                	if (current->next != NULL) {
                    		printf("Going Right! \n");
                    		current = current->next;
                	}
            	} else if(strcmp(current->concept, keyword) > 0){
                	if (current->prev != head) {
                    		printf("Going Left! \n");
                    		current = current->prev;					//DOESN'T WORK!!
        		}
        	}
        	if(strstr(current->sentence, keyword) != NULL){
                	current->timesUsed++;
                	return current;
            	}
            	else if (strcmp(current->sentence, keyword) < 0) {
                	if (current->next != NULL) {
                    		printf("Going Right! \n");
                    		current = current->next;
                	}
            	} else if(strcmp(current->sentence, keyword) > 0){
                	if (current->prev != head) {
                    		printf("Going Left! \n");
                    		current = current->prev;
                	}
            	}
    
	}
    }*/
    return NULL;
}


int search(char* data) {
   int pos = 0;
   gtpList *current=NULL;
   if(head==NULL) {
      //printf("Linked List not initialized");
      return 0;
   } 

   current = head;
   while(current!=NULL) {
      pos++;
      if(strcmp(current->concept,data)==0) {
         return 1;
      }

      if(current->next != NULL)
         current = current->next;
      else
         break;
   }

   
   return 2;
}
     
void list_display(){
	gtpList *ptr = NULL;
	ptr = head;
	
	FILE *fp;
	fp = fopen("dialogue.txt", "a");
	if(fp == NULL) {
        	printf("file couldn't be opened\n");
        	exit(1);
    	}
    	
	while(ptr!=NULL){
		printf("Concept :%s\n",ptr->concept); 
		printf("Sentence:%s\n",ptr->sentence); 
		fprintf(fp,"Concept: %s",ptr->concept);
		fprintf(fp,"\n");
		fprintf(fp,"Sentence: %s",ptr->sentence);
		fprintf(fp,"\n");
        	ptr=ptr->next;  
	}
	free(ptr);

}

void listdisplay_concept(){
	gtpList *ptr = NULL;
	ptr = head;

	FILE *fp;
	fp = fopen("dialogue.txt", "a");
	if(fp == NULL) {
        	printf("file couldn't be opened\n");
        	exit(1);
    	}
	
	while(ptr!=NULL){
		printf("Concept: %s\n",ptr->concept); 
		fprintf(fp,"Concept:  %s",ptr->concept);
		fprintf(fp,"\n");
        	ptr=ptr->next;  
	}
	free(ptr);

}

void listdisplay_timesUsed(){
	gtpList *ptr = NULL;
	ptr = head;
	
	FILE *fp;
	fp = fopen("dialogue.txt", "a");
	if(fp == NULL) {
        	printf("file couldn't be opened\n");
        	exit(1);
    	}
	
	while(ptr!=NULL){
		if(ptr->timesUsed > 0){ 
			printf("Concept: %s      Times Used: %d\n",ptr->concept,ptr->timesUsed);
			fprintf(fp,"Concept: %s      Times Used: %d\n",ptr->concept,ptr->timesUsed); 
		}	
        	ptr=ptr->next;  
	}
	free(ptr);

}

void display_struct(){
	gtpList *ptr = NULL;
	ptr = head;
	
	FILE *fp;
	fp = fopen("dialogue.txt", "a");
	if(fp == NULL) {
        	printf("file couldn't be opened\n");
        	exit(1);
    	}
    	
    	while(ptr!=NULL){
		
		printf("Concept: %s  Sentence: %s  Time Used: %d  Learned From: %s\n",ptr->concept,ptr->sentence,ptr->timesUsed,ptr->learnedFrom);
		fprintf(fp,"Concept: %s  Sentence: %s  Time Used: %d  Learned From: %s\n",ptr->concept,ptr->sentence,ptr->timesUsed,ptr->learnedFrom);	
        	ptr=ptr->next;  
	}
	free(ptr);
}
