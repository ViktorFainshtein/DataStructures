/*********************************
 * Reviewer:  
 * Author: Viktor Fainshtein
 * File Name: knight_tour.h
 * ******************************/

#ifndef __KNIGHT_TOUR_H__
#define __KNIGHT_TOUR_H__

#include <stddef.h>		/* __uint64_t */
#include <stdint.h>		/* __uint64_t */
#include "bit_array.h"

typedef struct position
{
	int x;
	int y;
} position_t;

void KnightTour(position_t position, int *path);

#endif /* __KNIGHT_TOUR_H__ */
