/*
 * phonebook.c
 *
 *  Created on: Oct 17, 2020
 *      Author: melike
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <strings.h>


struct Node {
	int data;
	struct Node* next;
	char name[50];
	char phoneNumber[11];
	char notes[300];
};

struct Node *head = NULL;

void sortEntries() {
	struct Node *first,*second, *swap;
	char tempName[100];
	char tempNumber[20];
	char tempNote[300];
	first = head;
	second = head->next;

	while(second != NULL){
	    if(strcmp(first->name,second->name) > 0){
	        strcpy(tempName,first->name);
	        strcpy(first->name,second->name);
	        strcpy(second->name,tempName);

	        strcpy(tempNumber,first->phoneNumber);
	        strcpy(first->phoneNumber,second->phoneNumber);
	        strcpy(second->phoneNumber,tempNumber);

	        strcpy(tempNote,first->notes);
	        strcpy(first->notes,second->notes);
	        strcpy(second->notes,tempNote);

	        swap = second;
	        first = swap;
	        second = swap->next;
	    }
	    else{
	        swap = second;
	        first = swap;
	        second = swap->next;
	    }
	}
	//listEntries();
}

void createNewEntry(){

    struct Node *newNode, *temp;
    newNode=(struct Node *)malloc(sizeof(struct Node));

    if(newNode == NULL){
        printf("\n It is out of memory space\n");
        exit(0);
    }

    char enteredName[50];
    char enteredPhoneNumber[11];
    char enteredNote[300];

    printf("Enter a Name: ");
    scanf("%s",enteredName);
    strcpy(newNode->name,enteredName);

    printf("Enter a Phone: ");
    scanf("%s",enteredPhoneNumber);
    strcpy(newNode->phoneNumber,enteredPhoneNumber);

    printf("Enter a Note: ");
    scanf("%s",enteredNote);
    strcpy(newNode->notes,enteredNote);

    newNode->next = NULL;

    if(head == NULL){
       head = newNode;
    }
    else{
        temp = head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newNode;
    }
    sortEntries();
}

void listEntries(){

	sortEntries();

    struct Node *temp;

    if(head == NULL){
        printf("\nPhonebook is empty\n");
        return;
    }
    else{
        temp = head;
        printf("The Phonebook elements are:\n");
        while(temp != NULL){
            printf("Name: %s\n", temp->name);
            printf("Phone Number: %s\n", temp->phoneNumber);
            printf("Note: %s\n", temp->notes);
            temp = temp->next ;
        }
    }
}

bool patternSearch(char* text, char* pattern){

    int pat = strlen(pattern);
    int txt = strlen(text);
    bool x=false;

    for (int i = 0; i <= txt - pat; i++) {
        int k;
        for (k = 0; k < pat; k++){
            if (text[i + k] != pattern[k])
            	break;
        }
        if (k == pat){
            x=true;
        }
    }
    return x;
}

void searchEntry(){

	struct Node *temp;
	char word[100];
    int i=0,flag;
    int find = 0;
    temp = head;

    if(temp == NULL){
        printf("\nYou cannot search because phonebook 's empty\n");
    }
    else{
        printf("\nEnter a word that you want to search?\n");
        scanf("%s",word);
        while (temp != NULL){
            if(patternSearch(temp->name, word) || patternSearch(temp->notes, word) ){
                printf("item found at location %d ",i+1);
                printf("\nName: %s\nPhone Number: %s\nNotes:%s", temp->name, temp->phoneNumber, temp->notes);
                flag=0;
                find=1;
                //break;
            }
            else{
                flag=1;
            }
            i++;
            temp = temp -> next;
        }
        if(flag==1 && find==0){
            printf("\nWord  not found\n");
        }
    }
}

void editEntry() {

	int pos = 0;
	char editedName[50];
	char newName[50];
	char newNumber[11];
	char newNote[300];
    struct Node *temp;

    if(head == NULL) {
       printf("The Phonebook 's empty");
       return;
    }
    temp = head;

    while(temp != NULL){
    	printf("Enter the name of the entry that you want to edit: ");
    	scanf("%s", editedName);
        if(patternSearch(temp->name, editedName)){
        	printf("Enter new Name: ");
        	scanf("%s", newName);
        	strcpy(temp->name,newName);

        	printf("Enter new Number: ");
        	scanf("%s", newNumber);
        	strcpy(temp->phoneNumber,newNumber);

        	printf("Enter new Note: ");
        	scanf("%s", newNote);
        	strcpy(temp->notes,newNote);

            printf("Old entry replaced with new entry named %s\n", newName);
            return;
        }

        temp = temp->next;
        pos++;
    }
    sortEntries();
    printf("%s does not exist in the list\n", editedName);

}


void deleteEntry(){
    int position;
    char sure[2];
    struct Node *temp,*deleted;
    if(head == NULL){
        printf("\nSorry! The Phonebook is Empty\n");
        exit(0);
    }
    else{
        printf("Please enter the number of the entry to be deleted: ");
        scanf("%d",&position);
        if(position == 0){
        	deleted = head;
        	printf("Entry named %s will be deleted. Are you sure? (y/n) ",deleted->name);
        	scanf("%s",sure);
        	if(patternSearch(sure, "y")){
        		head = head->next ;
        		printf("\nThe deleted entry is: %s", deleted->name);
        		free(deleted);
        	}
        }
        else{
        	deleted = head;
            for(int i=0;i<position;i++){
            	temp = deleted;
            	deleted=deleted->next;
                if(deleted == NULL){
                    printf("\nThere is no entry that have this number\n");
                    return;
                }
            }
        	printf("Entry named %s will be deleted. Are you sure? (y/n) ",deleted->name);
        	scanf("%s",sure);
        	if(patternSearch(sure, "y")){
        		temp->next = deleted->next ;
        		printf("\nThe deleted entry is: %s", deleted->name);
        		free(deleted);
        	}
        }
    }
    sortEntries();
}
void saveFile() {

	sortEntries();

	char fileName[100];

	printf("The Phonebook will be saved. Examle file name: record.txt Enter a file name: ");
	scanf("%s", fileName);

	FILE *f = fopen(fileName,"w+");
	if(f == NULL) printf("Error opening file\n");

	struct Node *temp;

	    if(head == NULL){
	    	fprintf(f, "Phonebook 's empty\n");
	    }
	    else{
	        temp = head;
	        fprintf(f, "The Phonebook entries are:\n");
	        while(temp != NULL){
	        	fprintf(f, "Name: %s\n", temp->name);
	        	fprintf(f, "Phone Number: %s\n", temp->phoneNumber);
	        	fprintf(f, "Notes: %s\n", temp->notes);
	            temp = temp->next ;
	        }
	    }

	fclose(f);

	printf("The file has been saved\n");

}

int loadFile() {

    struct Node *newNode, *temp;
    newNode=(struct Node *)malloc(sizeof(struct Node));

	//char loadedName[50];
	//char loadedNumber[11];
	//char loadedNote[300];
	char fileName[100];
	char line[600];

	printf("The Phonebook will be loaded. Examle file name: record.txt Enter a file name: \n");
	scanf("%s", fileName);

	FILE *f=fopen(fileName,"r");


	if(f==NULL) {
        printf("Error read'ng file\n");
        return 0;
    }
	else{
	    while (fgets(line, sizeof(line), f)) {
	        printf("%s", line);
	    }
	}
}

int main(void) {

	int option;

	printf("Welcome to myPhoneBook! Please select an option: \n");
	printf("1) New entry \n2) List all entries \n3) Edit \n4) Delete \n5) Search \n6) Save and exit \n7) Load \n");
	scanf("%d", &option);

	while(option<8){

	if(option == 1){
		createNewEntry();
	}
	else if(option == 2){
		listEntries();
	}
	else if(option == 3){
		editEntry();
	}
	else if(option == 4){
		deleteEntry();
	}
	else if(option == 5){
		searchEntry();
	}
	else if(option == 6){
		saveFile();
	}
	else if(option == 7){
		loadFile();
	}
	else{
		printf("You need to enter number between 1 and 7");
		scanf("%d", &option);
	}
	printf("\nPlease select an option: \n");
	scanf("%d", &option);
	}
}
