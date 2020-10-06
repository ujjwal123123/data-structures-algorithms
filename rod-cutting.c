#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int max_price(int *prices, int length) {
    if (length == 0) {
        return 0;
    }
    if (length == 1) {
        return prices[0];
    }

    int var_max_price = INT_MIN;
    for (int i = 0; i < length; i++) {
        int var_max_price_split =
            prices[i] + max_price(prices, length - i - 1);
        if (var_max_price_split > var_max_price) {
            var_max_price = var_max_price_split;
        }
    }

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
