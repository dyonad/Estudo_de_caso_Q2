#include "decode.h"

char* readFile() {
    FILE* file = fopen("message.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        perror("Error allocating memory");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';

    fclose(file);
    return buffer;
}

static const char base64_chars[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static int base64_decode_char(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c >= 'a' && c <= 'z') return c - 'a' + 26;
    if (c >= '0' && c <= '9') return c - '0' + 52;
    if (c == '+') return 62;
    if (c == '/') return 63;
    return -1;
}

char* base64(char* encoded_message) {
    int encoded_size = strlen(encoded_message);

    // Calcula o tamanho da mensagem decodificada
    int decoded_size = (encoded_size * 3) / 4;

    // Aloca memória para armazenar a mensagem decodificada
    char* decoded_message = (char*)malloc(decoded_size + 1);

    int i, j;
    int index = 0;

    for (i = 0; i < encoded_size; i += 4) {
        int sextet_a = base64_decode_char(encoded_message[i]);
        int sextet_b = base64_decode_char(encoded_message[i + 1]);
        int sextet_c = base64_decode_char(encoded_message[i + 2]);
        int sextet_d = base64_decode_char(encoded_message[i + 3]);

        int triple = (sextet_a << 18) | (sextet_b << 12) | (sextet_c << 6) | sextet_d;

        for (j = 0; j < 3 && index < decoded_size; j++, index++) {
            decoded_message[index] = (triple >> (16 - j * 8)) & 0xFF;
        }
    }

    // Adiciona um terminador de string
    decoded_message[decoded_size] = '\0';

    return decoded_message;
}

char* reverse(char* decoded_message) {
    int length = strlen(decoded_message);

    // Aloca memória para a mensagem invertida
    char* reversed_message = (char*)malloc(length + 1);

    if (reversed_message == NULL) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    int i, j;
    for (i = length - 1, j = 0; i >= 0; i--, j++) {
        reversed_message[j] = decoded_message[i];
    }

    // Adiciona um terminador de string
    reversed_message[length] = '\0';

    return reversed_message;
}