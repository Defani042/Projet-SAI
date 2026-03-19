#ifndef _POSITION_H_
#define _POSITION_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct s_position
{
    double x;
    double y;
    double z;
}s_position;

typedef s_position * position;

position creer_position(double x, double y , double z);

void liberer_position(position p);

#endif /*_POSITION_H_*/