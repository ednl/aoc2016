#include <stdio.h>
#include <stdlib.h>  // qsort

#define ALPH_LEN    26
#define NAME_LEN    80
#define NAME_FMT   "80"
#define CHKSUM_LEN   5
#define CHKSUM_FMT  "5"

static char name[NAME_LEN + 1] = {0};
static char checksum[CHKSUM_LEN + 1] = {0};

typedef struct {
    int count;
    char letter;
} AlphHist;
static AlphHist hist[ALPH_LEN] = {0};

static int cmphist(const void* a, const void* b)
{
    const AlphHist *h1 = (const AlphHist*)a;
    const AlphHist *h2 = (const AlphHist*)b;
    const int countdiff = h2->count - h1->count;  // safe because INT_MIN is not present
    if (!countdiff)
        return h1->letter - h2->letter;
    return countdiff;
}

int main(void)
{
    FILE *f = fopen("input04.txt", "r");
    if (!f)
        return 1;
    int i, n, sectorid, sectorsum = 0;
    while (fscanf(f, "%"NAME_FMT"[-a-z]%n%d[%"CHKSUM_FMT"s] ", name, &n, &sectorid, checksum) == 3) {
        for (int j = 0; j < ALPH_LEN; ++j)
            hist[j] = (AlphHist){0, 'a' + (char)j};
        if (n > 0)
            name[--n] = '\0';
        for (int j = 0; j < n; ++j) {
            int bin = name[j] - 'a';
            if (bin >= 0 && bin < ALPH_LEN)
                hist[bin].count++;
        }
        qsort(hist, ALPH_LEN, sizeof(AlphHist), cmphist);
        i = 0;
        while (i < CHKSUM_LEN && checksum[i] == hist[i].letter)
            ++i;
        if (i == CHKSUM_LEN) {
            sectorsum += sectorid;
            for (int j = 0; j < n; ++j) {
                if (name[j] == '-')
                    name[j] = ' ';
                else
                    name[j] = 'a' + (name[j] - 'a' + sectorid) % ALPH_LEN;
            }
            printf("%d : %s\n", sectorid, name);
        }
    }
    fclose(f);
    printf("Part 1: %d\n", sectorsum);
    return 0;
}
