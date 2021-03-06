#include "testAdrien.h"

void testCreationSnake()
{
    snakeList *test = createSnakeList(1, 1, north, 5);
    //    addSnakePartToList(test, createSnakePart(1, 2));
    printf("testb \n");

    printf("%d",test->length);

    int i = 1;
    while(i<20){
        if(shouldMove(test, &(test->countdown))){
            moveList(test);
            i++;

            if(8 == i){
                changeDirection(test, east);
                changeSpeed(test, test->speed-1);
                printf(" speed :%d ", test->speed);
            }

            if(11 == i){
                changeDirection(test, south);
                changeSpeed(test, test->speed-1);
                printf(" speed :%d ", test->speed);


            }

            if(14 == i){
                changeDirection(test, west);
                changeSpeed(test, test->speed-1);
                printf(" speed :%d ", test->speed);


            }

        printf("\n Direction=%d ", getDirection(test->direction));

        snakePart * tmp = test->snakeTail;
        while(tmp != NULL){
            printf(" %d %d ",tmp->x, tmp->y);
            tmp = tmp->nextSnakePart;
        }
    }
    }


    deletesnakeList(test);
    printf("Test");

    return 0;
}

void testCreationTable(){
    board * test=initBoard(1, 0);

    int y=0;
    while(y < constHeight){
        int x=0;
        while(x<constLength){
             printf("%c", readSquare(test, x, y));
             ++x;
        }
        printf("|\n");
        ++y;
    }

    printf("fin");
}


void testCreationSave(board * test){

    int y=0;
    while(y < constHeight){
        int x=0;
        while(x<constLength){
             printf("%c", readSquare(test, x, y));
             ++x;
        }
        printf("|\n");
        ++y;
    }

    printf("fin");
}

void testCreationSaveSnake(snakeList *test)
{
    //    addSnakePartToList(test, createSnakePart(1, 2));
    printf("testb \n");

    printf("%d :",test->length);

    int i = 1;

        snakePart * tmp = test->snakeTail;
        while(tmp != NULL){
            printf(" %d %d ",tmp->x, tmp->y);
            tmp = tmp->nextSnakePart;
        }

    return 0;
}
