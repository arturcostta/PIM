#include <stdio.h>
#include <stdlib.h>
#include "calcAge.h"
#include <locale.h>

typedef struct endereco{
    char rua[50];
    char numero[4];
    char bairro[40];
    char cidade[40];
    char estado[3];
    char CEP[8];
} Endereco;

typedef struct paciente {
    char cpf[11];
    char nome[100];
    char telefone[11];
    Endereco end;
    int dia,mes,ano;
    char dataDiagnostico[12];
    char email[30];
    char comorbidade[100];
} Paciente;

void flush_in() {
    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}

void login()
{
    flush_in();
    char login[15];
    char senha[15];
    int idade;
    printf("Digite o login:\n");
    scanf("%s",login);
    printf("Digite a senha:\n");
    scanf("%s",senha);
    if( (strcmp(login,"admin") == 0) && (strcmp(senha,"admin") == 0) )
    {
        printOpcoes();
    }else{
        printf("Login incorreto!\n");
    }
}

void cadastrar()
{
    fflush(stdin);
    FILE *arq =fopen("data.bin", "ab");

    Paciente paciente;
    printf("Digite o nome\n");
    fgets(paciente.nome, 100, stdin);

    printf("Digite a data de nascimento(dd/MM/yyyy)\n");
    scanf("%d/%d/%d",&paciente.dia,&paciente.mes,&paciente.ano);
    fflush(stdin);

    printf("Digite a comorbidade\n");
    fgets(paciente.comorbidade, 100, stdin);

    printf("Digite o CEP\n");
    //scanf("%s", paciente.end.CEP);
    fgets(paciente.end.CEP,8,stdin);
    fflush(stdin);

    printf("Digite o cpf\n");
    //scanf("%s",paciente.cpf);
    fgets(paciente.cpf,8,stdin);
    fflush(stdin);

    printf("Digite o telefone\n");
    //scanf("%s",paciente.telefone);
    fgets(paciente.telefone,11,stdin);
    fflush(stdin);

    printf("Digite a data do diagnóstico\n");
    //scanf("%s",paciente.dataDiagnostico);
    fgets(paciente.dataDiagnostico,12,stdin);
    fflush(stdin);

    printf("Digite o email\n");
    //scanf("%s",paciente.email);
    fgets(paciente.email,50,stdin);
    fflush(stdin);

    printf("Digite o nome da  rua\n");
    //fgets(paciente.end.rua, 50, stdin);
    fgets(paciente.end.rua,50,stdin);
    fflush(stdin);

    printf("Digite o número\n");
    //scanf("%d", &paciente.end.numero);
    fgets(paciente.end.numero,4,stdin);
    fflush(stdin);

    printf("Digite o bairro\n");
    fgets(paciente.end.bairro, 40,stdin);
    fflush(stdin);

    printf("Digite o cidade\n");
    fgets(paciente.end.cidade, 40,stdin);
    fflush(stdin);

    printf("Digite o estado\n");
    //scanf("%s",paciente.end.estado);
    fgets(paciente.end.estado, 3,stdin);

    //verificar idade
    int idade = calcAge(paciente.dia,paciente.mes,paciente.ano);
    if( idade > 65)
    {
        gravarPacienteRisco(&paciente.nome,&paciente.end.CEP,&paciente.comorbidade);
    }
    //

    if(fwrite(&paciente, sizeof(Paciente), 1, arq) != 1) {
        puts("Erro ao gravar conteudo no arquivo!");
        fclose(arq);
        return 1;
    }

    fclose(arq);
}

void gravarPacienteRisco(char nome[], char cep[], char comorbidade[])
{
    FILE *arq_text =fopen("data.txt", "a");
    int result;
    result = fputs(nome, arq_text);
    result = fputs(cep, arq_text);
    result = fputs(":", arq_text);
    result = fputs(comorbidade, arq_text);
    result = fputs("\n", arq_text);

    fclose(arq_text);
    printf("Arquivo de paciente no grupo de risco atualizado!");

}

void listar()
{
    FILE *arq = fopen("data.bin", "rb");
    Paciente paciente;
    int cont = 0;
    if(arq != NULL)
    {
        // aqui estou lendo todos os registros existentes no arquivo
        fread(&paciente, sizeof(Paciente), 1, arq);
        do {
            printf("PACIENTE NUMERO : %d\n",cont+1);
            printf("Nome: %s", paciente.nome);
            printf("Cpf: %s - Data de Nascimento: %d/%d/%d - Telefone: %s\n",paciente.cpf, paciente.dia, paciente.mes, paciente.ano, paciente.telefone);
            printf("Email: %sComorbidade: %sData do diagnóstico %s\n",paciente.email, paciente.comorbidade, paciente.dataDiagnostico);
            printf("Numero: %d - Rua: %s",paciente.end.numero, paciente.end.rua);
            printf("Bairro: %s",paciente.end.bairro);
            printf("Cidade: %s",paciente.end.cidade);
            printf("Estado: %s - CEP: %s\n", paciente.end.estado, paciente.end.CEP);
            printf("\n");
            printf(" -----------**********-----------");
            printf("\n");
            fread(&paciente, sizeof(Paciente), 1, arq);
            cont++;
        } while (!feof(arq)); // enquanto não chegar ao final do arquivo
    }
    else
    {
        printf("\nErro ao abrir o arquivo para leitura!\n");
		exit(1);
    }
    fclose(arq);

    system("pause");
}

void sair()
{
    printf("Programa finalizado!");
}

void printOpcoes()
{
    int opcao;
    do{
        flush_in();
        printf("\n\tSISTEMA DE CADASTROS DE DOENTES\n\n");

        printf("1. Cadastrar\n");
        printf("2. Listar\n");
        printf("0. Voltar menu anterior\n");

        scanf("%d", &opcao);
        switch(opcao)
        {
        case 1:
            cadastrar();
            break;
        case 2:
            listar();
            break;
        default:
            printf("Digite uma opcao valida\n");
    }
    system("cls || clear");
    }while(opcao);
}



int main()
{
    setlocale(LC_ALL, "Portuguese");
    int continuar=1;

    do
    {
        //flush_in();
        printf("\n\tSISTEMA DE CADASTROS DE DOENTES\n\n");
        printf("1. Login\n");
        printf("0. Sair\n");


        scanf("%d", &continuar);
        system("cls || clear");

        switch(continuar)
        {
            case 1:
                login();
                break;
            case 0:
                sair();
                break;
            default:
                printf("Digite uma opcao valida\n");
        }
    } while(continuar);
}
