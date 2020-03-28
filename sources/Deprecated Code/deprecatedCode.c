//
// Created by mondotosz on 14/03/2020.
//


//Header part

/*
#define BOATS_JSON "boats.json"
#define BOAT_LENGTH 'L'
#define BOAT_DIRECTION 'D'
#define BOAT_X 'X'
#define BOAT_Y 'Y'
#define BOAT_EXISTS 'E'

armada getArmada() ;


 */

/**
 * old function to get a fleet from a file
 * overcomplicated would only result on slowing down the code
 * it was interesting though
 * @return
 */
armada getArmada() {
    FILE *filePointer;
    char cursor;
    char tempString[MAX_NICKNAME_LENGTH];
    char currentVar;
    int currentBoat = 0;
    armada returnedArmada = {
            {
                    {"Destroyer", 2, 0, 0, HORIZONTAL, false},
                    {"Submarine", 3, 0, 0, HORIZONTAL, false},
                    {"Cruiser", 3, 0, 0, HORIZONTAL, false},
                    {"Battleship", 4, 0, 0, HORIZONTAL, false},
                    {"Carrier", 5, 0, 0, HORIZONTAL, false}
            },
            MAX_BOATS
    };


    //opens file
    filePointer = fopen(BOATS_JSON, "r");
    if (filePointer == NULL) {
        filePointer = fopen(BOATS_JSON, "w");
    } else {

        //gets the values in it
        strcpy(tempString, "");
        while (!feof(filePointer)) {
            do {
                fflush(stdin);
                fscanf(filePointer, "%c", &cursor);
            } while (cursor == ' ');
            //detects variable name
            if (cursor == '"') {
                //empty tempString
                strcpy(tempString, "");
                //get current variable
                do {
                    fflush(stdin);
                    fscanf(filePointer, "%c", &cursor);
                    if (cursor != '"') {
                        strncat(tempString, &cursor, 1);
                    }
                } while (cursor != '"');
                //on exit we get the var name
            }

            //translate chosen variable to a char usable in switch
            if (strcmp(tempString, "length") == 0) {
                currentVar = BOAT_LENGTH;
            } else if (strcmp(tempString, "direction") == 0) {
                currentVar = BOAT_DIRECTION;
            } else if (strcmp(tempString, "x") == 0) {
                currentVar = BOAT_X;
            } else if (strcmp(tempString, "y") == 0) {
                currentVar = BOAT_Y;
            } else if (strcmp(tempString, "exists") == 0) {
                currentVar = BOAT_EXISTS;
            } else {
                currentVar = ' ';
            }

            //if the variable is known then get its value
            if (currentVar != ' ') {
                do {
                    fflush(stdin);
                    fscanf(filePointer, "%c", &cursor);
                    //gets the value for the current variable
                    if (cursor == '"') {
                        strcpy(tempString, "");
                        do {
                            fflush(stdin);
                            fscanf(filePointer, "%c", &cursor);
                            if (cursor != '"') {
                                strncat(tempString, &cursor, 1);
                            } else {

                                //puts the value in the correct variable
                                switch (currentVar) {
                                    case BOAT_LENGTH:
                                        returnedArmada.boats[currentBoat].length = atoi(tempString);
                                        break;
                                    case BOAT_DIRECTION:
                                        returnedArmada.boats[currentBoat].direction = tempString[0];
                                        break;
                                    case BOAT_X:
                                        returnedArmada.boats[currentBoat].x = atoi(tempString) - 1;
                                        break;
                                    case BOAT_Y:
                                        returnedArmada.boats[currentBoat].y = atoi(tempString) - 1;
                                        break;
                                    case BOAT_EXISTS:
                                        if (strcmp(tempString, "true") == 0) {
                                            returnedArmada.boats[currentBoat].exists = true;
                                        }
                                        currentBoat++;
                                        break;
                                }

                                strcpy(tempString, "");
                            }
                        } while (cursor != '"');
                    }
                } while (cursor != '"');
            }

        }
    }
    fclose(filePointer);

    return returnedArmada;
}