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



int main(){
    printf("First number \n");
    breakInDigits(&head1);
    while (getchar() != '\n');
    printf("second number \n");
    breakInDigits(&head2);

    digitsNotTheSame(&head1, &head2);
    sumTheNum();

    printlist(&head1);
    printf("\n");
    printlist(&head2);
    printf("\n");
    printf("The final List: \n");
    printlist(&headFinal);
}

void breakInDigits(numList **head){
    int number;
    while (scanf("%d", &number) == 1) {
        printf("Give number:\n");
        makeList(head, number);
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
    numList *firstList=NULL,*secondList=NULL,*thirdList=NULL;
    firstList = head1;
    secondList = head2;
    thirdList = headFinal;
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

void printlist(numList **head){
    numList *ptr = NULL;
    ptr = *head;

    while(ptr != NULL){
        printf("%d",ptr->digit);
        ptr = ptr->next;
    }
}