#ifndef PLAYLIST_H
#define PLAYLIST_H

typedef struct playlist{
int song_ID;
 char title[500];
 char singer[500];
 int time_span; 
 struct playlist* next;
 struct playlist* prev;
}playlist;

playlist* addsong_toplaylist(playlist* head,int id,char atitle[],char asinger[],int time);
playlist* addalbum_toplaylist(Album *head,char aname[],playlist* playlisthead);
void displayplaylist(playlist *head);
void playnext_song(playlist* playlistHead);
void playprevious_song(playlist* playlistHead);
playlist* delete_song_fromplaylist(playlist* head,char atitle[]);
playlist* freeplaylist(playlist* playlistHead);

#endif
