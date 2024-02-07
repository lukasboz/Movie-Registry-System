/*
 * Author: Lukas Bozinov
 * Description: This program holds the functions to perform operations on a node in the linkedlist dedicated to movies.
 */

//include all required headers
#include "movieTheaterDB_movie.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

//create a node for movies
struct movieNode {
    int code;                     //positive and unique
    char name[MAX_MOVIE_NAME_LEN];//truncate after 100 chars
    char genre[MAX_GENRE_LEN];    //truncate after 25 chars
    float rating;                 //between 0.0-10.0 round to 1 decimal
    struct movieNode *next;       //pointer to the next node in the linked list
};

struct movieNode *firstMovie = NULL;// points to first movie

//this method helps with reading string input
int read_line(char str[], int n) {
    int c;
    int i = 0;
    while (isspace(c = getchar())) //for every space, getchar()
        ;                          // skip leading white space
    while (c != '\n' && c != EOF) {// loop until end of input string
        if (i < n) {               // only take number of chars specified
            str[i++] = c;
        }
        c = getchar();
    }
    str[i] = '\0';
    return i;
}

//this method deletes a movie node from the linked list
void eraseMovie() {
    struct movieNode *current = firstMovie, *previous = NULL;//create two new nodes, one that points to the current node and one that points to a previous one

    int code, found = 0;//set an integer variable for the user input and a flag for whether the node's been found or not

    //prompt user for code, and clear \n character from scanf
    printf("Movie code to remove: ");
    scanf("%d", &code);
    while (getchar() != '\n')
        ;

    //if the current node has data, and the code is the same as the code entered (aka the code entered corresponds to the head node)
    if (current != NULL && current->code == code) {
        firstMovie = current->next;//set the first movie pointer to the node after the current one
        free(current);             //free the memory of the current node
        printf("Movie removed.\n");//notify the user that the movie was removed
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
        printf("Movie not found.\n");//tell the user if the movie wasn't found
        return;                      //return to main function
    } else {                         //otherwise, set pointers to the correct position
        previous->next = current->next;
        free(current);             //free memory up
        printf("Movie removed.\n");//notify user of node removal
    }
}

//this function updates a movie by entering the code for any movie in the linked list
void updateMovie() {
    struct movieNode *current = firstMovie;//create a node, current, that is initialized to the first movie in the linked list
    int code, found = 0;                   //create a variable for user input and for a flag

    //prompt user, get input, trim '\n' character from scanf
    printf("Movie code to update: ");
    scanf("%d", &code);
    while (getchar() != '\n')
        ;

    //search for the movie to update
    while (current != NULL) {
        if (current->code == code) {
            found = 1;
            break;
        }
        current = current->next;
    }

    //if the movie isn't found in the linked list, tell the user
    if (!found) {
        printf("Movie doesn't exist.\n");
        return;
    } else {

        //prompt user for new movie code, receive input, trim off '\n'
        printf("New movie code: ");
        scanf("%d", &current->code);
        while (getchar() != '\n')
            ;

        //return to main if code entered is invalid
        if (current->code < 0) {
            printf("Invalid code.\n");
            return;
        }

        //prompt and read in strings using read_line function
        printf("Enter movie name: ");
        read_line(current->name, MAX_MOVIE_NAME_LEN);
        printf("Enter movie genre: ");
        read_line(current->genre, MAX_GENRE_LEN);

        //prompt user, receive input, trim '\n' character
        printf("Enter movie rating: ");
        scanf("%f", &current->rating);
        while (getchar() != '\n')
            ;

        //return to main prompt if rating is incorrect
        if (current->rating < 0 || current->rating > 10) {
            printf("Invalid rating.\n");
            return;
        }
    }
}

//this function prints out every node in the linked list
void printMovie() {
    struct movieNode *current = firstMovie; //start at the head node

    printf("Movie Code\tMovie Name\t\t\t\tMovie Genre\t\tMovie Rating\n");//print heading line
    while (current != NULL) { //print every node in the list
        printf("%-16d", current->code);
        printf("%-40s", current->name);
        printf("%-24s", current->genre);
        printf("%.1f\n", current->rating);
        current = current->next; //move to next node in list
    }
}

//this function searches for a node with a certain movie code
void searchMovie() {
    struct movieNode *current = firstMovie; //initialize a node with the head node's information
    int code, found = 0;//create a variable for user input and for a flag

    //prompt user, get code, trim '\n'
    printf("Movie code to search for: ");
    scanf("%d", &code);
    while (getchar() != '\n')
        ;

    //go through the whole linked list and then print the node if found
    while (current != NULL) {
        if (current->code == code) {
            printf("Movie Code\tMovie Name\t\t\t\tMovie Genre\t\tMovie Rating\n");
            printf(" %-12d", current->code);
            printf("%-40s", current->name);
            printf("%-24s", current->genre);
            printf("%.1f\n", current->rating);
            found = 1;
            break;
        }
        current = current->next; //go to next node in list
    }

    if (!found) //if the node isn't found, tell the user
        printf("Movie not found.\n");
}

//this function inserts a node in the linked list
void insertMovie() {
    struct movieNode *current, *previous = NULL, *newNode; //make three nodes, one for the previous node, one for the current node, and one for the node to be inserted
    newNode = malloc(sizeof(struct movieNode)); //allocate memory to the new node

    //check if we've run out of memory
    if (newNode == NULL) {
        printf("Database is full; can't add more movies.\n");
        return;
    }

    //prompt user, get input, trim '\n'
    printf("Enter movie code: ");
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
    for (current = firstMovie, previous = NULL;
         current != NULL && newNode->code > current->code;
         previous = current, current = current->next)
        ;

    //if the movie already exists in the linked list
    if (current != NULL && newNode->code == current->code) {
        printf("Movie already exists.\n"); //tell the user
        free(newNode); //free up memory for the newNode
        return; //return to the main function
    }

    //prompt user and get input for the name and genre of the movie (via read_line)
    printf("Enter movie name: ");
    read_line(newNode->name, MAX_MOVIE_NAME_LEN);
    printf("Enter genre: ");
    read_line(newNode->genre, MAX_GENRE_LEN);

    //prompt user, get input, trim '\n'
    printf("Enter rating: ");
    scanf("%f", &newNode->rating);
    while (getchar() != '\n')
        ;

    //if the rating is invalid (not between 0-10)
    if (newNode->rating < 0 || newNode->rating > 10) {
        printf("Invalid rating.\n"); //tell the user
        free(newNode); //free up memory allocated towards the newNode
        return; //return to main function
    }

    newNode->next = current; //set the next pointer of the newNode to the current node (the one ahead of it)
    if (previous == NULL) //if there are no other nodes in the list
        firstMovie = newNode; //this new node becomes the head node
    else //otherwise, modify the next pointer to point to the newNode
        previous->next = newNode;
}

//this is the main function of the program which calls all the functions above it when needed
void movieMain() {

    char cmd;//create a char variable to store the command given by the user
    //while true (unless broken out of)
    while (1) {

        //prompt the user for the operation code and receive input using scanf
        printf("Enter movie operation code: ");
        scanf("%c", &cmd);
        while (getchar() != '\n')
            ;//truncate as long as \n isn't the character being truncated

        //if 'i' is entered, that means the user wants to insert a movie, so we call the insert function
        if (cmd == 'i') {
            insertMovie();
            return;
            // if 's' is entered, we call the function that is used to search for a movie
        } else if (cmd == 's') {
            searchMovie();
            return;
            //if 'u' is entered, we call the function that is required to update a movie
        } else if (cmd == 'u') {
            updateMovie();
            return;
            //if 'p' is entered, we print every movie in order of its movie code
        } else if (cmd == 'p') {
            printMovie();
            return;
            //if 'e' is entered, we erase a movie according to its movie code
        } else if (cmd == 'e') {
            eraseMovie();
            return;
        } else {//if any other char is entered, we prompt the user again since the char entered is not a valid option
            printf("Invalid command, try again.\n");
        }
        printf("\n");//we add a newline every time a function is executed
    }

}//end of program
