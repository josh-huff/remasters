//
#include <stdio.h>
#include <time.h>


typedef struct{
	int id;
	char* name;
	char* type;
	int numConnections;
	struct Room* connections[6];	
}Room;

// Hard-coded pool of names
char* roomNames[] = {
    "Gazorpazorp", "C-137", "Cronenberg_World", "Blips_and_Chitz", 
    "Anatomy_Park", "Planet_Squanch", "Greasy_Grandma_World", 
    "Interdimensional_Customs", "Citadel_of_Ricks", "Gromflom_Prime"
};

// Room types -- one start, one end, and five middle rooms.
char* roomTypes[] = {
    "START_ROOM", "MID_ROOM", "END_ROOM"
};

// Prototypes
void initRooms(Room* rms[]);

int main(){

	srand(time(NULL));

    Room* rooms[7];
    initRooms(&rooms);

    return 0;
}

/*

Each file that stores a room must have exactly this form, where the … is additional room connections, as randomly generated:

ROOM NAME: <room name>
CONNECTION 1: <room name>
…
ROOM TYPE: <room type>
    
    The method of choosing the number of connections beforehand 
    that each room will have is not recommended, 
    as it's hard to make those chosen numbers match the constraints. 
*/

/*
void initRooms(Room* rms[]){
    int nameTaken[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int name, type;
    
    for(int i = 0; i < 7; i++){
        rms[i] = malloc(sizeof(Room));
        if(rms[i] == NULL){
            perror("Malloc failed when init'ing room %d\n", i);
        }

        // Choose a unique name at random
        while(true){
            name = rand() % 10;
            if(!nameTaken[name]){
                nameTaken[name] = 1;
                break;
            }
        }

        // Make first room start, last room end, all others middle
        switch(i){
            case 0:
                type = 0; // make it startroom
                break;
            case 6:            
                type = 2; // make it endroom
                break;
            default:
                type = 1; // make it midroom
        }
        
        rms[i]->name = roomNames[name]; // Might have to strcpy() instead
        rms[i]->id = i;
        rms[i]->type = roomTypes[type];
        rms[i]->numConnections = 0;        
    }
}

isConnected(); // Because a room can't connect to another room more than once
isSelf(); // Because a room can't connect to itself.
isAvailable();
connectRooms(roomA, roomB){

    // if room A connects to room B, 
    // then room B must have a connection back to room A
    connectTo(roomA, roomB);
    connectTo(roomB, roomA);
}
connectTo(roomA, roomB);
*/
void initRooms(Room* rms[]){
    int nameTaken[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int name, type;
    
    for(int i = 0; i < 7; i++){
        rms[i] = malloc(sizeof(Room));
        if(rms[i] == NULL){
            perror("Malloc failed when init'ing room %d\n", i);
        }

        // Choose a unique name at random
        while(true){
            name = rand() % 10;
            if(!nameTaken[name]){
                nameTaken[name] = 1;
                break;
            }
        }

        // Make first room start, last room end, all others middle
        switch(i){
            case 0:
                type = 0; // make it startroom
                break;
            case 6:            
                type = 2; // make it endroom
                break;
            default:
                type = 1; // make it midroom
        }
        
        rms[i]->name = roomNames[name]; // Might have to strcpy() instead
        rms[i]->id = i;
        rms[i]->type = roomTypes[type];
        rms[i]->numConnections = 0;        
    }
}


















/************************************************************
*
* buildroom.c
*
* -----------------
* Josh Huff 
* huffj@oregonstate.edu
* CS344 -- Summer 2017
* Program 2 Assignment
* -----------------
*
* Generate 7 different room files, one room per file, in a directory called "huffj.rooms.[PID]",
* where [PID] is the process ID of running instance of buildroom.c 
*
************************************************************
#include <fcntl.h>
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

// Global Variables (usually a no-no, but okay-ed for this assignment)

// Hard-coded pool of names
char* roomNames[] = {	"Gazorpazorp", "C-137", "Cronenberg_World", "Blips_and_Chitz", "Anatomy_Park", "Planet_Squanch", 
						"Greasy_Grandma_World", "Interdimensional_Customs", "Citadel_of_Ricks", "Gromflom_Prime"
};

// Room types -- one start, one end, and five middle rooms.
char* roomTypes[] = {"START_ROOM", "MID_ROOM", "MID_ROOM", "MID_ROOM", "MID_ROOM", "MID_ROOM", "END_ROOM"};

// Array of pointers to Room structs
struct Room* roomStructArr[7]; 

// ---- Functions provided by 2.2 Program Outlining
// Function Declarations (Definitions after main)
bool IsGraphFull();
void AddRandomConnection();
bool IsConnected(struct Room* x, struct Room* y);
struct Room* GetRandomRoom();
bool CanAddConnectionFrom(struct Room* x);
void ConnectRoom(struct Room* x, struct Room* y);
bool IsSameRoom(struct Room* x, struct Room* y);

int main(){

	// General purpose indices. I miss C99 already.
	int i, j;	

	// Seeds random number generator
	srand(time(NULL));

	// Instantiate room structs
	struct Room startRoom;
	struct Room midRoom1;
	struct Room midRoom2;
	struct Room midRoom3;
	struct Room midRoom4;
	struct Room midRoom5;
	struct Room endRoom;

	// Associate structs with global array
	roomStructArr[0] = &startRoom;
	roomStructArr[1] = &midRoom1;
	roomStructArr[2] = &midRoom2;
	roomStructArr[3] = &midRoom3;
	roomStructArr[4] = &midRoom4;
	roomStructArr[5] = &midRoom5;
	roomStructArr[6] = &endRoom;


********
*
* Generate Directory For Room Files		
*
********
	
	// Prepare the whole directory path string
	// Size should be equal to 14 characters from prefix, up to 5 characters from the PID, and the null terminator	
	char dirPath[20];
	memset(dirPath, '\0', 20);

	// Directory prefix includes 14 characters, plus null terminator.
	char dirPrefix[15] = "./huffj.rooms.\0"; 	
	strcat(dirPath, dirPrefix);
	
	// Get pid as an int and prepare the string version of the process id
	int pid = getpid();
	char strPid[6];
	memset(strPid, '\0', 6);	

	// Create string version of pid, then concatenate it to the whole dirPath
	snprintf(strPid, sizeof(strPid), "%d", pid);	
	strcat(dirPath, strPid);
		
    // Create directory with the new string
	mkdir(dirPath, 0755);

********
*
* Generate Individual Rooms		
*
********

	// "7 out of the 10 room names will be used." 
	char* roomsToBeGenerated[7];

	// "Have the rooms program randomly assign a room name to each one."
	// Array of rooms actually chosen to be generated
	// Note to self: This can probably be modularized and used for pairing rooms too?
	int choice;
	int is_unique;
	for (i = 0; i < 7; i++){

		// "A room name cannot be used in more than one room."
		// This do-while only assigns the room number if the random choice doesn't appear in the array.	
		do{

			is_unique = 1;	
			choice = rand() % 10; 
		
			// Search the current contents of roomsToBeGenerated and switch off the unique flag if the random choice is present.	
			for(int j = 0; j < i; j++){

				if(strcmp(roomsToBeGenerated[j], roomNames[choice]) == 0){
					is_unique = 0;
					break;
				}
			}
	
		}while (is_unique == 0);
		
		// If the random choice is new, update the room array 
		roomsToBeGenerated[i] = roomNames[choice];	
	}	

	
	// Using global array, populate each struct's members
	for(i = 0; i < 7; i++){

		roomStructArr[i]->id = i;
		roomStructArr[i]->name = calloc(25, sizeof(char));
		roomStructArr[i]->numConnections = 0;
		strcpy(roomStructArr[i]->name, roomsToBeGenerated[i]);
		roomStructArr[i]->type = calloc(11, sizeof(char));
		strcpy(roomStructArr[i]->type, roomTypes[i]);
	}


	// Create all connections in graph
	while (!IsGraphFull()){

		AddRandomConnection();
	}

*********
*
*  Write Room Struct Information to Room Files		
*
*********

	// ---- Adapted from code found in Lecture 2.4 
	FILE* fileHandle;
	char* filePath;
	char* individualFile;
	char* directorySeparator = "/";
	char* roomTag = "_room";

	filePath = malloc(sizeof(char) * 51);	
	individualFile = malloc(sizeof(char) * 31);

	// For each element of roomsToBeGenerated,
	// memset the components need to create filePath,
	// then create a file and write the struct info to it
	for(i = 0; i < 7; i++){

		memset(filePath, '\0', 51);	
		memset(individualFile, '\0', 31);

		strcat(filePath, dirPath);
		strcat(filePath, directorySeparator);	
		strcat(individualFile, roomsToBeGenerated[i]);
		strcat(filePath, individualFile);
		strcat(filePath, roomTag);

		fileHandle = fopen(filePath, "w");

		// Write Room Name to respective files
		fprintf(fileHandle, "ROOM NAME: %s\n", roomStructArr[i]->name);	

		// Write number of connections
		for(j = 0; j < roomStructArr[i]->numConnections; j++){

			fprintf(fileHandle, "CONNECTION %d: %s\n", j + 1, roomStructArr[i]->connections[j]->name);
		}

		// Write Room type
		fprintf(fileHandle, "ROOM TYPE: %s\n", roomStructArr[i]->type); 		

		fclose(fileHandle);
	}

	// Clean-up
	for(i = 0; i < 7; i++){

		free(roomStructArr[i]->name);
		free(roomStructArr[i]->type);	
	}

	free(filePath);
	free(individualFile);
	
	return 0;
}	



// Function Definitions
// Returns true if all rooms have 3 to 6 outbound connections, false otherwise
bool IsGraphFull(){

	int i;
	for(i = 0; i < 7; i++){
	
		if(roomStructArr[i]->numConnections < 3){
		
			return false;
		}
	}
	 
	return true;
}

// Adds a random, valid outbound connection from a Room to another Room
void AddRandomConnection(){

	struct Room* A = malloc(sizeof(struct Room));
	struct Room* B = malloc(sizeof(struct Room));

  	while(true){
    
		A = GetRandomRoom();

    	if (CanAddConnectionFrom(A) == true)
     		break;
  	}

  	do{
    
		B = GetRandomRoom();
	

	// A room cannot connect to itself, nor can a room connect to another room more than once.
  	}while(CanAddConnectionFrom(B) == false || IsSameRoom(A, B) == true || IsConnected(A, B) == true);

  	ConnectRoom(A, B);
  	ConnectRoom(B, A);

}

// A helper function to ensure the same room is not connected to multiple times
bool IsConnected(struct Room* x, struct Room* y){

	int i;
	for(i = 0; i < x->numConnections; i++){

		if (strcmp(x->connections[i]->name, y->name) == 0){

			return true;
		}
	}		

	return false;
}

// Returns a random Room, does NOT validate if connection can be added
struct Room* GetRandomRoom(){

	int randomNum = rand() % 7;

	return roomStructArr[randomNum];
}

// Returns true if a connection can be added from Room x, false otherwise
bool CanAddConnectionFrom(struct Room* x){


	if(x->numConnections < 6){

		return true;
	}

	return false;
}

// Connects Rooms x and y together, does not check if this connection is valid
void ConnectRoom(struct Room* x, struct Room* y){

	x->connections[x->numConnections] = y;
	x->numConnections++;	
}

// Returns true if Rooms x and y are the same Room, false otherwise
bool IsSameRoom(struct Room* x, struct Room* y){

	if(x->id == y->id){

		return true;
	}

	return false; 	
}
// End of Functions
// EOF
*/

