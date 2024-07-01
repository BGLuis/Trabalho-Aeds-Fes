#ifndef ESTADIA_H // Criar bloca de codigo se não existir
#define ESTADIA_H
#include <stdbool.h>

extern const char PATH_ESTADIA[];

struct Data{
	int dia;
	int mes;
	int ano;
};

struct Estadia{
	int codigo;
	int codigoCliente;
	int codigoQuarto;
	int hospedes;
	struct Data inicio;
	struct Data fim;
};

void CriaSeNaoExisteEstadia(); // Cria o arquivo se não existir
void RealizarReserva();
void CheckIn();
void CheckOut();
void ListaEstadia();
bool PodeReserva(int codigo, struct Data inicio, struct Data fim);
void ListaEstadiaPorCliente();
int calcularDiario(struct Data inicio, struct Data fim);
int transformaEmDias(struct Data data);

#endif // ESTADIA_H