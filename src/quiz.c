#include"quiz.h"
#include"util.h"


void menu(QuestionList *list){
    int option;
    do{
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

            case 3:{
                if(!emptyQuestionList(*list)){
                    printf("\n=== Remover pergunta ===\n");

                    int position = validateInt("Digite a posicao da pergunta a remover: ");;
                    int removedQuestion = removeQuestionByPosition(list, position);

                    if(removedQuestion){
                        printf("SUCESSO: pergunta na posicao %d foi removida.\n", position);
                    } else {
                        printf("ERRO: posicao invalida ou lista vazia");
                    }
                }
                break;
            }

            case 4:
                showAllQuestions(*list);
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

//========================= QUIZ FUNCTIONS ========================================

void createQuestionList(QuestionList *list){
    *list = NULL;
}

int emptyQuestionList(QuestionList list){
    return (list == NULL);
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

void addNewQuestion(QuestionList *list, QuestionNode *question){
    if (!list || !question){
        return;
    }

    question->next  = NULL;

    if(emptyQuestionList(*list)){
        *list = question;
        return;
    }

    QuestionNode *currentNode  = *list;
    while (currentNode->next !=  NULL){
        currentNode = currentNode->next;
    }
    
    currentNode->next = question;
}

int removeQuestion(QuestionList *list, QuestionNode *questionToRemove){
    
    //Verifica se a lista está vazia (aponta para NULL)
    if(emptyQuestionList(*list)){
        return 0;  // Lista vazia, não há o que remover
    }
    
    // 3. Verifica se o nó a ser removido é NULL
    if(questionToRemove == NULL) {
        return 0; // Nó inválido, não faz nada
    }
    
    QuestionList q = *list;

    //caso o nó a ser  removido for o primeiro
    if(q == questionToRemove) { 
        *list = q->next;
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

void showAllQuestions(QuestionList list){
    if(emptyQuestionList(list)){
        printf("ERRO: lista esta vazia.\n");
        return;
    }

    int i = 1;
    QuestionList currentNode = list;
    printf("\n====== LISTA DE QUESTOES ======\n");
    while (currentNode != NULL){
        printf("- Questao %d: %s\n",i,currentNode->question);
        for(int j = 0; j < 4;  j++){
            printf("  %c) %s\n", 'A'+j,  currentNode->options[j]);
        }
        printf("Resposta correta: %c\n", currentNode->correctAnswer);
        currentNode = currentNode->next;
        i++;
    }
    printf("\n====== FIM DA LISTA DE QUESTOES ======\n\n");
}

void freeQuestionList(QuestionList *list) {
    QuestionNode *current = *list;
    while (current != NULL) {
        QuestionNode *next = current->next;

        free(current->question);
        for (int i = 0; i < 4; i++) {
            free(current->options[i]);
        }
        free(current);

        current = next;
    }
    *list = NULL;
}

int removeQuestionByPosition(QuestionList *list, int questionPosition){
    if(emptyQuestionList(*list))  return 0;

    QuestionList ql = *list;
    int n = 1;

    if(questionPosition == 1){
        *list = ql->next;
        for (int i = 0; i < 4; i++){
            free(ql->options[i]);
        }
        free(ql->question);
        free(ql);
        return 1;
    }

    while (ql != NULL && n <  questionPosition-1){
        ql =  ql->next;
        n++;
    }

    if(ql == NULL || ql->next == NULL) return 0;

    QuestionList  qR = ql->next;
    ql->next = qR->next;
    for(int i = 0; i < 4; i++){
        free(qR->options[i]);
    }
    free(qR->question);
    free(qR);
    return 1;    
}

//========================= FILE FUNCTIONS ========================================

void saveQuestionList(QuestionList list){
  FILE *file = fopen("data/ListOfQuestions.txt", "w");
  if(file ==  NULL){
    printf("ERRO: nao foi possivel abrir o ficheiro");
    return;
  }

  QuestionList l  = list;
  while (l  != NULL){
    fprintf(file, "%s\n", l->question);

    for(int i = 0; i<4; i++){
      fprintf(file, "%s\n", l->options[i]);
    }

    fprintf(file,  "%c\n", l->correctAnswer);
    l  = l->next;
  }
  fclose(file);
  printf("SUCESSO: lista de  perguntas guardada em data/\n");
}

void loadQuestionList(QuestionList *list){
  FILE  *file = fopen("data/ListOfQuestions.txt", "r");
  if(file ==  NULL){
    printf("ERRO: nao foi possivel abrir  o ficheiro");
    return;
  }

  createQuestionList(list);

  char qQuestion[256];
  char qOptions[4][100];
  char qAnswer;
  char buffer[10];

  while (fgets(qQuestion, sizeof(qQuestion), file)){
    qQuestion[strcspn(qQuestion, "\n")] = '\0';

    for(int i = 0; i < 4; i++){
      if(!fgets(qOptions[i], sizeof(qOptions[i]), file)) break;
      qOptions[i][strcspn(qOptions[i], "\n")] = '\0';
    }

    if(!fgets(buffer,  sizeof(buffer), file)) break;
    qAnswer = toupper(buffer[0]);

    char *questionCpy = malloc(strlen(qQuestion) + 1);
    strcpy(questionCpy,qQuestion);

    char *opt[4];
    for (int i = 0; i < 4; i++){
      opt[i] = malloc(strlen(qOptions[i]) + 1);
      strcpy(opt[i], qOptions[i]);
    }

    QuestionNode *q = createQuestion(questionCpy,  opt, qAnswer);
    addNewQuestion(list, q);
  }
  fclose(file);
  printf("SUCESSO: lista de perguntas carregada de data/\n");
}