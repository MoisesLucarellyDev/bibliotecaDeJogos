# Projeto de Algoritmos e Estruturas de Dados

Este projeto é um Gerenciador de Biblioteca de Jogos de Videogame desenvolvido em c, utilizando listas ligadas, algoritmos de ordenação (Merge Sort) e busca (Busca Binária), manipulação de arquivos e modularização de código.

## Funcionalidades

* **Sistema de Login:** Cadastro e login de usuários.
* **Validação de E-mail:** Garante que o e-mail tenha `@`, menos de 80 caracteres e seja único no sistema.
* **CRUD de Jogos:**
    * Cadastrar novos jogos na biblioteca.
    * Listar todos os jogos cadastrados.
    * Editar as informações de um jogo existente.
    * Excluir um jogo da biblioteca.
* **Persistência de Dados:** Todas as informações de usuários e jogos são salvas em arquivos (`usuarios.dat`, `biblioteca.dat`) e recarregadas ao iniciar o programa.
* **Algoritmos Avançados:**
    * **Merge Sort:** Para ordenar a lista de jogos por ID.
    * **Busca Binária:** Para encontrar jogos de forma eficiente após a ordenação.
* **Operações Específicas:**
    * Listar jogos por uma plataforma específica.
    * Listar jogos por um gênero específico.
    * Calcular o valor total em reais da biblioteca de jogos.
    * Contar o número total de jogos na biblioteca.

## Criação de arquivos
   Não é necessário se preocupar com criar os arquivos, o código é responsável pela criação automática.
   
## Como Compilar e Executar

O projeto foi escrito em C e pode ser compilado com o GCC. No terminal, navegue até a pasta do projeto e execute o seguinte comando:

```bash
gcc main.c jogo.c usuario.c -o programa -Wall
```

Depois de compilar, execute o programa com:

```bash
./programa
```

---
