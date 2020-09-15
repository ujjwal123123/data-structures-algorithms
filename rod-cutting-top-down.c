#include "min_max.c"
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int get_memo_item(int *prices, int index, int *memo) {
    // base case
    if (index < 0) {
        return 0;
    }

    // recursive case
    if (memo[index] == INT_MIN) {
        for (int i = 0; i <= index; i++) {
            memo[index] =
                max(memo[index],
                    prices[i] + get_memo_item(prices, index - 1 - i, memo));
        }
    }
    return memo[index];
}

int max_price(int *prices, int length) {
    int *memo = (int *)malloc(sizeof(int) * length);
    for (int i = 0; i < length; i++) {
        memo[i] = INT_MIN;
    }
    int var_max_price = get_memo_item(prices, length - 1, memo);

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
