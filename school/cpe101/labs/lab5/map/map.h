#ifndef MAP_H
#define MAP_H

void square_all (double const input[], int size, double result []);

void add_n_all (double n, double const input[], int size, double result[]);

void distance_all (struct point const input[], int size, double result[]);

int are_positive (double const input[], int size, double result[]);

int are_greater_than (double n,double const input[],int size,double result[]);

int are_in_first_quadrant (struct point const input[], int size, struct point result[]);

double distance(struct point p1,struct point p2);

#endif 
