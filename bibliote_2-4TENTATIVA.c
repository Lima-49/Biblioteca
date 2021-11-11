#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct info_livro{
	char sigla;// [L]ivre, [E]mprestado, [R]eservado
	int reg;// registro do livro
};

typedef	struct aluno{
	char nome[80];
	char RA[7];
	int emprestado;// qtdede livros emprestados ?Max=3
	int reservado;// qtde de livros reservados ?Max =1
	struct info_livro tabela[4];
}aluno;


struct info_aluno{
	char sigla;
	char RA[7];
	int dia_ret;// dia ?m?x=31
	int mes_ret;// mes: fev=28 dias
	int dia_dev;// mes: abril=jun=set=nov=30 dias
	int mes_dev;// os demais = 31 dias
};

typedef struct livro{
	int reg;
	char titulo[80];
	char autor[80];
	struct info_aluno status[2];
} livro;



void inicialivro(livro**p,int tamanho);
void iniciaaluno(aluno**p,int tamanho);
int verificaAluno();
int verificaLivro();
void cadastroaluno(aluno*p_aluno);
void consultaAluno(aluno *p_aluno);
void cadastrolivro(livro*p_livro);
void consultalivro(livro *p_livro);
void gravaAluno(aluno *p_aluno,char *str,int pos);
void gravaLivro(livro *p_livro,char *str,int pos);
void mostra(aluno *p);
void mostra_parcial_aluno(aluno *p);
void mostra_livro(livro *p_livro);
void mostra_parcial_livro(livro *p_livro);
void busca_porRA(aluno *p_aluno);

int main(){
	
	int op;
	aluno*p_aluno;
	livro*p_livro;
	iniciaaluno(&p_aluno, 1);
	inicialivro(&p_livro, 1);

	
	do{
		 
		printf("\n[1]Cadastro\n[2]Consultar Aluno \n[3]Cadastra Livro\n[4]Consulta Livro\nOpcao: \n");  
		scanf("%i",&op);  
		fflush(stdin); 

		switch(op){    
		case 1: cadastroaluno(p_aluno);           
		break;    
		case 2: consultaAluno(p_aluno);            
		break;    
		case 3: cadastrolivro(p_livro);            
		break;
		case 4: consultalivro(p_livro);
		break;
		case 5: mostra(p_aluno);
		default: 
			free(p_aluno);
			free(p_livro);
			return 0;
		break;	
		
		
		}//switch
	
	}while(op!=5);
	

}//main

void inicialivro(livro **p, int tamanho){
    if((*p = (livro *)malloc(tamanho*sizeof(livro)))==NULL){
        printf("\nErro na alocacao. O programa sera encerrado!\n");
        exit(1);
	}
}

void iniciaaluno(aluno **p_aluno, int tamanho){
    if((*p_aluno = (aluno *)malloc( tamanho*sizeof(aluno)))==NULL){
        printf("\nErro na alocacao. O programa sera encerrado!\n");
        exit(1);
	}
}

void cadastroaluno(aluno*p_aluno){
	
	printf("Por favor Insira os Dados a seguir:\n");
	printf("Insira seu nome\n");
	scanf("%s",p_aluno->nome);
	fflush(stdin);
	printf("Insira seu Ra\n");
	scanf("%s",p_aluno->RA);
	fflush(stdin);
	printf("Insira quantidade de livros emprestados\n");
	scanf("%i",&p_aluno->emprestado);
	fflush(stdin);
	
	aluno *p;
	iniciaaluno(&p,1);
	int i=0, j= p_aluno->emprestado-1, tempReg =0, k=j;
	int qAluno;
	FILE *fptr=NULL;
	qAluno=verificaAluno();
	if((fptr=fopen("aluno.bin","rb"))==NULL)  
		printf("\nErro ao abrir o arquivo\n");
	else{
		p_aluno->reservado = 0;
		if( p_aluno->emprestado == 0 ){
			for( i=0; i<4; i++ ){
				(p_aluno->tabela+i)->sigla='L';
				(p_aluno->tabela+i)->reg= 0;
			}
		} else {
			for( i=0; i<4; i++ ){
				(p_aluno->tabela+i)->reg= 0;
			}
		}
		for( ; j>=0; j-- ){
			if( p_aluno->emprestado >= 1 && p_aluno->emprestado <= 4 ){
				printf("\ndigite o numero de registro do livro\n");
				scanf("%i", &tempReg );
				int flag=0, cont=0;
				//CASO OS 2 LIVROS ESTEJAM CADASTRADOS POR OUTROS ALUNO HÁ UM ERRO
				for(i=1;i<=qAluno;i++){
					fseek(fptr,i*sizeof(aluno),0);
					fread(p ,sizeof(aluno),1,fptr);
					for(cont =0; cont<4; cont++){
						if( tempReg == (p->tabela+cont)->reg && flag==0){
							//reservar o livro
							flag= 1;
						}else if (flag == 0){
							//emprestar o livro
							flag= 0;
						}
					}
				}
				if(flag == 1){
					printf("\nseu livro foi reservado\n");
					(p_aluno->tabela+3)->sigla='R';
					(p_aluno->tabela+3)->reg= tempReg;
					p_aluno->reservado = 1;
					p_aluno->emprestado--;
				}else if(flag== 0){
					printf("\nEmprestimo efetuado\n");
					(p_aluno->tabela+k-j)->sigla='E';
					(p_aluno->tabela+k-j)->reg= tempReg;
				}	
			}	
		}//FOR	
	}
	gravaAluno(p_aluno,"ab",1);		
}

void cadastrolivro(livro*p_livro){

   
   
	int i=0,data,mes,cont=0,qAluno,contVetor,conta, flag=0;

	int qreg = verificaLivro();
	p_livro->reg = qreg+1;
	
	printf("Insira o titulo do Livro\n");
	scanf("%s", p_livro->titulo);
	fflush(stdin);
	printf("Insira o nome do autor do Livro\n");
	scanf("%s", p_livro->autor);
	fflush(stdin);

	
	aluno *p;
	iniciaaluno(&p,1);
	
    for(i; i<2; i++){
        (p_livro->status+i)->sigla = 'L';
        (p_livro->status+i)->RA[7] = '-';
        (p_livro->status+i)->dia_ret = 0;
        (p_livro->status+i)->mes_ret = 0;
        (p_livro->status+i)->dia_dev = 0;
        (p_livro->status+i)->mes_dev = 0;
    }
	


	FILE *fptr=NULL;
	qAluno=verificaAluno();
	if((fptr=fopen("aluno.bin","rb"))==NULL)  
		printf("\nErro ao abrir o arquivo");
	else{

		for(i=1;i<=qAluno;i++){
			fseek(fptr,i*sizeof(aluno),0);
			fread(p ,sizeof(aluno),1,fptr);
			
			
			for(cont=0; cont<4; cont++){
				
				if( p_livro->reg == (p->tabela+cont)->reg && flag <2){
					
					(p_livro->status+flag)->sigla = (p->tabela+cont)->sigla;
					for(contVetor=0; contVetor<=7; contVetor++){
						(p_livro->status+flag)->RA[contVetor] = p->RA[contVetor];
					}
					printf("Insira o dia e mes de retirada (31 2): \n");
					scanf("%i %i", &(p_livro->status+flag)->dia_ret, &(p_livro->status+flag)->mes_ret);
					if( (p_livro->status+flag)->dia_ret + 7 > 31){
						conta=((p_livro->status+flag)->dia_ret + 7)-31;
						(p_livro->status+flag)->mes_ret++;
						(p_livro->status+flag)->dia_ret=conta;
					}else {
						(p_livro->status+flag)->dia_dev = (p_livro->status+flag)->dia_ret + 7;
						(p_livro->status+flag)->mes_dev = (p_livro->status+flag)->mes_ret;
					}
					
					
					
					//Mudar status[0] se mais de um então mudar status[1] também
					flag++;
				}
			}
		}
	}

	
	/**
	 * buscar no aluno quais tem o reg, 
	 * e se encotrar cadastrar no p->status se 1 no 0, se 2 no 1 e 0, se 0 mantem o for de baixo
	 */

	


	gravaLivro(p_livro,"ab",1);	
}

int  verificaAluno(){
	long int cont=0;
	FILE *fptr=NULL;
	if((fptr=fopen("aluno.bin","rb"))==NULL)
		return cont;
	else{  
		fseek(fptr,0,2);  //posiciona no fim do arquivo  
		cont=ftell(fptr)/sizeof(aluno);   //qtde de elementos  
		fclose(fptr);    //dentro do ELSE por conta do rb  
		return cont;  
	}//else
}//verifica

int  verificaLivro(){
	long int cont=0;
	FILE *fptr=NULL;
	if((fptr=fopen("livro.bin","rb"))==NULL)
		return cont;
	else{  
		fseek(fptr,0,2);  //posiciona no fim do arquivo  
		cont=ftell(fptr)/sizeof(livro);   //qtde de elementos  
		fclose(fptr);    //dentro do ELSE por conta do rb  
		return cont;  
	}//else
}//verifica


void gravaAluno(aluno *p_aluno,char *str,int pos){
	FILE *fptr=NULL;
	if((fptr=fopen("aluno.bin",str))==NULL)  
		printf("\nErro ao abrir o arquivo");
	else{  
		if(strcmp(str,"rb+")==0)    
			fseek(fptr,pos*sizeof(aluno),0);  
		fwrite(p_aluno,sizeof(aluno),1,fptr);  
	}//else
	fclose(fptr);           //fora do ELSE por conta do ab ou rb+
}//grava

void gravaLivro(livro *p_livro,char *str,int pos){
	FILE *fptr=NULL;
	if((fptr=fopen("livro.bin",str))==NULL)  
		printf("\nErro ao abrir o arquivo");
	else{  
		if(strcmp(str,"rb+")==0)    
			fseek(fptr,pos*sizeof(livro),0);  
		fwrite(p_livro,sizeof(livro),1,fptr);  
	}//else
	fclose(fptr);           //fora do ELSE por conta do ab ou rb+
}//grava



void consultalivro(livro *p_livro){
	int op;
	printf("Que tipo de consulta voce deseja fazer?\n Para consulta total digite[1]\n Para consulta parcial digite[2]");
	scanf("%i",&op);

	switch (op)
	{
	case 1:
		mostra_livro(p_livro);
		break;
	
	case 2:
		mostra_parcial_livro(p_livro);
		break;
		
	}
	
}
void consultaAluno(aluno *p_aluno){
	int op;
    
	printf("Que tipo de consulta voce deseja fazer?\n Para consulta total digite[1]\n Para consulta parcial digite[2]\n Para consulta por RA[3]\n");
	scanf("%i",&op);

	switch (op)
	{
	case 1:
		mostra(p_aluno);
		break;
	
	case 2:
		mostra_pacial_aluno(p_aluno);
		break;
    
    case 3:
        busca_porRA(p_aluno);
        break;
		
	}
	

}

void mostra(aluno *p_aluno){
	int i,qreg, j;
	FILE *fptr=NULL;
	qreg=verificaAluno();
	system("cls");
	if((fptr=fopen("aluno.bin","rb"))==NULL)  
		printf("\nErro ao abrir o arquivo");
	else{
		for(i=0;i<qreg;i++){
			fseek(fptr,i*sizeof(aluno),0);
			fread(p_aluno,sizeof(aluno),1,fptr);
			printf("\nNome: %s	RA: %s	Emprestado:	%i	Reservado: %i",p_aluno->nome,p_aluno->RA,p_aluno->emprestado,p_aluno->reservado);    
			for(j=0; j<=3; j++){
				printf("\nReg: %i", (p_aluno->tabela+j)->reg);
			}
			printf("\n\n");
		}//for  
	fclose(fptr);  
	}//else
	system("pause");
}//mostra

void mostra_pacial_aluno(aluno *p_aluno){
	int i,qreg, j;
	FILE *fptr=NULL;
	qreg=verificaAluno();
	system("cls");
	if((fptr=fopen("aluno.bin","rb"))==NULL)  
		printf("\nErro ao abrir o arquivo");
	else{
		for(i=0;i<qreg;i++){
			fseek(fptr,i*sizeof(aluno),0);
			fread(p_aluno,sizeof(aluno),1,fptr);
			int conta;
			conta=p_aluno->emprestado+p_aluno->reservado;
			printf("\nRA: %s	Livros Totais %i",p_aluno->RA,conta);    
			
			printf("\n\n");
		}//for  
	fclose(fptr);  
	}//else
	system("pause");
}//mostra

void mostra_livro(livro *p_livro){
	int i,qreg, j;
		FILE *fptr=NULL;
		qreg=verificaLivro();
		system("cls");
		if((fptr=fopen("livro.bin","rb"))==NULL)  
			printf("\nErro ao abrir o arquivo");
		else{
			for(i=0;i<qreg;i++){
				fseek(fptr,i*sizeof(livro),0);
				fread(p_livro,sizeof(livro),1,fptr);
				printf("\nRegistro: %i	Titulo: %s	Autor:	%s	", p_livro->reg, p_livro->titulo, p_livro->autor);    
				for(j=0; j<2; j++){
					printf(" Sigla: %c RA: %s Retirada: %i/%i Devolucao: %i/%i", (p_livro->status+j)->sigla, (p_livro->status+j)->RA, (p_livro->status+j)->dia_ret, (p_livro->status+j)->mes_ret, (p_livro->status+j)->dia_dev, (p_livro->status+j)->mes_dev );
				
				}
				printf("\n\n");
			}//for  
		fclose(fptr);  
		}//else
		system("pause");



	
}

void mostra_parcial_livro(livro *p_livro){
	int i,qreg, j;
		FILE *fptr=NULL;
		qreg=verificaLivro();
		system("cls");
		if((fptr=fopen("livro.bin","rb"))==NULL)  
			printf("\nErro ao abrir o arquivo");
		else{
			for(i=0;i<qreg;i++){
				fseek(fptr,i*sizeof(livro),0);
				fread(p_livro,sizeof(livro),1,fptr);
				printf("\nTitulo: %s",p_livro->titulo);    
				for(j=0; j<2; j++){
					printf(" Sigla: %c ", (p_livro->status+j)->sigla);
				
				}
				printf("\n\n");
			}//for  
		fclose(fptr);  
		}//else
		system("pause");
}

void busca_porRA(aluno *p_aluno)
{
  char num_ra[7];
  int i, achou =-1, qAluno, compara;
  qAluno= verificaAluno();
  printf("\nQual o RA a ser Buscado: ");
  scanf("%s", &num_ra);
  fflush(stdin);
  FILE *fptr=NULL;
  if((fptr=fopen("aluno.bin","rb"))==NULL)
  {
      printf("\nErro ao abrir o arquivo");
  }
  else 
  {
      for(i=0;i<qAluno;i++)
      {
          fseek(fptr,i*sizeof(aluno),0);
          fread(p_aluno,sizeof(aluno),1,fptr);
          compara = strcmp(p_aluno->RA, num_ra);
          if(compara==0)
          { 
            printf("\nNome: %s	RA: %s	Emprestado:	%i	Reservado: %i",p_aluno->nome,p_aluno->RA,p_aluno->emprestado,p_aluno->reservado); 
            printf("\n\n");
          }	
      }
    fclose(fptr);       
  }
}


