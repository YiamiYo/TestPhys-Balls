#ifndef Y_STRUCTS_H
#define Y_STRUCTS_H

typedef struct point {
	float X, Y;
} point;

typedef struct phys {
	float M;
	point N, V, A;
} phys;

#endif
