#ifndef CLIENT_H
#define CLIENT_H

//structs(todas possuem base em "listas ligadas" - possuem um ponteiro para o prox item da lista).
typedef struct client{
  char nome[100];
  int CPF;
  int fone;
  char email[100];
  struct Client *prox;
} Client;

void createClient(char*, int, int, char*);
Client* getFirstClient();
Client* getNextClient(Client*);
Client* getLastClient();
Client* getClientByCPF(int);
void updateClientByCPF(int, char*, int, char*);
void deleteClientByCPF(int);

#endif
