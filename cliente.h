#ifndef CLIENTE_H // Criar bloca de codigo se não existir
#define CLIENTE_H

extern const char PATH_CLIENTE[]; // Guarda o caminho do arquivo .dat

#include <stdbool.h>

struct Cliente{ // Estrutura de dados para armazenar os dados do cliente
  int codigo;
  char nome[40];
  char endereco[80];
  char telefone[20];
};

void CriaSeNaoExisteCliente(); // Cria o arquivo se não existir
void ListaCliente(); // Listar todos Cliente
int quantosClientes(); // Retorna a quantidade de clientes
void CadastraCliente(); // Cadastra Cliente
void PesquisaClientePorCodigo(); // Pesquisar por codigo
void PesquisaClientePorNome(); // Pesquisar por nome
bool ClienteExiste(int codigo);


#endif // CLIENTE_H