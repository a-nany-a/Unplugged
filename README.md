# Unplugged
Unplugged is a console-based music application written in C that allows users to manage playlists and songs using core data structures and file handling.
To compile the project a Makefile has been used 
The steps to compile are:
      make
     ./unplugged


main.c - Main CLI controller

music.c - Song & Album management
music.h - Structures & function declarations 

playlist.c - Circular playlist logic 
playlist.h - Playlist struct + function prototypes

history.c - Command history logging system 
history.h - History header 

songs.txt - Song library
albums.txt - album storage file 
history.txt - Auto-generated log file
