#include "Headers/Cidades.h"

/**
 * Insere Cidades na árvore, ordenada por ordem crescente de Id.
 *
 * Total de Destinos inicial e Distância para ela mesma é 0.
 * @param cidadesTree Árvore de Cidades
 * @param id Id da nova Cidade
 * @param nome Nome da nova Cidade
 * @param totalHabitantes Total de Habitantes da nova Cidade
 * @param distancia Distância entre a origem e destino
 * @return Árvore de Cidades atualizada
 */
CidadesTree *InserirCidadeTreePorId(CidadesTree *cidadesTree, int id, char *nome, int totalHabitantes,
                                    float distancia) {
    if (cidadesTree) {
        if (id < cidadesTree->id)
            cidadesTree->left = InserirCidadeTreePorId(cidadesTree->left, id, nome, totalHabitantes, distancia);
        else
            cidadesTree->right = InserirCidadeTreePorId(cidadesTree->right, id, nome, totalHabitantes, distancia);
    } else {
        cidadesTree = CALLOC(1, CidadesTree);
        cidadesTree->id = id;
        cidadesTree->nome = strdup(nome);
        cidadesTree->totalHabitantes = totalHabitantes;
        cidadesTree->totalDestinos = 0;
        cidadesTree->distancia = distancia;
        cidadesTree->left = cidadesTree->right = NULL;
    }
    return cidadesTree;
}

/**
 * Insere Cidades na árvore, ordenadas por ordem alfabética crescente, com repetições.
 *
 * Total de Destinos inicial e Distância para ela mesma é 0.
 * @param cidadesTree Árvore de Cidades
 * @param id Id da nova Cidade
 * @param nome Nome da nova Cidade
 * @param totalHabitantes Total de Habitantes da nova Cidade
 * @param distancia Distância entre a origem e destino
 * @return Árvore de Cidades atualizada
 */
CidadesTree *InserirCidadeTreePorNome(CidadesTree *cidadesTree, int id, char *nome, int totalHabitantes,
                                      float distancia) {
    if (cidadesTree) {
        if (strcmp(nome, cidadesTree->nome) < 0)
            cidadesTree->left = InserirCidadeTreePorNome(cidadesTree->left, id, nome, totalHabitantes, distancia);
        else
            cidadesTree->right = InserirCidadeTreePorNome(cidadesTree->right, id, nome, totalHabitantes, distancia);
    } else {
        cidadesTree = CALLOC(1, CidadesTree);
        cidadesTree->id = id;
        cidadesTree->nome = strdup(nome);
        cidadesTree->totalHabitantes = totalHabitantes;
        cidadesTree->totalDestinos = 0;
        cidadesTree->distancia = distancia;
        cidadesTree->left = cidadesTree->right = NULL;
    }
    return cidadesTree;
}

/**
 * Procura uma Cidade com um determinado Id, numa árvore.
 * @param cidadesTree Árvore de Cidades
 * @param id Id da Cidade a procurar
 * @return
 *      @param cidadesTree Cidade encontrada
 *      @param NULL Cidade não encontrada
 */
CidadesTree *ProcurarCidadePorId(CidadesTree *cidadesTree, int id) {
    if (cidadesTree) {
        if (id < cidadesTree->id)
            return ProcurarCidadePorId(cidadesTree->left, id);
        else if (id > cidadesTree->id)
            return ProcurarCidadePorId(cidadesTree->right, id);
        else
            return cidadesTree;
    } else
        return NULL;
}

/**
 * Procura a primeira Cidade com um determinado Nome, numa árvore.
 *
 * Quando a encontrar, enquanto o Nome da Cidade a encontrar for igual ao Nome da Cidade a ser percorrida, esta é
 * guardada e a verificação é passada para o ramo "right". Repete até não existirem Cidades com esse Nome.
 * @param cidadesTree Árvore de Cidades
 * @param nome Nome da Cidade a procurar
 * @param cidadesTreeEncontradas Árvore com as Cidades encontradas (entra a NULL)
 * @return
 *      @param cidadesTreeEncontradas Árvore com todas as Cidades encontradas
 *      @param NULL Nenhuma Cidade encontrada
 */
CidadesTree *ProcurarCidadePorNome(CidadesTree *cidadesTree, char *nome, CidadesTree *cidadesTreeEncontradas) {
    if (cidadesTree) {
        if (strcmp(nome, cidadesTree->nome) < 0)
            return ProcurarCidadePorNome(cidadesTree->left, nome, cidadesTreeEncontradas);
        else if (strcmp(nome, cidadesTree->nome) > 0)
            return ProcurarCidadePorNome(cidadesTree->right, nome, cidadesTreeEncontradas);
        else {
            while (cidadesTree != NULL) {
                if (strcmp(nome, cidadesTree->nome) == 0) {
                    cidadesTreeEncontradas = InserirCidadeTreePorId(cidadesTreeEncontradas, cidadesTree->id,
                                                                    cidadesTree->nome, cidadesTree->totalHabitantes,
                                                                    cidadesTree->distancia);
                    cidadesTree = cidadesTree->right;
                } else
                    break;
            }
            return cidadesTreeEncontradas;
        }
    } else
        return NULL;
}

/**
 * Insere um Destino na Cidade.
 *
 * Se esse destino já existir mas a nova distância for menor, vai atualizar a distância.
 * @param cidadesTree Árvore de Cidades
 * @param idOrigem Id da Cidade de Origem
 * @param idDestino Id da Cidade de Destino
 * @param distancia Distância entre a origem e destino
 */
void InserirDestino(CidadesTree *cidadesTree, int idOrigem, int idDestino, float distancia) {
    CidadesTree *cidadeOrigem = ProcurarCidadePorId(cidadesTree, idOrigem);
    CidadesTree *cidadeDestino = ProcurarCidadePorId(cidadesTree, idDestino);
    if (cidadeOrigem && cidadeDestino) {
        CidadesTree *cidadeDestinoNosDestinos = ProcurarCidadePorId(cidadeOrigem->destinos, idDestino);
        if (!cidadeDestinoNosDestinos) {
            cidadeOrigem->destinos = InserirCidadeTreePorId(cidadeOrigem->destinos, cidadeDestino->id,
                                                            cidadeDestino->nome, cidadeDestino->totalHabitantes,
                                                            distancia);
            cidadeOrigem->totalDestinos++;
        } else if (distancia < cidadeDestinoNosDestinos->distancia)
            cidadeDestinoNosDestinos->distancia = distancia;
    }
}

/**
 * Lista o Id das Cidades da árvore.
 *
 * Utilizada no Ex.: 1
 * @param cidadesTree Árvore de Cidades a listar
 */
void ListarIdCidadesTree(CidadesTree *cidadesTree) {
    if (cidadesTree) {
        ListarIdCidadesTree(cidadesTree->left);
        printf("\t\tId: %d\n", cidadesTree->id);
        ListarIdCidadesTree(cidadesTree->right);
    }
}

/**
 * Lista o Id e o Nome das Cidades da árvore.
 *
 * Utilizada no Ex.: 3
 * @param cidadesTree Árvore de Cidades a listar
 */
void ListarIdNomeCidadesTree(CidadesTree *cidadesTree) {
    if (cidadesTree) {
        ListarIdNomeCidadesTree(cidadesTree->left);
        printf("\t\t%d - %s\n", cidadesTree->id, cidadesTree->nome);
        ListarIdNomeCidadesTree(cidadesTree->right);
    }
}

/**
 * Lista o Id, Nome e Distância das Cidades da árvore.
 *
 * Utilizada no Ex.: 2
 * @param cidadesTree Árvore de Cidades a listar
 */
void ListarIdNomeDistanciaCidadesTree(CidadesTree *cidadesTree) {
    if (cidadesTree) {
        ListarIdNomeDistanciaCidadesTree(cidadesTree->left);
        printf("\t\t %d - %s - %f km\n", cidadesTree->id, cidadesTree->nome, cidadesTree->distancia);
        ListarIdNomeDistanciaCidadesTree(cidadesTree->right);
    }
}

/**
 * Lista as Cidades com mais de 50000 habitantes e para cada uma delas lista as Cidades com menos de 30000 habitantes
 * para as quais é possível viajar diretamente.
 *
 * Utilizada no Ex.: 3
 * @param cidadesTree Árvore de Cidades a verificar
 */
void ListaEx3(CidadesTree *cidadesTree) {
    if (cidadesTree) {
        ListaEx3(cidadesTree->left);
        if (cidadesTree->totalHabitantes > 50000) {
            CidadesTree *destinos = NULL;
            destinos = VerificaDestinosEx3(destinos, cidadesTree->destinos);
            if (destinos) {
                printf("\t%d - %s\n", cidadesTree->id, cidadesTree->nome);
                ListarIdNomeCidadesTree(destinos);
                DestruirCidadesTree(destinos);
                printf("\n");
            }
        }
        ListaEx3(cidadesTree->right);
    }
}

/**
 * Verifica os destinos de uma determinada Cidade.
 *
 * Auxiliar do procedimento ListaEx3.
 * @param destinos Árvore com os destinos
 * @param cidadesTree Cidade a verificar
 * @return Árvore com todos os Destinos com menos de 30000 habitantes
 */
CidadesTree *VerificaDestinosEx3(CidadesTree *destinos, CidadesTree *cidadesTree) {
    if (cidadesTree) {
        destinos = VerificaDestinosEx3(destinos, cidadesTree->left);
        if (cidadesTree->totalHabitantes < 30000)
            return destinos = InserirCidadeTreePorId(destinos, cidadesTree->id, cidadesTree->nome,
                                                     cidadesTree->totalHabitantes, cidadesTree->distancia);
        destinos = VerificaDestinosEx3(destinos, cidadesTree->right);
    }
    return destinos;
}

/**
 * Lista as Cidades que têm mais do que 1 destino.
 * @param cidadesTree Árvore de Cidades a listar
 */
void ListaEx4(CidadesTree *cidadesTree) {
    if (cidadesTree) {
        ListaEx4(cidadesTree->left);
        if (cidadesTree->totalDestinos > 1)
            printf("\t%d - %s - %d\n", cidadesTree->id, cidadesTree->nome, cidadesTree->totalDestinos);
        ListaEx4(cidadesTree->right);
    }
}

/**
 * Destrói a árvore das Cidades.
 * @param cidadesTree Árvore a destruir
 */
void DestruirCidadesTree(CidadesTree *cidadesTree) {
    if (cidadesTree) {
        DestruirCidadesTree(cidadesTree->left);
        DestruirCidadesTree(cidadesTree->right);
        DestruirCidadesTree(cidadesTree->destinos);
        free(cidadesTree->nome);
        free(cidadesTree);
    }
}

/**
 * Destrói a lista AuxRecord.
 * @param auxRecord AuxRecord a destruir
 */
void DestruirAuxRecord(AuxRecord *auxRecord) {
    if (auxRecord) {
        DestruirAuxRecord(auxRecord->next_rec);
        free(auxRecord);
    }
}

/**
 * Destrói a lista de Cidades.
 * @param cidadesLista  Lista de Cidades a destruir
 */
void DestruirCidadesLista(CidadesLista *cidadesLista) {
    if (cidadesLista) {
        DestruirCidadesLista(cidadesLista->next);
        free(cidadesLista);
    }
}

/**
 * Lista todos os dados da árvore de Cidades.
 * @param cidadesTree Árvore de Cidades a listar
 */
void ListarCidadesTree(CidadesTree *cidadesTree) {
    if (cidadesTree) {
        ListarCidadesTree(cidadesTree->left);
        printf("\tId: %d | Nome: %s | Total Habitantes: %d | Total Destinos: %d\n", cidadesTree->id, cidadesTree->nome,
               cidadesTree->totalHabitantes, cidadesTree->totalDestinos);
        ListarCidadesTree(cidadesTree->right);
    }
}

/**
 * Encontra e lista o caminho entre duas Cidades.
 * @param cidadesTree Árvore de Cidades
 * @param idOrigem Id da Cidade de Origem
 * @param idDestino Id da Cidade de Destino
 */
void EncontrarCaminho(CidadesTree *cidadesTree, int idOrigem, int idDestino) {
    AuxRecord *current = NULL, *open = InitAuxRecord(idOrigem), *closed = NULL;
    while (open) {
        current = open;
        open = open->next_rec;
        current->next_rec = NULL;
        if (current->idCidade == idDestino) break;
        CidadesLista *destinos = NULL;
        destinos = CidadesTreeParaLista(destinos, ProcurarCidadePorId(cidadesTree, current->idCidade)->destinos);
        for (CidadesLista *d = destinos; d; d = d->next) {
            if (ProcurarAuxRecordPorId(closed, d->id)) continue;
            float distanciaAteAqui = current->distanciaAteAqui + d->distancia;
            AuxRecord *destinationRecord = NULL;
            destinationRecord = ProcurarAuxRecordPorId(open, d->id);
            if (destinationRecord) {
                if (destinationRecord->distanciaAteAqui <= distanciaAteAqui) continue;
            } else {
                destinationRecord = InitAuxRecord(d->id);
            }
            destinationRecord->distanciaAteAqui = distanciaAteAqui;
            destinationRecord->conexao = current->idCidade;
            if (!ProcurarAuxRecordPorId(open, d->id))
                open = NovoAuxRecord(open, destinationRecord);
        }
        closed = NovoAuxRecord(closed, current);
        DestruirCidadesLista(destinos);
    }
    if (current->idCidade == idDestino) {
        AuxRecord *caminho = NULL;
        printf("\n\t\tDistância total: %f km", current->distanciaAteAqui);
        while (current->idCidade != idOrigem) {
            caminho = InserirElementoCaminho(caminho, current->idCidade, current->conexao);
            current = ProcurarAuxRecordPorId(closed, current->conexao);
        }
        ListarCaminho(caminho, cidadesTree);
        DestruirAuxRecord(caminho);
    }
    DestruirAuxRecord(open);
    DestruirAuxRecord(closed);
}

/**
 * Lista o caminho entre uma cidade origem e destino.
 * @param auxRecord Lista com o caminho entre as Cidades
 * @param cidadesTree Árvore de Cidades
 */
void ListarCaminho(AuxRecord *auxRecord, CidadesTree *cidadesTree) {
    if (auxRecord && auxRecord->conexao != 0) {
        printf("\n\t\t%d - \"%s\" -> %d - \"%s\"", auxRecord->conexao,
               ProcurarCidadePorId(cidadesTree, auxRecord->conexao)->nome, auxRecord->idCidade,
               ProcurarCidadePorId(cidadesTree, auxRecord->idCidade)->nome);
        ListarCaminho(auxRecord->next_rec, cidadesTree);
    }
}

/**
 * Converte uma árvore de Cidades para uma lista de Cidades.
 * @param cidadesLista Lista a ser preenchida
 * @param cidadesTree Árvore a ser convertida
 * @return Lista de Cidades
 */
CidadesLista *CidadesTreeParaLista(CidadesLista *cidadesLista, CidadesTree *cidadesTree) {
    if (cidadesTree) {
        cidadesLista = CidadesTreeParaLista(cidadesLista, cidadesTree->left);

        CidadesLista *novo = CALLOC(1, CidadesLista);
        novo->id = cidadesTree->id;
        novo->distancia = cidadesTree->distancia;
        novo->next = cidadesLista;
        cidadesLista = novo;

        cidadesLista = CidadesTreeParaLista(cidadesLista, cidadesTree->right);
    }
    return cidadesLista;
}

/**
 * Inicia uma lista AuxRecord com um Id de uma Cidade.
 *
 * Utilizada no procedimento "EncontrarCaminho".
 * @param id Id da Cidade inicial
 * @return Elemento criado
 */
AuxRecord *InitAuxRecord(int id) {
    AuxRecord *new = CALLOC(1, AuxRecord);
    new->idCidade = id;
    new->conexao = 0;
    new->distanciaAteAqui = 0;
    new->next_rec = NULL;
    return new;
}

/**
 * Adiciona uma Cidade à lista AuxRecord.
 *
 * Utilizada no procedimento "EncontrarCaminho".
 * @param auxRecord Lista a ser modificada
 * @param auxRecordAdicionar Elemento a adicionar
 * @return Lista modificada com o novo elemento
 */
AuxRecord *NovoAuxRecord(AuxRecord *auxRecord, AuxRecord *auxRecordAdicionar) {
    AuxRecord *novo = CALLOC(1, AuxRecord);
    novo->idCidade = auxRecordAdicionar->idCidade;
    novo->conexao = auxRecordAdicionar->conexao;
    novo->distanciaAteAqui = auxRecordAdicionar->distanciaAteAqui;
    novo->next_rec = auxRecord;
    auxRecord = novo;
    return auxRecord;
}

/**
 * Insere uma ligação entre Cidades.
 * @param auxRecord Lista de ligações entre Cidades
 * @param idCidade Id da Cidade Origem
 * @param conexao Is da Cidade destino
 * @return Lista de ligações entre Cidades atualizada
 */
AuxRecord *InserirElementoCaminho(AuxRecord *auxRecord, int idCidade, int conexao) {
    AuxRecord *novo = CALLOC(1, AuxRecord);
    novo->idCidade = idCidade;
    novo->conexao = conexao;
    novo->distanciaAteAqui = 0;
    novo->next_rec = auxRecord;
    auxRecord = novo;
    return auxRecord;
}

/**
 * Procura um elemento da lista AuxRecord.
 * @param auxRecord Lista a ser percorrida
 * @param id Id do elemento a procurar
 * @return
 *      @param auxRecord Elemento encontrado
 *      @param NULL Elemento não encontrado
 */
AuxRecord *ProcurarAuxRecordPorId(AuxRecord *auxRecord, int id) {
    if (!auxRecord)
        return NULL;
    else if (auxRecord->idCidade == id)
        return auxRecord;
    return ProcurarAuxRecordPorId(auxRecord->next_rec, id);
}