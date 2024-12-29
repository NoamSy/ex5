#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ADD_PLAYLIST 2
#define WATCH_PLAYLIST 1
#define AMOUNT_OF_OPTIONS_PLAYLISTS 6
#define DELETE_PLAYLIST 3
typedef struct Song {
    char* title;
    char* artist;
    int year;
    char* lyrics;
    int streams;
} Song;

typedef struct Playlist {
    char* name;
    Song** songs;
    int songsNum;
} Playlist;






//function that will free all playlists
void freePlaylists(Playlist ** playlists, int playlistCounter) {
    for (int i = 0; i < playlistCounter; ++i) {
        free(playlists[i]);
    }
}

void printPlaylistsMenu() {
    printf("Please Choose:\n"); 
    printf("\t1. Watch playlists\n\t2. Add playlist\n\t3. Remove playlist\n\t4. exit\n");   
}





//function that will print all songs in a playlist
void printSongs(Playlist ** playlists, int playlistCounter) {
    for (int song = 0; song < playlists[playlistCounter]->songsNum; ++song) {
        Song *currentSong =  playlists[playlistCounter]->songs[song];
        printf("%d. Title: %s\n   Artists: %s\n   Released: %d\n   Streams: %d\n",
            (song+1), currentSong->title, currentSong->artist,currentSong->year, currentSong->streams);
    }
}
//function that will print all platlists
void printPlaylists(Playlist ** playlists, int playlistCounter) {
    printf("Choose a playlist:\n");
    //print all playlists
    printf("\t");
    for (int playlist = 0; playlist < playlistCounter; ++playlist) {
        if (playlists == NULL || playlists[playlistCounter] == NULL) {
            exit(1);
        }
        printf("%d. %s\n\t", (playlist+1), playlists[playlist]->name);
    }
    //at the end print back to menu
    printf("%d. Back to main menu\n", (playlistCounter+1));
}
void printPlaylistOptions() {
    printf("\t1. Show Playlist\n\t2. Add Song\n\t3. Delete Song\n\t4. Sort\n\t5. Play\n\t6. exit\n");
}
void printSortOptions() {
    printf("1. sort by year\n2. sort by streams - ascending order\n3. sort by streams - descending order"
           "\n4. sort alphabetically\n");
}

void sortPlaylists(Playlist ** playlists, int chosenPlaylist) {
    int chosenSort;
    scanf("%d", &chosenSort);
    if (playlists[chosenPlaylist]->songsNum == 1) {}
    //alphabetical arangement
    if (chosenSort < 1 || chosenSort >= 4) {
        //array that will save all places of the songs in alpha way
        for (int m = 0; m < playlists[chosenPlaylist]->songsNum; ++m) {
            for (int i = 0; i < playlists[chosenPlaylist]->songsNum; ++i) {
                //if the left title is alpabetically earlier means strcmp will give less then 0, then we eed to switch
                //between them
                if (strcmp(playlists[chosenPlaylist]->songs[m]->title,playlists[chosenPlaylist]->songs[i]->title) < 0) {
                    //change between the two songs location
                    Song temp = *playlists[chosenPlaylist]->songs[m];
                    *playlists[chosenPlaylist]->songs[m] = *playlists[chosenPlaylist]->songs[i];
                    *playlists[chosenPlaylist]->songs[i] = temp;
                }

            }

        }
    }
    else if (chosenSort == 1) {
        for (int i = 0; i < playlists[chosenPlaylist]->songsNum; ++i) {
            for (int m = 0; m < playlists[chosenPlaylist]->songsNum; ++m) {
                //check if the year is earlier than the other year
                if (playlists[chosenPlaylist]->songs[m]->year < playlists[chosenPlaylist]->songs[i]->year) {
                    //change between the two songs location
                    Song temp = *playlists[chosenPlaylist]->songs[m];
                    *playlists[chosenPlaylist]->songs[m] = *playlists[chosenPlaylist]->songs[i];
                    *playlists[chosenPlaylist]->songs[i] = temp;
                }
            }
        }
    }
    //ascending streams arangement
    else if (chosenSort == 2) {
        for (int i = 0; i < playlists[chosenPlaylist]->songsNum; ++i) {
            for (int m = 0; m < playlists[chosenPlaylist]->songsNum; ++m) {
                //check if it has less streams then the others
                if (playlists[chosenPlaylist]->songs[m]->streams > playlists[chosenPlaylist]->songs[i]->streams) {
                    //change between the two songs location
                    Song temp = *playlists[chosenPlaylist]->songs[m];
                    *playlists[chosenPlaylist]->songs[m] = *playlists[chosenPlaylist]->songs[i];
                    *playlists[chosenPlaylist]->songs[i] = temp;
                }
            }
        }
    }
    //decensing streams arrangement
    else if (chosenSort == 3) {
        for (int i = 0; i < playlists[chosenPlaylist]->songsNum; ++i) {
            for (int m = 0; m < playlists[chosenPlaylist]->songsNum; ++m) {
                //check if it has more streams then the others
                if (playlists[chosenPlaylist]->songs[m]->streams < playlists[chosenPlaylist]->songs[i]->streams) {
                    //change between the two songs location
                    Song temp = *playlists[chosenPlaylist]->songs[m];
                    *playlists[chosenPlaylist]->songs[m] = *playlists[chosenPlaylist]->songs[i];
                    *playlists[chosenPlaylist]->songs[i] = temp;
                }
            }
        }
    }
    printf("sorted\n");
}
//function that will delete a song
void deleteSong(Playlist ** playlists, int playlistCounter, int songToDelete) {
    //if zero go back to menu
    if (songToDelete == 0)
        return;
    //go from song to delete to the final song, and replace every song to the one after so we get rid of the
    //deleted song
    //minus one so we can work with the pointers
    songToDelete--;
    for (int i = songToDelete; i < playlists[playlistCounter]->songsNum-1; ++i) {
        playlists[playlistCounter]->songs[i] = playlists[playlistCounter]->songs[i+1];
    }
    //free the last song as it is written twice
    free(playlists[playlistCounter]->songs[playlists[playlistCounter]->songsNum-1]);
    //we have minus one songs
    playlists[playlistCounter]->songsNum--;
    printf("Song deleted successfully.\n");
}
void deletePlaylist(Playlist ** playlists, int playlistToDelete, int playlistCounter) {
    playlistToDelete--;
    for (int i = playlistToDelete; i < playlistCounter-1; ++i) {
        playlists[i] = playlists[i+1];
    }
    free(playlists[playlistCounter-1]);
    printf("Playlist deleted.\n");
}


//function that will return a string
char * getString() {
    char * str = NULL;
    str = malloc(sizeof(char));
    if (str == NULL) {
        exit(1);
    }
    int currentChar = 0;
    char input;
    scanf(" %c", &input);
    while (input != '\n') {
        //+2 because we also need \0
        str = realloc(str, sizeof(char) * (currentChar + 2));
        if (str == NULL) {
            exit(1);
        }
        //add the char to the array
        str[currentChar] = input;
        currentChar++;
        scanf("%c", &input);
    }
    //set last char to \n
    str[currentChar] = '\0';
    return str;
}


int main() {
     Playlist ** playlists = NULL;

     int playlistCounter = 0;
     int choice;
     do{
      printf("Please Choose:\n\t1. Watch playlists\n\t2. Add playlist\n\t3. Remove playlist\n\t4. exit\n");
      scanf("%d", &choice);
      switch (choice) {
          case 4: {
              printf("Goodbye!\n");
              freePlaylists(playlists, playlistCounter);
              break;
          }
          case WATCH_PLAYLIST: {
            //loop for playlists options
            while (1) {
                //print all playlists
            printPlaylists(playlists, playlistCounter);
            int chosenPlaylist;
              //check valid input
            do {
                scanf("%d", &chosenPlaylist);
                if ((chosenPlaylist-1) <= playlistCounter)
                    break;
                printf("Invalid option\n");
                printPlaylists(playlists, playlistCounter);
            } while (1);
              //minus one so we can use it with the pointer
              chosenPlaylist--;
              //if user chose back to main menu go back to main menu!
              if (chosenPlaylist == playlistCounter)
                  break;
            //print menu for playlist
            printf("Playlist %s\n", playlists[chosenPlaylist]->name);
            //loop for playlists options
            while (1) {
                int chosenAction;
                printPlaylistOptions();
                do {
                    scanf("%d", &chosenAction);
                    //if we have invalid reprint menu
                    if (chosenAction > AMOUNT_OF_OPTIONS_PLAYLISTS) {
                        printf("Invalid option\n");
                        printPlaylistOptions();
                    }

                    else
                        break;
                } while (1);
                //if user chose last option which is exit, get out of loop and go back to main loop
                if (chosenAction == AMOUNT_OF_OPTIONS_PLAYLISTS)
                    break;
                switch (chosenAction) {
                    //play a chosen song
                    case 1: {
                        //print all songs
                        printSongs(playlists, chosenPlaylist);
                        //loop for songs view
                        while (1) {
                            printf("choose a song to play, or 0 to quit:\n");
                            int chosenSong;
                            scanf("%d", &chosenSong);
                            //print chosen song and check if its valid song
                            if (chosenSong == 0 || playlists[chosenPlaylist]->songsNum < (chosenSong-1))
                                break;
                            //update streams
                            playlists[chosenPlaylist]->songs[chosenSong-1]->streams++;
                            printf("$ %s $\n", playlists[chosenPlaylist]->songs[chosenSong-1]->lyrics);
                        }
                        break;
                    }
                    //add song to playlist
                    case 2:{
                        Song *inputSong = malloc(sizeof(Song));
                        if (inputSong == NULL)
                            exit(1);
                        printf("Enter song's details\n");
                        printf("Title:\n");
                        inputSong->title = getString();
                        printf("Artist:\n");
                        inputSong->artist = getString();
                        printf("Year:\n");
                        scanf("%d", &inputSong->year);
                        printf("Lyrics:\n");
                        inputSong->lyrics = getString();
                        inputSong->streams = 0;
                        //make songs conntain another song
                        playlists[chosenPlaylist]->songs = realloc(playlists[chosenPlaylist]->songs,
                            playlists[chosenPlaylist]->songsNum * sizeof(Song*));
                        //set song to inputSong
                        playlists[chosenPlaylist]->songs[playlists[chosenPlaylist]->songsNum] = inputSong;
                        //add one to total songs
                        playlists[chosenPlaylist]->songsNum++;
                        break;
                    }
                    //delete a song
                    case 3: {
                        printSongs(playlists, chosenPlaylist);
                        printf("Choose a song to delete, or 0 to quit:\n");
                        int chosenSongToDelete;
                        scanf("%d", &chosenSongToDelete);
                        deleteSong(playlists, chosenPlaylist, chosenSongToDelete);
                        break;
                    }
                    //sort the playlists with what the user choses
                    case 4: {
                        printf("choose:\n");
                        printSortOptions();
                        sortPlaylists(playlists, chosenPlaylist);
                        break;
                    }
                    //play all playlist songs
                    case 5: {
                        for (int songs = 0; songs < playlists[chosenPlaylist]->songsNum; ++songs) {
                            //print title
                            printf("Now playing %s:\n", playlists[chosenPlaylist]->songs[songs]->title);
                            //print lyrics
                            printf("$ %s $\n", playlists[chosenPlaylist]->songs[songs]->lyrics);
                        }
                        break;
                    }

                }
            }
            }
            break;
          }
          case ADD_PLAYLIST: {
                printf("Enter playlist's name:\n");
                char* name = NULL;
                playlists =  realloc(playlists, sizeof(Playlist*) * (playlistCounter + 1));
                if (playlists == NULL) {
                    exit(1);
                }
                playlists[playlistCounter] = malloc(sizeof(Playlist));
                name = getString();
                playlists[playlistCounter]->name = name;
                playlists[playlistCounter]->songsNum = 0;
                playlists[playlistCounter]->songs = NULL;
                playlistCounter++;
                break;
          }
          //delete playlist
          case DELETE_PLAYLIST: {
              printPlaylists(playlists, playlistCounter);
              int deletePlaylistNumber;
              scanf("%d", &deletePlaylistNumber);

              if (deletePlaylistNumber-1 > playlistCounter)
                  break;
              deletePlaylist(playlists, deletePlaylistNumber, playlistCounter);
              playlistCounter--;
              break;
          }

          default:
              break;

      }
     }while(choice != 4);
}
