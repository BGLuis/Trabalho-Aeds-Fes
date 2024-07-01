#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "quarto.h"

const char PATH_QUARTO[] = "data/room.dat";

//Verifica se o arquivo de quartos existe. Se não existir, cria um arquivo inicial com informações de seis quartos.
void CriaSeNaoExisteQuarto(){
  FILE *arquivo = fopen(PATH_QUARTO, "rb"); // Abrir o arquivo para leitura

  if(arquivo == NULL){ // Se o arquivo não existir
    struct Quarto quartos[6]; // Cria um vetor de 6 clientes

    // Cria 6 quartos
    quartos[0].numero = 101;
    quartos[0].hospedes = 5;
    quartos[0].diaria = 1000.00;
    quartos[0].ocupado = false;

    quartos[1].numero = 102;
    quartos[1].hospedes = 5;
    quartos[1].diaria = 1000.00;
    quartos[1].ocupado = false;

    quartos[2].numero = 201;
    quartos[2].hospedes = 4;
    quartos[2].diaria = 1000.00;
    quartos[2].ocupado = false;

    quartos[3].numero = 202;
    quartos[3].hospedes = 4;
    quartos[3].diaria = 1000.00;
    quartos[3].ocupado = false;

    quartos[4].numero = 301;
    quartos[4].hospedes = 2;
    quartos[4].diaria = 1000.00;
    quartos[4].ocupado = false;

    quartos[5].numero = 302;
    quartos[5].hospedes = 2;
    quartos[5].diaria = 1000.00;
    quartos[5].ocupado = false;    


    arquivo = fopen(PATH_QUARTO, "wb"); // Cria o arquivo
    fwrite(quartos, sizeof(struct Quarto), 6, arquivo); // Escreve os clientes no arquivo
    fclose(arquivo); // Fecha o arquivo
    
    // return 1; // criou o arquivo
  }
  else{
    fclose(arquivo); // Fecha o arquivo
  }

  // return 0; // já existe o arquivo
}

//Lista todos os quartos presentes no arquivo room.dat.
void ListaQuartos(){
  FILE *arquivo = fopen(PATH_QUARTO, "rb"); // Abrir o arquivo para leitura
  struct Quarto quarto;
  int i = 0;

  printf("%*s%*s%*s%*s\n", -8, "Numero", -15, "Max. Hospedes", -20, "Diaria", -20, "Status");
  while(fread(&quarto, sizeof(struct Quarto), 1, arquivo) != 0){
    printf("%*d",-8, quarto.numero);
    printf("%*d",-15, quarto.hospedes);
    printf("%*.2f",-20, quarto.diaria);
    quarto.ocupado ? printf("%*s",-20, "Ocupado") : printf("%*s",-20, "Livre");
    printf("\n");
    i++;
  } 
  fclose(arquivo); // Fecha o arquivo

}

//Permite o cadastro de um novo quarto no arquivo room.dat.
int quantosQuartos(){
  FILE *arquivo = fopen(PATH_QUARTO, "rb"); // Abrir o arquivo para leitura
  struct Quarto quarto;
  int i = 0;

  while(fread(&quarto, sizeof(struct Quarto), 1, arquivo) != 0) i++; // Conta quantos quartos existem
  
  fclose(arquivo); // Fecha o arquivo
  return i;
}

//Verificar se um código de quarto já existe no arquivo room.dat.
bool CodigoJaExiste(int codigo){
  FILE *arquivo = fopen(PATH_QUARTO, "rb");
  struct Quarto quarto;
  
  while(fread(&quarto, sizeof(struct Quarto), 1, arquivo) != 0){
    if(quarto.numero == codigo) return true;
  } 
  
  fclose(arquivo); // Fecha o arquivo
  return false;
}

//Cadastrar um novo quarto no arquivo room.dat.
void CadastraQuarto(){
  FILE *arquivo;
  struct Quarto quarto;
  bool codigo = false, hospedes = false, diaria = false;

  // Pegar Numero do quarto
  do{
    if(codigo) printf("Esse quarto já existe!\n");
    
    printf("Digite o numero do quarto: ");
    scanf("%d", &quarto.numero);
    
    codigo = CodigoJaExiste(quarto.numero);
  }while(codigo);

  // Pegar maximo de hospedes
  do{
    if(hospedes) printf("Escreva um numero valido\n");
    
    printf("Digite a quantidade de hospedes: ");
    scanf("%d", &quarto.hospedes);

    hospedes = !(quarto.hospedes > 0 && quarto.hospedes < 10);
  }while(hospedes);

  // Pegar diaria
  do{
    if(diaria) printf("Escreva um numero valido\n");

    printf("Digite a diaria: ");
    scanf("%f", &quarto.diaria);

    diaria = !(quarto.diaria > 0);
  }while(diaria);
  
  quarto.ocupado = false; // Quarto livre

  // adicionar ao banco
  arquivo = fopen(PATH_QUARTO, "ab");
  fwrite(&quarto, sizeof(struct Quarto), 1, arquivo);
  fclose(arquivo);
}

//Marcar um quarto como ocupado no arquivo room.dat com base no número do quarto fornecido.
void OcuparQuarto(int codigo){
  FILE *arquivo = fopen(PATH_QUARTO, "rb");
  struct Quarto *quartos, quarto;
  int i = 0;

  quartos = malloc(sizeof(struct Quarto));
  
  while(fread(&quarto, sizeof(struct Quarto), 1, arquivo) != 0){
    if(quarto.numero == codigo){
      quarto.ocupado = true;
    }
    quartos = realloc(quartos, sizeof(struct Quarto) * (i + 1));
    quartos[i] = quarto;
    i++;
  }
  
  fclose(arquivo);

  // reescrever os arquivos para atualizar os dados
  arquivo = fopen(PATH_QUARTO, "wb");
  fwrite(quartos, sizeof(struct Quarto), i, arquivo);
  fclose(arquivo);
  
  free(quartos);
}

//Marcar um quarto como desocupado no arquivo room.dat com base no número do quarto fornecido.
void DesocuparQuarto(int codigo){
  FILE *arquivo = fopen(PATH_QUARTO, "rb+");
  struct Quarto *quartos, quarto;
  int i = 0;
  
  quartos = malloc(sizeof(struct Quarto));
  
  while(fread(&quarto, sizeof(struct Quarto), 1, arquivo) != 0){
    if(quarto.numero == codigo){
      quarto.ocupado = false;
    }
    quartos = realloc(quartos, sizeof(struct Quarto) * (i + 1));
    quartos[i] = quarto;
    i++;
  }

  fclose(arquivo);

  // reescrever os arquivos para atualizar os dados
  arquivo = fopen(PATH_QUARTO, "wb");
  fwrite(quartos, sizeof(struct Quarto), i, arquivo);
  fclose(arquivo);
  free(quartos);
}

struct Quarto GetQuarto(int codigo){
  FILE *arquivo = fopen(PATH_QUARTO, "rb");
  struct Quarto quarto,s;
  while(fread(&quarto, sizeof(struct Quarto), 1, arquivo) != 0){
    if(quarto.numero == codigo){
      fclose(arquivo);
      return quarto;
    }
  }
  fclose(arquivo);
  return s;
} 

//A função QuartoExiste verifica se um quarto com o código especificado existe no arquivo de dados.
bool QuartoExiste(int codigo){
  FILE *arquivo = fopen(PATH_QUARTO, "rb");
  struct Quarto quarto;
  
  while(fread(&quarto, sizeof(struct Quarto), 1, arquivo) != 0){
    if(quarto.numero == codigo){
       fclose(arquivo);
       return true;
    }
  }
  
  fclose(arquivo);
  return false;
}

//A função QuartoSuporta verifica se um quarto com o código especificado pode acomodar a quantidade de hóspedes fornecida.
bool QuartoSuporta(int codigo, int hospedes){
  struct Quarto quarto = GetQuarto(codigo);
  return quarto.hospedes >= hospedes;
}

//A função QuartoOcupado verifica se um quarto com o código especificado está atualmente ocupado.
bool QuartoOcupado(int codigo){
  struct Quarto quarto = GetQuarto(codigo);
  return quarto.ocupado;
}