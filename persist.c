#include <stdio.h>
#include "persist.h"

void saveAll(){
    persistClient();
    persistStock();
    persistCard();
    persistSale();
}
void loadAll(){
    loadClient();
    loadStock();
    loadCard();
    loadSale();
}
