#include "movieTheaterDB.h"
#include <stdio.h>

int main() {

    char cmd;//create a char variable to store the command given by the user

    //print the header of the movie cinema (as shown in the example of the assignment on OWL)
    printf("*********************\n");
    printf("* 2211 Movie Cinema *\n");
    printf("*********************\n\n");

    //while true (unless broken out of)
    while (1) {

        //prompt the user for the operation code and receive input using scanf
        printf("Enter operation code: ");
        scanf("%c", &cmd);
        while (getchar() != '\n'); //truncate as long as \n isn't the character being truncated

        // if 'm' is entered, we call the .c file with movieMain() in it
        if (cmd == 'm') {
           movieMain();

            // if 'a' is entered, we call the .c file with actorMain() in it
        } else if (cmd == 'a') {
           actorMain();

        } else if (cmd == 'h') {

            printf(" Enter 'q' to quit the program.\n");
            printf(" Enter 'm' to perform a movie-related operation.\n");
            printf(" Enter 'a' to perform an actor-related operation.\n");
            printf(" Enter 'h' to bring up this help menu.\n");
        } else if (cmd == 'q') {
            return 0;
        }

        else {//if any other char is entered, we prompt the user again since the char entered is not a valid option
            printf("Invalid command, try again.\n");
        }
        printf("\n");//we add a newline every time a function is executed
    }

}//end of program