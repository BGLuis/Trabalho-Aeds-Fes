#include "cliente.h"
#include "estadia.h"
#include "funcionario.h"
#include "quarto.h"
#include "munit/munit.h"

int main(){

	// Cria arquivo binarios caso ele não existao
	CriaSeNaoExisteCliente();
	CriaSeNaoExisteQuarto();
	CriaSeNaoExisteFuncionario();
	CriaSeNaoExisteEstadia();

	// Funcionarios
	// Login
	munit_assert_int(Login(1, "123123"), ==, 1);
	munit_assert_int(Login(2, "123123"), ==, 2);
	munit_assert_int(Login(3, "123123"), ==, 3);
	munit_assert_int(Login(4, "123123"), ==, 4);

	// Quantos Fucionarios
	munit_assert_int(QuantosFuncionarios(), >=, 4);
	
	// Clientes
	// Quantos clientes
	munit_assert_int(quantosClientes(), >=, 5);

	// Cliente existe
	munit_assert_true(ClienteExiste(1));
	munit_assert_true(ClienteExiste(2));
	munit_assert_true(ClienteExiste(3));
	munit_assert_true(ClienteExiste(4));
	munit_assert_true(ClienteExiste(5));
	munit_assert_false(ClienteExiste(6));
	munit_assert_false(ClienteExiste(7));
	munit_assert_false(ClienteExiste(8));
	munit_assert_false(ClienteExiste(9));

	
	// Quartos
	// Quarto Existe
	munit_assert_true(QuartoExiste(101));
	munit_assert_true(QuartoExiste(102));
	munit_assert_true(QuartoExiste(201));
	munit_assert_true(QuartoExiste(202));
	munit_assert_true(QuartoExiste(301));
	munit_assert_true(QuartoExiste(302));
	munit_assert_false(QuartoExiste(1));
	munit_assert_false(QuartoExiste(2));
	munit_assert_false(QuartoExiste(3));
	munit_assert_false(QuartoExiste(4));

	// Quarto Suporta
	munit_assert_true(QuartoSuporta(101, 2));
	munit_assert_true(QuartoSuporta(102, 2));
	munit_assert_true(QuartoSuporta(201, 2));
	munit_assert_true(QuartoSuporta(202, 2));
	munit_assert_true(QuartoSuporta(301, 2));
	munit_assert_true(QuartoSuporta(302, 2));
	munit_assert_false(QuartoSuporta(101, 10));
	munit_assert_false(QuartoSuporta(102, 10));
	munit_assert_false(QuartoSuporta(201, 5));
	munit_assert_false(QuartoSuporta(202, 5));

	// Quarto Ocupado
	munit_assert_false(QuartoOcupado(101));
	munit_assert_false(QuartoOcupado(102));
	munit_assert_false(QuartoOcupado(201));
	munit_assert_false(QuartoOcupado(202));
	munit_assert_false(QuartoOcupado(301));
	munit_assert_false(QuartoOcupado(302));

	// Quantos Quartos
	munit_assert_int(quantosQuartos(), >=, 6);

	// Estadias
	// Pode resevar
	munit_assert_true(PodeReserva(101, (struct Data){1, 4, 2022}, (struct Data){12, 4, 2022}));
	munit_assert_true(PodeReserva(201, (struct Data){1, 1, 2022}, (struct Data){2, 1, 2022}));
	munit_assert_true(PodeReserva(301, (struct Data){25, 12, 2022}, (struct Data){2, 1, 2023}));

	// Calcular Diario 
	struct Data dia1 = {1, 1, 2022}, dia2 = {1, 12, 2023}, dia3 = {17, 3, 2024}, dia4 = {10, 10, 2025}, dia5 = {10, 6, 2026}, dia6 = {21, 1, 2027}, dia7 = {1, 1, 2028};
	munit_assert_int(calcularDiario(dia1, dia1), ==, 0);
	munit_assert_int(calcularDiario(dia1, dia2), ==, 695);
	munit_assert_int(calcularDiario(dia1, dia3), ==, 806);
	munit_assert_int(calcularDiario(dia1, dia4), ==, 1374);
	munit_assert_int(calcularDiario(dia1, dia5), ==, 1619);
	munit_assert_int(calcularDiario(dia1, dia6), ==, 1845);
	munit_assert_int(calcularDiario(dia1, dia7), ==, 2190);

	// Trasforma em dias
	munit_assert_int(transformaEmDias(dia1), ==, 738061);
	munit_assert_int(transformaEmDias(dia2), ==, 738756);
	munit_assert_int(transformaEmDias(dia3), ==, 738867);
	munit_assert_int(transformaEmDias(dia4), ==, 739435);
	munit_assert_int(transformaEmDias(dia5), ==, 739680);
	munit_assert_int(transformaEmDias(dia6), ==, 739906);
	munit_assert_int(transformaEmDias(dia7), ==, 740251);
	
	
	return 0;
}