#include <stdio.h>
#include <time.h>

void Cadastro();
void Listar();
//Chamada de funções externas

struct VarG
{
    int Op;
    char Cd;

}; //Variáveis do tipo Global

struct Cadastro
{
    char nome[25];
    char matricula[35];
    char cpf[15];
    char data[15];
    char notas[3];
}; // Variáveis do tipo Cadastro.Pessoa

FILE* DB; //Ponteiro do Banco de dados

struct VarG Global;
struct Cadastro Pessoa; // Definição das Structs

int main()
{
    system("cls"); //Limpa a tela (Linux)
    printf("=========================\n");
    printf(" GERENCIADOR DE ALUNOS\n");
    printf("=========================\n\n");

    printf("[1] - Cadastrar\n");
    printf("[2] - Alterar\n");
    printf("[3] - Consultar\n");
    printf("[4] - Remover\n");
    printf("[5] - Encerrar\n");
    printf("\n===============\n");
    printf("\nOpcao: ");
    scanf("%d", &Global.Op);
    getchar(); //Limpa o Buffer

    switch (Global.Op)
    {
    case 1:
        Cadastro(); //Funcão Cadastro é iniciada
        break;

    case 2:
        Alterar();
        break;

    case 3:
        Consultar(); //Função Listar é iniciada
        break;

    case 4:
        system("cls");
        Remover();
        break;

    case 5:
        system("cls");
        printf("######################\n");
        printf("# Fim da Execucao... #\n");
        printf("######################\n\n");
        break;

    default:
        printf("Valor invalido! Tente novamente...\n");
        sleep(1); //Pausa a tela por 1s (Linux)
        main();
        break;

    }

    return 0;
} //Fim da Função Principal

void Remover()
{
    char cpf[15];

    printf("\nDigite o CPF que deseja remover:");
    fgets(cpf, sizeof(cpf), stdin);

    buscar_e_remover_aluno(cpf);
}

void Alterar()
{
    char cpf[15];

    printf("\nDigite o CPF que deseja alterar:");
    fgets(cpf, sizeof(cpf), stdin);

    buscar_aluno_alterar(cpf);
}


void Cadastro()
{
    system("cls");
    DB = fopen("dados.txt", "a"); //Abertura do DB para a inserção de dados

    if(DB == NULL)   //Verificação do Banco de Dados
    {
        printf("\nErro no Banco de Dados...\n");
        return 1;

    }
    else
    {
        printf("==========\n");
        printf(" CADASTRO\n");
        printf("==========\n");

        printf("\nDigite o nome: ");
        fgets(Pessoa.nome, 25, stdin);

        do
        {
            printf("\nDigite o CPF: ");
            fgets(Pessoa.cpf, 15, stdin);
        }
        while (validarCPF(Pessoa.cpf) != 1);


        printf("\nDigite a matricula: ");
        fgets(Pessoa.matricula, 35, stdin);

        printf("\nDigite a data de nascimento: ");
        fgets(Pessoa.data, 35, stdin);

        printf("\nDigite as notas: ");
        fgets(Pessoa.notas, 35, stdin);


        system("cls");
        printf("\n=============================\n");
        printf("Finalizar cadastro? [s/n] : ");
        scanf("%c", &Global.Cd); //Conclusão do cadastro

        if(Global.Cd == 's')
        {
            fprintf(DB, "%s%s%s%s%s", Pessoa.cpf, Pessoa.nome, Pessoa.matricula, Pessoa.data, Pessoa.notas);

            fclose(DB); //Fecha o Banco de dados

            system("cls");
            printf("######################\n");
            printf("# Cadastro Concluido #\n");
            printf("######################\n");

            sleep(1);
            main();

        }
        else if(Global.Cd == 'n')
        {
            system("cls");
            printf("Cadastro Cancelado.\nVoltando ao Menu Principal...\n");
            fclose(DB); //Fecha DB
            getchar(); //Corrige bug quando Global.Cd != 's' && 'n'
            sleep(1);
            main();

        }
        else
        {
            printf("Valor inválido. Tente novamente...\n");
            fclose(DB); //Fecha DB
            sleep(1);
            Cadastro();

        }

    }

} //Fim da função Cadastro

void Consultar()
{
    char cpf[15];

    printf("\nDigite o CPF que deseja consultar:");
    fgets(cpf, sizeof(cpf), stdin);

    buscar_aluno(cpf);
}

void buscar_aluno(char cpf[15])
{
    system("cls");
    DB = fopen("dados.txt", "r"); //Abertura do DB para leitura de dados

    if(DB == NULL)   //Verificação do Banco de dados
    {
        printf("\nErro no Banco de Dados...\n");
        return 1;

    }
    else
    {
        char listagem[250]; //String geral para os dados

        while(fgets(listagem, 250, DB) != NULL)
        {
            //printf("%s", listagem);
            if (strcmp(listagem, cpf) == 0)
            {

                printf("######################\n");
                printf("# Aluno encontrado #\n");
                printf("######################\n\n");

                printf("CPF: %s", listagem);
                fgets(listagem, 250, DB);
                printf("Nome: %s", listagem);
                fgets(listagem, 250, DB);
                printf("Matricula: %s", listagem);
                fgets(listagem, 250, DB);
                printf("Data de nascimento: %s", listagem);
                fgets(listagem, 250, DB);
                printf("Notas: %s", listagem);
                break;
            }

            char aux[250];
            int contador = 3;
            while(fgets(aux, 250, DB) != NULL && contador != 0)
            {
                //printf("%s", aux);
                // printf("%i", contador);
                contador--;
            }

        }

        fclose(DB);

        printf("\nVoltar ao Menu Principal? [s/n]: ");
        scanf("%c", &Global.Cd);

        if(Global.Cd == 's')
        {
            main();

        }
        else if(Global.Cd != 's' && Global.Cd != 'n')
        {
            printf("Valor invalido.\nVoltando ao Menu Principal...\n");
            sleep(1);
            main();

        }
    }
}

int validarCPF(char cpf[12])
{
    cpf[strlen(cpf)-1] = '\0';

    int i, j, digito1 = 0, digito2 = 0;
    if(strlen(cpf) != 11)
    {
        printf("\nCPF invalido, digite novamente\n");
        return 0;
    }
    else if((strcmp(cpf,"00000000000") == 0) || (strcmp(cpf,"11111111111") == 0) || (strcmp(cpf,"22222222222") == 0) ||
            (strcmp(cpf,"33333333333") == 0) || (strcmp(cpf,"44444444444") == 0) || (strcmp(cpf,"55555555555") == 0) ||
            (strcmp(cpf,"66666666666") == 0) || (strcmp(cpf,"77777777777") == 0) || (strcmp(cpf,"88888888888") == 0) ||
            (strcmp(cpf,"99999999999") == 0))
    {
        printf("\nCPF invalido, digite novamente\n");
        return 0; ///se o CPF tiver todos os números iguais ele é inválido.
    }
    else
    {
        ///digito 1---------------------------------------------------
        for(i = 0, j = 10; i < strlen(cpf)-2; i++, j--) ///multiplica os números de 10 a 2 e soma os resultados dentro de digito1
            digito1 += (cpf[i]-48) * j;
        digito1 %= 11;
        if(digito1 < 2)
            digito1 = 0;
        else
            digito1 = 11 - digito1;
        if((cpf[9]-48) != digito1)
            return 0; ///se o digito 1 não for o mesmo que o da validação CPF é inválido
        else
            ///digito 2--------------------------------------------------
        {
            for(i = 0, j = 11; i < strlen(cpf)-1; i++, j--) ///multiplica os números de 11 a 2 e soma os resultados dentro de digito2
                digito2 += (cpf[i]-48) * j;
            digito2 %= 11;
            if(digito2 < 2)
                digito2 = 0;
            else
                digito2 = 11 - digito2;
            if((cpf[10]-48) != digito2)
            {
                printf("\nCPF invalido, digite novamente\n");
                return 0; ///se o digito 2 não for o mesmo que o da validação CPF é inválido
            }

        }
    }
    cpf[strlen(cpf)] = '\n';
    return 1;
}

void buscar_e_remover_aluno(char cpf[15])
{
    system("cls");
    DB = fopen("dados.txt", "r");

    if(DB == NULL)
    {
        printf("\nErro no Banco de Dados...\n");
        return 1;

    }
    else
    {
        char listagem[250]; //String geral para os dados

        int contadorDeLinhas = -1;
        while(fgets(listagem, 250, DB) != NULL)
        {
            contadorDeLinhas++;
            if (strcmp(listagem, cpf) == 0)
            {
                fclose(DB);
                recriar_arquivo(contadorDeLinhas);
            }
            char aux[250];
            int contador = 3;
            while(fgets(aux, 250, DB) != NULL && contador != 0)
            {
                contador--;
            }
        }

        fclose(DB);

        printf("\nVoltar ao Menu Principal? [s/n]: ");
        scanf("%c", &Global.Cd);

        if(Global.Cd == 's')
        {
            main();

        }
        else if(Global.Cd != 's' && Global.Cd != 'n')
        {
            printf("Valor invalido.\nVoltando ao Menu Principal...\n");
            sleep(1);
            main();

        }
    }
}

recriar_arquivo(int linha)
{
    FILE *fileptr1, *fileptr2;
    char ch;
    int delete_line = linha;

    if(delete_line > 0)
    {
        delete_line = delete_line * 5;
    }
    int delete_line_fim = delete_line + 4;

    int temp = 0;

    fileptr1 = fopen("dados.txt", "r");
    fileptr2 = fopen("replica.txt", "w");

    while (ch != EOF)
    {
        ch = getc(fileptr1);
        if(ch == EOF)
        {
            break;
        }
        if (ch == '\n')
        {
            temp++;
            if(temp==5)
            {
                continue;
            }
        }
        //except the line to be deleted
        if (temp < delete_line)
        {
            //copy all lines in file replica.c
            putc(ch, fileptr2);
        }

        if (temp > delete_line_fim)
        {
            putc(ch, fileptr2);
        }

    }
    fclose(fileptr1);
    fclose(fileptr2);

    remove("dados.txt");
    rename("replica.txt", "dados.txt");
}

void alterar_arquivo(int linha_alterar, char valor[50])
{
    FILE *fileptr1, *fileptr2;
    char ch;

    int temp = 0;

    fileptr1 = fopen("dados.txt", "r");
    fileptr2 = fopen("replica.txt", "w");

    while (ch != EOF)
    {
        ch = getc(fileptr1);
        if(ch == EOF)
        {
            break;
        }
        if (ch == '\n')
        {
            temp++;
        }

        //except the line to be deleted
        if (temp == linha_alterar)
        {
            temp++;
            putc('\n', fileptr2);
            for(int i = 0; i < 50; i++)
            {
                if(valor[i]== '\0')
                {
                    break;
                }
                putc(valor[i], fileptr2);
            }
            putc('\n', fileptr2);
            do
            {
                ch = getc(fileptr1);
            }
            while(ch != '\n');
            temp++;
        }
        else
        {
            putc(ch, fileptr2);
        }

    }
    fclose(fileptr1);
    fclose(fileptr2);

    remove("dados.txt");
    rename("replica.txt", "dados.txt");
}

void buscar_aluno_alterar(char cpf[15])
{
    system("cls");
    DB = fopen("dados.txt", "r"); //Abertura do DB para leitura de dados

    if(DB == NULL)   //Verificação do Banco de dados
    {
        printf("\nErro no Banco de Dados...\n");
        return 1;

    }
    else
    {
        char listagem[250]; //String geral para os dados
        int linha_alterar = 0;

        while(fgets(listagem, 250, DB) != NULL)
        {
            linha_alterar++;
            //printf("%s", listagem);
            if (strcmp(listagem, cpf) == 0)
            {

                printf("######################\n");
                printf("# Aluno encontrado #\n");
                printf("######################\n\n");

                printf("CPF: %s", listagem);
                fgets(listagem, 250, DB);
                printf("[1] - Nome: %s", listagem);
                fgets(listagem, 250, DB);
                printf("[2] - Matricula: %s", listagem);
                fgets(listagem, 250, DB);
                printf("[3] - Data de nascimento: %s", listagem);
                fgets(listagem, 250, DB);
                printf("[4] - Notas: %s", listagem);
                printf("[5] - Cancelar\n");
                break;
            }

            char aux[250];
            int contador = 3;
            while(fgets(aux, 250, DB) != NULL && contador != 0)
            {
                linha_alterar++;
                contador--;
            }

        }

        fclose(DB);

        int opcao = 0;

        printf("\n\nQual informacao deseja editar? ");
        scanf("%d", &opcao);

        char valor[50];

        switch (opcao)
        {
        case 1:
            printf("\nDigite o nome: ");
            scanf("%s", &valor);
            linha_alterar += opcao;
            alterar_arquivo(linha_alterar, valor);
            printf("Alteracao concluida...\n");
            sleep(1);
            main();
            break;

        case 2:
            printf("\nDigite a matricula: ");
            scanf("%s", &valor);
            linha_alterar += opcao;
            alterar_arquivo(linha_alterar, valor);
            printf("Alteracao concluida...\n");
            sleep(1);
            main();
            break;

        case 3:
            printf("\nDigite a data de nascimento (dd-mm-yyyy): ");
            scanf("%s", &valor);
            linha_alterar += opcao;
            alterar_arquivo(linha_alterar, valor);
            printf("Alteracao concluida...\n");
            sleep(1);
            main();
            break;

        case 4:
            printf("\nDigite as notas: ");
            scanf("%s", &valor);
            linha_alterar += opcao;
            alterar_arquivo(linha_alterar, valor);
            printf("Alteracao concluida...\n");
            sleep(1);
            main();
            break;

        case 5:
            system("cls");
            main();
            break;

        default:
            printf("Valor invalido! Tente novamente...\n");
            sleep(1);
            main();
            break;

        }
    }
}
