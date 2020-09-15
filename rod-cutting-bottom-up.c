#include "min_max.c"
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int max_price(int *prices, int length) {
    int *memo = (int *)malloc(sizeof(int) * length);
    for (int index = 0; index < length; index++) {
        memo[index] = INT_MIN;
    }

    for (int index = 0; index < length; index++) {
        for (int j = 0; j <= index; j++) {
            memo[index] = max(memo[index - j], prices[j]);
        }
    }

    int var_max_price = memo[length - 1];
    free(memo);
    return var_max_price;
}

int main() {
    int length;
    scanf(" %d", &length);

    int *prices = (int *)malloc(sizeof(int) * length);
    for (int i = 0; i < length; i++) {
        scanf(" %d", &prices[i]);
    }

    printf("%d\n", max_price(prices, length));
}
