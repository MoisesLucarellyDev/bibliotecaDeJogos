#include "usuario.h"

// Carrega a lista de usuários de um arquivo binário, como falei no outro arquivo, preferi usar 
// binario porque txt tava dando uns bugs.
UsuarioNode* carregarUsuarios(const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "rb"); 
    if (arquivo == NULL) {
        return NULL; 
    }
    UsuarioNode* cabeca = NULL;
    UsuarioNode* atual = NULL;
    Usuario temp_usuario;

    while (fread(&temp_usuario, sizeof(Usuario), 1, arquivo) == 1) {
        UsuarioNode* novoNode = (UsuarioNode*)malloc(sizeof(UsuarioNode));
        novoNode->usuario = temp_usuario;
        novoNode->proximo = NULL;
        if (cabeca == NULL) {
            cabeca = novoNode;
            atual = novoNode;
        } else {
            atual->proximo = novoNode;
            atual = novoNode;
        }
    }
    fclose(arquivo);
    return cabeca;
}


void salvarUsuarios(UsuarioNode* cabeca, const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "wb"); 
    if (arquivo == NULL) return;

    UsuarioNode* atual = cabeca;
    while (atual != NULL) {
        fwrite(&atual->usuario, sizeof(Usuario), 1, arquivo);
        atual = atual->proximo;
    }
    fclose(arquivo);
}


int verificarEmailUnico(UsuarioNode* cabeca, const char* email) {
    UsuarioNode* atual = cabeca;
    while (atual != NULL) {
        if (strcmp(atual->usuario.email, email) == 0) {
            return 0; 
        }
        atual = atual->proximo;
    }
    return 1; 
}

// Verifica se o formato do e-mail é válido (@ e tamanho).

int validarFormatoEmail(const char* email) {
    if (strchr(email, '@') == NULL) { 
        printf("Erro: E-mail invalido! Nao contem '@'.\n");
        return 0;
    }
    if (strlen(email) >= 80) { 
        printf("Erro: E-mail muito longo! (max 79 caracteres).\n");
        return 0;
    }
    return 1;
}


UsuarioNode* cadastrarUsuario(UsuarioNode* cabeca) {
    Usuario novo_usuario;
    char temp_email[80];

    printf("\n--- Cadastro de Novo Usuario ---\n");
    printf("Digite seu nome: ");
    fgets(novo_usuario.nome, 50, stdin);
    novo_usuario.nome[strcspn(novo_usuario.nome, "\n")] = 0;


    while (1) {
        printf("Digite seu e-mail: ");
        fgets(temp_email, 80, stdin);
        temp_email[strcspn(temp_email, "\n")] = 0;

        if (validarFormatoEmail(temp_email) && verificarEmailUnico(cabeca, temp_email)) {
            strcpy(novo_usuario.email, temp_email);
            break;
        } else if (!verificarEmailUnico(cabeca, temp_email)) {
            printf("Erro: Este e-mail ja esta cadastrado. Tente outro.\n");
        }
    }

    printf("Digite sua senha: ");
    fgets(novo_usuario.senha, 50, stdin);
    novo_usuario.senha[strcspn(novo_usuario.senha, "\n")] = 0;

    UsuarioNode* novoNode = (UsuarioNode*)malloc(sizeof(UsuarioNode));
    novoNode->usuario = novo_usuario;
    novoNode->proximo = cabeca; // Adiciona no início da lista

    printf("Usuario '%s' cadastrado com sucesso!\n", novo_usuario.nome);
    return novoNode;
}


Usuario* realizarLogin(UsuarioNode* cabeca) {
    char email[80], senha[50];
    int tentativas = 3;

    while (tentativas > 0) {
        printf("\n--- Login ---\n");
        printf("E-mail: ");
        fgets(email, 80, stdin);
        email[strcspn(email, "\n")] = 0;

        printf("Senha: ");
        fgets(senha, 50, stdin);
        senha[strcspn(senha, "\n")] = 0;

        UsuarioNode* atual = cabeca;
        while (atual != NULL) {
            if (strcmp(atual->usuario.email, email) == 0 && strcmp(atual->usuario.senha, senha) == 0) {
                printf("\nLogin bem-sucedido! Bem-vindo(a), %s!\n", atual->usuario.nome);
                return &atual->usuario; 
            }
            atual = atual->proximo;
        }
        
        tentativas--;
        printf("E-mail ou senha incorretos. Voce tem mais %d tentativa(s).\n", tentativas);
    }
    printf("Numero maximo de tentativas atingido.\n");
    return NULL; 
}