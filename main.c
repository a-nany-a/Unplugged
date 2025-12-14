#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "music.h"
#include "playlist.h"
#include "history.h"

void readline(char *b, int size) {
int i=0,ch;
while (i<size - 1){
ch=getchar();
if (ch=='\n' || ch==EOF)break;
b[i++]=ch; }
b[i]='\0';
}


void list_all_songs(Song *head);
Album* find_album_by_number(Album *head, int num);
Song* find_song_in_album_by_number(Album *a, int num);

int main() {
    Song *library = load_song();       
    Album *albums = load_album(library);    
    playlist *playlistHead = NULL;        
    add_to_history("C-unplugged Started");
    int choice;
    while (1) {
        printf("\nC-UNPLUGGED :\n");
        printf("1. List all songs in library\n");
        printf("2. List all albums\n");
        printf("3. Create new album\n");
        printf("4. Add song to an album\n");
        printf("5. Delete song from an album\n");
        printf("6. Save albums\n");
        printf("7. Add a song to playlist\n");
        printf("8. Add an album to playlist\n");
        printf("9. Play next song\n");
        printf("10. Play previous song\n");
        printf("11. Show playlist\n");
        printf("12. Delete song from playlist\n");
        printf("13. View command history\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d",&choice);
        getchar();

        FILE *ptr=fopen("history.txt", "a");
        if(ptr != NULL){
        fprintf(ptr,"User Command: %d\n", choice);
        fclose(ptr);
        }

        if(choice==0){
            add_to_history("Program Exited");
            printf("Exiting...please wait don't close the tab your albums are being saved..\n");
            save_album(albums);
            return 0;
        }

        else if(choice==1){    //list all the songs
            printf("\n:::: SONG LIBRARY ::::\n");
            list_all_songs(library);
        }

        else if(choice==2){ //list album
            printf("\n:::: ALBUMS ::::\n");
            list_album(albums);
        }

        else if(choice==3){   //create album
            char name[500];
            printf("Enter new album name: ");
            fgets(name,sizeof(name),stdin);
            name[strcspn(name, "\n")]=0;
            albums = add_album(albums, name);
            add_to_history("Created an album");
            printf("Album \"%s\" created.\n", name);
        }

        else if(choice==4){ // add song to album
           printf("Please select the album:\n");
           list_album(albums);
           char album_name[500];
           printf("Name the album (enter the name): ");
           readline(album_name, 500);

           char title[500];
           printf("Enter song title: ");
           readline(title, 500);
           addsong_toalbum(albums,library, album_name, title);
           add_to_history("Added song to album");
           }

        else if(choice==5){
            char album_name[500],song_title[500];
            printf("Enter album name: ");
            readline(album_name,500); 
            printf("Enter song title to delete: ");
            readline(song_title,500);
            delete_song_fromalbum(album_name, song_title, albums);
            add_to_history("Deleted song from album");
        }

        else if(choice==6){ //albums saved
            save_album(albums);
            add_to_history("Saved albums");
        }

        else if(choice==7){   // add song to playlist
            printf("\n:::: SONG LIBRARY ::::\n");
            list_all_songs(library);
            int songnum;
            printf("Enter song number from library to add: ");
            scanf("%d",&songnum);
            getchar();
            Song *temp=library;
            int index=1;
            while(temp!= NULL && index<songnum) {
             temp=temp->next;
            index++;
        }

           if(temp==NULL) {
           printf("Invalid song number!\n");
           }
    else{
        playlistHead = addsong_toplaylist(playlistHead, temp->song_ID, temp->title, temp->singer, temp->time_span);
        printf("Song '%s' added to playlist.\n", temp->title);
        add_to_history("Added single song to playlist");
        }
        }


        else if(choice==8){//add album to playlist
            char aname[500];
            printf("Select an album by it's name : ");
            scanf("%s",aname);
            getchar();
            playlistHead=addalbum_toplaylist(albums, aname, playlistHead);
            add_to_history("Added album to playlist");
        }

        else if(choice==9){
            playnext_song(playlistHead);
            add_to_history("Next song being played");
        }

        else if(choice==10){
            playprevious_song(playlistHead);
            add_to_history("Previous song being played");
        }

        else if(choice==11) { //display playlist
            printf("\n:::: PLAYLIST ::::\n");
            displayplaylist(playlistHead);
        }

        else if(choice==12){
            char title[500];
            printf("Enter the song's title that you want to delete from playlist: ");
            scanf("%s",title);
            //getchar();
            playlistHead=delete_song_fromplaylist(playlistHead,title);
            add_to_history("Deleted song from playlist");
        }

        else if(choice==13){//show history
            display_history();
        }
        else {
            printf("Invalid option!\n");
        }
    }
    return 0;
}

void list_all_songs(Song *head){
    int ind=1;
    while (head->next!=NULL) {
    printf("%d. %s — %s (%d)\n",ind++,head->title,head->singer,head->time_span);
     head = head->next;
    }
}

/* If needed later: album index selection helpers */
Album* find_album_by_number(Album *head, int num) {
    int count = 1;
    while (head != NULL) {
        if (count == num) return head;
        head = head->next;
        count++;
    }
    return NULL;
}



