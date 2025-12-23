#include <stdio.h>
#include <stdint-gcc.h>
#include <stdlib.h>

static const int8_t b64_table[256] = {
    ['A'] = 0,  ['B'] = 1,  ['C'] = 2,  ['D'] = 3,
    ['E'] = 4,  ['F'] = 5,  ['G'] = 6,  ['H'] = 7,
    ['I'] = 8,  ['J'] = 9,  ['K'] = 10, ['L'] = 11,
    ['M'] = 12, ['N'] = 13, ['O'] = 14, ['P'] = 15,
    ['Q'] = 16, ['R'] = 17, ['S'] = 18, ['T'] = 19,
    ['U'] = 20, ['V'] = 21, ['W'] = 22, ['X'] = 23,
    ['Y'] = 24, ['Z'] = 25,

    ['a'] = 26, ['b'] = 27, ['c'] = 28, ['d'] = 29,
    ['e'] = 30, ['f'] = 31, ['g'] = 32, ['h'] = 33,
    ['i'] = 34, ['j'] = 35, ['k'] = 36, ['l'] = 37,
    ['m'] = 38, ['n'] = 39, ['o'] = 40, ['p'] = 41,
    ['q'] = 42, ['r'] = 43, ['s'] = 44, ['t'] = 45,
    ['u'] = 46, ['v'] = 47, ['w'] = 48, ['x'] = 49,
    ['y'] = 50, ['z'] = 51,

    ['0'] = 52, ['1'] = 53, ['2'] = 54, ['3'] = 55,
    ['4'] = 56, ['5'] = 57, ['6'] = 58, ['7'] = 59,
    ['8'] = 60, ['9'] = 61,

    ['+'] = 62, ['/'] = 63
};

int main(void){
    FILE* fp = fopen("input-2.txt", "r");
    FILE* out = fopen("out.jpg", "wb");
    unsigned char line[5] = {'\0'};

    while(fgets(line, sizeof(line), fp)){
        uint8_t bytes_length = 3;
        if(line[3] == '='){
            if(line[2] == '='){
                bytes_length = 1;
            }
            else{
                bytes_length = 2;
            }
        }

        uint8_t number[4] = {0};
        uint32_t combined = 0;

        for(int i = 0; i < 4; i++){
            number[i] = b64_table[line[i]];
            combined |= number[i] << (6 * (3 - i));
        }

        //uint8_t *bytes = (uint8_t*)malloc(bytes_length * sizeof(uint8_t));
        uint8_t bytes[3] = {0};
        if(!bytes){
            printf("memory allocation for bytes array failed!\n");
        }

        for(int i = 0; i < bytes_length; i++){
            bytes[i] = 0;
        }

        combined = combined >> (3 - bytes_length) * 8;

        for(int i = 0; i < bytes_length; i++){
            bytes[bytes_length - 1 - i] = (uint8_t)(combined & 0b11111111);
            combined = combined >> 8;
        }
        fwrite(bytes, 1, bytes_length, out);
        
        
    }


    fclose(fp);
    fclose(out);
    
}
