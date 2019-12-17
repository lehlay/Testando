#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct acao
{
    int lucro;
    int preco;
} Acao;


typedef struct _investimento_
{
    Acao *acao;
    double porcentagem;
    double lucro;
    double d_investido;

}Investimento;


typedef struct _investidor_
{
    char name[50];
    double dinheiro;
    double totalLucro;
    int qtdInvestimentos;
    Investimento *investimentos;

}Investidor;

typedef struct _rkg_ {
    char n[5][50];
    double p[5];
} Rkg;

Investidor *novoInvestidor(int dinheiro);
int destroyInvestidor(Investidor *inv);

void printAcao(Acao *ac, int i);
int compra(Acao*, Investidor*, int*, double menorValor);
void ranking(double pontuacao, char* nome, Rkg);



Investidor *novoInvestidor(int dinheiro){
    Investidor *inv;
    inv = (Investidor*)malloc(sizeof(Investidor));
    if(inv!=NULL){
        printf("\nInforme o nome do investidor: ");
        fgets(inv->name, sizeof(inv->name), stdin);
        inv->name[strlen(inv->name)-1] = '\0';
        inv->dinheiro = dinheiro;
        inv->totalLucro = 0;
        inv->qtdInvestimentos = 0;
        inv->investimentos = (Investimento*)malloc(sizeof(Investimento)*100);
        if(inv->investimentos!=NULL){
            return inv;
        }
        free(inv);
    }
    return NULL;
}

int destroyInvestidor(Investidor *inv){
    if(inv!=NULL){
        free(inv->investimentos);
        free(inv);
        return 1;
    }
    return 0;
}

void printAcao(Acao *ac, int i){
    if(ac!=NULL){
        printf("%d - Lucro da Acao: %d\n", i, ac->lucro);
        printf("%d - Preco da Acao: %d\n", i, ac->preco);
    }
}

// Recebe o vetor de ações
int compra(Acao* acoes, Investidor* inv, int* ct, double menorValor){

    int choice = 0, i = 0, cont;
    double lucro_da_rodada=0, lucroAtual=0, custo_da_rodada=0, porcentagem =0, dinheiro = inv->dinheiro;
    double p = (porcentagem/100)*dinheiro;

    setbuf(stdin, NULL);
    printf("\nDigite o numero da acao ou -1 para sair:\n");
    scanf("%d", &choice);
    if (choice == -1) return -1;

  
    printf("Digite a porcentagem da acao (10 a 100%%):\n");
    scanf(" %lf", &porcentagem);

    if(porcentagem >= 10 && porcentagem <= 100){
    
 //se a porcentagem que eu for pagar for maior que  o dinheiro q eu investir entao eu printo saldo insuficiente
    if( p < inv->dinheiro ){ 

    //printar processo para informar usuario da escolha que ele fara para ver se ele tem certeza
    printf("\n----------------------------------\n");
    printf("\nInvestimento\n");
    printf("Lucro :%0.3lf\n", ((porcentagem/100)* acoes[choice].lucro));
    printf("Preco :%0.3lf\n", ((porcentagem/100)* acoes[choice].preco));
    printf("\n----------------------------------\n");

    
    int querContinuar;
    printf("\nQuer continuar o investimento?(0 - nao/ 1 - sim)\n");
    scanf("%d", &querContinuar);

    switch(querContinuar){
        case(1):
            // Incremento o valor que estah no cont da função main
            cont = ++*ct;
            //Lucro e custo da compra
            lucro_da_rodada = (double) ((porcentagem/100)* acoes[choice].lucro);
            custo_da_rodada = (double) ((porcentagem/100)* acoes[choice].preco);
            lucroAtual = inv->totalLucro + lucro_da_rodada;
            dinheiro = dinheiro - custo_da_rodada;

            // Atualiza na struct inv
            inv->dinheiro = dinheiro;
            inv->totalLucro = lucroAtual;
            inv->qtdInvestimentos= cont;
            inv->investimentos[cont-1].porcentagem = porcentagem;
            inv->investimentos[cont-1].lucro = lucro_da_rodada;
            inv->investimentos[cont-1].d_investido = custo_da_rodada;
            inv->investimentos[cont-1].acao->lucro = acoes[choice].lucro;
            inv->investimentos[cont-1].acao->preco = acoes[choice].preco;
            printf("\n----Compra realizada----\n");
            printf("\nDinheiro Atual:%0.3lf\n", inv->dinheiro);
            printf("Lucro Atual:%0.3lf\n", inv->totalLucro);
            printf("Vezes investidas:%d\n", inv->qtdInvestimentos);
            printf("\n--------------------------\n");
            printf("\nCarteira de Acoes:\n");
            printf("\n--------------------------\n");

              //Para exibir o valor de cada compra eh preciso converter os tipos nas structs que estão incompatíveis
                    for (i = 0; i < cont; i ++){
                        printf("\n Custo:%0.3f Lucro %0.3lf\n",inv->investimentos[i].d_investido,inv->investimentos[i].lucro);
                    }
    
            return 0;
    

            break;

            case 0:
            printf("\nInvestimento cancelado, mas nao desiste ainda\n");
            return 0;
            break;
                
        default:
            printf("\nInvestimento cancelado\n");
            return 0;
            break;
        }
    
    }

    else
    {
        printf("\n----------------------------\n");
        printf("\nSaldo insuficiente para essa acao\n");
        printf("\n----------------------------\n");
        return 0;
    }
    }
    else{
        printf("\n----------------------------\n");
        printf("\nPorcentagem invalida, tente novamente...\n");
        printf("\n----------------------------\n");
    }
}

    




void ranking(double pontuacao, char* nome, Rkg placar){
 printf("teste aisjaosjiaopjsopa");

    FILE *record;
    int i, a;
    double tempP;
    char tempN[50];

    record = fopen("records.txt", "r");
 printf("teste aisjaosjiaopjsopa");

    for (i=0; i<5; i++){
        fgets(placar.n[i][0],50, record);
         printf("%s", placar.n[i][0]);

        fscanf (record, " %lf", &placar.p[i]);
printf("%lf", placar.p[i]);


    }

   // rewind(record);

    for (i = 0; i<5; i++){

       
        if (placar.p[i] <= pontuacao){
            tempP = placar.p[i];
            strcpy (tempN, placar.n[i][0]);
            strcpy (placar.n[i][0], nome);
            placar.p[i] = pontuacao;

            for ( a = 5; a>(i+1); a++){
                strcpy (placar.n[a][0], placar.n[a-1][0]);
               placar. p[a] = placar.p[a-1];
            }

            strcpy (placar.n[i+1][0], tempN);
            placar.p[i+1] = tempP; 
            break;
        }
    }

    rewind(record);
  

    //escrevendo a pontuação e o nome no arquivo
    for (i=0; i<5; i++){
         fprintf(record,"%s", placar.n[i][0]);
         fprintf(record, "%lf", placar.p[i]);
    }

    fclose(record);
   
    for (i=0; i<5; i++){
        printf("%s", placar.n[i][0]);
        printf("%lf", placar.p[i]);
    }
    

}


///MAIN
int main(){


    //menu
        printf("\nJogo do investimento\n");
        printf("\nComo jogar:\n");
        printf("\n-Escolha uma fase");
        printf("\n-Informe seu nome");
        printf("\n-Informe a acao escolhida");
        printf("\nInsira a porcentagem da acao que queira investir");
        printf("\nE pronto voce pode continuar investindo se quiser\n");

        printf("\n-------------MENU---------------\n");
        printf("\n[1] - JOGAR\n");
        printf("\n[2] - I.A.\n");
        printf("\n[3] - SAIR\n");
        printf("\n-------------------------------\n");

        int nMenu;
        printf("\nInsira a opcao desejada:\n");
        scanf("%d", &nMenu);

    //"final" do menu

    Investidor *inv;
    Acao *acoes;
    // Declarei o contador "i" porque no meu pc não roda declarando dentro do for
    // Declarei uma variável chamada level para seleção do cenário
    int qtdAcoes, i, level;
    FILE  *arquivo;
    double dinheiro;
    char test[100];
    // Criei um contador que será usado na função de compra, e para imprimir as aquisições na tela
    int aux, cont = 0;
    int auxFase;
    int auxNivel;
    char nome[50];
    int dif;
    double l; 
    double menorValor = acoes[0].preco;
    Rkg placar;


    switch (nMenu)
    {
    case (1):
        // Criei um comando de seleção do nível
        printf("Informe o nivel\n");
        printf("\n[1] - 8 acoes\n");
        printf("\n[2] - 10 acoes\n");
        printf("\n[3] - 15 acoes\n");
        printf("\n[4] - 24 acoes\n");
        printf("\n[5] - 100 acoes\n\n");
        scanf("%d", &level);

        switch (level){
            case 1: arquivo = fopen("investimento/invest1.txt", "r"); break;
            case 2: arquivo = fopen("investimento/invest2.txt", "r"); break;
            case 3: arquivo = fopen("investimento/invest3.txt", "r"); break;
            case 4: arquivo = fopen("investimento/invest4.txt", "r"); break;
            case 5: arquivo = fopen("investimento/invest5.txt", "r"); break;
            default: printf("\nFase inexistente\n"); break;
        }
        // Eu limpo o ENTER que fica depois que a pessoa digita o nivel
        setbuf(stdin, NULL);
     if(level >= 1 && level<=5){
        //fazer um if para verificar se o arquivo foi aberto
        if(arquivo != NULL){
 
                fscanf(arquivo, "%d", &qtdAcoes);
                fscanf(arquivo, "%d", &aux);
                dinheiro = aux/1.0;
                acoes = (Acao*)malloc(sizeof(Acao)*qtdAcoes);

                for(i=0; i<qtdAcoes; i++){
                    fscanf(arquivo, "%d", &acoes[i].lucro);
                }
                for(i=0; i<qtdAcoes; i++){
                    fscanf(arquivo, "%d", &(acoes[i].preco));
                }
   
                    for( i=0; i<qtdAcoes; i++){
                    printAcao((acoes+i), i);
                    printf("\n");
                    }
                
              
        }


            // Cadastra o novo jogador
            inv = (Investidor*) novoInvestidor(dinheiro);
            if (inv == NULL) printf("Erro na alocacao de novoInvestidor");
            
            // acao servirá para guardar o lucro e o preco das ações para cada investimento
            for (i = 0; i <100; i++){
                inv->investimentos[i].acao = malloc(sizeof(Acao));
            }
            // Atualiza o dinehiro na struct do investidor
            inv->dinheiro = dinheiro;

            for(i=0;i<qtdAcoes;i++){
                if(menorValor > acoes[i].preco){
                menorValor = acoes[i].preco * 0.1;
                }
            }




            // Enquanto ele tiver dinheiro ou não optar por sair, o jogador pode comprar mais ações
            while (inv->dinheiro > menorValor ) {
                //printar acoes sempre que o user for invesir
                int choice = 0;
                choice = compra(acoes, inv, &cont, menorValor);
                if (choice == -1) break;
                for( i=0; i<qtdAcoes; i++){
                        printAcao((acoes+i), i);
                        printf("\n");
                }
            }
            
            ranking(inv->totalLucro, inv->name, placar);

            
            printf("\n\nResumo dos Investimentos de %s\n", inv->name);


            for (i = 0; i <cont; i++){
                printf("\nCusto:%.2lf Lucro %.2lf\n",inv->investimentos[i].d_investido,inv->investimentos[i].lucro);
            }                               
            printf("\nDinheiro Final:%.2lf\n", inv->dinheiro);
            printf("Lucro Final:%.2lf\n", inv->totalLucro);
            printf("Vezes investidas:%d\n", inv->qtdInvestimentos);
            

           
        }
        break;

    case 2:
        // Criei um comando de seleção do nível

        printf("Informe o a dificuldade\n");
        printf("\n[1] - Easy\n");
        printf("\n[2] - medium\n");
        printf("\n[3] - Hard\n");
        scanf("%d",&dif);
        switch (dif){
            case 1: arquivo = fopen("investimento/invest1.txt", "r"); break;
            case 2: arquivo = fopen("investimento/invest2.txt", "r"); break;
            case 3: arquivo = fopen("investimento/invest3.txt", "r"); break;
            default: printf("\nFase inexistente\n"); break;
        }



        if(dif<0 || dif>3){
            break;
        }
        printf("Informe o nivel\n");
        printf("\n[1] - 8 acoes\n");
        printf("\n[2] - 10 acoes\n");
        printf("\n[3] - 15 acoes\n");
        printf("\n[4] - 24 acoes\n");
        printf("\n[5] - 100 acoes\n\n");
        scanf("%d", &level);

        switch (level){
            case 1: arquivo = fopen("investimento/invest1.txt", "r"); break;
            case 2: arquivo = fopen("investimento/invest2.txt", "r"); break;
            case 3: arquivo = fopen("investimento/invest3.txt", "r"); break;
            case 4: arquivo = fopen("investimento/invest4.txt", "r"); break;
            case 5: arquivo = fopen("investimento/invest5.txt", "r"); break;
            default: printf("\nFase inexistente\n"); break;
        }
        // Eu limpo o ENTER que fica depois que a pessoa digita o nivel
        setbuf(stdin, NULL);

        int auxValue;
     if(level >= 1 && level<=5){
        //fazer um if para verificar se o arquivo foi aberto
        if(arquivo != NULL){
 
                fscanf(arquivo, "%d", &qtdAcoes);
                fscanf(arquivo, "%d", &aux);
                int profit[qtdAcoes];
                int price[qtdAcoes];
                dinheiro = aux/1.0;
                acoes = (Acao*)malloc(sizeof(Acao)*qtdAcoes);
                for(i=0; i<qtdAcoes; i++){
                    fscanf(arquivo, "%d", &(profit[i]));
                }
                for(i=0; i<qtdAcoes; i++){
                    fscanf(arquivo, "%d", &(price[i]));
                }



/*
            if(dif == 1){
                 ga(aux,price,profit,20); 

            }
               if(dif == 2){
                 ga(aux,price,profit,50); 

            }
               if(dif == 3){
                 ga(aux,price,profit,200); 

            }   */           
        }


           
        }
        break;

    case 3:
        break;
    default:
        printf("\nOpcao inexistente\n");
        break;
    }

   

 

    
   
   
  //inv->investimentos[i].d_investido 
  //o que é:
  // um ponteiro do tipo investidor que 
  //aponta para um vetor alocado dinamicamente 
  //que é preenchido por d-investido.



system("pause");

}
