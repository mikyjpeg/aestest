#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "rijndael.h"

#define LIST_SIZE 16

void print_128bit_block(unsigned char *block) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      unsigned char value = BLOCK_ACCESS(block, i, j);

      // Print spaces before small numbers to ensure that everything is aligned
      // and looks nice
      if (value < 10) printf(" ");

      if (value < 100) printf(" ");

      printf("%d", value);
    }
    printf("\n");
  }
}

int main() {
  unsigned char plaintext[16] = {50, 67, 246, 168, 136, 90, 48, 141,
                                 49, 49, 152, 162, 224, 55, 7,  52};
  unsigned char key[16] = {43,  126, 21, 22,  40, 174, 210, 166,
                           171, 247, 21, 136, 9,  207, 79,  60};

  unsigned char *ciphertext = aes_encrypt_block(plaintext, key);
  unsigned char *recovered_plaintext = aes_decrypt_block(ciphertext, key);

  printf("############ ORIGINAL PLAINTEXT ###########\n");
  print_128bit_block(plaintext);

  printf("\n\n################ CIPHERTEXT ###############\n");
  print_128bit_block(ciphertext);

  printf("\n\n########### RECOVERED PLAINTEXT ###########\n");
  print_128bit_block(recovered_plaintext);

  free(ciphertext);
  free(recovered_plaintext);

  return 0;
}
