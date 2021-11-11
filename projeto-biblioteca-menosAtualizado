#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct info_livro{
    char sigla; // [L]ivre, [E]mprestado, [R]eservado
    int reg; // registro do livro
} info_livro;

typedef struct aluno{
    char nome[80];
    char RA[7];
    int emprestado; // qtde de livros emprestados – Max=3
    int reservado; // qtde de livros reservados – Max =1
    struct info_livro tabela[4];
} aluno;

typedef struct info_aluno{
    char sigla;
    char RA[7];
    int dia_ret; // dia – máx=31
    int mes_ret; // mes: fev=28 dias
    int dia_dev; // mes: abril=jun=set=nov=30 dias
    int mes_dev; // os demais = 31 dias
} info_aluno;

typedef struct livro{
    int reg; // gerado automaticamente
    char titulo[80];
    char autor[80];
    struct info_aluno status[2];
} livro;

void aloca_aluno(aluno **p, int tamanho);
void aloca_livro(livro **p, int tamanho);
void cadastra_aluno(aluno *p_aluno);
void cadastra_livro(livro *p_livro);
void consulta_aluno(aluno *p_alunos, int quantidade_alunos);
void consulta_livros(livro *p_livros, int quantidade_livros);
void mostra_todos_alunos(aluno *p_alunos, int quantidade_alunos);
void busca_aluno_ra(aluno *p_alunos, int quantidade_alunos, char *ptr_ra_pesquisado);

void main()
{    
    aluno *alunos = NULL;
    livro *livros=NULL;
    int option, quantidade_alunos=0, quantidade_livros=0;

    do
    {
        printf("\n[1] CADASTRO DE ALUNOS\n");
        printf("[2] CONSULTA ALUNOS\n");
            //SUBMENU
        printf("[3] CADASTRO DE LIVROS\n");
        printf("[4] CONSULTA LIVROS\n");
            //SUBMEU
        printf("[5] SAIR DO PROGRAMA\n");

        printf("Digite a opcao desejada:");
        scanf("%i", &option);
        fflush(stdin);
        switch(option)
        {
        case 1:
            aloca_aluno(&alunos, quantidade_alunos+1);
            cadastra_aluno(alunos+quantidade_alunos);
            quantidade_alunos++;
            break;
        case 2:
            consulta_aluno(alunos, quantidade_alunos);
            break;
        case 3:
            aloca_livro(&livros, quantidade_livros+1);
            cadastra_livro(livros+quantidade_livros);
            quantidade_livros++;
            break;
        case 4:
            consulta_livros(livros, quantidade_livros);
            break;
        case 5:
            printf("\nSistema encerrado pelo usuario!\n\n");
            break;
        default:
            printf("\nOpcao nao reconhecida!\n");
        }

    }while(option != 5);
}

// Funções alunos;

void aloca_aluno(aluno **p, int tamanho){
    if((*p = (aluno *)realloc(*p, tamanho*sizeof(aluno)))==NULL){
        printf("O programa sera encerrado, erro na alocacao de aluno");
        exit(1);
    }
}
//Aloca aluno

void cadastra_aluno(aluno *p_aluno){
    int iterador = 0;
    printf("\nNome do aluno: ");
    gets(p_aluno->nome);
    fflush(stdin);

    printf("RA do aluno: ");
    gets(p_aluno->RA);
    fflush(stdin);

    p_aluno->emprestado = 0;
    p_aluno->reservado = 0;
    for (iterador; iterador < 4; iterador++){
        p_aluno->tabela[iterador].sigla = 'L';
        p_aluno->tabela[iterador].reg = 0;
    }
}
//Cadastra aluno

void mostra_todos_alunos(aluno *p_alunos, int quantidade_alunos){
    int iterador_alunos = 0;
    for (iterador_alunos; iterador_alunos < quantidade_alunos; iterador_alunos++){
        printf("Nome: %s \tRA: %s", (p_alunos+iterador_alunos)->nome, (p_alunos+iterador_alunos)->RA);
        int iterador_tabela=0;
        for(iterador_tabela; iterador_tabela < 4; iterador_tabela++){
            printf("\t%c - ", (p_alunos+iterador_alunos)->tabela[iterador_tabela].sigla);
            printf("%i", (p_alunos+iterador_alunos)->tabela[iterador_tabela].reg);
        }
        printf("\n");
    }
}
//Mostra todos os alunos

void busca_aluno_ra(aluno *p_alunos, int quantidade_alunos, char *ptr_ra_pesquisado){
    int iterador_alunos = 0, comparacao;
    for (iterador_alunos; iterador_alunos < quantidade_alunos; iterador_alunos++){
        comparacao = strcmp((p_alunos+iterador_alunos)->RA, ptr_ra_pesquisado);
        if(comparacao == 0){
            printf("Nome: %s", (p_alunos+iterador_alunos)->nome);
            printf("\tRA: %s", (p_alunos+iterador_alunos)->RA);
            int iterador_tabela=0;
            for(iterador_tabela; iterador_tabela < 4; iterador_tabela++){
                printf("\t%c - ", (p_alunos+iterador_alunos)->tabela[iterador_tabela].sigla);
                printf("%i", (p_alunos+iterador_alunos)->tabela[iterador_tabela].sigla);
            }
            printf("\n");
        }
    }
}
//Busca alunos por RA


void consulta_aluno(aluno *p_alunos, int quantidade_alunos){
    int tipo_consulta_aluno;
    char ra_pesquisado[7], *ptr_ra_pesquisado;
    ptr_ra_pesquisado = ra_pesquisado;

    system("cls");
    printf("[1] CONSULTA COMPLETA DE ALUNOS\n");
    printf("[2] CONSULTA DE ALUNO POR RA\n");
    printf("[3] VOLTAR AO MENU ANTERIOR\n");
    printf("Digite a opcao desejada:");
    scanf("%i", &tipo_consulta_aluno);
    fflush(stdin);
    printf("\n");
    
    switch (tipo_consulta_aluno)
    {
    case 1:
        mostra_todos_alunos(p_alunos, quantidade_alunos);
        break;
    case 2:
        printf("Digite o RA do aluno que deseja buscar: ");
        gets(ptr_ra_pesquisado);
        printf("\n");
        busca_aluno_ra(p_alunos, quantidade_alunos, ptr_ra_pesquisado);
        break;
    case 3:
        main();
    default:
        printf("Opcao de consulta nao existe!");
        break;
    }
}
//Submenu busca aluno




//Funções livros;

void aloca_livro(livro **p, int tamanho){
    if((*p = (livro *)realloc(*p, tamanho*sizeof(livro)))==NULL){
        printf("O programa sera encerrado, erro na alocacao de info_livro");
        exit(1);
    }
}
//Aloca livro

void cadastra_livro(livro *p_livro){
    static int registro = 1;
    p_livro->reg = registro;
    registro++;

    printf("\n");

    printf("Qual o titulo do livro: ");
    gets(p_livro->titulo);
    fflush(stdin);
    

    printf("Qual o nome do autor do livro: ");
    gets(p_livro->autor);
    fflush(stdin);

    int iterador_info_aluno=0;
    for(iterador_info_aluno; iterador_info_aluno<2; iterador_info_aluno++){
        p_livro->status[iterador_info_aluno].sigla = 'L';
        p_livro->status[iterador_info_aluno].RA[7] = '-';
        p_livro->status[iterador_info_aluno].dia_ret = 0;
        p_livro->status[iterador_info_aluno].mes_ret = 0;
        p_livro->status[iterador_info_aluno].dia_dev = 0;
        p_livro->status[iterador_info_aluno].mes_dev = 0;
    }
}
//Cadastra livro

void mostra_todos_livros(livro *p_livros, int quantidade_livros){
    int iterador_livros = 0;
    printf("\n");
    for (iterador_livros; iterador_livros < quantidade_livros; iterador_livros++){
        printf("%i - Titulo:%-21s Autor:%-15s", (p_livros+iterador_livros)->reg, (p_livros+iterador_livros)->titulo, (p_livros+iterador_livros)->autor);
        int iterador_status = 0;
        for(iterador_status; iterador_status<2; iterador_status++){
            printf("  Status: %-2c", (p_livros+iterador_livros)->status[iterador_status].sigla);
            printf("  RA: %-8s", (p_livros+iterador_livros)->status[iterador_status].RA);
            printf("Ret: %-2i/%-2i", (p_livros+iterador_livros)->status[iterador_status].dia_ret, (p_livros+iterador_livros)->status[iterador_status].mes_ret);
            printf("  Dev: %-2i/%-2i", (p_livros+iterador_livros)->status[iterador_status].dia_dev, (p_livros+iterador_livros)->status[iterador_status].mes_dev);
        }
        printf("\n");
    }
}
//Mostra todos os livros





void consulta_livros(livro *p_livros, int quantidade_livros){
    int tipo_consulta_livro;
    char titulo_pesquisado[80], status_pesquisado;
    char *ptr_titulo_pesquisado, *ptr_status_pesquisado;
    ptr_titulo_pesquisado = titulo_pesquisado;
    // ptr_status_pesquisado = status_pesquisado; tentar enviar o endereço da variavel

    system("cls");

    printf("[1] CONSULTA COMPLETA DE LIVROS\n");
    printf("[2] CONSULTA DE LIVRO POR TITULO\n");
    printf("[3] CONSULTA DE LIVRO POR STATUS\n");
    printf("[4] VOLTAR AO MENU ANTERIOR\n");
    printf("Digite a opcao desejada:");
    scanf("%i", &tipo_consulta_livro);
    fflush(stdin);
    
    switch (tipo_consulta_livro)
    {
    case 1:
        mostra_todos_livros(p_livros, quantidade_livros);
        break;
    case 4:
        main();
    default:
        printf("Erro ao consultar alunos!");
        break;
    }
}
//Submenu consulta livros