#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define TAMANHO 4
#define MAX_PROBLEMAS 10
#define MAX_NOME_LENGTH 20
#define NUMEROS 10

// estruturas

typedef struct {
    char nome[MAX_NOME_LENGTH];
    int tabuleiro[TAMANHO][TAMANHO];
    int solucao[TAMANHO][TAMANHO];
} ProblemaSudoku;

typedef struct {
    char nome[MAX_NOME_LENGTH];
    int jogadas;
    int jogadasInvalidas;
} StatusProblema;

//  funções

void menu(int *numProblemas, ProblemaSudoku problemas[MAX_PROBLEMAS], StatusProblema status[MAX_PROBLEMAS], int *totalJogos, int *jogosBemSucedidos, int ProblemaAnterior);

void adicionarProblema(ProblemaSudoku problemas[MAX_PROBLEMAS], int *numProblemas);

void alterarNomeProblema(ProblemaSudoku problemas[MAX_PROBLEMAS], int numProblemas);

int escolherJogo(int numProblemas, ProblemaSudoku problemas[MAX_PROBLEMAS]);

int escolherProblemaAleatorio(int ProblemaAnterior, int numProblemas);

void Problema(ProblemaSudoku problema);

void jogarSudoku(ProblemaSudoku problemas[MAX_PROBLEMAS], int *numProblemas, ProblemaSudoku problema, StatusProblema *status, int *totalJogos, int *jogosBemSucedidos, int ProblemaAnterior);

int jogadaValida(ProblemaSudoku problema, int linha, int coluna, int num);

bool sudokuCompleto(ProblemaSudoku problema);

int carregarProblemas(ProblemaSudoku problemas[MAX_PROBLEMAS], char filename[]);

int carregarEstatisticas(StatusProblema status[MAX_PROBLEMAS], int *totalJogos, int *jogosBemSucedidos, char filename[]);

void guardarEstatisticas(ProblemaSudoku problemas[MAX_PROBLEMAS], StatusProblema status[MAX_PROBLEMAS], int numProblemas, int totalJogos, int jogosBemSucedidos, char filename[]);

void guardarProblemas(ProblemaSudoku problemas[MAX_PROBLEMAS], int numProblemas, char filename[]);

void Estatisticas(StatusProblema status[MAX_PROBLEMAS], int numProblemas, int totalJogos, int jogosBemSucedidos);

#endif