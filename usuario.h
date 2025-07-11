#ifndef USUARIO_H
#define USUARIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char nome[50];
    char email[80];
    char senha[50];
} Usuario;


typedef struct UsuarioNode {
    Usuario usuario;
    struct UsuarioNode* proximo;
} UsuarioNode;


UsuarioNode* carregarUsuarios(const char* nome_arquivo);
void salvarUsuarios(UsuarioNode* cabeca, const char* nome_arquivo);
int verificarEmailUnico(UsuarioNode* cabeca, const char* email);
int validarFormatoEmail(const char* email);
UsuarioNode* cadastrarUsuario(UsuarioNode* cabeca);
Usuario* realizarLogin(UsuarioNode* cabeca);

#endif 