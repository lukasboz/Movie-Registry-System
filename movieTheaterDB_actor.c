/*
* Author: Lukas Bozinov
* Student Number: 251284757
* Instructor: Mr. Beldman
* Description: This program holds the functions to perform operations on a node in the linkedlist dedicated to actors.
*/

//include all required headers
#include "movieTheaterDB_actor.h"
#include <stdio.h>
#include <stdlib.h>

//create a node for actors
struct actorNode {
    int code;                     //must be positive + unique
    char name[MAX_ACTOR_NAME_LEN];//truncate over 50 chars
    int age;                      //0-120 only
    char profile[MAX_PROFILE_LEN];//truncate over 50 chars
    struct actorNode *next; //pointer to the next node in the linked list
};

struct actorNode *firstActor = NULL;// points to first actor

//this method deletes an actor node from the linked list
void eraseActor() {
    struct actorNode *current = firstActor, *previous = NULL;//create two new nodes, one that points to the current node and one that points to a previous one

    int code, found = 0;//set an integer variable for the user input and a flag for whether the node's been found or not

    //prompt user for code, and clear \n character from scanf
    printf("Actor code to remove: ");
    scanf("%d", &code);
    while (getchar() != '\n')
        ;

    //if the current node has data, and the code is the same as the code entered (aka the code entered corresponds to the head node)
    if (current != NULL && current->code == code) {
        firstActor = current->next;//set the first actor pointer to the node after the current one
        free(current);             //free the memory of the current node
        printf("Actor removed.\n");//notify the user that the actor was removed
        return;                    //return to the main function
    }

    //otherwise, if the code entered does not respond to the current node
    while (current != NULL) {       //traverse the linked list
        if (current->code == code) {//if the node is found, break out of the loop
            found = 1;
            break;
        }
        previous = current;//otherwise, continue the linked list traversal
        current = current->next;
    }

    if (!found) {
        printf("Actor not found.\n"); //tell the user if the actor wasn't found
        return;
    } else { //otherwise, set pointers to the correct position
        previous->next = current->next;
        free(current);//free memory up
        printf("Actor removed.\n");//notify user of node removal
    }
}

//this function updates an actor by entering the code for any movie in the linked list
void updateActor() {
    struct actorNode *current = firstActor; //create a node, current, that is initialized to the first actor in the linked list
    int code, found = 0; //create a variable for user input and for a flag

    //prompt user, get input, trim '\n' character from scanf
    printf("Actor code to update: ");
    scanf("%d", &code);
    while (getchar() != '\n')
        ;

    //search for the actor to update
    while (current != NULL) {
        if (current->code == code) {
            found = 1;
            break;
        }
        current = current->next;
    }
    //if the actor isn't found in the linked list, tell the user
    if (!found) {
        printf("Actor doesn't exist.\n");
        return;
    } else {
        //prompt user for new actor code, receive input, trim off '\n'
        printf("New actor code: ");
        scanf("%d", &current->code);
        while (getchar() != '\n')
            ;
        //return to main if code entered is invalid
        if (current->code < 0) {
            printf("Invalid code.\n");
            return;
        }
        //prompt and read in string using read_line function
        printf("Enter actor name: ");
        read_line(current->name, MAX_ACTOR_NAME_LEN);

        //prompt user for new actor code, receive input, trim off '\n'
        printf("Enter actor age: ");
        scanf("%d", &current->age);
        while (getchar() != '\n')
            ;
        //prompt user, receive input, trim '\n' character
        if (current->age < 0 || current->age > 120) {
            printf("Invalid rating.\n");
            return;
        }
        //prompt and read in string using read_line function
        printf("Enter actor profile: ");
        read_line(current->profile, MAX_PROFILE_LEN);
    }
}
//this function prints out every node in the linked list
void printActor() {
    struct actorNode *current = firstActor;//start at the head node

    printf("Actor Code\tActor Name\t\t\t\tActor Age\t\tActor Profile\n");//print heading line
    while (current != NULL) {//print every node in the list
        printf("%-16d", current->code);
        printf("%-40s", current->name);
        printf("%-24d", current->age);
        printf("%s\n", current->profile);
        current = current->next;//move to next node in list
    }
}
//this function searches for a node with a certain actor code
void searchActor() {
    struct actorNode *current = firstActor; //initialize a node with the head node's information
    int code, found = 0;//create a variable for user input and for a flag

    //prompt user, get code, trim '\n'
    printf("Actor code to search for: ");
    scanf("%d", &code);
    while (getchar() != '\n')
        ;

    //go through the whole linked list and then print the node if found
    while (current != NULL) {
        if (current->code == code) {
            printf("Actor Code\tActor Name\t\t\t\tActor Age\t\tActor Profile\n");
            printf("%-16d", current->code);
            printf("%-40s", current->name);
            printf("%-24d", current->age);
            printf("%s\n", current->profile);
            found = 1;
            break;
        }
        current = current->next; //go to next node in list
    }

    if (!found)//if the node isn't found, tell the user
        printf("Actor not found.\n");
}

//this function inserts a node in the linked list
void insertActor() {
    struct actorNode *current, *previous = NULL, *newNode; //make three nodes, one for the previous node, one for the current node, and one for the node to be inserted
    newNode = malloc(sizeof(struct actorNode)); //allocate memory to the new node

    //check if we've run out of memory
    if (newNode == NULL) {
        printf("Database is full; can't add more movies.\n");
        return;
    }

    //prompt user, get input, trim '\n'
    printf("Enter actor code: ");
    scanf("%d", &newNode->code);
    while (getchar() != '\n')
        ;

    //if the code is invalid, tell the user, free the memory for newNode, and return to the main loop
    if (newNode->code < 0) {
        printf("Invalid code.\n");
        free(newNode);
        return;
    }

    //loop through the entire linked list and search for a spot to insert it
    for (current = firstActor, previous = NULL;
         current != NULL && newNode->code > current->code;
         previous = current, current = current->next)
        ;

    //if the actor already exists in the linked list
    if (current != NULL && newNode->code == current->code) {
        printf("Actor already exists.\n"); //tell the user
        free(newNode); //free up memory for the newNode
        return; //return to the main function
    }

    //prompt and read in string using read_line function
    printf("Enter actor name: ");
    read_line(newNode->name, MAX_ACTOR_NAME_LEN);

    //prompt user, get input, trim '\n'
    printf("Enter actor age: ");
    scanf("%d", &newNode->age);
    while (getchar() != '\n')
        ;

    //if the age is invalid (not between 0-120)
    if (newNode->age < 0 || newNode->age > 120) {
        printf("Invalid age.\n");
        free(newNode);
        return;
    }
    //prompt and read in string using read_line function
    printf("Enter actor profile: ");
    read_line(newNode->profile, MAX_PROFILE_LEN);


    //update pointers (same as in movieTheaterDB_movie.c)
    newNode->next = current;
    if (previous == NULL)
        firstActor = newNode;
    else
        previous->next = newNode;
}

//this is the main function of the program which calls all the functions above it when needed
void actorMain(void) {
    char cmd;//create a char variable to store the command given by the user
    //while true (unless broken out of)
    while (1) {

        //prompt the user for the operation code and receive input using scanf
        printf("Enter actor operation code: ");
        scanf("%c", &cmd);
        while (getchar() != '\n')
            ;//truncate as long as \n isn't the character being truncated

        //if 'i' is entered, that means the user wants to insert a actor, so we call the insert function
        if (cmd == 'i') {
            insertActor();
            return;
            // if 's' is entered, we call the function that is used to search for a actor
        } else if (cmd == 's') {
            searchActor();
            return;
            //if 'u' is entered, we call the function that is required to update a actor
        } else if (cmd == 'u') {
            updateActor();
            return;
            //if 'p' is entered, we print every actor in order of its actor code
        } else if (cmd == 'p') {
            printActor();
            return;
            //if 'e' is entered, we erase a movie according to its actor code
        } else if (cmd == 'e') {
            eraseActor();
            return;
        } else {//if any other char is entered, we prompt the user again since the char entered is not a valid option
            printf("Invalid command, try again.\n");
        }
        printf("\n");//we add a newline every time a function is executed
    }
}//end of program