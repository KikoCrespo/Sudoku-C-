#include "headers.h"

// menu 

void menu(int *numProblemas, ProblemaSudoku problemas[MAX_PROBLEMAS], StatusProblema status[MAX_PROBLEMAS], int *totalJogos, int *jogosBemSucedidos, int ProblemaAnterior){ 
    
    int opcao;
    int escolha;

    do {
        printf("\n===== Sudoku =====\n");
        printf("1. Jogar Sudoku\n");
        printf("2. Adicionar Novo Problema\n");
        printf("3. Alterar Nome de um Problema\n");
        printf("4. Consultar Estatísticas\n");
        printf("5. Sair\n");
        printf("Escolha: ");
        scanf(" %d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                if(numProblemas > 0){
                    printf("Escolha o tipo de jogo:\n");
                    printf("1. Jogo Aleatorio\n");
                    printf("2. Escolher Jogo\n");
                    printf("3. Voltar\n");
                    printf("Escolha: ");
                    scanf("%d", &escolha);
                    getchar();
                    if (escolha == 1) {
                        int problemaSelecionado = escolherProblemaAleatorio(ProblemaAnterior, *numProblemas);
                        jogarSudoku(problemas, numProblemas, problemas[problemaSelecionado], status, totalJogos, jogosBemSucedidos, ProblemaAnterior);
                        ProblemaAnterior = problemaSelecionado;
                    } else if (escolha == 2) {
                        int problemaSelecionado = escolherJogo(*numProblemas, problemas);
                        jogarSudoku(problemas, numProblemas, problemas[problemaSelecionado], status, totalJogos, jogosBemSucedidos, ProblemaAnterior);
                        ProblemaAnterior = problemaSelecionado;
                    }else if(escolha == 3){
                        menu(numProblemas, problemas, status, totalJogos, jogosBemSucedidos, ProblemaAnterior);
                    }
                }else{
                        printf("Nao existem problemas de Sudoku disponiveis.\n");
                        adicionarProblema(problemas, numProblemas);
                    }
                break;
            case 2:
                // Adicionar novo problema
                    adicionarProblema(problemas, numProblemas);
 
                break;
            case 3:
                // Alterar o nome do problema
                alterarNomeProblema(problemas, *numProblemas);
                break;
            case 4:
                // Consultar estatisticas
                Estatisticas(status, *numProblemas, *totalJogos, *jogosBemSucedidos);
                break;
            case 5:
                // Sair e guardar estatisticas e problemas 
                guardarEstatisticas(problemas, status, *numProblemas, *totalJogos, *jogosBemSucedidos, "estatisticas.txt");
                guardarProblemas(problemas, *numProblemas, "sudoku_problemas.txt");
                break;
            default:
                printf("Opção invalida. Tente novamente.\n");
        }

    } while (opcao != 5);

}

// escolher tipo de jogo

int escolherJogo(int numProblemas, ProblemaSudoku problemas[MAX_PROBLEMAS]){
    int op;
    printf("Jogos:\n\n");
    for (int i = 0; i < numProblemas; i++)
    {
        printf("%d: %s\n",i+1,problemas[i].nome);
    }
    printf("\n\nEscolha o jogo que pretende jogar: ");
    scanf("%d", &op);
    getchar();

    return op-1;
}

// adicionar problema sudoku
/* funcao que adiciona um sudoku , pedindo ao usuario para preencher o problema por linhas , tratamos o problema em matriz */

void adicionarProblema(ProblemaSudoku problemas[MAX_PROBLEMAS], int *numProblemas) {
    if (*numProblemas >= MAX_PROBLEMAS) {
        printf("Limite maximo de problemas atingido.\n");
        return;
    }

    printf("Digite o nome do novo problema: ");
    scanf("%s", problemas[*numProblemas].nome);
    getchar();
    printf("Digite os numeros do Sudoku (0 para posicao vazia):\n");
    for (int i = 0; i < TAMANHO; i++) {
        printf("Linha: %d\n", i + 1) ;
        for (int j = 0; j < TAMANHO; j++) {
            printf("Coluna %d: ", j + 1);
            scanf("%d", &problemas[*numProblemas].tabuleiro[i][j]);
        }
    }
    getchar();
    (*numProblemas)++;
    return;
}

// alterar nome
/* funcao que altera o nome a partir do nome existente, com comparacao de strings */

void alterarNomeProblema(ProblemaSudoku problemas[MAX_PROBLEMAS], int numProblemas) {
    char NomeAnterior[MAX_NOME_LENGTH];
    char NovoNome[MAX_NOME_LENGTH];
 
    printf("========== Lista de jogos ===========\n");
    for (int i = 0; i < numProblemas; i++)
    {
        printf("%d: %s\n",i+1,problemas[i].nome);
    }
    

    printf("Digite o nome do problema que deseja alterar: ");
    scanf("%s", NomeAnterior);
    getchar();
    int i;
    for (i = 0; i < numProblemas; i++) {
        if (strcmp(problemas[i].nome, NomeAnterior) == 0) {
            printf("Digite o novo nome: ");
            scanf("%s", NovoNome);
            getchar();
            // Verificar se o novo nome já existe
            int j;
            for (j = 0; j < numProblemas; j++) {
                if (j != i && strcmp(problemas[j].nome, NovoNome) == 0) {
                    printf("Ja existe um problema com esse nome.\n");
                    return;
                }
            }

            strcpy(problemas[i].nome, NovoNome);
            printf("Nome alterado com sucesso.\n");
            return;
        }
    }

    printf("Problema nao encontrado.\n");
}

// mostrar Problema 
/* funcao para mostrar o sudoko no interface do usuario */

void Problema(ProblemaSudoku problema) {
    printf("\n========== %s =============\n", problema.nome);
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            printf("%2d ", problema.tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// escolher problema aleatorio
/* Onde o programa faz uma escolha aleatoria dos sudokus existentes */

int escolherProblemaAleatorio(int ProblemaAnterior, int numProblemas) {
    int problemaAleatorio;
    
    if (numProblemas <= 0) {
        printf("Nao existem problemas de Sudoku disponiveis.\n");
        exit(0);
    }

    do {
        problemaAleatorio = rand() % numProblemas;
    } while (problemaAleatorio == ProblemaAnterior);

    return problemaAleatorio;
}

// jogar jogo
/*  onde se processa o jogo e as verificacoes */

void jogarSudoku(ProblemaSudoku problemas[MAX_PROBLEMAS], int *numProblemas ,ProblemaSudoku problema, StatusProblema *status, int *totalJogos, int *jogosBemSucedidos, int ProblemaAnterior) {
    int jogadasInvalidas = 0;
    
    while (true) {
        system("clear");
          
        /* mostrar o jogo na tela do usuario */
        Problema(problema);
        printf("\nSudoku nao esta completo.\n");
       
        int linha, coluna, num;
        printf("Digite a linha (1-%d), coluna (1-%d) e numero (1-%d) separados por espaço (0 0 0 para sair): ", TAMANHO, TAMANHO, TAMANHO);
        scanf("%d %d %d", &linha, &coluna, &num);

        /* sair do jogo */
        if (linha == 0 || coluna == 0 || num == 0) {
            break;
        }

        linha--;
        coluna--;

        if (linha < 0 || linha >= TAMANHO || coluna < 0 || coluna >= TAMANHO || num > TAMANHO || num < 0) {
            printf("Jogada invalida. Tente novamente.\n");
            continue;
        }

        if (jogadaValida(problema, linha, coluna, num)) {
            problema.tabuleiro[linha][coluna] = num;
            Problema(problema);
        } else {
            printf("Jogada invalida. Tente novamente.\n");
            jogadasInvalidas++;
            if (jogadasInvalidas >= 2) {
                printf("Fez duas jogadas invalidas. Jogo encerrado.\n");
                break;
            }
        }
        if (sudokuCompleto(problema)) {
                printf("Parabens! Completou o Sudoku.\n");
                printf("1. Sair\n2. jogar novamente: ");
                int opcao;
                scanf("%d", &opcao);
                if (opcao == 2) {
                    int problemaSelecionado = escolherProblemaAleatorio(ProblemaAnterior, *numProblemas);
                    jogarSudoku(problemas, numProblemas, problemas[problemaSelecionado], status, totalJogos, jogosBemSucedidos, ProblemaAnterior);
                    ProblemaAnterior = problemaSelecionado;
                } else {
                    menu(numProblemas, problemas, status, totalJogos, jogosBemSucedidos, ProblemaAnterior);                   
                }
        } 
    }
    

    (*totalJogos)++;
    if (jogadasInvalidas < 2) {
        (*jogosBemSucedidos)++;
    }

    for (int i = 0; i < MAX_PROBLEMAS; i++) {
        if (strcmp(status[i].nome, problema.nome) == 0) {
            status[i].jogadas++;
            status[i].jogadasInvalidas += jogadasInvalidas;
            strcpy(status[i].nome, problema.nome);
            break;
        }
    }
}

// verificacao da jogada

int jogadaValida(ProblemaSudoku problema, int linha, int coluna, int num) {

    /* // Verificar se existe algum numero na posicao
    if (problema.tabuleiro[linha][coluna] != 0) {
        return 0;
    } */
    
    if(num != 0){
    // Verificar se o numero esta na mesma linha ou coluna
         for (int i = 0; i < TAMANHO; i++) {
            if (problema.tabuleiro[linha][i] == num || problema.tabuleiro[i][coluna] == num) {
                return 0;
                }
            }
        // Verificar se o numero esta na matriz 2x2 
        int startlinha = (linha / 2) * 2;
        int startCol = (coluna / 2) * 2;
        for (int i = startlinha; i < startlinha + 2; i++) {
            for (int j = startCol; j < startCol + 2; j++) {
                if (problema.tabuleiro[i][j] == num) {
                    return 0;
                }
            }
        }
    }

    return 1;
}

// verificacao se o sudoku esta completo
/* verifica se existem espaços por prencher, isto é, casas com zeros */

bool sudokuCompleto(ProblemaSudoku problema) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            if (problema.tabuleiro[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

// estatisticas

void Estatisticas(StatusProblema status[MAX_PROBLEMAS], int numProblemas, int totalJogos, int jogosBemSucedidos) {
    printf("\n===== Estatisticas =====\n");

    for (int i = 0; i < numProblemas; i++) {
        printf("Problema: %s \nJogado: %d vez(es)\n Jogadas invalidas: %d\n", status[i].nome, status[i].jogadas, status[i].jogadasInvalidas);
    }

    printf("Numero total de jogos: %d\n", totalJogos);
    printf("Numero de jogos concluidos com sucesso: %d\n", jogosBemSucedidos);

    if (totalJogos > 0) {
        float successPercentage = ((float)jogosBemSucedidos / totalJogos) * 100;
        printf("Percentagem de sucesso: %.1f%%\n", successPercentage);
    } else {
        printf("Percentagem de sucesso: Nao existe\n");
    }
}


// Guardar em ficherios


 /* Guardar Eststosticas */

void guardarEstatisticas(ProblemaSudoku problemas[MAX_PROBLEMAS], StatusProblema status[MAX_PROBLEMAS], int numProblemas, int totalJogos, int jogosBemSucedidos, char filename[]) {
    FILE *arquivo = fopen(filename, "w");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de estatisticas.\n");
        exit(0);
    }

    fprintf(arquivo, "Total de jogos: %d\nJogos Bem Sucedidos: %d\n", totalJogos, jogosBemSucedidos);

    for (int i = 0; i < numProblemas; i++) {
        fprintf(arquivo, "status: %s \njogadas:%d \njogadas invalidas: %d\n", status[i].nome, status[i].jogadas, status[i].jogadasInvalidas);
    }

    fclose(arquivo);
}

 /* Guardar Problemas */

void guardarProblemas(ProblemaSudoku problemas[MAX_PROBLEMAS], int numProblemas, char filename[]) {
    FILE *arquivo = fopen(filename, "w");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo para guardar problemas.\n");
        exit(0);
    }

    for (int i = 0; i < numProblemas; i++) {
        fprintf(arquivo, "%s\n", problemas[i].nome);
        for (int j = 0; j < TAMANHO; j++) {
            for (int k = 0; k < TAMANHO; k++) {
                fprintf(arquivo, "%d ", problemas[i].tabuleiro[j][k]);
            }
            fprintf(arquivo, "\n");
        }
    }

    fclose(arquivo);
}


// carregar ficheiros

/* Carregar estatisticas */

int carregarEstatisticas(StatusProblema status[MAX_PROBLEMAS], int *totalJogos, int *jogosBemSucedidos, char filename[]) {
    FILE *arquivo = fopen(filename, "r");
    if (!arquivo) {
        printf("Arquivo de estatisticas nao encontrado.\n");
        return 0;
    }

    fscanf(arquivo, "%d %d", totalJogos, jogosBemSucedidos);

    int i = 0;
    while (fscanf(arquivo, "%s %d", status[i].nome, &status[i].jogadas) == 2) {
        i++;
        if (i >= MAX_PROBLEMAS) {
            break;
        }
    }

    fclose(arquivo);
    return i;
}

/* Carregar Problemas */

int carregarProblemas(ProblemaSudoku problemas[MAX_PROBLEMAS], char filename[]) {
    FILE *arquivo = fopen(filename, "r");
    if (!arquivo) {
        printf("Arquivo de Problemas nao encontrado.\n");
        return 0;
    }

    int numProblemas = 0;
    while (fscanf(arquivo, "%s", problemas[numProblemas].nome) == 1) {
        for (int i = 0; i < TAMANHO; i++) {
            for (int j = 0; j < TAMANHO; j++) {
                fscanf(arquivo, "%d", &problemas[numProblemas].tabuleiro[i][j]);
            }
        }
        for (int i = 0; i < TAMANHO; i++) {
            for (int j = 0; j < TAMANHO; j++) {
                fscanf(arquivo, "%d", &problemas[numProblemas].solucao[i][j]);
            }
        }

        numProblemas++;
        if (numProblemas >= MAX_PROBLEMAS) {
            break; 
        }
    }

    fclose(arquivo);
    return numProblemas;
}