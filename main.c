#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decode.h"

int main() {
    char* encoded_message = readFile();
    char* decoded_message = base64(encoded_message);
    char* reversed_message = reverse(decoded_message);

    printf("Message.txt: %s\n", encoded_message);
    printf("Decoded Message: %s\n", decoded_message);
    printf("Reversed Message: %s\n", reversed_message);

    system("pause");

    free(encoded_message);
    free(decoded_message);
    free(reversed_message);

    return 0;
}