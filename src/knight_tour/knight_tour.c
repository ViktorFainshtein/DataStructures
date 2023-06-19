/*********************************
 * Reviewer: Sigal Horden
 * Author: Viktor Fainshtein
 * File Name: knight_tour.c
 * ******************************/
#include <stdio.h>  /*printf*/
#include "knight_tour.h"

typedef struct movement_lut
{
    position_t LUT[8];
}mov_lut;

static int Play(bit_array_t board, position_t position, int *path, mov_lut lut);
static int CalcPosition(int row, int col);
static int IsMoveLegit(bit_array_t board, position_t position);

static void WarndorffsAlgo(position_t position, int *path);
static int NextMove(bit_array_t *board, position_t *position, int *path, mov_lut lut);
static int MoveDegree(bit_array_t board, position_t position, mov_lut lut);
static int Neighbour(position_t position, position_t next_pos, mov_lut lut);

void KnightTour(position_t position, int *path)
{
    bit_array_t board = (__uint64_t)0;
    mov_lut lut = {{{1,-2}, {-1,-2}, {2,-1}, {-2,-1}, {2,1} , {-2,1}, {1,2}, {-1,2}}};
    int curr_pos = CalcPosition(position.x, position.y);
    board = BitArraySetOn(board, curr_pos);
    *path = curr_pos;

    WarndorffsAlgo(position, path);
/* 
    if(Play(board, position, ++path, lut) == 0)
    {
        printf("Solution does not exist");
    }
 */
}

static int Play(bit_array_t board, position_t position, int *path, mov_lut lut)
{
    int i = 0;
    int board_pos = 0;
    position_t pos = {0,0};
    if(BitArrayCountOn(board) == 64)
    {
        return 1;
    }

    for(i = 0; i < 8; i++)
    {
        pos.x = position.x + lut.LUT[i].x;
        pos.y = position.y + lut.LUT[i].y;
        board_pos = CalcPosition(pos.x, pos.y);

        if(IsMoveLegit(board, pos))
        {
            board = BitArraySetOn(board, board_pos);
            *path = board_pos;
            if(Play(board, pos, ++path, lut))
            {
                return 1;
            }
            else
            {
                board = BitArraySetOff(board, board_pos);
                *path = board_pos;
                --path;
            }
        }
    }
    return 0;
}

static int CalcPosition(int x, int y)
{
    return (y * sizeof(__uint64_t)) + x;
}

static int IsMoveLegit(bit_array_t board, position_t position)
{
    return ((position.x <= 7 && 
            position.x >= 0 && 
            position.y >= 0 && 
            position.y <= 7) && 
            ((BitArrayGetVal(board, CalcPosition(position.x, position.y)) == 0)
            ));
}

static void WarndorffsAlgo(position_t position, int *path)
{
    bit_array_t board = (__uint64_t)0;
    position_t next_pos = position;
    mov_lut lut = {{{1,2}, {2,1}, {-1,2}, {-2,1}, {-1,-2} , {-2,-1}, {1,-2}, {2,-1}}};
    int curr_pos = CalcPosition(position.x, position.y);
    int i = 0;
    board = BitArraySetOn(board, curr_pos);
    *path = curr_pos;
    for(i = 0; i < 63; ++i)
    {
        if(NextMove(&board, &position, ++path, lut) == 1)
        {
            printf("Solution does not exist");
        }
    }
    if(!Neighbour(position, next_pos, lut))
    {
        printf("Solution does not exist");
    }
}

static int NextMove(bit_array_t *board, position_t *position, int *path, mov_lut lut)
{
    int min_deg_idx = -1, c = 0, min_deg = (8+1);
    position_t next_pos = {0,0};
    int i = 0;
    int board_pos = 0;

    for(i = 0; i < 8; i++)
    {
        next_pos.x = position->x + lut.LUT[i].x;
        next_pos.y = position->y + lut.LUT[i].y;

        c = MoveDegree(*board, next_pos, lut);

        if(IsMoveLegit(*board, next_pos) && c < min_deg)
        {
            min_deg_idx = i;
            min_deg = c;
        }
    }

    if(min_deg_idx == -1)
    {
        return 1;
    }

    next_pos.x = position->x + lut.LUT[min_deg_idx].x;
    next_pos.y = position->y + lut.LUT[min_deg_idx].y;

    board_pos = CalcPosition(next_pos.x, next_pos.y);
    *board = BitArraySetOn(*board, board_pos);
    *path = board_pos;

    position->x = next_pos.x;
    position->y = next_pos.y;

    return 0;
}

static int MoveDegree(bit_array_t board, position_t position, mov_lut lut)
{
    int count = 0;
    int i = 0;
    for (i = 0; i < 8; ++i)
    {
        position.x += lut.LUT[i].x;
        position.y += lut.LUT[i].y;
        if (IsMoveLegit(board, position))
        {
            count++;
        }
        position.x -= lut.LUT[i].x;
        position.y -= lut.LUT[i].y;
    }    
    return count;
}

static int Neighbour(position_t position, position_t next_pos, mov_lut lut)
{
    int i = 0;
    for (i = 0; i < 8; ++i)
    {
        if (((position.x+lut.LUT[i].x) == next_pos.x)&&((position.y+ lut.LUT[i].y) == next_pos.y))
        {
            return 0;
        }
    }
    return 1;
}
