//this header file creates the prototype functions for the movieTheaterDB_actor.c file and defines macros
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef ASSIGNMENT_5_MOVIETHEATERDB_ACTOR_H
#define ASSIGNMENT_5_MOVIETHEATERDB_ACTOR_H
#define MAX_ACTOR_NAME_LEN 50 //define a macro for the longest possible name length
#define MAX_PROFILE_LEN 50 //define a macro for the longest possible genre length

void actorMain(void);
void searchActor(void);
void insertActor(void);
void eraseActor(void);
void updateActor(void);
void printActor(void);
int read_line(char str[], int n);

#endif//ASSIGNMENT_5_MOVIETHEATERDB_ACTOR_H
