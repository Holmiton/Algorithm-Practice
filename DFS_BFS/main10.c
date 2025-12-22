#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
/*
 pos belong to [0, 80]
 row = pos/9-----[0, 8] ---- 9*(n - 1)+0 --> 9*(n - 1) + 8
 col = pos%9-----[0, 8]
 block_row = row / 3 -----[0,0]->[2, 2]
 block_col = col % 3
*/
long long total = 0;

void printMatrix(uint16_t (*grid)[9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%u ", grid[i][j]);
        }
        printf("\n");
    }
}

void iniMask(uint16_t (*grid)[9], uint16_t* rowMask, uint16_t* colMask, uint16_t (*blockMask)[3]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j]) {
                rowMask[i] |= 1 << grid[i][j];
                colMask[j] |= 1 << grid[i][j];
                //block_row = i / 3, block_col = j / 3
                blockMask[i/3][j/3] |= 1 << grid[i][j];
            }
        }
    }
}

void dfs(int pos, uint16_t (*grid)[9], uint16_t* rowMask, uint16_t* colMask, uint16_t (*blockMask)[3]) {
    if (pos == 81) {
        printf("completed:\n");
        printMatrix(grid);
        return;
    }

    int row = pos / 9;
    int col = pos % 9;

    if (grid[row][col]) {
        dfs(pos + 1, grid, rowMask, colMask, blockMask);
        return;
    }

    int b_row = row / 3;
    int b_col = col / 3;
    uint16_t used = rowMask[row] | colMask[col] |  blockMask[b_row][b_col];
    uint16_t available = ~used & 0b0000001111111110;
    while (available) {
        uint16_t v = -available & available; // the lowest 1
        available -= v;
        rowMask[row] |= v;
        colMask[col] |= v;
        blockMask[b_row][b_col] |= v;
        grid[row][col] =(uint16_t)log2(v);
        dfs(pos + 1, grid, rowMask, colMask, blockMask);
        grid[row][col] = 0;
        blockMask[b_row][b_col] ^= v;
        colMask[col] ^= v;
        rowMask[row] ^= v;
    }
}

int main(void) {
    char line[32];
    uint16_t grid[9][9] = {{0}};
    FILE* fp = fopen("input.txt", "r");
    for (int i = 0; i < 9; i++) {
        if (!fgets(line, sizeof(line), fp)) {
            printf("file open failed!");
            return 0;
        }
        for (int j = 0; j < 9; j++) {
            if (line[j] != '.') {
                grid[i][j] = line[j] - '0';
            }
        }
    }

    // for (int i = 0; i < 9; i++) {
    //     for (int j = 0; j< 9; j++) {
    //         printf("%d ", grid[i][j]);
    //     }
    //     printf("\n");
    // }
    fclose(fp);

    uint16_t rowMask[9] = {0};
    uint16_t colMask[9] = {0};
    uint16_t blockMask[3][3] = {{0}};

    iniMask(grid, rowMask, colMask, blockMask);

    dfs(0, grid, rowMask, colMask, blockMask);

    return 0;
}
