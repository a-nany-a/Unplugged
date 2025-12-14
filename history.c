#include <stdio.h>
#include "history.h"

void add_to_history(char command[]){
FILE *fptr;
fptr=fopen("history.txt","a");
if(fptr==NULL){printf("sorry! unable to open the history file.\n");
return;}
fprintf(fptr,"User Command : %s\n", command);
fclose(fptr);
}

void display_history(){
FILE *fptr;    
fptr=fopen("history.txt", "r");
if(fptr==NULL){printf("sorry! unable to open the history file.\n");
return;}
char str[500];
printf("Your History::\n");
while(fgets(str, sizeof(str), fptr) != NULL){
    printf("%s", str);
}
fclose(fptr);
}