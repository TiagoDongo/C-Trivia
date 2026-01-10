#include"quiz.h"
#include"util.h"

void menu(){
    int option;
    do
    {
        printf("\n----- QUIZ GAME -----\n");
        printf("1 - Jogar\n");
        printf("2 - Adicionar nova pergunta\n");
        printf("3 - Eliminar pergunta\n");
        printf("4 - Mostrar  todas as perguntas\n");
        printf("5 - Mostrar classificacao\n");
        printf("6 - Procurar Jogador\n");
        printf("0 - Sair\n");
        option = validateInt("Digite a tua opcao: ");

        switch (option){
            case 1:
                break;

            case 2:
                break;

            case 3:
                break;

            case 4:
                break;

            case 5:
                break;

            case 6:
                break;

            case 0:
                printf("Saindo...\n");
                break;
        
            default:
                printf("ERRO: opcao invalida!\n");
                break;
        }
    } while (option != 0);
    
}

void createQuestionList(QuestionList *qlist){
    *qlist = NULL;
}

int emptyQuestionList(QuestionList qList){
    return (qList == NULL);
}

QuestionNode *createQuestion(char *question, char *options[4], char correctAnswer){
    QuestionNode *newNode = (QuestionNode*)malloc(sizeof(QuestionNode));
    if(newNode == NULL){
        return NULL;
    }

    newNode->question = question;

    for (int i = 0; i < 4; i++){
        newNode->options[i] = options[i];
    }
    
    newNode->correctAnswer = correctAnswer;
    newNode->next = NULL;

    return newNode;
}

void addNewQuestion(QuestionList *qList, QuestionNode *question){
    if (!qList || !question){
        return;
    }

    if (emptyQuestionList(*qList)){
        *qList = question;
        question->next = NULL;
        return;
    }

    QuestionNode *currentNode = *qList;
    while (currentNode->next != NULL){
        currentNode = currentNode->next;
    }
    
    currentNode->next = question;
    question->next = NULL;
}

int removeQuestion(QuestionList *qList, QuestionNode *questionToRemove){
    
    //Verifica se a lista está vazia (aponta para NULL)
    if(emptyQuestionList(*qList)){
        return 0;  // Lista vazia, não há o que remover
    }
    
    // 3. Verifica se o nó a ser removido é NULL
    if(questionToRemove == NULL) {
        return 0; // Nó inválido, não faz nada
    }
    
    QuestionList q = *qList;

    //caso o nó a ser  removido for o primeiro
    if(q == questionToRemove) { 
        *qList = q->next;
        free(q);
        return 1;
    }

    //busca o nó no  resto dalista
    while(q->next  != NULL && q->next != questionToRemove){
        q = q->next;
    }

    //caso se encontrar  o nó
    if(q->next == questionToRemove) {
        QuestionNode *qToRemove  = q->next;
        q->next = qToRemove->next;
        free(qToRemove);
        return 1;
    }else{
        return 0;
    }
}