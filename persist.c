#include <stdio.h>
#include "persist.h"
#include "client.h"
#include "stock.h"
#include "sales.h"

void saveAll(){
    FILE *file;

    file = fopen("db.bin", "w+b");

    if (file == NULL) {
        return;
    }

    fwrite(getFirstClient(), sizeof(Client), 1, file);
//    fwrite(getFirstStock(), sizeof(Stock), 1, file);
//    fwrite(getFirstCard(), sizeof(Card), 1, file);
//    fwrite(getFirstSale(), sizeof(Sale), 1, file);

    fclose(file);
}
void loadAll(){
    FILE *file;

    file = fopen("db.bin", "rb");

    if (file == NULL) {
        return;
    }

    freeStock();
    fread(getStock(), sizeof(Client), 1, file);
//    fread(getFirstStock(), sizeof(Stock), 1, file);
//    fread(getFirstCard(), sizeof(Card), 1, file);
//    fread(getFirstSale(), sizeof(Sale), 1, file);

    fclose(file);
}
