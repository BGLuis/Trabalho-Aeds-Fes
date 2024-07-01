#include "funcionario.h"
#include "cliente.h"
#include "estadia.h"
#include "quarto.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const char PATH_FUNCIONARIO[] = "data/employee.dat";

//Esta função é responsável por limpar o buffer de entrada (stdin). Ela descarta todos os caracteres pendentes no buffer de entrada até encontrar um caractere de nova linha (\n) ou o final do arquivo (EOF).
void flush_in(){
   int ch;

   while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}

//A função Continue() exibe uma mensagem para o usuário indicando que ele deve digitar algo para continuar. Ela espera por um único caractere de entrada do usuário antes de retornar ao programa principal.
void Continue(){
  flush_in();
  
  char a;
  printf("\n");
  printf("Digite algo para continuar...\n");
  scanf("%c\n",&a);
  
  flush_in();
}

//Esta função verifica se o arquivo que armazena os dados dos funcionários existe. Se não existir, ela cria um arquivo novo e inicializa com dados fictícios de funcionários.
void CriaSeNaoExisteFuncionario() {
  FILE *arquivo = fopen(PATH_FUNCIONARIO, "rb"); // Abrir o arquivo para leitura

  if (arquivo == NULL) {                // Se o arquivo não existir
    struct Funcionario funcionarios[4]; // Cria um vetor de 4 funcionarios

    // Cria 4 funcionarios
    funcionarios[0].codigo = 1;
    strcpy(funcionarios[0].nome, "Gustavo Oliveira Ell");
    strcpy(funcionarios[0].telefone, "(73) 99784-4325");
    strcpy(funcionarios[0].cargo, "Gerente");
    strcpy(funcionarios[0].senha, "123123");
    funcionarios[0].salario = 1800;

    funcionarios[1].codigo = 2;
    strcpy(funcionarios[1].nome, "Maria Tereza da Conceição");
    strcpy(funcionarios[1].telefone, "(73) 99877-3598");
    strcpy(funcionarios[1].cargo, "Auxiliar de Limpeza");
    strcpy(funcionarios[1].senha, "123123");
    funcionarios[1].salario = 1500;

    funcionarios[2].codigo = 3;
    strcpy(funcionarios[2].nome, "João da Silva Albuquerque");
    strcpy(funcionarios[2].telefone, "(73) 99875-9151");
    strcpy(funcionarios[2].cargo, "Recepcionista");
    strcpy(funcionarios[2].senha, "123123");
    funcionarios[2].salario = 1600;

    funcionarios[3].codigo = 4;
    strcpy(funcionarios[3].nome, "Santino Farias");
    strcpy(funcionarios[3].telefone, "(73) 99755-1540");
    strcpy(funcionarios[3].cargo, "Garcom");
    strcpy(funcionarios[3].senha, "123123");
    funcionarios[3].salario = 1600;

    arquivo = fopen(PATH_FUNCIONARIO, "wb"); // Cria o arquivo
    fwrite(funcionarios, sizeof(struct Funcionario), 4,
           arquivo); // Escreve os funcionarios no arquivo
    fclose(arquivo); // Fecha o arquivo

    // return 1; // criou o arquivo
  } else {
    fclose(arquivo); // Fecha o arquivo
  }

  // return 0; // já existe o arquivo
};

//Esta função lista todos os funcionários cadastrados no sistema, lendo os dados do arquivo onde os funcionários estão armazenados.
void ListaFuncionario() {
  FILE *arquivo = fopen(PATH_FUNCIONARIO, "rb"); // Abrir o arquivo para leitura
  struct Funcionario funcionario;
  int i = 0;

  printf("%*s%*s%*s%*s%*s\n", -8, "Codigo", -40, "Nome", -20, "Telefone", -20, "Cargo", -7, "Salario");
  
  while (fread(&funcionario, sizeof(struct Funcionario), 1, arquivo) != 0) {
    printf("%*d",-8, funcionario.codigo);
    printf("%*s",-40, funcionario.nome);
    printf("%*s",-20, funcionario.telefone);
    printf("%*s",-20, funcionario.cargo);
    printf("%*.2f",-7, funcionario.salario);
    printf("\n");
    i++;
  }
  fclose(arquivo); // Fecha o arquivo
}

//Retorna o número total de funcionários cadastrados no sistema.
int QuantosFuncionarios() {
  FILE *arquivo = fopen(PATH_FUNCIONARIO, "rb"); // Abrir o arquivo para leitura
  struct Funcionario funcionario;
  int i = 0;

  while (fread(&funcionario, sizeof(struct Funcionario), 1, arquivo) != 0) {
    i++;
  }
  fclose(arquivo); // Fecha o arquivo
  return i;
}

//Permite o cadastro de um novo funcionário, coletando informações como nome, telefone, cargo, senha e salário. Os dados são então escritos no arquivo de funcionários.
void CadastraFuncionario() {
  struct Funcionario funcionario;

  bool nome = false, telefone = false, cargo = false, salario = false, senha = false;
  // Pegar nome
  do{
    if(nome) printf("Escreva um nome valido\n");
    
    printf("Insira o nome do funcionario: ");
    scanf("%[^\n]%*c", funcionario.nome);
    fflush(stdin);

    nome = !(strlen(funcionario.nome) > 3);
  }while(nome);
  system("clear || cls");
  
  // Pegar telefone
  do{
    if(telefone) printf("Escreva um telefone válido e com DDD\n");
    
    printf("Insira o telefone do funcionario ((XX) XXXX-XXXX): ");
    scanf("%[^\n]%*c", funcionario.telefone);
    fflush(stdin);

    telefone = !(strlen(funcionario.telefone) > 9); // ver se consegui validar o formato
  }while(telefone);
  system("clear || cls");

  // Pegar cargo
  do{
    if(cargo) {
      printf("Escreva um cargo valido\n");
      printf("- Gerente\n- Auxiliar de Limpeza\n- Recepcionista\n- Garçom\n");
    };
    
    printf("Insira o cargo do funcionario:");
    scanf("%[^\n]%*c", funcionario.cargo);
    fflush(stdin);
    cargo = !((strcmp(funcionario.cargo, "Gerente") == 0) ||
      (strcmp(funcionario.cargo, "Auxiliar de Limpeza") == 0) ||
      (strcmp(funcionario.cargo, "Recepcionista") == 0) ||
      (strcmp(funcionario.cargo, "Garçom") == 0));
  }while(cargo);
  system("clear || cls");

  // Pegar senha
  do{
    if(senha) printf("Escreva uma senha valida\n");

    printf("Insira a senha do funcionario: ");
    scanf("%[^\n]%*c", funcionario.senha);
    fflush(stdin);

    nome = !(strlen(funcionario.nome) > 0);
  }while(senha);
  system("clear || cls");
  // Pegar salario
  do{
    if(salario) printf("Escreva um salario valido\n");
    
    printf("Insira o salario do funcionario: ");
    scanf("%f", &funcionario.salario);
    fflush(stdin);
    system("clear || cls");
    
    salario = !(funcionario.salario > 0);
  }while(salario);

  
  funcionario.codigo = QuantosFuncionarios() + 1;

  // adicionar ao banco
  FILE *arquivo = fopen(PATH_FUNCIONARIO, "ab"); 
  fwrite(&funcionario, sizeof(struct Funcionario), 1, arquivo);
  fclose(arquivo);
}

//Permite pesquisar um funcionário específico pelo seu código. Retorna os dados do funcionário se encontrado.
void PesquisaFuncionarioPorCodigo() {
  int codigo;
  printf("Insira o codigo do funcionario: ");
  scanf("%d", &codigo);

  FILE *arquivo = fopen(PATH_FUNCIONARIO, "rb");
  struct Funcionario funcionario;
  int i = 0;
  
  printf("%*s%*s%*s%*s%*s\n", -8, "Codigo", -40, "Nome", -20, "Telefone", -20, "Cargo", -7, "Salario");
  while (fread(&funcionario, sizeof(struct Funcionario), 1, arquivo) != 0) {
    if (codigo == funcionario.codigo) {
      printf("%*d",-8, funcionario.codigo);
      printf("%*s",-40, funcionario.nome);
      printf("%*s",-20, funcionario.telefone);
      printf("%*s",-20, funcionario.cargo);
      printf("%*.2f",-7, funcionario.salario);
      printf("\n");
      i++;
    }
  }
  fclose(arquivo); // Fecha o arquivo
}

//Permite pesquisar funcionários cujo nome contenha uma determinada sequência de caracteres. Retorna todos os funcionários cujos nomes correspondem ao critério de pesquisa.
void PesquisaFuncionarioPorNome() {
  char nome[40];
  printf("Insira o nome do funcionario: ");
  scanf("%s", nome);

  FILE *arquivo = fopen(PATH_FUNCIONARIO, "rb");
  struct Funcionario funcionario;
  int i = 0;
  
  printf("%*s%*s%*s%*s%*s\n", -8, "Codigo", -40, "Nome", -20, "Telefone", -20, "Cargo", -7, "Salario");
  
  while (fread(&funcionario, sizeof(struct Funcionario), 1, arquivo) != 0)   {
    char *result = strstr(funcionario.nome, nome);
    if (result != NULL) {
      printf("%*d",-8, funcionario.codigo);
      printf("%*s",-40, funcionario.nome);
      printf("%*s",-20, funcionario.telefone);
      printf("%*s",-20, funcionario.cargo);
      printf("%*.2f",-7, funcionario.salario);
      printf("\n");
      i++;
    }
  }
  fclose(arquivo); // Fecha o arquivo
}

//Realiza o login de um funcionário no sistema, verificando se o código e a senha fornecidos correspondem a um funcionário registrado.
int Login(int codigo, char *senha) {
  FILE *arquivo = fopen(PATH_FUNCIONARIO, "rb");
  struct Funcionario funcionario;
  int i = 0;

  while (fread(&funcionario, sizeof(struct Funcionario), 1, arquivo) != 0) {
    if (codigo == funcionario.codigo) {
      if (strcmp(senha, funcionario.senha) == 0) {
        if (strcmp("Gerente", funcionario.cargo) == 0) {
          return 1;
        } else if (strcmp("Auxiliar de Limpeza", funcionario.cargo) == 0) {
          return 2;
        } else if (strcmp("Recepcionista", funcionario.cargo) == 0) {
          return 3;
        } else if (strcmp("Garcom", funcionario.cargo) == 0) {
          return 4;
        }
      }
    }
  }
  fclose(arquivo);
  return 0;
}


// Menus
//Essa função apresenta um menu de opções para realizar diferentes tipos de pesquisas relacionadas a clientes, como pesquisa por nome, código, listar todos os clientes e pesquisar reserva (estadia).
void PesquisaCliente() {
  int opcao;
  while(opcao != 4){
    printf("Insira o número de acordo com a opção desejada:\n\n");
    printf("1 - Pesquisar por Nome\n");
    printf("2 - Pesquisar por Código\n");
    printf("3 - Pesquisar todos\n");
    printf("4 - Voltar\n");
    
    fflush(stdin);
    scanf("%d", &opcao);
    fflush(stdin);

    system("clear || cls");
    switch (opcao) {
    case 1:
      PesquisaClientePorNome();
      Continue();
      break;
    case 2:
      PesquisaClientePorCodigo();
      Continue();
      break;
    case 3:
      ListaCliente();
      Continue();
      break;
    case 4:
      break;
    default:
      printf("Opção inválida!\n");
      break;
    }
    system("clear || cls");
  }
}

//Similar à função PesquisaCliente(), esta função apresenta um menu para realizar diferentes tipos de pesquisas relacionadas a funcionários, como pesquisa por nome, código e listar todos os funcionários.
void PesquisaFuncionario() {
  int opcao;
  while(opcao != 4){
    printf("Insira o número de acordo com a opção desejada:\n\n");
    printf("1 - Pesquisar por Nome\n");
    printf("2 - Pesquisar por Código\n");
    printf("3 - Pesquisar todos\n");
    printf("4 - Voltar\n");
    scanf("%d", &opcao);
    fflush(stdin);

    system("clear || cls");
    switch (opcao) {
    case 1:
      PesquisaFuncionarioPorNome();
      Continue();
      break;
    case 2:
      PesquisaFuncionarioPorCodigo();
      Continue();
      break;
    case 3:
      ListaFuncionario();
      Continue();
      break;
    case 4:
      break;
    default:
      printf("Opção inválida!\n");
      break;
    }
    system("clear || cls");
  }
}

//Esta função apresenta um menu de opções para realizar diferentes tipos de cadastros, como cadastro de funcionário, cliente, estadia e quartos.
void Cadastro() {
  int opcao;
  while(opcao != 5){
    printf("Insira o número de acordo com a opção desejada:\n\n");
    printf("1 - Cadastro de Funcionários\n");
    printf("2 - Cadastro de Clientes\n");
    printf("3 - Cadastro de Estadia (Reserva)\n");
    printf("4 - Cadastro de Quartos\n");
    printf("5 - Voltar\n");
    scanf("%d", &opcao);
    fflush(stdin);

    system("clear || cls");
    flush_in();
    switch (opcao) {
    case 1:
      CadastraFuncionario();
      Continue();
      break;
    case 2:
      CadastraCliente();
      Continue();
      break;
    case 3:
      RealizarReserva();
      Continue();
      break;
    case 4:
      CadastraQuarto();
      Continue();
      break;
    case 5:
      break;
    default:
      printf("Opção inválida!\n");
      break;
    }
    system("clear || cls");
  }
}

//A função PesquisaEstadia apresenta ao usuário um menu de opções para pesquisar estadias. O usuário pode optar por listar todas as estadias e reservas marcadas, pesquisar estadias por clientes, ou voltar ao menu anterior. Dependendo da escolha do usuário, a função chama outras funções para realizar a tarefa desejada.
void PesquisaEstadia () {

  int opcao;
  while(opcao != 3){
    printf("Insira o número de acordo com a opção desejada:\n\n");
    printf("1 - Pesquisar todas as estadias e reservas marcadas \n");
    printf("2 - Pesquisar estadias por clientes\n");
    printf("3 - Voltar\n");
    scanf("%d", &opcao);
    fflush(stdin);

    system("clear || cls");
    switch (opcao) {
      case 1:
        ListaEstadia();
        Continue();
        break;
      case 2:
        ListaEstadiaPorCliente();
        Continue();
        break;
      case 3:
        break;
      default:
        printf("Opção inválida!\n");
        break;
    }
    system("clear || cls");
  }
  
}

//Apresenta um menu de opções para realizar pesquisas tanto de clientes quanto de funcionários, além de permitir retornar ao menu anterior.
void Pesquisa() {
  int opcao;
  while(opcao != 4){
    printf("Insira o número de acordo com a opção desejada:\n\n");
    printf("1 - Pesquisar Clientes\n");
    printf("2 - Pesquisar Funcionários\n");
    printf("3 - Pesquisar por Estadias (Reservas)\n");
    printf("4 - Voltar\n");
    scanf("%d", &opcao);
    fflush(stdin);

    system("clear || cls");
    switch (opcao) {
      case 1:
        PesquisaCliente();
        break;
      case 2:
        PesquisaFuncionario();
        break;
      case 3:
        PesquisaEstadia ();
        break;
      case 4:
        break;
      default:
        printf("Opção inválida!\n");
        break;
    }
    system("clear || cls");
  }
}

//Esta função representa o menu principal do sistema para o perfil de gerente. Apresenta opções para pesquisa, cadastro, realizar reserva, check-in, check-out e sair do sistema.
void MenuGerente() {
  int opcao;
  while(opcao != 6){
    printf ("MENU PRINCIPAL\n");
    printf("Insira o número de acordo com a opção desejada:\n\n");
    printf("1 - Pesquisa\n");
    printf("2 - Cadastro\n");
    printf("3 - Realizar Reserva\n");
    printf("4 - Check In\n");
    printf("5 - Check Out\n");
    printf("6 - Sair\n");
    scanf("%d", &opcao);
    fflush(stdin);

    system("clear || cls");
    
    switch (opcao) {
      case 1:
        Pesquisa();
        break;
      case 2:
        Cadastro();
        break;
      case 3:
        RealizarReserva();
        Continue();
        break;
      case 4:
        CheckIn();
        Continue();
        break;
      case 5:
        CheckOut();
        Continue();
        break;
      case 6:
        break;
      default:
        printf("Opção inválida!\n");
        break;
    }
    system("clear || cls");
  }
}

//Apresenta um menu de opções específico para o perfil de recepcionista. Oferece opções para cadastro de clientes, realizar reserva (não implementado), check-in e check-out.
void MenuRecepcionista () {
  int opcao;
  while(opcao != 5){
    printf("Insira o número de acordo com a opção desejada:\n");
    printf("1 - Cadastro de Clientes\n"); 
    printf("2 - Realizar Reserva\n"); //cadastro de estadia
    printf("3 - Check In\n"); 
    printf("4 - Check Out\n"); 
    printf("5 - Sair\n");

    scanf ("%d",&opcao );
    flush_in();
    switch (opcao) {
      case 1:
        CadastraCliente();
        Continue();
        break;
      case 2:
         RealizarReserva();
        printf("Não implementado\n");
        Continue();
        break;
      case 3:
        CheckIn();
        printf("Não implementado\n");
        Continue();
        break;
      case 4:
        CheckOut();
        printf("Não implementado\n");
        Continue();
        break;
      case 5:
        break;
      default:
        printf("Opção inválida!\n");
        break;
    }
    system("clear || cls");
  }
}

//Mostra um menu simplificado para o perfil de auxiliar de limpeza, permitindo apenas a checagem de quartos disponíveis.
void MenuAuxiliar(){
  int opcao;
  printf ("Menu Auxiliar De Limpeza\n");
  printf ("Checagem de Quartos\n\n"); 

  ListaQuartos();
  
  Continue();
}