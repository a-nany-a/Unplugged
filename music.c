#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "music.h"

Song* load_song(){
FILE *fptr = fopen("songs.txt", "r");
if(fptr == NULL){
printf("Error! songs.txt could not be found.\n");
return NULL; }
Song *head = NULL;
Song *tail = NULL;
char str[500];

while(fgets(str, sizeof(str), fptr)){
int i = 0;
while(str[i] != '\0'){
    if(str[i] == '\n'){
    str[i] = '\0';
    break;}
    i++; }

char idstr[500], title[500], singer[500], dur[500];//duration
int id_idx=0, t_idx=0, s_idx=0, d_idx=0;
int p=0;
 for(int j=0;str[j]!='\0';j++){
    if(str[j]=='|'){
    p++;
    continue;}
    if(p==0)idstr[id_idx++] = str[j];
    else if(p==1)title[t_idx++] = str[j];
    else if(p==2)singer[s_idx++] = str[j];
    else dur[d_idx++] = str[j];
    }

idstr[id_idx]='\0';
title[t_idx]='\0';
singer[s_idx]='\0';
dur[d_idx]='\0';
int id =0;
for(int k = 0; idstr[k] != '\0'; k++){
id =id*10 + (idstr[k]-'0');
}
int duration = 0;
for(int k=0;dur[k]!='\0';k++){
duration = duration*10 + (dur[k]-'0');
}

Song *newsong = malloc(sizeof(Song)); //store in linked list
newsong->song_ID = id;
strcpy(newsong->title,title);
strcpy(newsong->singer,singer); 
newsong->time_span = duration;
newsong->next = NULL;

if(head==NULL){
head=newsong;
tail=newsong;}
else {
tail->next = newsong;
tail = newsong;
}
}
fclose(fptr);
return head;
}

Album *add_album(Album *head,char aname[]){ //linked list mei insert new album
Album *newalbum=malloc(sizeof(Album));
strcpy(newalbum->name,aname);
newalbum->songs=NULL; 
newalbum->next=NULL;
if(head==NULL)head=newalbum;
else{Album *temp;
temp=head;
while(temp->next!=NULL)temp=temp->next;
temp->next=newalbum;}
return head;
}

void addsong_toalbum(Album *albums, Song *library, char album_name[], char song_title[]) {
Album *tail = albums;
while(tail!= NULL){
if(strcmp(tail->name,album_name) == 0)break;
tail=tail->next;
}
if(tail == NULL){
printf("Sorry! Album '%s' not found.\n", album_name);
return;
}
Song *temp = library;
 while(temp!= NULL) {
if (strcmp(temp->title, song_title) == 0)break;
    temp=temp->next;
}
if(temp== NULL){
printf("Sorry! Song '%s' was not found in library.\n", song_title);
return;
}

Song *newsong = malloc(sizeof(Song));
if(!newsong){
printf("Error allocating memory for new song!\n");
 return;
}

newsong->song_ID =temp->song_ID;
strcpy(newsong->title,temp->title);
strcpy(newsong->singer,temp->singer);
newsong->time_span=temp->time_span;
newsong->next=NULL;

if(tail->songs == NULL){
tail->songs = newsong;
} 
else {
 Song *temp = tail->songs;
while (temp->next != NULL)
temp = temp->next;
temp->next = newsong;
}
printf("Song '%s' has been added to album '%s'\n", song_title, album_name);
}


void list_album(Album *head){
if(head==NULL)printf("No Album found\n\n");
else{Album *temp;
    temp=head;
    while(temp!=NULL){
    printf("Album name:%s\n\n",temp->name);
    if(temp->songs==NULL)printf("No songs in the album\n\n");
    else{Song *node;
    node=temp->songs;
    while(node!=NULL){printf("Title:%s\n",node->title);
                    printf("singer:%s\n",node->singer);
                    printf("Duration:%d\n\n",node->time_span);
                    node=node->next;}
                            }
    temp=temp->next;
    }
}
}

void delete_song_fromalbum(char albumname[],char delsong[],Album *head){
Album *temp;
temp=head;
while(temp!=NULL){
    if(strcmp(temp->name,albumname)==0){
        Song *del;
        del=temp->songs;
        if (del== NULL){
    printf("This album has no songs.\n");
    return;}
        if(strcmp(del->title,delsong)==0){Song *de=temp->songs;
            temp->songs=temp->songs->next;
            free(de);
            printf("Song deleted.\n");
            return;}
    while(del!=NULL && del->next!=NULL){    
    if(strcmp(del->next->title,delsong)==0){Song *delete;
        delete=del->next;
        del->next=del->next->next;
        free(delete);
        printf("Song deleted.\n");
    return;}
    else del=del->next;} }
    else temp=temp->next;
}
printf("Could not find the right match to delete\n");
}   

void save_album(Album *head){
FILE *fptr;
fptr=fopen("albums.txt","w");
Album *temp = head;
    while (temp != NULL) {
        // Write album name
        fprintf(fptr,"#Album:%s\n",temp->name);

        // Write songs inside this album
        Song *temp_song = temp->songs;
        while (temp_song != NULL){
fprintf(fptr, "song:%s|%s|%d\n",temp_song->title, temp_song->singer,temp_song->time_span);
        temp_song = temp_song->next;
        }
        temp = temp->next;
    }
    fclose(fptr);
    printf("Albums is now saved to albums.txt\n");
}

void add_loaded_song(Album *albums, Song *library, char album_name[], char title[], char singer[], int duration) {
    Album *tail = albums;
    while(tail!= NULL){
    if(strcmp(tail->name,album_name)==0)break;
        tail=tail->next;
    }
    if(tail==NULL)return;
    Song *temp =library;
    int real_id = 0;
    while (temp != NULL) {
        if (strcmp(temp->title, title) == 0) {
            real_id = temp->song_ID;
            break;
        }
        temp = temp->next;
    }
    Song *newsong = malloc(sizeof(Song));
    strcpy(newsong->title, title);
    strcpy(newsong->singer, singer);
    newsong->time_span = duration;
    newsong->song_ID = real_id;
    newsong->next = NULL;

    if(tail->songs == NULL)
        tail->songs = newsong;
    else {
        Song *t=tail->songs;
        while(t->next != NULL)
            t=t->next;
        t->next=newsong;
    }
}

Album* load_album(Song *library){          // we need this function to store those created albums permenantly
FILE *fptr = fopen("albums.txt", "r");
    if(fptr == NULL){
        printf("There are no previously saved albums.\n");
        return NULL;
    }
    Album *head = NULL;
    Album *cur_album = NULL;
    char str[400];
    while (fgets(str, sizeof(str), fptr)) {
       for (int i=0;str[i]!='\0';i++) {
    if (str[i]=='\n') {
        str[i]='\0';
        break;}
    }
        if(strncmp(str,"#Album:", 7) == 0) {
        char aname[500];
        strcpy(aname, str+7);//str+7 yaha pe directly album name ko point karega
        head=add_album(head, aname);
        if(cur_album==NULL)cur_album= head;
        else {
        Album *temp;
        temp=head;
        while(temp->next != NULL)temp=temp->next;
        cur_album=temp;
         }
        }

        else if(strncmp(str,"song:",5)==0 && cur_album != NULL){
        char title[500], singer[500];
        int duration;
        char *word=str+5;
        int i = 0;
        int k = 0;
        while (word[k] != '|' && word[k] != '\0'){
        title[i++]=word[k++];
        }
        title[i] ='\0';
        k++; 
        i = 0;
        while (word[k] != '|' && word[k] != '\0') {
            singer[i++] = word[k++];
        }
        singer[i] ='\0';
        k++;
        duration = atoi(word + k);//Skips leading whitespace Reads digits until a non-digit appears ,Stops converting at the first invalid character
        add_loaded_song(head,library,cur_album->name, title, singer, duration);
    }
    }

    fclose(fptr);
    printf("Albums loaded\n");
    return head;
}
