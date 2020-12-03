#include <stdio.h>
#include "persist.h"

//saveALL: salva todos os registros do programa.
void saveAll(){
    persistClient();
    persistStock();
    persistCard();
    persistSale();
}

//loadALL: carrega todos os registros do programa.
void loadAll(){
    loadClient();
    loadStock();
    loadCard();
    loadSale();
}
