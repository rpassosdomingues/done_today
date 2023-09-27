#ifndef HORSEWALK_H
#define HORSEWALK_H

#include <stdbool.h>

/**
 * Each node represents a position
 * on the chessboard that the knight visited.
 * - This struct has x and y coordinates, and
 * - pointers to the next and previous node in the list.
*/
typedef struct horse {
    int x, y;
    struct horse *next, *prev;
    int moves[8][2];
} Horse;

Horse* newHouse (int x, int y);
void addHouse (Horse** head, int x, int y);
void printList (Horse* head);
void addEnd (Horse* start, int x, int y);
int validMove(int x, int y, int M, int N);
int countTripsClosed (Horse horse, int M, int N, bool **chessboard);
int allHouses (int** visited, int M, int N);

bool **readInstance(int instance_num);
void calculatesTrips(bool **chessboard);

#endif // HORSEWALK_H