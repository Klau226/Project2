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
#define C ">"
#define S ":"
#define GPT "ChatGpt$ "
#define USER "User$ "
#define MAX_LENGTH 5


void reply(char* concept,int search);
void learn(char* user_string);
char* learn_kbr();
void insert_kbr(char* concept,char* sentence,int used,char* type);
void sortlist();
int search(char* stringToSearch); 
void list_display();
void listdisplay_concept();
void listdisplay_timesUsed();
void file_kbr();
void learn_file(char* file_string);
void forget(char* user_string);
void deleteNode(gtpList *del);
char* question(char *user_string);
gtpList* answerTheQuestion(char* keyword,gtpList* prevSearch);

int main(){
	char *user_string=NULL,*sentence=NULL,*kbr,*file,*forget_string,*point,*answer,*keyword,*printConcept,*printTimesUsed,*help;
	char *c,*s,*sstring=NULL,*sstring1=NULL;
	int desicion;
	int i=0;
	char* questions;
	gtpList *current=NULL,*ptr=NULL;
	
	
	FILE *fp;
	fp = fopen("dialogue.txt", "w");
	if(fp == NULL) {
        	printf("file couldn't be opened\n");
        	exit(1);
    	}
	
	srand(time(NULL));	
	printf("Type exit if you want to end the programm and to print the list\n");
	printf("Type Help Me Please to help you with the grammar\n");
	printf("\n");
	printf("%s Hi, i dont have time to chat go away\n",GPT);
	//file_kbr();
	//getchar();
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
		
		fwrite(user_string,1,strlen(user_string),fp);
		fprintf(fp, "\n");
		
						    			
		if(kbr){
			learn(user_string);
			sortlist();
			//list_dispay();
			
		}
		else if(file){
			learn_file(user_string);
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
			keyword = strstr(user_string,"*");
			if(keyword){
				questions = question(user_string);
				ptr = answerTheQuestion(questions,ptr);
				if (ptr != NULL){
					reply(questions,6);
					printf("%s%s \n",GPT,ptr->sentence);
					//fwrite(ptr->concept,1,strlen(ptr->concept),fp);
					fprintf(fp, "\n");
				}
				else{
					reply(questions,5);
					
				}
			}
			else{
				reply(user_string,4);
				//printf("If you have a question use '*your question*' \n");
			}
			//reply(user_string,4);
		}
		else if(answer){
			keyword = strstr(user_string,"*");
			if(keyword){
				questions = question(user_string);
				current = answerTheQuestion(questions,current);
				if (current != NULL){
					reply(questions,6);
					printf("%s%s \n",GPT,current->sentence);
					//printf("The current is : %s",current->concept);
				}
				else{
					reply(questions,5);
					
				}
			}
			else{
				reply(user_string,4);
			}
		}
		else if(help){
			printf("\n");
			printf("-------------------------------------------------------------------------------------------------------------------------------\n");
			printf("~If you want to learn something type: learn this > 'Your Concept': 'Your Sentence'\n");
			printf("~If you want to read from a file type: read this > 'File Name'\n");
			printf("~If you want to delete something type: forget this > 'Concept'\n");
			printf("~If you want to search something type anything you like and the keyword *keyword* that you want to search\n");
			printf("~If you want to speak with Chat GPT just end your conversation with '.' or '?'\n");
			printf("~If you want to print the list which prints only the concept type: 'What do you know about?'\n");
			printf("~If you want to print the concept and the times that the concept or the sentence have been used type: 'What do you talk about?'\n");
			printf("-------------------------------------------------------------------------------------------------------------------------------\n");
			printf("\n");
		}
		else{
			printf("Type the keywords fool,first time chatting with me? \n");
		}
		//list_display();
	}while(strcmp(user_string,"exit")!=0);
	list_display();
	fclose(fp);
}

void reply(char *concept,int search){
	int i=0,j=0;
	char *learn_first[5]={"Learnig about","","WOW!","Ok then","Well i guess"};
	char *learn_second[5]={" was interesting."," was good,can you leave me alone now?",".",", but why though?"," Good job"};
	char *sheKnows_first[5]={"You think i am stupid?","Eh? are you drunk?","Go see a doctor","Please!","Try again"};
	char *sheKnows_second[5]={" i already know this."," i know that! you have taught me this,fool"," pfff let it go,you are just stupid"," stop teaching me things that i know!"," i know it!"};
	char *deletion_first[5]={"Hmmm i think i remember somethink like ","What is ","i dont understand you what is ","??? ",""};
	char *deletion_second[5]={" nhaa its nothing."," i just forgot it."," i dont remember :)"," i am so naive."," pfff i have alzheimer"};
	char *point[5] = {"You are right!","Lets do this","If you say so","I dont think so but okay","Let me be please"};
	char *cantFind_first[5]={"I am done ","Try again ","Lookout! ","Cmooon ","Are you serious? "};
	char *cantFind_second[5]={" couldnt find the word."," there is no such word."," neither concept nor centence like this."," search again."," no word like this."};
	char *found_first[5]={"Hurray! ","Searching..... ","Lets get to work....","Well ","It seems like "};
	char *found_second[5]={" found it!"," found it, now let me be"," found it, stop bothering me now"," found it and it wasn't easy"," ffffound stop now",};
	//gtpList *new=NULL;
	
	FILE *fp;
	fp = fopen("dialogue.txt", "a");
	if(fp == NULL) {
        	printf("file couldn't be opened\n");
        	exit(1);
    	}
	
	if (search == 2 || search==0){
		i = rand()%5;
		j = rand()%5;
		printf("%s %s%s%s\n",GPT,learn_first[i],concept,learn_second[j]);
		fprintf(fp,"%s %s%s%s\n",GPT,learn_first[i],concept,learn_second[j]);
	}
	else if(search == 1){
		i = rand()%5;
		j = rand()%5;
		printf("%s %s%s%s\n",GPT,sheKnows_first[i],concept,sheKnows_second[j]);
		fprintf(fp,"%s %s%s%s\n",GPT,sheKnows_first[i],concept,sheKnows_second[j]);
	}
	else if(search==3){
		i = rand()%5;
		j = rand()%5;
		printf("%s %s%s%s\n",GPT,deletion_first[i],concept,deletion_second[j]);
		fprintf(fp,"%s %s%s%s\n",GPT,deletion_first[i],concept,deletion_second[j]);
	}
	else if(search == 4){
		i = rand()%5;
		printf("%s %s\n",GPT,point[i]);
		fprintf(fp,"%s %s\n",GPT,point[i]);
	}
	else if(search == 5){
		i = rand()%5;
		j = rand()%5;
		printf("%s %s%s%s\n",GPT,cantFind_first[i],concept,cantFind_second[j]);
		fprintf(fp,"%s %s%s%s\n",GPT,cantFind_first[i],concept,cantFind_second[j]);
	}
	else if(search == 6){
		i = rand()%5;
		j = rand()%5;
		printf("%s %s%s%s\n",GPT,found_first[i],concept,found_second[j]);
		fprintf(fp,"%s %s%s%s\n",GPT,found_first[i],concept,found_second[j]);
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
   	insert_kbr(variables[0],variables[1],0,"kbr");
   	i=0;
}

void forget(char* user_string){
	gtpList *ptr=NULL, *current=NULL;
	char* token = NULL;
	char* variables[3];
	char* sstring;
	int i=0;
	
	sstring = (char*)malloc(sizeof(user_string)*sizeof(char));
	sstring = user_string;
	//printf("the user string is %s \n",sstring);
	sstring = strcat(sstring,": ");
	//printf("the final string is %s \n",sstring);
	token = strtok(sstring,">:");
	while( token != NULL ) {
      		token = strtok(NULL,">:");
		if (token!=NULL){
			variables[i]=token;
			i++;
		}
   	}
   	i=0;
   	
   		     
	if(head == NULL) {  
    		printf("%s For real you need a doctor,first time i hear about %s \n",GPT,variables[0]);
        	return;  
    	}   
	current = head;    
	while(current!=NULL) {
      		if(strcmp(current->concept,variables[0])==0) {
		 	printf("%s found and deleted\n", variables[0]);
		 	deleteNode(current);
		 }
		 current = current->next;	
	}    	

	
	reply(variables[0],3);
	
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
void insert_kbr(char* concept,char* sentence,int used,char* type){
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
	char* token1 = NULL;
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
	fptr = fopen(sstring,"r");
	if (fptr == NULL){
		printf("%s Check the file:%s again or i will beat you up!\n",GPT,variables[0]);
		return;
	}
	
	fseek(fptr, 0, SEEK_END);
	str_length = ftell(fptr);
	rewind(fptr);
	//fseek(fptr, 0, SEEK_SET);
	// Allocate memory to contain the whole file including the null byte.
	str = calloc(str_length + 1, sizeof(char)); // +1 for null byte.
	final_str = calloc(str_length + 20, sizeof(char));
	// Read the contents of the file into the buffer.
	//fread(str, 1, str_length, fptr); 								ERROR
	while(fgets(str,str_length, fptr))
	{
    		str[strcspn(str, "\n")] = '\0';
		if (strcmp(str, "\n") == 0) break;
	}
	

	// Null terminate the string.
	str[str_length] = '\0';
	if (str==NULL){
		printf("done \n");
		return;
	}

	// Close the file.
	fclose(fptr);
	
	//printf("First string:    %s", str);
	strcat(final_str,"read this > ");
	strcat(final_str,str);
	//printf("Second String:    %s", final_str);
	
	//token = strtok(final_str,">.");
	//printf("the token is: %s \n",token);
	/*while( token != NULL ) {
      		token = strtok(NULL,">.");
		if (token!=NULL){
			printf("first token: %s i: %d\n",token,i);
			variables1[i][j]=token;
			j++;
			printf("second token: %s i: %d\n",token,i);
			strcat(token_str,"read this > ");
			strcat(token_str,token);
			printf("the token_str is: %s \n",variables1[i][j]);
			token1 = strtok(token_str,">:");
			//printf("the toke1 is: %s \n",token1);
			while( token1 != NULL ) {
      				token1 = strtok(NULL,">:");
				if (token1!=NULL){
					//printf("first token: %s i: %d\n",token1,j);
					variables1[i][j]=token1;
					i++;
					printf("second token: %s i: %d\n",variables1[i][j],j);
					//printf("%s %s\n",variables[0],variables[1]);
				}
   			}
   			j=0;
   			//printf("tokened: %s %s \n",variables1[0],variables1[1]);		
   			//insert_kbr(variables2[0],variables2[1],0);
   			//i=0;*/
			//printf("second token: %s i: %d\n",token,i);
			//printf("%s %s\n",variables[0],variables[1]);
		//}
   	//}
   	//printf("tokened: %s %s \n",variables1[0],variables1[1]);		
   	//insert_kbr(variables1[0],variables1[1],0);
   	//i=0;
	
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
   			
   	insert_kbr(variables1[0],variables1[1],0,"file");
   	i=0;
	
}

char* question(char *user_string){
	char* token = NULL;
	int i=0,j;
	char* variables[3];
	token = strtok(user_string,"**");
	while( token != NULL ) {
      		token = strtok(NULL,"**");
		if (token!=NULL){
			variables[i]=token;
			i++;
		}
   	}
   	//printf("first token: %s\n",variables[0]);
   	//answerTheQuestion(variables[0]);		
   	i=0;
   	return variables[0];
}

gtpList* answerTheQuestion(char* keyword,gtpList* prevSearch){
	gtpList *current = NULL;
	
	if (head==NULL){
		//printf("Linked List not initialized");
      		return NULL;
	}
	current = head;
	if (prevSearch == NULL){
		while(current!=NULL){
			if(strcmp(current->concept,keyword)==0){
				//printf("%s %s\n",GPT,current->sentence);
				current->timesUsed++;
				//printf("%s %d\n",GPT,current->timesUsed);
			
				return current;
			}
			if(current->next != NULL)
         			current = current->next;
      			else
      				break;
		}
		
		while(current!=NULL){
			if(strstr(current->sentence,keyword)){
				//printf("%s %s\n",GPT,current->sentence);
				current->timesUsed++;
				//printf("%s %d\n",GPT,current->timesUsed);
			
				return current;
			}
			if(current->next != NULL)
         			current = current->next;
      			else
      				break;
		}
	}
	else{
		current = prevSearch;
		while(current!=NULL){
			if(strcmp(current->concept,keyword)==0){
				//printf("%s %s\n",GPT,current->sentence);
				current->timesUsed++;
				//printf("%s %d\n",GPT,current->timesUsed);
			
				return current;
			}
			else if(strcmp(current->concept,keyword)<0){
				if(current->next != NULL){
					printf("Going Right! \n");
         				current = current->next;
         			}
      				else
      					break;
			}
			else if(strcmp(current->concept,keyword)>0){
				if(current->prev != NULL){
					printf("Going Left! \n");
					current = current->prev;
				}
				else
					break;
			}
			
		}
		while(current!=NULL){
			if(strcmp(current->sentence,keyword)){
				//printf("%s %s\n",GPT,current->sentence);
				current->timesUsed++;
				//printf("%s %d\n",GPT,current->timesUsed);
			
				return current;
			}
			else if(strcmp(current->sentence,keyword)<0){
				if(current->next != NULL){
					printf("Going Right! \n");
         				current = current->next;
         			}
      				else
      					break;
			}
			else if(strcmp(current->sentence,keyword)>0){
				if(current->prev != NULL){
					printf("Going Left! \n");
					current = current->prev;
				}
				else
					break;
			}
			
		}
	}
	
	
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
         printf("%s found at position %d\n", data, pos);
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
		printf("Concept : %s\n",ptr->concept); 
		printf("Sentence: %s\n",ptr->sentence); 
		fprintf(fp,"Concept:  %s",ptr->concept);
		fprintf(fp,"\n");
		fprintf(fp,"Sentence:  %s",ptr->sentence);
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
