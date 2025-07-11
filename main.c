#include "usuario.h"
#include "jogo.h"


void exibirMenuPrincipal();
void exibirMenuLogin();

void exibirMenuLogin() {
    printf("\n===== BEM-VINDO AO GERENCIADOR DE BIBLIOTECA =====\n");
    printf("1. Realizar Login\n");
    printf("2. Cadastrar Novo Usuario\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

void exibirMenuPrincipal() {
    printf("\n===== MENU PRINCIPAL =====\n");
    printf("1. Cadastrar novo jogo\n");
    printf("2. Listar todos os jogos\n");
    printf("3. Editar um jogo\n");
    printf("4. Excluir um jogo\n");
    printf("---------------------------\n");
    printf("5. Ordenar jogos por ID (Merge Sort)\n");
    printf("6. Buscar jogo por ID (Busca Binaria)\n");
    printf("---------------------------\n");
    printf("7. Listar jogos por plataforma\n");
    printf("8. Listar jogos por genero\n");
    printf("9. Ver valor total da biblioteca\n");
    printf("10. Ver quantidade total de jogos\n");
    printf("---------------------------\n");
    printf("0. Salvar e Deslogar\n");
    printf("Escolha uma opcao: ");
}

int main() {
    
    UsuarioNode* listaDeUsuarios = carregarUsuarios("usuarios.dat");
    Usuario* usuarioLogado = NULL;
    int opcao_login;


    while(usuarioLogado == NULL) {
        exibirMenuLogin();
        scanf("%d", &opcao_login);
        getchar(); // Limpa o buffer

        switch(opcao_login) {
            case 1:
                usuarioLogado = realizarLogin(listaDeUsuarios);
                break;
            case 2:
                listaDeUsuarios = cadastrarUsuario(listaDeUsuarios);
                salvarUsuarios(listaDeUsuarios, "usuarios.dat"); 
                break;
            case 0:
                printf("Finalizando o programa.\n");
                return 0; 
            default:
                printf("Opcao invalida.\n");
        }
    }
    
    
    
    Node* minhaBiblioteca = NULL;
    int proximo_id = 1;
    char NOME_ARQUIVO[100];
    sprintf(NOME_ARQUIVO, "biblioteca_%s.dat", usuarioLogado->nome); 

    minhaBiblioteca = carregarJogos(NOME_ARQUIVO, &proximo_id);
    int opcao_main;

    do {
        exibirMenuPrincipal();
        scanf("%d", &opcao_main);
        getchar();

        switch(opcao_main) {
            case 1: minhaBiblioteca = cadastrarJogo(minhaBiblioteca, &proximo_id); break;
            case 2: listarJogos(minhaBiblioteca); break;
            case 3: {
                int id_edit;
                printf("Digite o ID do jogo para editar: ");
                scanf("%d", &id_edit); getchar();
                editarJogo(minhaBiblioteca, id_edit);
                break;
            }
            case 4: {
                int id_del;
                printf("Digite o ID do jogo para excluir: ");
                scanf("%d", &id_del); getchar();
                minhaBiblioteca = excluirJogo(minhaBiblioteca, id_del);
                break;
            }
            case 5: 
                mergeSort(&minhaBiblioteca);
                printf("Biblioteca ordenada com sucesso!\n");
                listarJogos(minhaBiblioteca);
                break;
            case 6: {
                int id_busca;
                printf("Digite o ID do jogo a ser buscado: ");
                scanf("%d", &id_busca); getchar();
                mergeSort(&minhaBiblioteca); 
                Jogo* encontrado = buscarJogoPorId_BuscaBinaria(minhaBiblioteca, id_busca);
                if (encontrado != NULL) {
                    printf("\n--- Jogo Encontrado ---\nID: %d, Nome: %s, Preco: R$%.2f\n", encontrado->id, encontrado->nome, encontrado->preco);
                    free(encontrado); 
                } else {
                    printf("Jogo com ID %d nao encontrado.\n", id_busca);
                }
                break;
            }
            case 7: listarPorPlataforma(minhaBiblioteca); break;
            case 8: listarPorGenero(minhaBiblioteca); break;
            case 9: calcularValorTotal(minhaBiblioteca); break;
            case 10: contarTotalDeJogos(minhaBiblioteca); break;
            case 0: 
                salvarJogos(minhaBiblioteca, NOME_ARQUIVO);
                printf("Biblioteca salva. Deslogando...\n");
                break;
            default: printf("Opcao invalida!\n"); break;
        }

    } while(opcao_main != 0);

    

    return 0;
}