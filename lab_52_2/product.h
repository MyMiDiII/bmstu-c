#ifndef __PRODUCT_H__

#define __PRODUCT_H__

#define MAX_NAME_LEN 30
#define MAX_MAKER_LEN 15

typedef struct
{
    char name[MAX_NAME_LEN + 1];
    char maker[MAX_MAKER_LEN + 1];
    unsigned int price;
    unsigned int number;
} product_t;

int file_size(FILE *file, size_t *size);

int read_product(product_t *product);

#endif