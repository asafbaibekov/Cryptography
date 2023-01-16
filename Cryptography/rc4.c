//
//  rc4.c
//  Cryptography
//
//  Created by Asaf Baibekov on 13/01/2023.
//

#include "rc4.h"

void swap_uint8_t(uint8_t *a, uint8_t *b) {
	uint8_t temp = *a;
	*a = *b;
	*b = temp;
}

void print_key_stream(uint8_t *keystream) {
	for (int i = 0 ; i < (UINT8_MAX + 1); i++)
		printf("%02x ", keystream[i]);
	printf("\n");
}

uint8_t *RC4_init(char *key) {
	if (key == NULL) return NULL;
	size_t key_size = strlen(key);
	if (key_size > (UINT8_MAX + 1)) return NULL;
	
	uint8_t *array = malloc(sizeof(uint8_t) * (UINT8_MAX + 1));
	uint8_t *key_array = malloc(sizeof(uint8_t) * (UINT8_MAX + 1));
	for (int i = 0; i <= UINT8_MAX; i++) {
		array[i] = i;
		key_array[i] = key[i % key_size];
	}
	
	for (int i = 0, j = 0; i <= UINT8_MAX; i++) {
		j = (j + array[i] + key_array[i]) % (UINT8_MAX + 1);
		swap_uint8_t(&array[i], &array[j]);
	}
	free(key_array);
	
	uint8_t *keyStream = malloc(sizeof(uint8_t) * (UINT8_MAX + 1));
		
	for (int i = 0, j = 0, size = 0; size < (UINT8_MAX + 1); size++) {
		i = (i + 1) % (UINT8_MAX + 1);
		j = (j + array[i]) % (UINT8_MAX + 1);
		swap_uint8_t(&array[i], &array[j]);
		keyStream[size] = array[(array[i] + array[j]) % (UINT8_MAX + 1)];
	}
	
	return keyStream;
}

uint8_t *RC4_encrypt(char *string, uint8_t *keyStream) {
	if (string == NULL) return NULL;
	if (keyStream == NULL) return NULL;
	size_t plain_text_length = strlen(string);
	uint8_t *encrypted_text = malloc(sizeof(uint8_t) * (plain_text_length + 1));
	encrypted_text[plain_text_length] = '\0';
	for (int i = 0 ; i < plain_text_length; i++)
		encrypted_text[i] = string[i] ^ keyStream[i];
	return encrypted_text;
}

char *RC4_decrypt(char *cipher, uint8_t *keyStream) {
	return (char *) RC4_encrypt(cipher, keyStream);
}
