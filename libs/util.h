/*
-> File Description
-> 
*/

#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int validateInt(const char *prompt);
int validateString(const char *prompt, char *destination, int maxLenght);

#endif