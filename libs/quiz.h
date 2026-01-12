/**
 * @file quiz.h
 * @brief Header principal do sistema de quiz
 * 
 * Este ficheiro contém as declarações de estruturas de dados e funções
 * para o sistema de gerenciamento de quiz, incluindo:
 * - Árvore binária de jogadores
 * - Lista ligada de questões
 * - Funções de manipulação de dados
 */

#ifndef QUIZ_H_INCLUDED
#define QUIZ_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/**
 * @brief Estrutura que de dados responsavel por armazenar os jogadores
 * 
 * @param playerName array de caracteres que armazena o nome do jogador
 * @param score inteiro que armazena a pontuação do jogador
 * @param *left ponteiro para o nó filho esquerdo
 * @param *right ponteiro para o nó filho direito
 */
typedef struct player {
    char playerName[100];      ///< Nome do jogador (máx. 99 caracteres + '\0')
    int score;                 ///< Pontuação atual do jogador
    struct player *left;       ///< Ponteiro para subárvore esquerda (nomes menores)
    struct player *right;      ///< Ponteiro para subárvore direita (nomes maiores)
} Player;

void arvoraPlayer(Player **root);


Player *createPlayerTree( const char* nome, int score)


/**
 * @brief estrututa de dados responsavel por armazenar uma lista de perguntas
 
 * @param *question ponteiro do tipo char que armazera a pergunta
 * @param *option array de string que armazera a `4 opções` de resposta 
 * @param correctAnswer caracter que armazera a resposta correta
 * @param *next ponteiro para o proximo nó da lista
 * 
 */
typedef struct questionNode{
    char *question;
    char *options[4];
    char correctAnswer;
    struct questionNode *next;
}QuestionNode;


/**
 * @brief Tipo para representar uma lista de questões
 */
typedef QuestionNode *QuestionList;

/**
 * @brief Função que imprime o menu principal do sistema
 */
void menu();

// question functions

/**
 * @brief Inicializa uma lista de questões como vazia
 * @param qlist Ponteiro para a lista a ser inicializada
 */
void createQuestionList(QuestionList *qlist); 

/**
 * @brief Verifica se uma lista de questões está vazia
 * @param qList Lista de questões a verificar
 * @return 1 se vazia, 0 se não
 */
int emptyQuestionList(QuestionList qList);

/**
 * @brief Adiciona uma questão ao final da lista
 * @param qList Ponteiro para a lista
 * @param question Questão a adicionar
 */
void  addNewQuestion(QuestionList *qList, QuestionNode *question);

/**
 * @brief Cria uma nova questão
 * @param questionText Texto da pergunta
 * @param options Array de 4 opções
 * @param correctAnswer Resposta correta (A-D)
 * @return Ponteiro para questão ou NULL se erro
 */
QuestionNode *createQuestion(char *question, char *options[4], char correctAnswer);

/**
 * @brief Remove uma questão da lista
 * @param qList Ponteiro para a lista
 * @param questionToRemove Questão a remover
 * @return `1` se sucesso, `0` se erro
 */
int removeQuestion(QuestionList *qList, QuestionNode *questionToRemove);

#endif