
#include "apple.h"

//Initialization
struct apple *init_apple() {
    apple *toReturn = NULL;

    toReturn = malloc(sizeof(apple));
    if (toReturn == NULL) /*Allocation failed */
        {
            exit(0);
        }

    //Randomize the position within the limits of the field
    toReturn->pos_x = rand() % 50;
    toReturn->pos_y = rand() % 60;

    //Choose a number between 0 and 100 and defines the apple_type
    int random_type = rand() % 100;

    if(random_type > 90) {
        toReturn->apple_type = 5;
        toReturn->apple_char = SPECIAL_APPLE;
        //Special apples can vanish after 10 moves by the snake
        toReturn->countdown = 10;

    } else {
        toReturn->apple_type = 1;
        toReturn->apple_char = NORMAL_APPLE;
        toReturn->countdown = -1;
    }

    return toReturn;
}





//----------------------GETTERS AND SETTERS----------------------//
int get_apple_pos_x(apple *currentApple) {
    return currentApple->pos_x;
}

int get_apple_pos_y(apple *currentApple) {
    return currentApple->pos_y;
}

int get_apple_type(apple *currentApple) {
    return currentApple->apple_type;
}

int get_countdown(apple *currentApple) {
    return currentApple->countdown;
}

void set_apple_pos_x(apple *currentApple, int x_to_set) {
    currentApple->pos_x = x_to_set;
}

void set_apple_pos_y(apple *currentApple, int y_to_set) {
    currentApple->pos_y = y_to_set;
}
//--------------------------------------------------------------//





//----------------------FUNCTIONS OF APPLE---------------------//
void decrease_countdown(apple *currentApple) {
    int countdown = currentApple->countdown;
    if(countdown > 0) {
        countdown--;
    }
}

void print_apple(apple *currentApple) {
    printf("Position de la pomme : %d, %d\n", currentApple->pos_x, currentApple->pos_y);
    printf("Countdown restant : %d\n", currentApple->countdown);
    printf("Caract�re de la pomme : %c\n", currentApple->apple_char);
    int type = currentApple->apple_type;
    if(type == 1) {
        printf("Type de la pomme : Normale\n");

    } else {
        printf("Type de la pomme : Sp�ciale\n");
    }
}
