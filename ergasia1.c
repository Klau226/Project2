#include <stdio.h>
#include <stdlib.h>

typedef struct gList
{
    int digit;
    struct gList *next;
    struct gList *prev;
}numList;

numList *head1 = NULL;                                          // First List
numList *head2 = NULL;                                          // Second List
numList *headFinal = NULL;                                      // Third and final List storing the result


void breakInDigits(numList **head);                             // Taking from the user the digit
numList* createNode(int digit);                                 // Making the linked list with the digit
void makeList(numList **head , int num);                        // Making the list so every new list is at the end
void makeListAtStart(numList **head, int num);                  // Making the list so every new list is at the start
void digitsNotTheSame(numList** num1, numList** num2);          // Making sure that the 2 numbers have the same number of digits.If they dont i fill the number with less digits with 0s
void sumTheNum();                                               // Making the Addition
int compareLists();                                             // Checking which number is the largest 
void minusTheNum();                                             // Making the Subtraction
void printlist(numList **head);                                 // Printing the List
void newList(numList** head);                                   // Deleting the whole list when the user wants to make a different calculation


int main(){
    int choice;
    printf("Hi welcome \n");
    do {
        printf("----------------------------\n");
        printf("PRESS: \n");
        printf("1. ADDITION \n");
        printf("2. SUBTRACTION \n");
        printf("3. EXIT \n");
        printf("----------------------------\n");
        printf("CHOOSE: ");
        scanf("%d", &choice);
        printf("\n");
        printf("When you want to stop storing digits press something that is not a number \n");

        if(choice == 3){
            printf("GOODBYE COME BACK LATER \n");
            break;
        }
        if(choice < 1 || choice > 2){
            printf("!!! No such input.Please try again !!! \n");    // Making sure that the user is inserting numbers that the menu needs
            continue;
        }

        printf("--- Store you number digit by digit ---\n");
        printf("FIRST NUMBER: \n");
        breakInDigits(&head1);                                      // Storing digit by digit the number                              
        while (getchar() != '\n');
        printf("SECOND NUMBER: \n");
        breakInDigits(&head2);

        digitsNotTheSame(&head1, &head2);                           // Making the numbers equal in digits
        while (getchar() != '\n');
        if(choice == 1){
            sumTheNum();
        }
        if(choice == 2){
            minusTheNum();
        }

        printf("----------------------------\n");
        printf("RESULT: \n");
        printlist(&headFinal);
        printf("\n");
        printf("----------------------------\n");

        newList(&head1);                                            // Freeing the memory every time a new number is inserted or when the programm closes
        newList(&head2);
        newList(&headFinal);

    }while(choice != 3);
    return 0;
}

void breakInDigits(numList **head){
    int number;
    while (scanf("%d", &number) == 1) {
        if(number > 9){                                             // The digit should be lower than 10 so i can store every digit seperate
            printf("!!! The digit should't be > 9 !!! \n");
            printf("Try again \n");
            continue;
        }
        else{
            printf("Give digit:\n");
            makeList(head, number);
        }
    }
}

numList* createNode(int digit){
    numList *newNode = (numList*)malloc(sizeof(numList));
    newNode->digit = digit;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void makeList(numList **head , int num){
    numList* newNode = createNode(num);
    numList* temp = *head;

    if (*head == NULL) {                                            // If the list is empty, make the new node the head
        *head = newNode;
    } else {
        while (temp->next != NULL) {                                // Traverse to the end of the list
            temp = temp->next;
        }

        temp->next = newNode;                                       // Connect the new node to the last node
        newNode->prev = temp;
    }

}

void makeListAtStart(numList **head , int num){
    numList *new = NULL;
    new = (numList*)malloc(sizeof(numList));

    if(new == NULL){
        printf("Memory allocation failed \n");
        exit(0);
    }
    if(*head == NULL){
        new->digit = num;
        new->next = NULL;
        new->prev = NULL;
        *head = new;
    }
    else{
        new->digit = num;
        new->prev = NULL;
        new->next = *head;
        (*head)->prev = new;
        *head = new;
    }
}

void digitsNotTheSame(numList** num1, numList** num2){
    int count1 = 0, count2 = 0;

    numList* temp = *num1;
    while (temp != NULL) {
        count1++;                                                   // Counting the nodes
        temp = temp->next;
    }
    temp = *num2;
    while (temp != NULL) {
        count2++;
        temp = temp->next;
    }

    while (count1 < count2) {
        makeListAtStart(num1, 0);                                   // Making sure that the 2 lists have the same number of digits by adding 0 at the start
        count1++;
    }

    while (count2 < count1) {
        makeListAtStart(num2, 0);
        count2++;
    }
}


void sumTheNum(){
    int mod,sum=0;
    numList *firstList=NULL,*secondList=NULL;
    firstList = head1;
    secondList = head2;
    while(firstList->next != NULL && secondList->next != NULL){         // Traversing the list at the end so we can start making the addition
        firstList = firstList->next;
        secondList = secondList->next;
    }
    while(firstList != NULL && secondList != NULL){
        sum = firstList->digit+secondList->digit;                       // Making the addition
        if(sum > 9){                                                    // If we have a carry
            if(firstList->prev == NULL && secondList->prev == NULL){    // If it is the first node then allocate memory and store it in the third list
                makeListAtStart(&headFinal,sum);
                firstList = firstList->prev;
                secondList = secondList->prev;
            }
            else{                                                       // Else calculate the mod of the addition and store it, than add +1 to the next number of the list
                mod = sum%10;                                           // I didnt add the carry i just add the next number that the addition will be
                makeListAtStart(&headFinal,mod);
                firstList->prev->digit++;
                secondList = secondList->prev;
                firstList = firstList->prev;
            }
        }
        else{
            makeListAtStart(&headFinal,sum);
            firstList = firstList->prev;
            secondList = secondList->prev;
        }
    }
}

int compareLists(){                     // Helping with the Subtraction. Checking which number is the largest, the first digit of the list is determining which number is the largest
    numList *list1 = head1;
    numList *list2 = head2;

    while (list1 != NULL && list2 != NULL){     
        if(list1->digit > list2->digit){
            return 1;                       // Returning 1 if the first list is the largest
        }
        else if(list1->digit < list2->digit){
            return -1;                      // Returning -1 if the second list is the largest
        }
        list1 = list1->next;
        list2 = list2->next;

        return 0;                           // Both lists are equal
    }

}

void minusTheNum(){
    int sum = 0,bigger;
    numList *firstList = NULL, *secondList = NULL;
    firstList = head1;
    secondList = head2;
    
    bigger = compareLists();                                        // Which is the biggest
    while(firstList->next != NULL && secondList->next != NULL){     // Traversing at the end of the list
        firstList = firstList->next;
        secondList = secondList->next;
    }

    if(bigger == 1 || bigger == 0){                                 // If the first list is bigger or equal
        while(firstList != NULL && secondList != NULL){
            if (firstList->digit < secondList->digit){              // if the first digit that we substract is smaller than the other digit(ex: 3-6)
                firstList->digit = firstList->digit + 10;           // then make the 3 +10 = 13 and make the substract
                firstList->prev->digit--;                           // and i substract the next number with 1 without using a carry
            }
            sum = firstList->digit - secondList->digit;             // Making the final substraction 
            printf("MINUS: %d \n",sum);
            makeListAtStart(&headFinal,sum);                        // Storing it to the third list
            firstList = firstList->prev;
            secondList = secondList->prev;
        }
    }   
    else if(bigger == -1){                                          // If the second list is bigger
        while(firstList != NULL && secondList != NULL){
            if (secondList->digit < firstList->digit){
                secondList->digit = secondList->digit + 10;
                secondList->prev->digit--;
            }
            sum = secondList->digit - firstList->digit;
            printf("MINUS: %d \n",sum);
            makeListAtStart(&headFinal,sum);
            firstList = firstList->prev;
            secondList = secondList->prev;
        }
    }
}

void printlist(numList **head){                     // Print a list
    numList *ptr = NULL;
    ptr = *head;
    while(ptr != NULL){
        printf("%d",ptr->digit);
        ptr = ptr->next;
    }
}
void newList(numList** head) {                      // Freeing a list
    numList* current = *head;
    numList* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;                                   // Set the head to NULL after deleting all nodes
}
