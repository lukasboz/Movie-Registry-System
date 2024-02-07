//this header file creates the prototype functions for the movieTheaterDB_movie.c file and defines macros
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef ASSIGNMENT_5_MOVIETHEATERDB_MOVIE_H
#define ASSIGNMENT_5_MOVIETHEATERDB_MOVIE_H
#define MAX_MOVIE_NAME_LEN 100 //define a macro for the longest possible name length
#define MAX_GENRE_LEN 25 //define a macro for the longest possible genre length

void movieMain(void);
void searchMovie(void);
void insertMovie(void);
void eraseMovie(void);
void updateMovie(void);
void printMovie(void);
int read_line(char str[], int n);

#endif//ASSIGNMENT_5_MOVIETHEATERDB_MOVIE_H
