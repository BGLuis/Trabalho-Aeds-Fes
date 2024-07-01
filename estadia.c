#include "estadia.h"
#include "cliente.h"
#include "quarto.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char PATH_ESTADIA[] = "data/abode.dat";

//A função transformaEmDias converte uma data representada por uma estrutura Data (que contém os campos ano, mes e dia) no número total de dias desde o "início do tempo" (considerando um cálculo simplificado). O cálculo assume que todos os anos têm 365 dias e todos os meses têm 30 dias, o que não leva em conta anos bissextos ou a variação real no número de dias dos meses.
int transformaEmDias(struct Data data){
  return (data.ano * 365) + (data.mes * 30) + data.dia;
}

//Essa função é responsável por criar o arquivo de estadias se ele não existir. Ela abre o arquivo em modo leitura ("rb") e, se o arquivo não existir, abre novamente em modo escrita ("wb") para criar o arquivo vazio. Em seguida, fecha o arquivo.
void CriaSeNaoExisteEstadia() {
  FILE *arquivo = fopen(PATH_ESTADIA, "rb"); // Abrir o arquivo para leitura
  if (arquivo == NULL)
  arquivo = fopen(PATH_ESTADIA, "wb");
  fclose(arquivo); // Fecha o arquivo
}

//A função calcularDiario calcula a diferença em dias entre duas datas, representadas pelas estruturas Data inicio e fim. Ela utiliza a função transformaEmDias para converter cada data no número total de dias desde um ponto inicial e então calcula a diferença entre esses dois valores.
int calcularDiario(struct Data inicio, struct Data fim){
  return transformaEmDias(fim) - transformaEmDias(inicio);
}

struct Estadia GetEstadia(int codigo){
  FILE *arquivo = fopen(PATH_ESTADIA, "rb");
  struct Estadia estadia, s;
  int i = 0;

  while(fread(&estadia, sizeof(struct Estadia), 1, arquivo) != 0){
    if(estadia.codigo == codigo){
      fclose(arquivo);
      return estadia;
    }
  }
  
  fclose(arquivo);
  return s;
}

//Essa função verifica se um quarto pode ser reservado para as datas especificadas. Ela lê as estadias do arquivo de estadias, compara os períodos de estadia para o mesmo quarto e retorna verdadeiro se o quarto estiver disponível para reserva ou falso caso contrário.
bool PodeReserva(int codigoQuarto, struct Data inicio, struct Data fim) {
  FILE *arquivo = fopen(PATH_ESTADIA, "rb");
  struct Estadia *estadias, estadia;
  int i = 0;

  estadias = malloc(sizeof(struct Estadia));

  while (fread(&estadia, sizeof(struct Estadia), 1, arquivo) != 0) {
    if (estadia.codigoQuarto == codigoQuarto) {
      estadias = realloc(estadias, (i + 1) * sizeof(struct Estadia));
      estadias[i] = estadia;
      i++;
    }
  }

  if (i == 0) {
  free(estadias);
  return true;
  };

  int inicioHospedagem = transformaEmDias(inicio);
  int fimHospedagem = transformaEmDias(fim);

  for (int i = 0; i < sizeof(estadias); i++) {
    int inicioEstadia = transformaEmDias(estadias[i].inicio);
    int fimEstadia = transformaEmDias(estadias[i].fim);
    if ((inicioEstadia >= inicioHospedagem && fimEstadia <= inicioHospedagem) ||
      (inicioEstadia <= fimHospedagem && fimEstadia >= fimHospedagem)) {
      free(estadias);
      return false;
    }
  }

  free(estadias);
  return true;
}

//A função geraCodigo() é utilizada para gerar um novo código para uma estadia com base nos códigos existentes no arquivo de estadias. Ela conta quantas estadias já estão registradas, adiciona 1 ao último código encontrado e retorna esse novo código para ser usado na criação de uma nova estadia.
int geraCodigo(){
  FILE *arquivo = fopen(PATH_ESTADIA, "rb");
  struct Estadia estadia;
  int i = 0;
  while (fread(&estadia, sizeof(struct Estadia), 1, arquivo) != 0){
    i++;
  }
  fclose(arquivo);
  return i+1;
}

//Essa função permite realizar a reserva de um quarto para um cliente com base nas entradas fornecidas pelo usuário. Ela solicita o código do cliente, número do quarto, número de hóspedes e datas de início e fim da estadia. Em seguida, verifica se o quarto pode ser reservado usando a função PodeReserva() e, se possível, cadastra a estadia no arquivo de estadias.
void RealizarReserva() {
  ListaCliente();
  printf("\n");
  
  struct Estadia estadia;
  bool clienteCod = false, clienteCodExiste = false, quartoNum = false, quartoExiste = false, quartoSuporta = false, hospedes = false, inicio = false, fim = false;
  int dia_inicio, mes_inicio, ano_inicio, dia_fim, mes_fim, ano_fim;

  do {
    if (clienteCod) {
      printf("Digite um codigo válido\n");
    }
    if(clienteCodExiste){
      printf("Cliente não encontrado\n");
    }
    printf("Escreva o código do cliente: ");
    scanf("%d", &estadia.codigoCliente);
  
    clienteCod = estadia.codigoCliente <= 0;
    clienteCodExiste = !ClienteExiste(estadia.codigoCliente);
  } while (clienteCod || clienteCodExiste);

  system("clear || cls");
  ListaQuartos();
  printf("\n");

  do {
    if (quartoNum) {
      printf("Digite um numerio válido\n");
    }
    if(quartoExiste){
      printf("Quarto não encontrado\n");
    }
    printf("Escreva o numero do quarto: ");
    scanf("%d", &estadia.codigoQuarto);
  
    quartoNum = estadia.codigoCliente <= 0;
    quartoExiste = !QuartoExiste(estadia.codigoQuarto);
  } while (quartoNum || quartoExiste);

  system("clear || cls");

  do {
    if (hospedes) {
      printf("Digite um numerio válido\n");
    }
    if(quartoSuporta){
      printf("Quarto não suporta a quantidade de hospedes\n");
    }
    printf("Escreva o numero de hóspedes: ");
    scanf("%d", &estadia.hospedes);
  
    hospedes = estadia.hospedes <= 0;
    quartoSuporta = !QuartoSuporta(estadia.codigoQuarto, estadia.hospedes);
  }while (hospedes || quartoSuporta);

  system("clear || cls");
  
  do {
  if (inicio) {
    printf("Digite uma data valida para o inicio\n");
  }
  if (fim) {
    printf("Digite uma data válida para o final\n");
  }
  fflush(stdin);
  printf("Escreva a data de entrada (dd/mm/yyyy): ");
  scanf("%d/%d/%d", &dia_inicio, &mes_inicio, &ano_inicio);
  fflush(stdin);
    
  fflush(stdin);
  printf("Escreva a data de saída (dd/mm/yyyy): ");
  scanf("%d/%d/%d", &dia_fim, &mes_fim, &ano_fim);
  fflush(stdin);

  //Verificar se a e validar
  // Início
    
  if (
      (mes_inicio == 2 && dia_inicio > 29) ||
      ((mes_inicio == 4 || mes_inicio == 6 || mes_inicio == 9 || mes_inicio == 11) && dia_inicio > 30) ||
      (mes_fim > 12)
  ){
    inicio = true;
  }else{
    inicio = false;
  }

  // Fim
  if (
      (mes_fim == 2 && dia_fim > 29) ||
      ((mes_fim == 4 || mes_fim == 6 || mes_fim == 9 || mes_fim == 11) && dia_fim > 30) ||
      (mes_fim > 12) 
    ) {
    fim = true;
  }else{
    fim = false;
  }

    estadia.inicio.ano = ano_inicio; 
    estadia.inicio.mes = mes_inicio;
    estadia.inicio.dia = dia_inicio;
    
    estadia.fim.ano = ano_fim;
    estadia.fim.mes = mes_fim;
    estadia.fim.dia = dia_fim;

    if(!(fim) && !(inicio)){
      if(transformaEmDias(estadia.inicio) > transformaEmDias(estadia.fim)){
        printf("A data de inicio não poder ser maior de saida\n");
        inicio = true;
        fim = true;
      }
    }
  }while (fim || inicio );

  if(PodeReserva(estadia.codigoQuarto, estadia.inicio, estadia.fim)){
    // Cadastrar a estadia no sistema
    estadia.codigo = geraCodigo();
    FILE *arquivo = fopen(PATH_ESTADIA, "ab");
    fwrite(&estadia, sizeof(struct Estadia), 1, arquivo);
    fclose(arquivo);
    printf("Reserva de %d foi realizada com sucesso", calcularDiario(estadia.inicio, estadia.fim));
    
  }
  else{
    // Fala que o quarto não pode ser reservado
    printf("O Quarto não pode ser reservado");
  }
}

//Essa função lista todas as estadias cadastradas no arquivo de estadias. Ela abre o arquivo para leitura ("rb"), lê cada estadia do arquivo usando fread() e imprime suas informações formatadas na tela.
void ListaEstadia(){
  FILE *arquivo = fopen(PATH_ESTADIA, "rb");
  struct Estadia estadia;

  printf("%*s%*s%*s%*s%*s%*s\n", -10, "Codigo", -20, "Codigo do cliente", -20, "Numero do quarto", -25, "Quatidade de Hospedes", -20, "data de inicio", -20, "Data de saida");

  while (fread(&estadia, sizeof(struct Estadia), 1, arquivo) != 0){
    char inicio[15], fim[15];
    sprintf(inicio, "%d/%d/%d", estadia.inicio.dia, estadia.inicio.mes, estadia.inicio.ano);
    sprintf(fim, "%d/%d/%d", estadia.fim.dia, estadia.fim.mes, estadia.fim.ano);
    printf("%*d",-10, estadia.codigo);
    printf("%*d",-20, estadia.codigoCliente);
    printf("%*d",-20, estadia.codigoQuarto);
    printf("%*d",-25, estadia.hospedes);
    printf("%*s", -20 ,inicio);
    printf("%*s",-20 ,fim);
    printf("\n");

  }
}

//A função CheckIn permite que o usuário realize o check-in de uma estadia. Primeiro, ela lista todas as estadias disponíveis, solicita o código da estadia desejada, verifica se a estadia existe e, em caso afirmativo, marca o quarto correspondente como ocupado.
void CheckIn(){
  ListaEstadia();
  printf("\n");
  
  int codigo;
  struct Estadia estadia;
  printf("Digite o codigo da estadia que deseja check in: ");
  scanf("%d",&codigo);

  estadia = GetEstadia(codigo);
  
  if(estadia.codigoCliente == 0){
    printf("Estadia não encontrada");
  }
  else{ 
    OcuparQuarto(estadia.codigoQuarto);
    printf("CheckIn Feito com sucesso");
  }
}

//A função CheckOut permite que o usuário realize o check-out de uma estadia. Ela lista todas as estadias disponíveis, solicita o código da estadia desejada, verifica se a estadia existe e, em caso afirmativo, desocupa o quarto, calcula e informa o preço a ser pago e os pontos de fidelidade acumulados pelo cliente.
void CheckOut(){
  ListaEstadia();
  printf("\n");
  
  int codigo;
  struct Estadia estadia;
  printf("Digite o codigo da estadia que deseja check in: ");
  scanf("%d",&codigo);

  estadia = GetEstadia(codigo);
  if(estadia.codigoCliente == 0){
    printf("Estadia não encontrada");
  }
  else{ 
    struct Quarto quarto;
    quarto = GetQuarto(estadia.codigoQuarto);
    DesocuparQuarto(estadia.codigoQuarto);
    printf("O preço a ser pago e R$%.2f\n", calcularDiario(estadia.inicio, estadia.fim) * quarto.diaria);
    printf("O cliente ganhou %d pontos de fidelidade\n", calcularDiario(estadia.inicio, estadia.fim) *10);
    printf("CheckOut Feito com sucesso\n");
  }
}

//A função ListaEstadiaPorCliente lista todas as estadias de um cliente específico. Ela solicita o código do cliente, percorre o arquivo de estadias para encontrar todas as estadias do cliente e exibe as informações dessas estadias. Além disso, calcula e exibe os pontos de fidelidade acumulados pelo cliente.
void ListaEstadiaPorCliente(){
  ListaCliente();
  printf("\n");
  
  int codCliente;
  printf("Escreva o codigo do cliente: ");
  scanf("%d",&codCliente);
  
  FILE *arquivo = fopen(PATH_ESTADIA, "rb");
  struct Estadia estadia;
  int dias = 0;

  printf("%*s%*s%*s%*s%*s%*s\n", -10, "Codigo", -20, "Codigo do cliente", -20, "Numero do quarto", -25, "Quatidade de Hospedes", -20, "data de inicio", -20, "Data de saida");

  while (fread(&estadia, sizeof(struct Estadia), 1, arquivo) != 0){
    if(estadia.codigoCliente == codCliente){
      char inicio[15], fim[15];
      
      dias += calcularDiario(estadia.inicio, estadia.fim);
      
      sprintf(inicio, "%d/%d/%d", estadia.inicio.dia, estadia.inicio.mes, estadia.inicio.ano);
      sprintf(fim, "%d/%d/%d", estadia.fim.dia, estadia.fim.mes, estadia.fim.ano);
      printf("%*d",-10, estadia.codigo);
      printf("%*d",-20, estadia.codigoCliente);
      printf("%*d",-20, estadia.codigoQuarto);
      printf("%*d",-25, estadia.hospedes);
      printf("%*s", -20, inicio);
      printf("%*s",-20, fim);
      printf("\n");
    }
  }
  printf("\n Pontos de fidelidade atuais: %d\n", dias * 10);
}