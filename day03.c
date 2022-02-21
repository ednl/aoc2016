#include <stdio.h>
#include <stdbool.h>

static inline bool isvalid(unsigned int a, unsigned int b, unsigned int c)
{
    return (a + b > c) && (a + c > b) && (b + c > a);
}

int main(void)
{
    FILE *f = fopen("input03.txt", "r");
    if (!f)
        return 1;
    unsigned int v1 = 0, v2 = 0, a[9];
    while (fscanf(f, " %u %u %u %u %u %u %u %u %u", &a[0], &a[1], &a[2], &a[3], &a[4], &a[5], &a[6], &a[7], &a[8]) == 9) {
        v1 += isvalid(a[0], a[1], a[2]);
        v1 += isvalid(a[3], a[4], a[5]);
        v1 += isvalid(a[6], a[7], a[8]);
        v2 += isvalid(a[0], a[3], a[6]);
        v2 += isvalid(a[1], a[4], a[7]);
        v2 += isvalid(a[2], a[5], a[8]);
    }
    fclose(f);
    printf("Part 1: %u\nPart 2: %u\n", v1, v2);
    return 0;
}
