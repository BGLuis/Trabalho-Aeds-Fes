#ifndef FUNCIONARIO_H // Criar bloca de codigo se não existir
#define FUNCIONARIO_H

extern const char PATH_FUNCIONARIO[]; // Guarda o caminho do arquivo .dat


struct Funcionario{ // Estrutura de dados para armazenar os dados do funcionario
  int codigo;
  char nome[40];
  char telefone[20];
  char cargo[20];
  float salario;
  char senha[40];
};

void CriaSeNaoExisteFuncionario(); // Cria o arquivo se não existir
void ListaFuncionario(); // Listar todos funcionarios
int QuantosFuncionarios(); // Retorna a quantidade de funcionarios
void CadastraFuncionario(); // Cadastra funcionarios
void PesquisaFuncionarioPorCodigo(); // Pesquizar por codigo
void PesquisaFuncionarioPorNome(); // Pesquizar por nome
int Login(int codigo, char *senha); // Login do funcionario)
void MenuGerente(); // Menu do gerente
void MenuRecepcionista(); // Menu do recepcionista
void MenuAuxiliar(); // Menu do auxiliar
void ListaEstadia();
int QuantosFuncionarios();

#endif // FUNCIONARIO_H