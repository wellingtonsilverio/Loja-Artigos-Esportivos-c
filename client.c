#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

Client *clients;

//createClient: recebe os dados do novo cliente, e o adiciona a lista de clientes.
void createClient(char* name, int CPF, int phone, char* email) {
    Client* child = (Client*) malloc(sizeof(Client));
    Client* lastClient = getLastClient();

    if (lastClient->CPF == 0) {
        strcpy(lastClient->nome, name);
        lastClient->CPF = CPF;
        lastClient->fone = phone;
        strcpy(lastClient->email, email);
        lastClient->prox = NULL;

        return;
    }

    strcpy(child->nome, name);
    child->CPF = CPF;
    child->fone = phone;
    strcpy(child->email, email);
    child->prox = NULL;

    lastClient->prox = child;

    return;
}

//getFirstClient: retorna o primeiro cliente.
Client* getFirstClient() {
    if (clients == NULL) {
        clients = (Client*) malloc(sizeof(Client));
        clients->CPF = 0;
        clients->prox = NULL;
    }

    return clients;
}

//getNextClient: retorna o proximo cliente da lista.
Client* getNextClient(Client* client){
    if (client == NULL) {
        return client;
    }

    return client->prox;
}

//getLastClient: retorna o ultimo cliente da lista.
Client* getLastClient(){
    Client* client = getFirstClient();
    while (1) {
        if (getNextClient(client) == NULL) {
            return client;
        }
        client = getNextClient(client);
    }
}

//getClientByCPF: recebe o CPF, e retorna o cliente correspondente.
Client* getClientByCPF(int CPF) {
    Client* client = getFirstClient();

    if (client == NULL || client->CPF == 0) {
        return;
    }

    while (client != NULL && client->CPF != CPF) {
        client = client->prox;
    }

    return client;
}

//updateClientByCPF: recebe os dados para atualizacao do cliente, o modifica seu registro na lista de clientes.
void updateClientByCPF(int CPF, char* name, int phone, char* email) {
    Client* client = getClientByCPF(CPF);

    if (client == NULL) {
        return;
    }

    strcpy(client->nome, name);
    client->fone = phone;
    strcpy(client->email, email);
}

//deleteClientByCPF: recebe o CPF do cliente a ser excluido, e o exclui da lista de clientes.
void deleteClientByCPF(int CPF) {
    Client* client = getClientByCPF(CPF);
    Client* aux = (Client*) malloc(sizeof(Client));

    *aux = *client;
    if (getNextClient(aux) != NULL) {
        *client = *getNextClient(aux);
    }

    free(aux);
}

//persistClient: salva toda lista de clientes em um arquivo binario.
void persistClient(){
    FILE *file;

    file = fopen("client.bin", "w+b");

    if (file == NULL) {
        return;
    }

    Client* client = getFirstClient();

    while (client != NULL) {
        fwrite(client, sizeof(Client), 1, file);
        client = getNextClient(client);
    }

    fclose(file);
}

//loadClient: carrega os dados da lista de clientes que estão no arquivo para a memoria do sistema.
void loadClient(){
    FILE *file;

    file = fopen("client.bin", "rb");

    if (file == NULL) {
        return;
    }

    freeClient();
    Client* client = getFirstClient();

    while(1){
        Client* read = (Client*) malloc(sizeof(Client));

        size_t r = fread(read, sizeof(Client), 1, file);

        if (r < 1) {
            break;
        } else {
            if (client == NULL) {
                client = (Client*) malloc(sizeof(Client));
                client->CPF = 0;
                client->prox = NULL;
            }
            if (client->CPF == 0) {
                read->prox = NULL;
                *client = *read;
            } else {
                read->prox = NULL;
                client->prox = read;
                client = getNextClient(client);
            }

        }
    }

    fclose(file);
}

//freeClient: libera a memoria da lista de clientes.
void freeClient(){
    free(clients);
}

