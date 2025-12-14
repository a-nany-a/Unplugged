#ifndef MUSIC_H   
#define MUSIC_H   

typedef struct Song {
    int song_ID;
    char title[500];
    char singer[500];
    int time_span;
    struct Song *next;
} Song;

typedef struct Album {
    int album_ID;
    char name[500];
    Song *songs;
    struct Album *next;
} Album;


Song* load_song();
Album *add_album(Album *head,char aname[]);
void addsong_toalbum(Album *head,Song* library,char aname[],char atitle[]);
void list_album(Album *head);
void delete_song_fromalbum(char albumname[],char delsong[],Album *head);
void save_album(Album *head);
void add_loaded_song(Album *albums,Song *library,char album_name[],char title[],char singer[],int duration);
Album* load_album(Song *library);
#endif