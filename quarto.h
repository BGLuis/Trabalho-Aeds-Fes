#ifndef QUARTO_H // Criar bloca de codigo se não existir
#define QUARTO_H
#include <stdbool.h>
extern const char PATH_QUARTO[]; // Guarda o caminho do arquivo .dat

struct Quarto{ // Estrutura de dados para armazenar os dados do quarto
  int numero;
  int hospedes;
  float diaria;
  bool ocupado;
};

void CriaSeNaoExisteQuarto(); // Cria o arquivo se não existir
void ListaQuartos();
int quantosQuartos();
void CadastraQuarto(); // Cadastra Quarto
void OcuparQuarto(int codigo);
void DesocuparQuarto(int codigo);
struct Quarto GetQuarto(int codigo);
bool QuartoExiste(int codigo);
bool QuartoSuporta(int codigo, int hospedes);
bool QuartoOcupado(int codigo);
#endif // QUARTO_H