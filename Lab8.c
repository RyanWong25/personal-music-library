//
// APS105 Lab 8 Lab8.c
//
// This is a program written to maintain a personal music library, 
// using a linked list to hold the songs in the library.
//
// Author: Ryan Jo Wong
// Student Number: 1003825140
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// A node in the linked list

// Each string in the node is declared as a character pointer variable,
// so they need to be dynamically allocated using the malloc() function,
// and deallocated using the free() function after use.

typedef struct node {
    char *artist ;
    char *songName ;
    char *genre ;
    struct node *nextNode ;
} Node;

// Declarations of linked list functions
//
// DECLARE YOUR LINKED-LIST FUNCTIONS HERE
//


// Declarations of support functions
// See below the main function for descriptions of what these functions do

void inputStringFromUser( char prompt[], char s[], int arraySize ) ;
void songNameDuplicate( char songName[] ) ;
void songNameFound( char songName[] ) ;
void songNameNotFound( char songName[] ) ;
void songNameDeleted( char songName[] ) ;
void artistFound( char artist[] ) ;
void artistNotFound( char artist[] ) ;
void printMusicLibraryEmpty( void ) ;
void printMusicLibraryTitle( void ) ;

const int MAX_LENGTH = 1024;

int main( void ) {
    // Declare the head of the linked list.
    //   ADD YOUR STATEMENT(S) HERE
    Node *head = NULL;
    
    // Announce the start of the program
    printf( "Personal Music Library.\n\n" ) ;
    printf( "%s", "Commands are I (insert), D (delete), S (search by song name),\n"
         "P (print), Q (quit).\n" ) ;
    
    char response ;
    char input[ MAX_LENGTH + 1 ] ;
    do {
        inputStringFromUser( "\nCommand", input, MAX_LENGTH ) ;

        // Response is the first character entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper( input[0] ) ;

        if( response == 'I' ) {
            // Insert a song into the linked list.
            // Maintain the list in alphabetical order by song name.
            //   ADD STATEMENT(S) HERE
            char *promptName = "Song name" ;
            char *promptArtist =  "Artist" ;
            char *promptGenre = "Genre" ;
            char songName[MAX_LENGTH + 1]; 
            char artist[MAX_LENGTH + 1];
            char genre[MAX_LENGTH + 1];
            inputStringFromUser(promptName, songName, MAX_LENGTH);
            inputStringFromUser(promptArtist, artist, MAX_LENGTH);
            inputStringFromUser(promptGenre, genre, MAX_LENGTH);
            Node *newSong = (Node*) malloc(sizeof(Node));
            newSong -> songName = (char*) malloc(MAX_LENGTH * sizeof(char));
            newSong -> artist = (char*) malloc(MAX_LENGTH * sizeof(char));
            newSong -> genre = (char*) malloc(MAX_LENGTH * sizeof(char));
            strcpy(newSong -> songName, songName);
            strcpy(newSong -> artist, artist);
            strcpy(newSong -> genre, genre);
            Node *temp = head;
            Node *prevTemp = head;
            bool duplicate = false;
            
            //empty music library, just put in song
            if (head == NULL)
                head = newSong;
            //new song precedes the head song, replace head
            else if (strcmp(newSong -> songName, head -> songName) < 0)
            {
                head = newSong;
                head -> nextNode = temp; 
            }
            else if (strcmp(newSong -> songName, head -> songName) == 0)
            {
                songNameDuplicate(newSong -> songName);
                duplicate = true;
            }
            //1-node linked list, where new song goes after
            else if (head -> nextNode == NULL)
            {
                head -> nextNode = newSong;
                newSong -> nextNode = NULL;
            }
            else
            {
                bool inserted = false;
                temp = temp -> nextNode;
                while (temp != NULL)
                {
                    if (strcmp(temp -> songName, newSong -> songName) < 0)
                    {
                        prevTemp = prevTemp -> nextNode;
                        temp = temp -> nextNode;
                    }
                    else if (strcmp(prevTemp -> songName, newSong -> songName) == 0)
                    {
                        songNameDuplicate(newSong -> songName);
                        duplicate = true;
                        break;
                    }
                    else
                    {
                        prevTemp -> nextNode = newSong;
                        newSong -> nextNode = temp;
                        inserted = true;
                        break;
                    }
                }
                if (!duplicate && !inserted)
                {
                    prevTemp -> nextNode = newSong;
                    newSong -> nextNode = temp;
                }
            }
            
            // USE THE FOLLOWING STRINGS WHEN PROMPTING FOR DATA:
            //    char *promptName = "Song name" ;
            //    char *promptArtist =  "Artist" ;
            //    char *promptGenre = "Genre" ;

        }
        else if( response == 'D' ) {
            // Delete a song from the list.

            char *prompt = "\nEnter the name of the song to be deleted" ;

            //   ADD STATEMENT(S) HERE
            if (head == NULL)
                printMusicLibraryEmpty();
            else
            {
                char song[MAX_LENGTH + 1];
                inputStringFromUser(prompt, song, MAX_LENGTH);
                Node *position = head;
                Node *prevPos = head;
                bool foundSong = false;
                //delete song from the beginning of library
                if (strcmp(head -> songName, song) == 0)
                {
                    Node *temp = head;
                    head = head -> nextNode;
                    songNameDeleted(song);
                    free(temp -> songName);
                    free(temp -> artist);
                    free(temp -> genre);
                    free(temp);
                    foundSong = true;
                }
                else
                {
                    position = position -> nextNode;
                    while (position != NULL)
                    {
                        if (strcmp(position -> songName, song) == 0)
                        {
                            prevPos -> nextNode = position -> nextNode;
                            songNameDeleted(song);
                            free(position -> songName);
                            free(position -> artist);
                            free(position -> genre);
                            free(position);
                            foundSong = true;
                            break;
                        }
                        position = position -> nextNode;
                        prevPos = prevPos -> nextNode;
                    }
                }
                if (!foundSong)
                    songNameNotFound(song);
            }
        }

        else if( response == 'S' ) {
            // Search for a song by its name.

            char *prompt = "\nEnter the name of the song to search for" ;

            //   ADD STATEMENT(S) HERE
            if (head == NULL)
                printMusicLibraryEmpty();
            else
            {
                char song[MAX_LENGTH + 1];
                inputStringFromUser(prompt, song, MAX_LENGTH);
                Node *position = head;
                bool foundSong = false;
                while (position != NULL)
                {
                    if (strcmp(position -> songName, song) == 0)
                    {
                        songNameFound(song);
                        printf("\n%s\n", position -> songName);
                        printf("%s\n", position -> artist);
                        printf("%s\n", position -> genre);
                        foundSong = true;
                        break;
                    }
                    position = position -> nextNode;
                }
                if (!foundSong)
                    songNameNotFound(song);
            }
        }
        else if( response == 'P' ) {
            // Print the music library.

            //   ADD STATEMENT(S) HERE
            if (head == NULL)
                printMusicLibraryEmpty();
            else
            {
                printMusicLibraryTitle();
                Node *position = head;
                while (position != NULL)
                {
                    printf("\n%s\n", position -> songName);
                    printf("%s\n", position -> artist);
                    printf("%s\n", position -> genre);
                    position = position -> nextNode;
                }
            }
        }
        else if( response == 'Q' ) {
            ; // do nothing, we'll catch this below
        }
        else {
            // do this if no command matched ...
            printf( "\nInvalid command.\n" ) ;
        }
    } while( response != 'Q' ) ;
  
    // Delete the entire linked list.
    //   ADD STATEMENT(S) HERE
    Node *position = head;
    while (position != NULL)
    {
        songNameDeleted(position -> songName);
        Node *temp = position;
        free(temp -> songName);
        free(temp -> artist);
        free(temp -> genre);
        free(temp);
        if (position -> nextNode == NULL)
            head = NULL;
        position = position -> nextNode;
    }
    
    // Print the linked list to confirm deletion.
    //   ADD STATEMENT(S) HERE
    if (head == NULL)
        printMusicLibraryEmpty();
    else
    {
        printMusicLibraryTitle();
        Node *position = head;
        while (position != NULL)
        {
            printf("\n%s\n", position -> songName);
            printf("%s\n", position -> artist);
            printf("%s\n", position -> genre);
            position = position -> nextNode;
        }
    }    
    return 0 ;
}

// Support Function Definitions

// Prompt the user for a string safely, without buffer overflow
void inputStringFromUser(char prompt[], char s[], int maxStrLength) {
    int i = 0;
    char c;
    
    printf( "%s --> ", prompt ) ;
    while( i < maxStrLength && (c = getchar()) != '\n' )
        s[i++] = c ;
    s[i] = '\0' ;
}

// Function to call when the user is trying to insert a song name 
// that is already in the personal music library.
void songNameDuplicate( char songName[] ) {
    printf( "\nA song with the name '%s' is already in the music library.\n"
            "No new song entered.\n", songName);
}

// Function to call when a song name was found in the personal music library.
void songNameFound( char songName[] ) {
    printf( "\nThe song name '%s' was found in the music library.\n",
           songName ) ;
}

// Function to call when a song name was not found in the personal music library.
void songNameNotFound( char songName[] ) {
    printf( "\nThe song name '%s' was not found in the music library.\n",
           songName);
}

// Function to call when a song name that is to be deleted
// was found in the personal music library.
void songNameDeleted( char songName[] ) {
    printf( "\nDeleting a song with name '%s' from the music library.\n",
           songName);
}

// Function to call when printing an empty music library.
void printMusicLibraryEmpty(void) {
    printf( "\nThe music library is empty.\n" ) ;
}

// Function to call to print a title when the entire music library is printed.
void printMusicLibraryTitle(void) {
    printf( "\nMy Personal Music Library: \n" ) ;
}

// Add your functions below this line.

//   ADD STATEMENT(S) HERE