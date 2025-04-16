#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arcfour.h>
#include <assert.h>

int8 *readkey(int8 *);
int main(int, char **);
