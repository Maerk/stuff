#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

typedef struct _L0R0 
{
  unsigned int l0: 6; 
  unsigned int r0: 6; 
} L0R0;

typedef struct _Key 
{
  unsigned int key: 9;
} Key;

uint8_t s1 [2][8] = {{5,2,1,6,3,4,7,0},{1,4,6,2,0,7,5,3}};
uint8_t s2 [2][8] = {{4,0,6,5,7,1,3,2},{5,3,0,7,6,2,1,4}};

uint8_t expansion (uint8_t r0); //in: 6bit, out: 8bit
uint8_t getBox (uint8_t sbox[2][8], uint8_t in_sbox); //in: mat3bit 4bit, out: 3bit
uint8_t feistel (uint8_t r0, uint8_t key); //in: 6bit 8bit, out: 6bit
L0R0 turn (L0R0 input, uint8_t key); //in: L0R0 8bit, out: L0R0
uint8_t keySchedule (Key key, uint8_t n_round);//in: 9bit 4bit, out: 8bit
char* des (char* plaintext, char* key, uint64_t n_round);

uint8_t expansion (uint8_t r0)
{
  return ( (r0 <<2) & 0b11000000 ) | 
	 ( ((r0 & 0b00001000) >> 1 | (r0 & 0b00001000) << 1) | ((r0 & 0b00000100) << 1 | (r0 & 0b00000100) << 3) ) | 
	 ( r0 & 0b00000011 );
}

uint8_t getBox (uint8_t sbox[2][8], uint8_t in_sbox)
{
  uint8_t row = (in_sbox & 0b00001000) >> 3;
  uint8_t col = in_sbox & 0b00000111;
  return sbox[row][col];
}

uint8_t feistel (uint8_t r0, uint8_t key)
{
  uint8_t r0_xor_key = expansion(r0) ^ key;
  uint8_t out_s1 = getBox(s1, (r0_xor_key & 0b11110000) >> 4);
  uint8_t out_s2 = getBox(s2, r0_xor_key & 0b00001111);
  return ((out_s1 << 3) | out_s2);
}

L0R0 turn (L0R0 input, uint8_t key)
{
  L0R0 output;
  output.l0 =  input.r0;
  output.r0 =  feistel(input.r0, key) ^ input.l0;
  return output;
}

uint8_t keySchedule (Key key, uint8_t n_round)
{
  //n_round %= 9; //fare in des e prendo uint16_t (0-8 shift)
  Key bitmask;
  bitmask.key = (((uint16_t) pow(n_round, 2.0) - 1) << (uint16_t)(9 - n_round));  
  return ( (key.key << n_round) | ((key.key & bitmask.key) >> (uint16_t)(9 - n_round)) );
}

char* des (char* plaintext, char* key, uint64_t n_round)
{
  Key chiave;
  L0R0 input;
  input.l0 = 0b101110;
  input.r0 = 0b011011;
  chiave.key = 0b001001101;

  uint64_t i;
  for(i=0; i<n_round; i++)
  {
    uint8_t roundkey = keySchedule(chiave, (i%9));
    printf("round_key %d: %d \n", i+1, roundkey);
    input = turn(input,roundkey);
    printf("output %d: %d  %d\n", i+1, input.l0,input.r0);
  }

  return  (char*)malloc(sizeof(0));
}

int main(int argc, char* argv[])
{
  char* a = des("Ciao", "key", 3); // è un test, prende solo il round
  return 0;
}
