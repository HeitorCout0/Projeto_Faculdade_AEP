#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

// Fun��o para criptografar a senha usando Cifra de Substitui��o, incluindo letras e n�meros
void criptografarSenha(char* senha, int chave) {
    int i;
    for (i = 0; senha[i] != '\0'; i++) {
        // Criptografar letras min�sculas (a-z)
        if (senha[i] >= 'a' && senha[i] <= 'z') {
            senha[i] = ((senha[i] - 'a' + chave) % 26) + 'a';
        }
        // Criptografar letras mai�sculas (A-Z)
        else if (senha[i] >= 'A' && senha[i] <= 'Z') {
            senha[i] = ((senha[i] - 'A' + chave) % 26) + 'A';
        }
        // Criptografar n�meros (0-9)
        else if (senha[i] >= '0' && senha[i] <= '9') {
            senha[i] = ((senha[i] - '0' + chave) % 10) + '0';
        }
    }
}

// Fun��o para descriptografar a senha usando Cifra de C�sar, incluindo letras e n�meros
void descriptografarSenha(char* senha, int chave) {
    int i;
    for (i = 0; senha[i] != '\0'; i++) {
        // Descriptografar letras min�sculas (a-z)
        if (senha[i] >= 'a' && senha[i] <= 'z') {
            senha[i] = ((senha[i] - 'a' - chave + 26) % 26) + 'a';
        }
        // Descriptografar letras mai�sculas (A-Z)
        else if (senha[i] >= 'A' && senha[i] <= 'Z') {
            senha[i] = ((senha[i] - 'A' - chave + 26) % 26) + 'A';
        }
        // Descriptografar n�meros (0-9)
        else if (senha[i] >= '0' && senha[i] <= '9') {
            senha[i] = ((senha[i] - '0' - chave + 10) % 10) + '0';
        }
    }
}

int main() {
    setlocale(LC_ALL, "portuguese");  /* Permitir colocar acentua��o em portugu�s */

    /* Declara��o das vari�veis */
    char nomes[100][50];     /* Array para armazenar at� 100 nomes de usu�rios */
    char emails[100][50];    /* Array para armazenar at� 100 e-mails de usu�rios */
    char senhas[100][50];    /* Array para armazenar at� 100 senhas criptografadas */
    int qtdUsuarios = 0;     /* Contador para o n�mero de usu�rios cadastrados */
    int opcao;
    int id;
    int chaveCriptografia = 3;  /* Definindo uma chave para a Cifra de C�sar (deslocamento de 3 caracteres) */

    FILE *arquivoCriptografados;  /* Arquivo para armazenar dados com senha criptografada */
    FILE *arquivoDescriptografados;  /* Arquivo para armazenar dados com senha descriptografada */

    do {
        /* Menu */
        printf("\nMenu de Op��es:\n");
        printf("1. Incluir novo usu�rio\n");
        printf("2. Alterar usu�rio\n");
        printf("3. Excluir usu�rio\n");
        printf("4. Listar usu�rios\n");
        printf("5. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);
        getchar();  /* Limpa o buffer do teclado */

        switch(opcao) {
            case 1:
                /* Incluir novo usu�rio */
                if (qtdUsuarios >= 100) {
                    printf("Limite de usu�rios atingido!\n");
                } else {
                    printf("Informe o nome do usu�rio: ");
                    fgets(nomes[qtdUsuarios], 50, stdin);
                    nomes[qtdUsuarios][strcspn(nomes[qtdUsuarios], "\n")] = '\0';  /* Remove o '\n' no final */

                    printf("Informe o e-mail do usu�rio: ");
                    fgets(emails[qtdUsuarios], 50, stdin);
                    emails[qtdUsuarios][strcspn(emails[qtdUsuarios], "\n")] = '\0';  /* Remove o '\n' no final */

                    printf("Informe a senha do usu�rio: ");
                    fgets(senhas[qtdUsuarios], 50, stdin);
                    senhas[qtdUsuarios][strcspn(senhas[qtdUsuarios], "\n")] = '\0';  /* Remove o '\n' no final */

                    /* Criptografa a senha antes de salvar */
                    char senhaCriptografada[50];
                    strcpy(senhaCriptografada, senhas[qtdUsuarios]);
                    criptografarSenha(senhaCriptografada, chaveCriptografia);

                    /* Salva os dados com senha criptografada em um arquivo */
                    arquivoCriptografados = fopen("usuarios_criptografados.txt", "a");
                    if (arquivoCriptografados == NULL) {
                        printf("Erro ao abrir o arquivo para salvar os dados criptografados.\n");
                        return 1;
                    }
                    fprintf(arquivoCriptografados, "%s,%s,%s\n", nomes[qtdUsuarios], emails[qtdUsuarios], senhaCriptografada);
                    fclose(arquivoCriptografados);

                    /* Salva as senhas descriptografadas em outro arquivo */
                    arquivoDescriptografados = fopen("usuarios_descriptografados.txt", "a");
                    if (arquivoDescriptografados == NULL) {
                        printf("Erro ao abrir o arquivo para salvar as senhas descriptografadas.\n");
                        return 1;
                    }
                    fprintf(arquivoDescriptografados, "%s,%s,%s\n", nomes[qtdUsuarios], emails[qtdUsuarios], senhas[qtdUsuarios]);
                    fclose(arquivoDescriptografados);

                    qtdUsuarios++;
                    printf("Usu�rio inclu�do com sucesso!\n");
                }
                break;

            case 2:
                /* Alterar dados de um usu�rio */
                printf("Informe o ID do usu�rio a ser alterado (1 a %d): ", qtdUsuarios);
                scanf("%d", &id);
                getchar();  /* Limpa o buffer do teclado */

                if (id < 1 || id > qtdUsuarios) {
                    printf("Usu�rio n�o encontrado!\n");
                } else {
                    id--;  /* Ajuste para o �ndice correto (0-based) */
                    printf("Informe o novo nome: ");
                    fgets(nomes[id], 50, stdin);
                    nomes[id][strcspn(nomes[id], "\n")] = '\0';  /* Remove o '\n' no final */
                    printf("Informe o novo e-mail: ");
                    fgets(emails[id], 50, stdin);
                    emails[id][strcspn(emails[id], "\n")] = '\0';  /* Remove o '\n' no final */
                    printf("Informe a nova senha: ");
                    fgets(senhas[id], 50, stdin);
                    senhas[id][strcspn(senhas[id], "\n")] = '\0';  /* Remove o '\n' no final */

                    /* Criptografa a nova senha antes de salvar */
                    char senhaCriptografada[50];
                    strcpy(senhaCriptografada, senhas[id]);
                    criptografarSenha(senhaCriptografada, chaveCriptografia);

                    /* Regrava os dados no arquivo com senha criptografada */
                    arquivoCriptografados = fopen("usuarios_criptografados.txt", "w");
                    if (arquivoCriptografados == NULL) {
                        printf("Erro ao abrir o arquivo para salvar os dados criptografados.\n");
                        return 1;
                    }
                    int i;
                    for (i = 0; i < qtdUsuarios; i++) {
                        fprintf(arquivoCriptografados, "%s,%s,%s\n", nomes[i], emails[i], senhas[i]);
                    }
                    fclose(arquivoCriptografados);

                    /* Regrava as senhas descriptografadas no arquivo */
                    arquivoDescriptografados = fopen("usuarios_descriptografados.txt", "w");
                    if (arquivoDescriptografados == NULL) {
                        printf("Erro ao abrir o arquivo para salvar as senhas descriptografadas.\n");
                        return 1;
                    }
                    for (i = 0; i < qtdUsuarios; i++) {
                        fprintf(arquivoDescriptografados, "%s,%s,%s\n", nomes[i], emails[i], senhas[i]);
                    }
                    fclose(arquivoDescriptografados);

                    printf("Usu�rio alterado com sucesso!\n");
                }
                break;

            case 3:
                /* Excluir um usu�rio */
                printf("Informe o ID do usu�rio a ser exclu�do (1 a %d): ", qtdUsuarios);
                scanf("%d", &id);
                getchar();  /* Limpa o buffer do teclado */

                if (id < 1 || id > qtdUsuarios) {
                    printf("Usu�rio n�o encontrado!\n");
                } else {
                    id--;  /* Ajuste para o �ndice correto (0-based) */
                    int i;
                    for (i = id; i < qtdUsuarios - 1; i++) {
                        strcpy(nomes[i], nomes[i + 1]);
                        strcpy(emails[i], emails[i + 1]);
                        strcpy(senhas[i], senhas[i + 1]);
                    }
                    qtdUsuarios--;

                    /* Regrava os dados no arquivo */
                    arquivoCriptografados = fopen("usuarios_criptografados.txt", "w");
                    if (arquivoCriptografados == NULL) {
                        printf("Erro ao abrir o arquivo para salvar os dados criptografados.\n");
                        return 1;
                    }
                    for (i = 0; i < qtdUsuarios; i++) {
                        fprintf(arquivoCriptografados, "%s,%s,%s\n", nomes[i], emails[i], senhas[i]);
                    }
                    fclose(arquivoCriptografados);

                    /* Regrava as senhas descriptografadas no arquivo */
                    arquivoDescriptografados = fopen("usuarios_descriptografados.txt", "w");
                    if (arquivoDescriptografados == NULL) {
                        printf("Erro ao abrir o arquivo para salvar as senhas descriptografadas.\n");
                        return 1;
                    }
                    for (i = 0; i < qtdUsuarios; i++) {
                        fprintf(arquivoDescriptografados, "%s,%s,%s\n", nomes[i], emails[i], senhas[i]);
                    }
                    fclose(arquivoDescriptografados);

                    printf("Usu�rio exclu�do com sucesso!\n");
                }
                break;

            case 4:
                /* Listar todos os usu�rios */
                if (qtdUsuarios == 0) {
                    printf("N�o h� usu�rios cadastrados!\n");
                } else {
                    printf("\nLista de Usu�rios:\n");
                    int i;
                    for (i = 0; i < qtdUsuarios; i++) {
                        /* Descriptografa a senha para exibir */
                        char senhaDescriptografada[50];
                        strcpy(senhaDescriptografada, senhas[i]);
                        descriptografarSenha(senhaDescriptografada, chaveCriptografia);
                        printf("ID: %d, Nome: %s, Email: %s, Senha: %s\n", i + 1, nomes[i], emails[i], senhaDescriptografada);
                    }
                }
                break;

            case 5:
                printf("Saindo...\n");
                break;

            default:
                printf("Op��o inv�lida! Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}

