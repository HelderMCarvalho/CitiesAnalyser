#ifndef TP2_AEDII_CIDADES_H
#define TP2_AEDII_CIDADES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CALLOC(quantidade, tipo)    (tipo*) calloc(quantidade, sizeof(tipo))

/**
 * Árvore que guarda Cidades.
 */
typedef struct cidadesTree {
    int id, totalHabitantes, totalDestinos;
    char *nome;
    float distancia;
    struct cidadesTree *destinos, *left, *right;
} CidadesTree;

/**
 * Lista que guarda Cidades.
 *
 * Utilizada apenas no procedimento "EncontrarCaminho".
 */
typedef struct cidadesLista {
    int id;
    float distancia;
    struct cidadesLista *next;
} CidadesLista;

/**
 * Lista auxiliar que guarda conexões entre Cidades.
 *
 * Utilizada apenas no procedimento "EncontrarCaminho".
 */
typedef struct auxRecord {
    int idCidade, conexao;
    float distanciaAteAqui;
    struct auxRecord *next_rec;
} AuxRecord;

CidadesTree *InserirCidadeTreePorId(CidadesTree *cidadesTree, int id, char *nome, int totalHabitantes, float distancia);

CidadesTree *InserirCidadeTreePorNome(CidadesTree *cidadesTree, int id, char *nome, int totalHabitantes,
                                      float distancia);

CidadesTree *ProcurarCidadePorId(CidadesTree *cidadesTree, int id);

CidadesTree *ProcurarCidadePorNome(CidadesTree *cidadesTree, char *nome, CidadesTree *cidadesTreeEncontradas);

void InserirDestino(CidadesTree *cidadesTree, int idOrigem, int idDestino, float distancia);

void ListarIdCidadesTree(CidadesTree *cidadesTree);

void ListarIdNomeCidadesTree(CidadesTree *cidadesTree);

void ListarIdNomeDistanciaCidadesTree(CidadesTree *cidadesTree);

void ListaEx3(CidadesTree *cidadesTree);

CidadesTree *VerificaDestinosEx3(CidadesTree *destinos, CidadesTree *cidadesTree);

void ListaEx4(CidadesTree *cidadesTree);

void DestruirCidadesTree(CidadesTree *cidadesTree);

void DestruirAuxRecord(AuxRecord *auxRecord);

void ListarCidadesTree(CidadesTree *cidadesTree);

void EncontrarCaminho(CidadesTree *cidadesTree, int idOrigem, int idDestino);

void ListarCaminho(AuxRecord *auxRecord, CidadesTree *cidadesTree);

CidadesLista *CidadesTreeParaLista(CidadesLista *cidadesLista, CidadesTree *cidadesTree);

AuxRecord *InitAuxRecord(int id);

AuxRecord *NovoAuxRecord(AuxRecord *auxRecord, AuxRecord *auxRecordAdicionar);

AuxRecord *InserirElementoCaminho(AuxRecord *auxRecord, int idCidade, int conexao);

AuxRecord *ProcurarAuxRecordPorId(AuxRecord *auxRecord, int id);

#endif //TP2_AEDII_CIDADES_H