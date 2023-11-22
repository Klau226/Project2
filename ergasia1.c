#include <stdio.h>
#include <stdlib.h>

typedef struct gList
{
    int digit;
    struct gList *next;
    struct gList *prev;
}numList;

numList *head1 = NULL;
numList *head2 = NULL;
numList *headFinal = NULL;


void breakInDigits(numList **head);
void makeList(numList **head , int num);
numList* createNode(int digit);
void makeListAtStart(numList **head, int num);
void printlist(numList **head);
void sumTheNum();
void digitsNotTheSame(numList** num1, numList** num2);
void minusTheNum();
int compareLists();


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
            printf("No such input.Please try again \n");
            continue;
        }

        printf("--- Store you number digit by digit ---\n");
        printf("FIRST NUMBER: \n");
        breakInDigits(&head1);
        while (getchar() != '\n');
        printf("SECOND NUMBER: \n");
        breakInDigits(&head2);

        digitsNotTheSame(&head1, &head2);
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

    }while(choice != 3);
    return 0;
}

void breakInDigits(numList **head){
    int number;
    while (scanf("%d", &number) == 1) {
        if(number > 9){
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

    // If the list is empty, make the new node the head
    if (*head == NULL) {
        *head = newNode;
    } else {
        // Traverse to the end of the list
        while (temp->next != NULL) {
            temp = temp->next;
        }

        // Connect the new node to the last node
        temp->next = newNode;
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
        count1++;
        temp = temp->next;
    }
    temp = *num2;
    while (temp != NULL) {
        count2++;
        temp = temp->next;
    }

    // Add leading zeros to the smaller number
    while (count1 < count2) {
        makeListAtStart(num1, 0);
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
    //thirdList = headFinal;
    while(firstList->next != NULL && secondList->next != NULL){
        firstList = firstList->next;
        secondList = secondList->next;
    }
    while(firstList != NULL && secondList != NULL){
        sum = firstList->digit+secondList->digit;
        if(sum > 9){
            if(firstList->prev == NULL && secondList->prev == NULL){
                makeListAtStart(&headFinal,sum);
                firstList = firstList->prev;
                secondList = secondList->prev;
            }
            else{
                mod = sum%10;
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

int compareLists(){
    numList *list1 = head1;
    numList *list2 = head2;

    while (list1 != NULL && list2 != NULL){
        if(list1->digit > list2->digit){
            return 1;
        }
        else if(list1->digit < list2->digit){
            return -1;
        }
        list1 = list1->next;
        list2 = list2->next;

        return 0; // Both lists are equal
    }

}

void minusTheNum(){
    int sum = 0,bigger;
    numList *firstList = NULL, *secondList = NULL;
    firstList = head1;
    secondList = head2;
    
    bigger = compareLists();
    while(firstList->next != NULL && secondList->next != NULL){
        firstList = firstList->next;
        secondList = secondList->next;
    }

    if(bigger == 1 || bigger == 0){
        while(firstList != NULL && secondList != NULL){
            if (firstList->digit < secondList->digit){
                firstList->digit = firstList->digit + 10;
                firstList->prev->digit--;
            }
            sum = firstList->digit - secondList->digit;
            printf("MINUS: %d \n",sum);
            makeListAtStart(&headFinal,sum);
            firstList = firstList->prev;
            secondList = secondList->prev;
        }
    }
    else if(bigger == -1){
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

void printlist(numList **head){
    numList *ptr = NULL;
    ptr = *head;
    while(ptr != NULL){
        printf("%d",ptr->digit);
        ptr = ptr->next;
    }
}