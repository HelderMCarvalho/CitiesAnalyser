#include <stdio.h>
#include "Partials/Headers/Cidades.h"

#define clear()     printf("\e[1;1H\e[2J")

int main() {
    int opcaoMenu = 0, opcaoFicheiro = 0;
    FILE *ficheiroWC = NULL, *ficheiroCidadesDestinos = NULL;
    CidadesTree *cidadesPorId = NULL, *cidadesPorNome = NULL;
    do {
        printf("\nEscolha o ficheiro que pretende analisar:");
        printf("\n\t1 -> Pequeno");
        printf("\n\t2 -> Grande");
        printf("\n\tOpção: ");
        scanf("%d", &opcaoFicheiro);
        switch (opcaoFicheiro) {
            case 1: {
                ficheiroWC = fopen("./dados/small/worldcities.csv", "r");
                ficheiroCidadesDestinos = fopen("./dados/small/cidadesPT.txt", "r");
                break;
            }
            case 2: {
                ficheiroWC = fopen("./dados/BIG/worldcities.csv", "r");
                ficheiroCidadesDestinos = fopen("./dados/BIG/cidadesIberia.txt", "r");
                break;
            }
            default: {
                printf("\t\tOpção inválida!\n\n");
            }
        }
    } while (opcaoFicheiro != 1 && opcaoFicheiro != 2);
    if (!ficheiroWC) {
        printf("\nNão foi possível abrir o ficheiroWC!\n");
        perror("fopen");
        exit(1);
    }
    if (!ficheiroCidadesDestinos) {
        printf("\nNão foi possível abrir o ficheiroCidadesDestinos!\n");
        perror("fopen");
        exit(1);
    }
    while (!feof(ficheiroWC)) {
        char line[512];
        char *aux;
        fgets(line, 512, ficheiroWC);
        if (!feof(ficheiroWC)) {
            // Coluna 1
            for (aux = line; *aux != ','; aux++) {}
            char *aux2 = strdup(aux + 1);
            *aux = '\0';
//            printf("\n%s", line);

            // Coluna 2
            for (aux = aux2; *aux != ','; aux++) {}
            char *aux3 = strdup(aux + 1);
            *aux = '\0';
//            printf(" %s", aux2);

            // Coluna 3
            for (aux = aux3; *aux != ','; aux++) {}
            char *aux4 = strdup(aux + 1);
            *aux = '\0';
//            printf(" %s", aux3);

            // Coluna 4
            for (aux = aux4; *aux != ','; aux++) {}
            char *aux5 = strdup(aux + 1);
            *aux = '\0';
//            printf(" %s", aux4);

            // Coluna 5
            for (aux = aux5; *aux != ','; aux++) {}
            char *aux6 = strdup(aux + 1);
            *aux = '\0';
//            printf(" %s", aux5);

            // Coluna 6
            for (aux = aux6; *aux != ','; aux++) {}
            char *aux7 = strdup(aux + 1);
            *aux = '\0';
//            printf(" %s", aux6);

            // Coluna 7
            for (aux = aux7; *aux != ','; aux++) {}
            char *aux8 = strdup(aux + 1);
            *aux = '\0';
//            printf(" %s", aux7);

            // Coluna 8
            for (aux = aux8; *aux != ','; aux++) {}
            char *aux9 = strdup(aux + 1);
            *aux = '\0';
//            printf(" %s", aux8);

            // Coluna 9
            for (aux = aux9; *aux != ','; aux++) {}
            char *aux10 = strdup(aux + 1);
            *aux = '\0';
//            printf(" %s", aux9);

            // Coluna 10
            for (aux = aux10; *aux != ','; aux++) {}
            char *aux11 = strdup(aux + 1);
            *aux = '\0';
//            printf(" %s", aux10);

            // Coluna 11
            for (aux = aux11; *aux != ',' && *aux != '\0'; aux++) {}
            *aux = '\0';
//            printf(" %s", aux11);

            int id = atoi(aux11), totalHabitantes = atoi(aux10);

            if (id != 0) {
                cidadesPorId = InserirCidadeTreePorId(cidadesPorId, id, aux2, totalHabitantes, 0);
                cidadesPorNome = InserirCidadeTreePorNome(cidadesPorNome, id, aux2, totalHabitantes, 0);
            }

            free(aux2);
            free(aux3);
            free(aux4);
            free(aux5);
            free(aux6);
            free(aux7);
            free(aux8);
            free(aux9);
            free(aux10);
            free(aux11);
        }
    }

    while (!feof(ficheiroCidadesDestinos)) {
        char line[512];
        char *aux;
        fgets(line, 512, ficheiroCidadesDestinos);
        if (!feof(ficheiroCidadesDestinos)) {
            // Coluna 1
            for (aux = line; *aux != ','; aux++) {}
            char *aux2 = strdup(aux + 1);
            *aux = '\0';
//            printf("\n%s", line);

            // Coluna 2
            for (aux = aux2; *aux != ','; aux++) {}
            char *aux3 = strdup(aux + 1);
            *aux = '\0';
//            printf(" %s", aux2);

            // Coluna 3
            for (aux = aux3; *aux != ','; aux++) {}
            char *aux4 = strdup(aux + 1);
            *aux = '\0';
//            printf(" %s", aux3);

            // Coluna 4
            for (aux = aux4; *aux != ','; aux++) {}
            char *aux5 = strdup(aux + 1);
            *aux = '\0';
//            printf(" %s", aux4);

            // Coluna 5
            for (aux = aux5; *aux != ',' && *aux != '\0'; aux++) {}
            *aux = '\0';
//            printf(" %s", aux5);

            int idOrigem = atoi(line), idDestino = atoi(aux3);
            float distancia = (float) atof(aux5);
            InserirDestino(cidadesPorId, idOrigem, idDestino, distancia);

            free(aux2);
            free(aux3);
            free(aux4);
            free(aux5);
        }
    }
    clear();
    do {
        printf("\n\n----- MENU -----");
        printf("\nEscolha a sua opção:");
        printf("\n1 -> Ex. 1");
        printf("\n2 -> Ex. 2");
        printf("\n3 -> Ex. 3");
        printf("\n4 -> Ex. 4");
        printf("\n5 -> Ex. 5");
        printf("\n0 -> Sair");
        printf("\nOpção: ");
        scanf("%d", &opcaoMenu);
        switch (opcaoMenu) {
            case 1: {
                CidadesTree *cidadesTreeEncontradas = NULL;
                char *nomeCidade = NULL;
                printf("\tIntroduza o Nome da Cidade que quer pesquisar: ");
                scanf("%ms", &nomeCidade);
                cidadesTreeEncontradas = ProcurarCidadePorNome(cidadesPorNome, nomeCidade, cidadesTreeEncontradas);
                while (!cidadesTreeEncontradas) {
                    printf("\t\tCidade inexistente! Tente de novo.\n\n\tIntroduza o Nome da Cidade que quer pesquisar: ");
                    scanf("%ms", &nomeCidade);
                    cidadesTreeEncontradas = ProcurarCidadePorNome(cidadesPorNome, nomeCidade, cidadesTreeEncontradas);
                }
                free(nomeCidade);
                ListarIdCidadesTree(cidadesTreeEncontradas);
                DestruirCidadesTree(cidadesTreeEncontradas);
                break;
            }
            case 2: {
                int idCidade;
                printf("\tIntroduza o Id da Cidade que quer ver os Destinos diretos: ");
                scanf("%d", &idCidade);
                CidadesTree *cidadeOrigem = ProcurarCidadePorId(cidadesPorId, idCidade);
                while (!cidadeOrigem) {
                    printf("\t\tCidade inexistente! Tente de novo.\n\n\tIntroduza o Id da Cidade que quer ver os Destinos: ");
                    scanf("%d", &idCidade);
                    cidadeOrigem = ProcurarCidadePorId(cidadesPorId, idCidade);
                }
                ListarIdNomeDistanciaCidadesTree(cidadeOrigem->destinos);
                break;
            }
            case 3: {
                ListaEx3(cidadesPorId);
                break;
            }
            case 4: {
                ListaEx4(cidadesPorId);
                break;
            }
            case 5: {
                int idCidadeOrigem, idCidadeDestino, idsIguais = 0;
                do {
                    if (idsIguais) {
                        printf("\t\tId de Origem e Destino igual!\n\n");
                    }
                    printf("\tIntroduza o Id da Cidade de origem: ");
                    scanf("%d", &idCidadeOrigem);
                    CidadesTree *cidadeOrigem = ProcurarCidadePorId(cidadesPorId, idCidadeOrigem);
                    while (!cidadeOrigem) {
                        printf("\t\tCidade inexistente! Tente de novo.\n\n\tIntroduza o Id da Cidade de origem: ");
                        scanf("%d", &idCidadeOrigem);
                        cidadeOrigem = ProcurarCidadePorId(cidadesPorId, idCidadeOrigem);
                    }
                    printf("\tIntroduza o Id da Cidade de destino: ");
                    scanf("%d", &idCidadeDestino);
                    CidadesTree *cidadeDestino = ProcurarCidadePorId(cidadesPorId, idCidadeDestino);
                    while (!cidadeDestino) {
                        printf("\t\tCidade inexistente! Tente de novo.\n\n\tIntroduza o Id da Cidade de origem: ");
                        scanf("%d", &idCidadeDestino);
                        cidadeDestino = ProcurarCidadePorId(cidadesPorId, idCidadeDestino);
                    }
                    idsIguais = idCidadeOrigem == idCidadeDestino ? 1 : 0;
                } while (idsIguais);
                EncontrarCaminho(cidadesPorId, idCidadeOrigem, idCidadeDestino);
                break;
            }
            case 0: {
                DestruirCidadesTree(cidadesPorId);
                DestruirCidadesTree(cidadesPorNome);
                exit(1);
                break;
            }
            default: {
                printf("\n\tOpção inválida!");
                break;
            }
        }
    } while (opcaoMenu != 0);
//    int i;
//    scanf("%d", &i); // Impede a saída do programa
    return 0;
}