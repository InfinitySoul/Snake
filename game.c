#include <stdio.h>
#include <stdlib.h>

#include "game.h"

game* init_game(snakeList * snake, board * map, int lives) {
    game *toReturn = NULL;

    toReturn = malloc(sizeof(game));
    if (toReturn == NULL) /*Allocation failed */
        {
            exit(0);
        }

    if(snake == NULL)toReturn->snake = createSnakeList(2, 2, rand()%4, 3);
    else toReturn->snake = snake;

    if(NULL == map)toReturn->game_map = initBoard(1, 0);
    else toReturn->game_map = map;

    if(NULL == lives)toReturn->lives = 3;
    else toReturn->lives = lives;

    return toReturn;
}

void launch_game(int walls_on, int borders_on, int start_speed, int increasing_speed_on, game* game) {
    print_map(game->game_map);
    print_interface();

    //Creates the snake in data and outputs it
    gotoligcol(get_snake_y(game->snake), get_snake_x(game->snake));
    printf("#");
    setElementAtPosition(game->game_map, '#', get_snake_x(game->snake), get_snake_y(game->snake));

    //Creates an apple in data and outputs it. Keeps the old position of the snake and if the user chose to quit
    apple *current_apple = create_new_apple(game->game_map);
    int old_position_x, old_position_y;
    int quit = 0;
    int score = 0;
    int lives = 3;
    int allowed_to_move = 0;

    while(score < 40 && lives > 0 && !quit) {

        old_position_x = get_snake_x(game->snake);
        old_position_y = get_snake_y(game->snake);
        char testlol3 = readSquare(game->game_map, 3, 4);

        if(_kbhit()) {

            int key = _getch();

            switch(key) {
                case KEY_SAVE: printf("Save :D\n"); break;
                case KEY_LOAD: printf("Load :O\n"); break;
                case KEY_QUIT: quit = 1; break;
                case KEY_PAUSE: getch(); break;
                case KEY_UP: changeDirection(game->snake, north); break;//Changer par changeDirection du Snake
                case KEY_DOWN: changeDirection(game->snake, south); break;
                case KEY_LEFT: changeDirection(game->snake, west); break;
                case KEY_RIGHT: changeDirection(game->snake, east); break;
            }
        }

        allowed_to_move = canMove(game->snake, game->game_map);

        if(allowed_to_move) {

            if(shouldMove(game->snake, &(game->snake->countdown))) {

                //Checks if the next square is an apple. If so, adds a part to the snake.
                if(is_square_apple(game->game_map, old_position_x+(game->snake->direction->x), old_position_y+(game->snake->direction->y))) {
                    score += get_apple_type(current_apple);
                    update_score(score);

                    //Erases the apple
                    setElementAtPosition(game->game_map, ' ', old_position_x+(game->snake->direction->x), old_position_y+(game->snake->direction->y));

                    //Adds as much part to the snake as needed
                    int i;
                    for(i = 0; i < get_apple_type(current_apple); i++) {
                        addPartToList(game->snake, game->snake->snakeTail->x, game->snake->snakeTail->y);
                    }

                    //Creates a new apple and outputs it
                    free(current_apple);
                    current_apple = create_new_apple(game->game_map);

                    //Outputs the new part of the snake
                    gotoligcol(get_snake_y(game->snake), get_snake_x(game->snake));
                    printf("#");
                } else {
                    //Makes the snake move
                    moveList(game->snake);
                }

                update_snake_data_output(game);
            }
        } else if(getDirection(game->snake->direction) != none_dir) {
            changeDirection(game->snake, none_dir);
            lives--;
            update_lives(lives);
        }
    }
}

int canMove(snakeList *snake, board *map) {
    int canMove = 0;

    //Gets the position and direction of the snake
    int position_x = get_snake_x(snake);
    int position_y = get_snake_y(snake);

    //Check the next square in data
    char nextSquare = readSquare(map, position_x+(snake->direction->x), position_y+(snake->direction->y));

    //Checks if it is anything but a wall or the snake itself
    if(nextSquare != 35) {
        canMove = 1;
    }

    return canMove;
}

int is_square_apple(board *table, int pos_x, int pos_y) {
    int is_it_apple = 0;

    //Reads the square gave by the arguments
    char square = readSquare(table, pos_x, pos_y);

    //Checks if it is an apple
    if(square == NORMAL_APPLE || square == SPECIAL_APPLE) {
        is_it_apple = 1;
    }

    return is_it_apple;
}

//Creates a new apple on the board and outputs it
apple* create_new_apple(board *table) {
    //Initializes an apple
    apple *current_apple = init_apple(table);

    //Sets in data its position, passing its character
    setElementAtPosition(table, get_apple_char(current_apple), get_apple_pos_x(current_apple), get_apple_pos_y(current_apple));

    //Outputs the apple
    gotoligcol(get_apple_pos_y(current_apple), get_apple_pos_x(current_apple));
    printf("%c", get_apple_char(current_apple));

    return current_apple;
}

void update_snake_data_output(game* game) {
    //Puts the character in the data table, and checks if it really did
    setElementAtPosition(game->game_map, '#', get_snake_x(game->snake), get_snake_y(game->snake));

    //Sets the cursor where the snake will be and output a character
    gotoligcol(get_snake_y(game->snake), get_snake_x(game->snake));
    printf("#");

    //Same logic to erase the tail
    setElementAtPosition(game->game_map, ' ', game->snake->snakeTail->x, game->snake->snakeTail->y);
    gotoligcol(game->snake->snakeTail->y, game->snake->snakeTail->x);
    printf(" ");
}
