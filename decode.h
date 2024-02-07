#ifndef DECODE_H
#define DECODE_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "decode.c"

char* readFile();
char* base64(char* encoded_message);
char* reverse(char* decoded_message);

#endif