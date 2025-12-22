#include <stdio.h>
#include <stdint.h>
#define N 7
long long total = 0;
uint8_t row_mask[N];
uint8_t col_mask[N];

void dfs(int pos) {
    if (pos == (N - 1) * (N - 1)) {
        total++;
        return;
    }
    uint8_t row = pos / (N - 1) + 1;
    uint8_t col = pos % (N - 1) + 1;
    uint8_t used = row_mask[row] | col_mask[col];
    uint8_t available = (~used) & 0b11111110;
    while (available) {
        uint8_t v = -available & available;
        available -= v;
        row_mask[row] |= v;
        col_mask[col] |= v;
        dfs(pos + 1);
        row_mask[row] ^= v;
        col_mask[col] ^= v;
    }
}


int main(void) {
    for (int i = 0; i < N; i++) {
        row_mask[i] = 0;
        col_mask[i] = 0;
    }
    for (int i = 0; i < N; i++) {
        row_mask[0] |= 1 << (i + 1);
        col_mask[i] |= 1 << (i + 1);
    }
    for (int j = 0; j < N; j++) {
        row_mask[j] |= 1 << (j + 1);
        col_mask[0] |= 1 << (j + 1);
    }
    dfs(0);
    printf("7th reduced latin squares = %d", total);
    return 0;
}

