#include"quiz.h"
#include"util.h"

//========================= SYSTEM FUNCTIONS ========================================

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
            case 0:
                printf("Saindo...\n");
                break;

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
        
            default:
                printf("ERRO: opcao invalida!\n");
                break;
        }
    } while (option != 0);
    
}

//========================= PLAYER FUNCTIONS ========================================

Player* createPlayerTreeNode(){
    Player* node = (Player*)malloc(sizeof(Player));
    if(node == NULL){
        printf("Erro ao alocar memoria!\n");
        exit(EXIT_FAILURE);
    }

    strcpy(node->playerName,"\0");
    node->score = 0;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void addPlayerIntoTree(Player** tree,char playerName[100],int score){
    Player* node = createPlayerTreeNode();

    strcpy(node->playerName,playerName);
    node->score = score;

    if(*tree == NULL){
        *tree = node;
        return;
    }

    Player* current = *tree;
    Player* father = NULL;

    while(current != NULL){
        father = current;
        if(strcmp(node->playerName,current->playerName) < 0){
            current = current->left;
        }else{
            current = current->right;
        }
    }

    if(strcmp(father->playerName,playerName) < 0){
        father->right = node;
    }else{
        father->left = node;
    }
}

int removePlayerFromTree(Player** tree,char* playerName){
    Player* current = *tree;
    Player* father = NULL;

    while(current != NULL && (strcmp(current->playerName,playerName)<0)){
        father = current;

        if(strcmp(current->playerName,playerName)<0){
            current->right;
        }else{
            current->left;
        }

        if(current = NULL){
            return 0;
        }

        //Caso 1:Folha

        //Caso 2: Filho

        //Caso 3: Filhos

    }

    return 1;
}

//========================= QUESTION FUNCTIONS ========================================

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

void saveQuestionList(QuestionList qlist){
  FILE *file = fopen("data/ListOfQuestions.txt", "w");
  if(file ==  NULL){
    printf("ERRO: nao foi possivel abrir o ficheiro");
    return;
  }

  QuestionList l  = qlist;
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

void loadQuestionList(QuestionList *qlist){
  FILE  *file = fopen("data/ListOfQuestions.txt", "r");
  if(file ==  NULL){
    printf("ERRO: nao foi possivel abrir  o ficheiro");
    return;
  }

  createQuestionList(qlist);

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
    addNewQuestion(qlist, q);
  }
  fclose(file);
  printf("SUCESSO: lista de perguntas carregada de data/\n");
}