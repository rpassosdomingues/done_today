#include <stdio.h>
#include <stdlib.h>

// Podemos olhar para uma struct como uma caixa onde podemos guardar, "sem limites", uma coleção de variáveis.
typedef struct pf {
    char nome[50];
    char sexo;
    int idade;
} PessoaFisica;

/*
void define_nome (char *nome) {
    printf("Digite o nome: ");
    scanf(" %s", nome);
}

void define_sexo (char *sexo) {
    printf("Digite o sexo: ");
    scanf(" %c", sexo);
}

void define_idade (int *idade) {
    printf("Digite a idade: ");
    scanf(" %d", idade);
}
*/

void preenche_struct (PessoaFisica *pessoa) {
    //printf("Digite o nome: ");
    //scanf(" %s", &pessoa->nome);
    //scanf(" %s", &(*pessoa).nome);
    //getchar();
    printf("Digite o sexo: ");
    scanf(" %c", &pessoa->sexo);
    //scanf(" %c", &(*pessoa).sexo);
    printf("Digite a idade: ");
    scanf(" %d", &pessoa->idade);
    //scanf(" %d", &(*pessoa).idade);
}

void imprime_struct (PessoaFisica pessoa) {
    printf(" Nome: %s\n", pessoa.nome);
    printf(" Sexo: %c\n", pessoa.sexo);
    printf("Idade: %d anos\n", pessoa.idade);
}

/*
void imprime_endereco (PessoaFisica pessoa) {
    printf("Endereco Funcao: %p\n", &pessoa.nome[0]);
}
*/

int main () {
    PessoaFisica pessoafisica;

    // Atribuições individuais dentro da struct
    //pessoafisica.sexo = 'f';
    //pessoafisica.idade = 18;
    
    /*
    // Chamadas de função passando campos dentro da struct por referência
    define_nome(&pessoafisica.nome[0]);
    define_sexo(&pessoafisica.sexo);
    define_idade(&pessoafisica.idade);
    */
    preenche_struct(&pessoafisica);
    
    // Chamada de função para imprimir na tela as atribuições da struct
    imprime_struct(pessoafisica);

    return 0;
}