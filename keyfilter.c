#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//Maximum size of all strings in this project.
#define MAX_SIZE 101

//Function, that will save all first letters form txt file, if user hasn't write argument.
void firstLetters(char *nextLetters){
    //Variable, that will receive values for txt file.
    char adresses[MAX_SIZE];
    while(fgets(adresses,sizeof(adresses), stdin) != NULL){
        for(int i = 0; adresses[i]!='\0';i++) adresses[i]=toupper(adresses[i]); //case insensitive
        if(strchr(nextLetters, adresses[0]) == NULL) strncat(nextLetters, &adresses[0], 1);
    }
}

//Function, that will work on saving all next letters, depends on what user has written.
void searchLocation(char userLetters[], char *nextLetters, char* onlyOne, int *similiarityAmount, int *scanAmount){

    //Variable, that will receive values for txt file.
    char adresses[MAX_SIZE];
    //This variable, which will help append new chars to array nextLetters(ENABLE)
    int iForNextLetters = 0;

    for(int i=0; userLetters[i]!='\0';i++) userLetters[i]=toupper(userLetters[i]); //case insensitive

    while(fgets(adresses,sizeof(adresses), stdin) != NULL){
        *scanAmount+=1;

        //This boolean variable I need to check for complete similiarity.
        bool allEqual = true;

        for(int i = 0; adresses[i]!='\0';i++) adresses[i]=toupper(adresses[i]); //case insensiive

        for(int i = 0; i<(int)strlen(userLetters); i++){
            if(adresses[i] == userLetters[i])
                continue;
            else{
                allEqual = false;
                break;
            }
        }

        //If there is complete similiarty, the new letter will append in array
        if(allEqual==true){
            if(strchr(nextLetters, adresses[strlen(userLetters)]) == NULL){
                nextLetters[iForNextLetters]=adresses[strlen(userLetters)];
                nextLetters[iForNextLetters+1]= '\0';
                iForNextLetters++;
        }
            *similiarityAmount+=1;
 
            //If there is only one similiarity, I save it here.
            //Actually I need it for FOUND.
            strcpy(onlyOne, adresses);
        }
    }
}

//Help function that will print out results in alphabet order
void inAlphabetOrder(char *nextLetters){
    int ascii_size = 128;
    printf("Enable: ");
    for(int i = 0; i<ascii_size; i++){

        for(int k=0; nextLetters[k] != '\0'; k++)
            if(i==nextLetters[k] && nextLetters[k]!=10) printf("%c", nextLetters[k]);

        }

        printf("\n");
}


int main(int argc, char **argv){

    //string for saving value(s), for ENABLE
    char nextLetters[MAX_SIZE] = "";
    char *nextLetters_ptr = nextLetters;

    //string for saving value, for FOUND
    char onlyOne[MAX_SIZE]="";
    char *onlyOne_ptr = onlyOne;

    //variable for saving amount of similarity
    int similiarityAmount = 0;
    //variable for saving amount of scan to help me do stderr if file is empty
    int scanAmount = 0;

    //If user hasn't written anything as argument
    if(argc==1){
        firstLetters(nextLetters_ptr);

        //Treatment of error conditions
        if(strlen(nextLetters) == 0) { 
            fprintf(stderr, "Text file is empty\n");
            return 1;
        }
        else inAlphabetOrder(nextLetters_ptr);
    }

    //If user has written something as argument
    else if(argc==2){

        searchLocation(argv[1], nextLetters_ptr, onlyOne_ptr, &similiarityAmount, &scanAmount);

        //Here I check how many similarities there were, and depending on this I print out the result
        if(similiarityAmount>1) inAlphabetOrder(nextLetters_ptr);

        else if(similiarityAmount==1) printf("Found: %s", onlyOne);

        //Treatment of error conditions
        else if(scanAmount == 0) {
            fprintf(stderr, "Text file is empty\n");
            return 1;
        }

        else if(similiarityAmount==0) printf("Not found\n");
    }
    
    //If user has written more than one argument(string)
    //Treatment of error conditions
    else if(argc>2){
        fprintf(stderr, "Too many arguments\n");
        return 1;
    }

    return 0;
}
