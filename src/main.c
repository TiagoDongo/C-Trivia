/*
- Tema do Quiz: 

- Autores:
    - Leonardo Domingues
    - Liedson Delgado
    - Tiago Dongo
    - 
*/

#include<stdio.h>
#include"quiz.h"
#include"util.h"



int main() {
    QuestionList list;
    createQuestionList(&list);

    printf("\n=== Mini-teste interativo do Quiz ===\n");

    int n = validateInt("Quantas perguntas deseja adicionar? ");

    for (int i = 0; i < n; i++) {
        printf("\nPergunta %d:\n", i + 1);

        // --- Pergunta ---
        char questionBuffer[256];
        while (!validateString("Digite a pergunta: ", questionBuffer, sizeof(questionBuffer)));

        char *questionCopy = (char *)malloc(strlen(questionBuffer) + 1);
        if (!questionCopy) exit(EXIT_FAILURE);
        strcpy(questionCopy, questionBuffer);

        // --- Opções ---
        char *options[4];
        char optionBuffer[4][100];

        for (int j = 0; j < 4; j++) {
            char prompt[50];
            sprintf(prompt, "Digite a opção %c: ", 'A' + j);
            while (!validateString(prompt, optionBuffer[j], sizeof(optionBuffer[j])));
            
            options[j] = (char *)malloc(strlen(optionBuffer[j]) + 1);
            if (!options[j]) exit(EXIT_FAILURE);
            strcpy(options[j], optionBuffer[j]);
        }

        // --- Resposta correta ---
        char answerBuffer[10];
        char correctAnswer;
        do {
            while (!validateString("Digite a letra da resposta correta (A-D): ", answerBuffer, sizeof(answerBuffer)));
            correctAnswer = toupper(answerBuffer[0]);
        } while (correctAnswer < 'A' || correctAnswer > 'D');

        // --- Criar e adicionar questão ---
        QuestionNode *q = createQuestion(questionCopy, options, correctAnswer);
        addNewQuestion(&list, q);
    }

    printf("\n=== Todas as perguntas adicionadas ===\n");
    showAllQuestions(list);

    if (!emptyQuestionList(list)) {
        int pos;

        printf("\n=== Remover pergunta ===\n");
        pos = validateInt("Digite a posição da pergunta a remover: ");
        int rm  = removeQuestionByPosition(&list, pos);

        if (rm) {
            printf("Pergunta da posição %d removida com sucesso.\n", pos);
        } else {
            printf("Erro: posição inválida ou lista vazia.\n");
        }

        printf("\n=== Lista após remoção ===\n");
        showAllQuestions(list);
    }

    // --- Liberar memória ---
    freeQuestionList(&list);

    printf("\nMemória liberada. Encerrando o mini-quiz.\n");

    return 0;
}
