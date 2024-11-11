#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

void criptografarSenha(char* senha, int chave) {
    int i;
    for (i = 0; senha[i] != '\0'; i++) {
        // Criptografar letras minúsculas (a-z)
        if (senha[i] >= 'a' && senha[i] <= 'z') {
            senha[i] = ((senha[i] - 'a' + chave) % 26) + 'a';
        }
        // Criptografar letras maiúsculas (A-Z)
        else if (senha[i] >= 'A' && senha[i] <= 'Z') {
            senha[i] = ((senha[i] - 'A' + chave) % 26) + 'A';
        }
        // Criptografar números (0-9)
        else if (senha[i] >= '0' && senha[i] <= '9') {
            senha[i] = ((senha[i] - '0' + chave) % 10) + '0';
        }
    }
}

void descriptografarSenha(char* senha, int chave) {
    int i;
    for (i = 0; senha[i] != '\0'; i++) {
        // Descriptografar letras minúsculas (a-z)
        if (senha[i] >= 'a' && senha[i] <= 'z') {
            senha[i] = ((senha[i] - 'a' - chave + 26) % 26) + 'a';
        }
        // Descriptografar letras maiúsculas (A-Z)
        else if (senha[i] >= 'A' && senha[i] <= 'Z') {
            senha[i] = ((senha[i] - 'A' - chave + 26) % 26) + 'A';
        }
        // Descriptografar números (0-9)
        else if (senha[i] >= '0' && senha[i] <= '9') {
            senha[i] = ((senha[i] - '0' - chave + 10) % 10) + '0';
        }
    }
}

int main() {
    setlocale(LC_ALL, "portuguese");  /* Permitir colocar acentuação em português */

    /* Declaração das variáveis */
    char nomes[100][50];     /* Array para armazenar até 100 nomes de usuários */
    char emails[100][50];    /* Array para armazenar até 100 e-mails de usuários */
    char senhas[100][50];    /* Array para armazenar até 100 senhas criptografadas */
    int qtdUsuarios = 0;     /* Contador para o número de usuários cadastrados */
    int opcao;
    int id;
    int chaveCriptografia = 3;  

    FILE *arquivoCriptografados;  /* Arquivo para armazenar dados com senha criptografada */
    FILE *arquivoDescriptografados;  /* Arquivo para armazenar dados com senha descriptografada */

    do {
        /* Menu */
        printf("\nMenu de Opções:\n");
        printf("1. Incluir novo usuário\n");
        printf("2. Alterar usuário\n");
        printf("3. Excluir usuário\n");
        printf("4. Listar usuários\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();  /* Limpa o buffer do teclado */

        switch(opcao) {
            case 1:
                /* Incluir novo usuário */
                if (qtdUsuarios >= 100) {
                    printf("Limite de usuários atingido!\n");
                } else {
                    printf("Informe o nome do usuário: ");
                    fgets(nomes[qtdUsuarios], 50, stdin);
                    nomes[qtdUsuarios][strcspn(nomes[qtdUsuarios], "\n")] = '\0';  /* Remove o '\n' no final */

                    printf("Informe o e-mail do usuário: ");
                    fgets(emails[qtdUsuarios], 50, stdin);
                    emails[qtdUsuarios][strcspn(emails[qtdUsuarios], "\n")] = '\0';  /* Remove o '\n' no final */

                    printf("Informe a senha do usuário: ");
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
                    printf("Usuário incluído com sucesso!\n");
                }
                break;

            case 2:
                /* Alterar dados de um usuário */
                printf("Informe o ID do usuário a ser alterado (1 a %d): ", qtdUsuarios);
                scanf("%d", &id);
                getchar();  /* Limpa o buffer do teclado */

                if (id < 1 || id > qtdUsuarios) {
                    printf("Usuário não encontrado!\n");
                } else {
                    id--;  /* Ajuste para o índice correto (0-based) */
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

                    printf("Usuário alterado com sucesso!\n");
                }
                break;

            case 3:
                /* Excluir um usuário */
                printf("Informe o ID do usuário a ser excluído (1 a %d): ", qtdUsuarios);
                scanf("%d", &id);
                getchar();  /* Limpa o buffer do teclado */

                if (id < 1 || id > qtdUsuarios) {
                    printf("Usuário não encontrado!\n");
                } else {
                    id--;  /* Ajuste para o índice correto (0-based) */
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

                    printf("Usuário excluído com sucesso!\n");
                }
                break;

            case 4:
                /* Listar todos os usuários */
                if (qtdUsuarios == 0) {
                    printf("Não há usuários cadastrados!\n");
                } else {
                    printf("\nLista de Usuários:\n");
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
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}

