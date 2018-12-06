#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

typedef struct Room{
	int id;
	char* name;
	char* type;
	int numConnections;
	struct Room* connections[6];	
}Room;

// Prototypes
void makeRoomsFromFile(Room* rms[]);
char* getNewestDir();
char* getFromFile(FILE* fileHandle, char* option);
int getNumConnFromFile(FILE* fileHandle);
void populateRoomArray(Room* rms[], DIR* rdir, char* prefix, char* path);
void initRoom(Room* rms[], int id, char* name, char* type, int numConn);
void populateConnections(Room* rms[], char* prefix, char* path);
void initConnections(Room* rms[], int id, FILE* fh);
int lookupByName(Room* rms[], char* query);
bool endRoomFound(Room* currentRoom);
void prompt(Room* currentRoom);
Room* getPlayerInput(Room* rms[], Room* currRoom);
bool isConnected(Room* self, char* playerInput);
void errorMsg();
void gameOverMsg(Room* rms[], int history[], int numSteps);

int main(){

    Room* rooms[7];
    Room* currRoom;
    Room* destination;

    int numSteps = 0;    
    // Generous history size for people who are terrible at mazes, like myself.    
    int history[128];
    for(int i = 0; i < 128; i++){
        history[i] = 8; // Init to a known impossible value, for debugging
    }

    // Populate rooms array with information from latest rooms directory    
    makeRoomsFromFile(rooms);
    
    // Establish starting room
    for(int i = 0; i < 7; i++){
        if(strcmp(rooms[i]->type, "START_ROOM") == 0){
            currRoom = rooms[i];
        }
    }
    
    do{   
        // Main game loop
        prompt(currRoom);
        destination = getPlayerInput(rooms, currRoom); 

        // If choice is valid, update history, number of steps, and current room
        if(destination != currRoom){
            history[numSteps] = destination->id;
            numSteps++;
            currRoom = destination;
        }

        // Loop only ends when END_ROOM is found
        if(endRoomFound(currRoom)){
            gameOverMsg(rooms, history, numSteps);            
            break;
        }
    }while(true);

    // Clean-up
    for(int i = 0; i < 7; i++){
        free(rooms[i]->name);
        free(rooms[i]->type);
        free(rooms[i]);
    }

    return 0;
}

void makeRoomsFromFile(Room* rms[]){
    char fullPath[512]; // Just to shut up gcc warnings. The max is about 50.       
     
    // Look in most recent directory    
    char* prefix = getNewestDir();
    memset(fullPath, '\0', 512);
    snprintf(fullPath, 512, "%s", prefix);
     
    DIR* roomsDir = opendir(fullPath);
    populateRoomArray(rms, roomsDir, prefix, fullPath);       
    closedir(roomsDir);
    populateConnections(rms, prefix, fullPath);
    free(prefix);
}

char* getFromFile(FILE* fileHandle, char* option){
    size_t maxLineSize = 40;
    char* currentLine = malloc(40);
    char* currentToken;
    int gl_rv;

    fseek(fileHandle, 0, SEEK_SET);
    
    if(strcmp(option, "NAME:") == 0 || strcmp(option, "TYPE:") == 0){
        char* char_attr = (char*) malloc(50);
        gl_rv = getline(&currentLine, &maxLineSize, fileHandle);

        while(gl_rv > 0){
            currentToken = strtok(currentLine, " "); 
            currentToken = strtok(NULL, " ");
            if(strcmp(currentToken, option) == 0){
            currentToken = strtok(NULL, " ");

                memset(char_attr, '\0', 50);
                strcpy(char_attr, currentToken);
                char_attr[strcspn(char_attr,"\n")] = 0;
                free(currentLine);
                return (void*) char_attr;
            }
            gl_rv = getline(&currentLine, &maxLineSize, fileHandle);
        }           
    }
}

int getNumConnFromFile(FILE* fileHandle){
    size_t maxLineSize = 40;
    char* currentLine = malloc(40);
    char* currentToken;
    int gl_rv;
    int connCount = 0;

    gl_rv = getline(&currentLine, &maxLineSize, fileHandle);
    while(gl_rv > 0){
        currentToken = strtok(currentLine, " ");
        if(strcmp(currentToken, "CONNECTION") == 0){
            connCount++;
        }
        gl_rv = getline(&currentLine, &maxLineSize, fileHandle);
    }
    free(currentLine);
    return connCount;    
}


void populateRoomArray(Room* rms[], DIR* rdir, char* prefix, char* fullPath){
    FILE* fH;
    struct dirent *currFile;
    int id, numConnections, i = 0;
    char* name;
    char* type;
    
    while(i < 7){
        currFile = readdir(rdir);
        if(currFile){    
            if(strcmp(currFile->d_name, ".") == 0 || 
                strcmp(currFile->d_name, "..") == 0){
                continue;
            }
            snprintf(fullPath, 512, "%s/%s", prefix, currFile->d_name);
             
            fH = fopen(fullPath, "r");
            if(fH == NULL){
                perror("Error opening room file for reading.\n");
            }
           
            id = i;   
            name = (char*) getFromFile(fH, "NAME:");
            numConnections = getNumConnFromFile(fH);
            type = (char*) getFromFile(fH, "TYPE:");

            initRoom(rms, i, name, type, numConnections);
            fclose(fH);
            i++;
        }
    }
}

// Basic constructor for a room
void initRoom(Room* rms[], int id, char* name, char* type, int numConn){
    rms[id] = malloc(sizeof(Room));
    if(rms[id] == NULL){
        perror("Malloc failed when init'ing room\n");
    }
    
    rms[id]->name = name;
    rms[id]->id = id;
    rms[id]->type = type;
    rms[id]->numConnections = numConn;
}

void populateConnections(Room* rms[], char* prefix, char* fullPath){
    FILE* fH;
    memset(fullPath, '\0', 512);
    snprintf(fullPath, 512, "%s", prefix);
    DIR* rdir = opendir(fullPath);
    struct dirent *currFile;
    int i = 0;
    while(i < 7){
        currFile = readdir(rdir);

        if(currFile){
            if(strcmp(currFile->d_name, ".") == 0 || 
                strcmp(currFile->d_name, "..") == 0){
                continue;
            }
            snprintf(fullPath, 512, "%s/%s", prefix, currFile->d_name);
          
            fH = fopen(fullPath, "r");
            if(fH == NULL){
                perror("Error opening room file for reading.\n");
            }
            
            initConnections(rms, i, fH);
            
            fclose(fH);
        }
        
        i++;
    }
    closedir(rdir);
}

// Glean connection information for an individual room
void initConnections(Room* rms[], int i, FILE* fh){
    int connToAdd, k = -1;
    char col1[15];
    char col2[10];
    char col3[25];

    while(fscanf(fh, "%s %s %s", col1, col2, col3) != EOF){
       if(strstr(col1, "CONNECTION")){
            connToAdd = lookupByName(rms, col3); 
            rms[i]->connections[k] = rms[connToAdd];
        }
        k++;
    }
}

int lookupByName(Room* rms[], char* query){
    for(int i = 0; i < 7; i++){
        if(strcmp(rms[i]->name, query) == 0){
            return i;        
        }
    }
}

// Returns newest directory with Adventure rooms in it
char* getNewestDir(){
    DIR* currentDir;
    struct dirent *currentFile;
    struct stat attributes;
    int mostRecent = 0;
    char* newestDir = malloc(50); 

    if(currentDir = opendir(".")){
        while(currentFile = readdir(currentDir)){
            if(strstr(currentFile->d_name, "huffj.rooms.")){       
                stat(currentFile->d_name, &attributes);
                
                if((int) attributes.st_mtime > mostRecent){
                    mostRecent = (int) attributes.st_mtime;
                    memset(newestDir, '\0', 50);
                    strcpy(newestDir, currentFile->d_name);
                }
            }
            currentFile = readdir(currentDir);
        }
    }
        
    closedir(currentDir);  
    return newestDir;
}

bool endRoomFound(Room* currentRoom){
    return strcmp(currentRoom->type, "END_ROOM") == 0;
}

void prompt(Room* currentRoom){
    printf("\nCURRENT LOCATION: %s\nPOSSIBLE CONNECTIONS:", currentRoom->name);
    for(int i = 0; i < currentRoom->numConnections; i++){
        printf(" %s", currentRoom->connections[i]->name);
        printf("%c", (i < currentRoom->numConnections - 1) ? ',' : '.');
    }
    printf("\nWHERE TO? >");
}

Room* getPlayerInput(Room* rms[], Room* currRoom){
    Room* destination = currRoom;
    char *playerInput;
    size_t inputSize = 25;

    // Get and validate player input
    playerInput = (char*) malloc(inputSize);
    if(playerInput == NULL){
        perror("Error creating user input buffer");
    }
    memset(playerInput, '\0', inputSize);
    getline(&playerInput, &inputSize, stdin);
    playerInput[strcspn(playerInput,"\n")] = 0;

    // Stay in current room unless dest is valid choice
    int valid = lookupByName(rms, playerInput);
    if((valid > -1) && (valid <  7) && isConnected(currRoom, playerInput)){
        destination = rms[valid];
    }else{
        errorMsg();
    }
    
    free(playerInput);
    return destination;
}

bool isConnected(Room* self, char* playerInput){
    for(int i = 0; i < self->numConnections; i++){
        if(strcmp(self->connections[i]->name, playerInput) == 0){
            return true;
        }
    }
    return false;
}

void errorMsg(){
    printf("\nHUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.\n");
}

void gameOverMsg(Room* rms[], int history[], int numSteps){	
	printf("\nYOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
	printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", numSteps);

    int visited; // Added for readability.
    for(int i = 0; i < numSteps; i++){
        visited = history[i];
        printf("%s\n", rms[visited]->name);
    }  
}











































/***********************************************************
*
* adventure.c
*
* -----------------
* Josh Huff 
* huffj@oregonstate.edu
* CS344 -- Summer 2017
* Program 2 Assignment
* -----------------
*
* Guide player through rooms created with buildroom.c
*
*************************************************************
#include <dirent.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

// ---- Struct code heavily borrowed from Block 2 - 2.1 page
struct Room{

   	int id;
   	char* name;
   	char* type;
   	int numConnections;
   	struct Room* connections[6];
};

// Array of pointers to Room structs
struct Room* roomStructArr[7];

// ---- Visited Piazza and followed Jacob Skinner's post about mutexes
// ---- Also feverishly watched 2.3 Lecture
//Create a mutex (global)
pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;

// Define a function of type void* for writing your time.
void* callTime(void* currentTime);

int main(){


	// At the beginning of the main function:
	// Lock the mutex
	pthread_mutex_lock(&myMutex);

	// Create a thread bound to the time-writing function
	pthread_t thread;
	int result = pthread_create(&thread, NULL, callTime, NULL);


	// General-purpose indices
	int i, j;

	// Instantiate room structs
	struct Room startRoom;
	struct Room midRoom1;
	struct Room midRoom2;
	struct Room midRoom3;
	struct Room midRoom4;
	struct Room midRoom5;
	struct Room endRoom;

	// Associate room structs with pointers in array
	roomStructArr[0] = &startRoom;
	roomStructArr[1] = &midRoom1;
	roomStructArr[2] = &midRoom2;
	roomStructArr[3] = &midRoom3;
	roomStructArr[4] = &midRoom4;
	roomStructArr[5] = &midRoom5;
	roomStructArr[6] = &endRoom;

	// ---- Adapted from 2.4 Manipulating Directories example	
	// Perform a stat() function call on rooms directories and open the one with most recent st_mtime component of the returned stat struct.
	int newestDirTime = -1; // Modified timestamp of newest subdir examined
	char targetDirPrefix[32] = "huffj.rooms."; // Prefix we're looking for
 	char newestDirName[256]; // Holds the name of the newest dir that contains prefix
 	memset(newestDirName, '\0', sizeof(newestDirName));

  	DIR* dirToCheck; // Holds the directory we're starting in
  	struct dirent *fileInDir; // Holds the current subdir of the starting dir
  	struct stat dirAttributes; // Holds information we've gained about subdir

  	dirToCheck = opendir("."); // Open up the directory this program was run in

  	if (dirToCheck > 0){
    
		while ((fileInDir = readdir(dirToCheck)) != NULL){

	    	if (strstr(fileInDir->d_name, targetDirPrefix) != NULL){
        
        		stat(fileInDir->d_name, &dirAttributes);

        		if ((int)dirAttributes.st_mtime > newestDirTime){

	          		newestDirTime = (int)dirAttributes.st_mtime;
          			memset(newestDirName, '\0', sizeof(newestDirName));
          			strcpy(newestDirName, fileInDir->d_name);
        		}
      		}
    	}
  	}

  	closedir(dirToCheck); // Close the directory we opened

 	// Read all files from this directory
	char* scrapeDirectory;
	scrapeDirectory = malloc(sizeof(char) * 256);

	// Set scrapeDirecory up to be the prefix for each file accessed
	memset(scrapeDirectory, '\0', 256);
	strcat(scrapeDirectory, "./");
	strcat(scrapeDirectory, newestDirName);


	// ---- This required a few lengthy visits to StackOverflow
	DIR* roomsDir;
	char* directorySeparator = "/";
	FILE* datadump;
	int loopcount = 0;

	// Read this particular file
	char* scrapeFile;
	scrapeFile = malloc(sizeof(char) * 256);

	char* dataBuffer;
	dataBuffer = malloc(sizeof(char) * 256);

	roomsDir = opendir(scrapeDirectory);
	
	if (roomsDir > 0){

		while((fileInDir = readdir(roomsDir)) != NULL){

			// ---- Stack Overflow suggested readdir checks . and .. first, but it LIED
			// So this safeguards against the fileInDir pointer giving us directories
			if(	(strcmp(fileInDir->d_name, ".") == 0) || 
				(strcmp(fileInDir->d_name, "..") == 0)	){

				continue;
			}

			// Reset scrapeFile and have it receive the new file's information
			memset(scrapeFile, '\0', 256);
			strcat(scrapeFile, scrapeDirectory);
			strcat(scrapeFile, directorySeparator);
			strcat(scrapeFile, fileInDir->d_name);
			
			datadump = fopen(scrapeFile, "r");

			// Each valuable token is the third on the line	
			for(i = 0; i < 3; i++){

				fscanf(datadump, "%s", dataBuffer);	
			}
			
			roomStructArr[loopcount]->id = loopcount;
			
			roomStructArr[loopcount]->name = calloc(25, sizeof(char));
			memset(roomStructArr[loopcount]->name, '\0', 25);
			strcpy(roomStructArr[loopcount]->name, dataBuffer);

			// After the name is read, connections are treated slightly differently.
			// Using a count and strcmp, determine how many connections there are and populate struct with them
			int connectionCount = 0;
			bool reachedType = false;
			do{

				fscanf(datadump, "%s", dataBuffer);
				if( (strcmp("CONNECTION", dataBuffer) == 0) ){
				
					for(i = 0; i < 2; i++){
					
						fscanf(datadump, "%s", dataBuffer);
					}
					
					// As shamedful as it is, I don't know how to fix this other than to open up a second file and repeat the above.
					//strcpy(roomStructArr[loopcount]->connections[connectionCount]->name, dataBuffer);					
						
					connectionCount++;
				}

				else{
					
					reachedType = true;
				}

			}while(!reachedType);

			roomStructArr[loopcount]->numConnections = connectionCount;
	
			// Finally, get the type.
            for(i = 0; i < 3; i++){

                fscanf(datadump, "%s", dataBuffer);
            }
			
			roomStructArr[loopcount]->type = calloc(25, sizeof(char));
			strcpy(roomStructArr[loopcount]->type, dataBuffer);
								
			loopcount++;	

		}

		fclose(datadump);
		closedir(roomsDir);
	}

	// I know this is probably unnecessary duplication, and thus bad style, but I'm struggling to get this complete.
	loopcount = 0;
	roomsDir = opendir(scrapeDirectory);
   
    if (roomsDir > 0){

        while((fileInDir = readdir(roomsDir)) != NULL){
   
            // ---- Stack Overflow suggested readdir checks . and .. first, but it LIED
            // So this safeguards against the fileInDir pointer giving us directories
            if( (strcmp(fileInDir->d_name, ".") == 0) || 
                (strcmp(fileInDir->d_name, "..") == 0)  ){
                
                continue;
            }
   
            // Reset scrapeFile and have it receive the new file's information
            memset(scrapeFile, '\0', 256);
            strcat(scrapeFile, scrapeDirectory);
            strcat(scrapeFile, directorySeparator);
            strcat(scrapeFile, fileInDir->d_name);
   
            datadump = fopen(scrapeFile, "r");

            // Each valuable token is the third on the line 
            for(i = 0; i < 3; i++){

                fscanf(datadump, "%s", dataBuffer);
            }

			bool reachedType = false;
			int connectionCount = 0;
        	char* connectionName;
			connectionName = malloc(sizeof(char) * 32);
			memset(connectionName, '\0', 32);
			 
		    do{

                fscanf(datadump, "%s", dataBuffer);
                if( (strcmp("CONNECTION", dataBuffer) == 0) ){
   
                    for(i = 0; i < 2; i++){
   
                        fscanf(datadump, "%s", dataBuffer);
                    }
   
                	for(i = 0; i < 7; i++){
						strcpy(connectionName, roomStructArr[i]->name);

						if( strcmp(connectionName, dataBuffer) == 0 ){

							roomStructArr[loopcount]->connections[connectionCount] = roomStructArr[i];	
							connectionCount++;
						}		
					}
				}

                else{

                    reachedType = true;
                }

            }while(!reachedType);
            
			loopcount++;		
		}

		// Re-order array so 0 is start and 6 is end
		for(i = 1; i < 7; i++){

				struct Room* temp;		
				int tempID;

				// If everything is in its place, skip the loop altogether.
				if(	strcmp(roomStructArr[0]->type, "START_ROOM") == 0 &&
					strcmp(roomStructArr[6]->type, "END_ROOM") == 0	){
				
					break;
				}


				// Otherwise, the structs and their IDs must be swapped.
				if(strcmp(roomStructArr[i]->type, "START_ROOM") == 0){

					temp = roomStructArr[0];
					roomStructArr[0] = roomStructArr[i];		
					roomStructArr[i] = temp;

					tempID = roomStructArr[0]->id;
					roomStructArr[0]->id = roomStructArr[i]->id;
					roomStructArr[i]->id = tempID;
				}
			
				// Otherwise, the structs and their IDs must be swapped.
				if(strcmp(roomStructArr[i]->type, "END_ROOM") == 0){

					temp = roomStructArr[6];
					roomStructArr[6] = roomStructArr[i];		
					roomStructArr[i] = temp;

					tempID = roomStructArr[6]->id;
					roomStructArr[6]->id = roomStructArr[i]->id;
					roomStructArr[i]->id = tempID;
				}

			}
		}

****************************************
*
* We can finally play the game!
*
*****************************************
	struct Room* currentRoom = roomStructArr[0];
		
	bool gameOver = false;
	bool IsValidLocation = false;	
	bool timeCalled = false;
	int playerSteps = 0;
	struct Room* pathHistory[36];

	// ---- Had help from lecture 2.4 and a C For Dummies blog page. No shame.
	char* userInputBuffer = NULL;	
	size_t bufferSize = 26;
	size_t numCharsEntered;

	// Function Prototypes
	void printLocations();
	void prompt();
	void errorMsg();

	while(!gameOver){

		// Loops the prompt until user provides something valid
		if(timeCalled){

			timeCalled = false;
			prompt();
		}

		else{

			printLocations(currentRoom);
			prompt();
		}

		// Get the last position of the user input string and null terminate it
		numCharsEntered = getline(&userInputBuffer, &bufferSize, stdin);			
		userInputBuffer[numCharsEntered - 1] = '\0';

		// Time requires special output, and avoids showing locations again
		if(strcmp(userInputBuffer, "time") == 0 ){
	
		// Whenever the user inputs time:
			// Unlock the mutex, allowing the thread to run
			pthread_mutex_unlock(&myMutex);			

			// Join to the time-writing thread, allowing it to complete before continuing your main thread
			
			// Lock the mutex
						

			// Create another thread bound to the time-writing function, which will block until the mutex is unlocked

			printf("\n");
			printf("time has been called.\n");
			printf("\n");
			//call time 
			timeCalled = true;
		}

		// If it's not time, then it is either a valid room or not.
		else {				
				
			// Reset validity
			IsValidLocation = false;
				
			for(i = 0; i < currentRoom->numConnections; i++){

				// If the input matches a connection name, it is valid	
				if(strcmp(userInputBuffer, currentRoom->connections[i]->name) == 0){
						
					// Update path history
					pathHistory[playerSteps] = currentRoom;

					// Update step count
					playerSteps++;
						
					// Set new current room
					currentRoom = currentRoom->connections[i];	
	
					// If new current room is end, switch game to over 	
					if(currentRoom->id == 6){

						gameOver = true;
						
					}
					printf("\n");
					IsValidLocation = true;
					break;	
					
					// Otherwise, it's not valid. Post the errorMsg and let them try again.	
					if(!IsValidLocation){

						errorMsg();
						
					}			
				}
			
			}
		}
	}	

	// Game over stuff happens here.
	printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
	printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", playerSteps);	
	for(i = 0; i < playerSteps; i++){

		printf("%s\n", pathHistory[i]->name);		
	}
	printf("%s\n", currentRoom->name);



	return 0;
}

// Function Definitions
void printLocations(struct Room* currentRoom){
			
	printf("CURRENT LOCATION: %s\n",currentRoom->name);		
	printf("POSSIBLE CONNECTIONS: ");

	int i;
	for(i = 0; i < currentRoom->numConnections; i++){

		if(i == 0){

			printf("%s", currentRoom->connections[i]->name);
		}			
	
		else{

			printf(", %s",currentRoom->connections[i]->name);	
		}
	}
	
	printf("\n");
}

void prompt(){

	printf("WHERE TO? >");
}

void errorMsg(){

	printf("\nHUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.\n");
}

// ---- Consulted tutorialspoint.com entry for strftime
void* callTime(void* argument){

	// It's really important to put a lock on the mutex first thing when this function is called.
	pthread_mutex_lock(&myMutex);

	time_t rawTime;
	struct tm* info;
	char buffer[80];

	time (&rawTime);

	info = localtime(&rawTime);

	// Render 1:03pm, Tuesday, September 13, 2016
	//"%I:%M%P, %A, %B %d, %Y" 
	strftime(buffer, 80, "%I:%M%P, %A, %B %e, %Y", info);
	printf("%s", buffer);

	pthread_mutex_unlock(&myMutex);
	return NULL;
	
}
*/

