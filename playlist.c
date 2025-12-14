#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "music.h"
#include "playlist.h"

//playlist *playlistHead = NULL;
playlist *currentsong = NULL;

playlist* addsong_toplaylist(playlist* head,int id,char atitle[],char asinger[],int time){
playlist *newsong=malloc(sizeof(playlist));
strcpy(newsong->title,atitle);
strcpy(newsong->singer,asinger);
newsong->song_ID=id;
newsong->time_span=time;          
newsong->next=head;    //coz its circular
if(head==NULL){head=newsong;
               newsong->next = newsong;//doubly linked list
               newsong->prev = newsong;}
else{playlist *temp;
temp=head->prev;
temp->next=newsong;
newsong->prev=temp;
head->prev=newsong;
newsong->next=head;}
return head;
}

playlist* addalbum_toplaylist(Album *head,char aname[],playlist* playlistHead){
Album* temp;
temp=head;
while(temp!=NULL){
    if(strcmp(temp->name,aname)==0){
        Song* songhead=temp->songs;
        while(songhead!=NULL){playlistHead=addsong_toplaylist(playlistHead,songhead->song_ID,songhead->title,songhead->singer,songhead->time_span);
        songhead=songhead->next;}
        printf("The requested Album has been added to the playlist.\n");
    return playlistHead;}
    temp=temp->next;
}
printf("sorry! Album not found.\n");
return playlistHead;
}

void displayplaylist(playlist *head){
 if(head==NULL){printf("Sorry! playlist not found\n");return;}   
playlist* temp;
temp=head;
printf("Title:%s\nArtist:%s\nDuration:%d\n",temp->title,temp->singer,temp->time_span);
printf("---------------------------------------- \n");
temp=temp->next;
while(temp!=head){
    printf("Title:%s\nArtist:%s\nDuration:%d\n",temp->title,temp->singer,temp->time_span);
    printf("---------------------------------------- \n");
    temp=temp->next;
}    
}

void playnext_song(playlist* playlistHead){
 if(playlistHead==NULL){printf("Sorry! playlist is empty\n");return;}
if(currentsong==NULL){currentsong=playlistHead;
printf("ID:%d\nTitle:%s\nArtist:%s\nDuration:%d\n",currentsong->song_ID,currentsong->title,currentsong->singer,currentsong->time_span);
printf("---------------------------------------- \n");    
return;}
currentsong=currentsong->next;
printf("ID:%d\nTitle:%s\nArtist:%s\nDuration:%d\n",currentsong->song_ID,currentsong->title,currentsong->singer,currentsong->time_span);
printf("---------------------------------------- \n");
}

void playprevious_song(playlist* playlistHead){
if(playlistHead==NULL){printf("Sorry! playlist is empty\n");return;}    
if(currentsong==NULL){currentsong=playlistHead->prev;
printf("ID:%d\nTitle:%s\nArtist:%s\nDuration:%d\n",currentsong->song_ID,currentsong->title,currentsong->singer,currentsong->time_span);
printf("---------------------------------------- \n");return;}  
currentsong=currentsong->prev;
printf("ID:%d\nTitle:%s\nArtist:%s\nDuration:%d\n",currentsong->song_ID,currentsong->title,currentsong->singer,currentsong->time_span);
printf("---------------------------------------- \n");
}

playlist* delete_song_fromplaylist(playlist* head,char atitle[]){
if(head==NULL){
    printf("Sorry! playlist is empty\n");
    return head;
}
if(strcmp(head->title,atitle)==0){
    playlist *delete=head; // Only one node present
    if(head->next==head){
        //free(head);
        head=NULL;
        printf("Song deleted.\n");
        return head;
    }
    head=head->next;
    head->prev=delete->prev;
    delete->prev->next=head;
    printf("Deleted song: %s\n",atitle);
    free(delete);
    return head;
}
playlist *temp=head->next;
while(temp!=head){
    if(strcmp(temp->title,atitle)==0){
        temp->prev->next=temp->next;
        temp->next->prev=temp->prev;
        printf("Song deleted\n");
        free(temp);
        return head;
    }
    temp=temp->next;
}

printf("Song not found\n");
return head;
}


playlist *freeplaylist(playlist* playlistHead){
    if(playlistHead==NULL){
    printf("Playlist is already empty.\n");
    return playlistHead;
}
if(playlistHead->next==playlistHead){
    free(playlistHead);
    playlistHead=NULL;
    printf("Your playlist has been cleared.\n");
    return playlistHead;
}
playlist *mark=playlistHead->next;
playlist *next;
while(mark!=playlistHead){
    next=mark->next;
    free(mark);
    mark=next;
}
free(playlistHead);
playlistHead=NULL;
printf("Your playlist has been cleared.\n");
return playlistHead;                        
};



