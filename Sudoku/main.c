#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "headers.h"


/* IMPORTANTE:  Para jogar tem que abrir o executavel (que se enocntra na mesma pasta com nome "sudoku") pois é necessario compilar dois arquivos C para o arranque do mesmo  */

int main() {

    // Iniciar as estruturas na main
    ProblemaSudoku problemas[MAX_PROBLEMAS];
    StatusProblema status[MAX_PROBLEMAS];

   
    // random dos numeros
    srand(time(NULL));


    //variáveis iniciais 
    int totalJogos = 0;
    int jogosBemSucedidos = 0;
    int jogadasInvalidas = 0;
    int ProblemaAnterior = -1;
    int numProblemas = 0 ;

    // Carregar estatísticas
    carregarEstatisticas(status, &totalJogos, &jogosBemSucedidos, "estatisticas.txt");

    // Carregar problemas
    numProblemas = carregarProblemas(problemas, "sudoku_problemas.txt");

    // Menu
    menu(&numProblemas, problemas, status, &totalJogos, &jogosBemSucedidos, ProblemaAnterior);   

    return 0;
}











