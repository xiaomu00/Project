#ifndef _PUBLIC_H_
#define _PUBLIC_H_
///////////////////////////////
////Í·ÎÄ¼þ ¡¢ºê

#include<iostream>
#include<assert.h>
#include<time.h>
#include<stdlib.h>
#include<memory.h>
#include<stdio.h>
using namespace std;

typedef unsigned char u_char;
typedef unsigned long u_long;


#define SEQLIST_DEFAULT_SIZE  30
#define ERR_EXIT(m) \
do\
{\
	perror(m); \
	exit(EXIT_FAILURE); \
}while (0)




#endif /*_PUBLIC_H_*/
