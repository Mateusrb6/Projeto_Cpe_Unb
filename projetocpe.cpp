#include <iostream>
using namespace std;

/*
 Agenda para armazenar nome, telefone e email
 deve ser possivel editar o conteudo

 Também deve ser possivel apagar e editar as entradas e a pesquisa de contatos por meio de qualquer uma de
suas informações
*/

struct contatos
{
    // armazena os dados dos contatos
    string nome;
    int telefone;
    string email;
};


void imprimir_menu(){
    // imprime opções para o usuário escolher o que quer fazer
    cout << "--------- Agenda de contatos --------- \n" << "Funcoes: \n" <<
         "(1) Consultar contatos adicionados \n" << "(2) adicionar contato \n" <<
         "(3) apagar contato \n" << "(4) editar contatos \n" << "(5) Mostrar contatos\n" << "(6) encerrar\n";
    cout << "Selecione uma das opcoes acima. \n";
}

int selecionar_opcao(){
    int opcao;
    cin >> opcao;
    return opcao;
}
void consultar_contato(){

}

void adicionar_contato(){

}

void apagar_contato(){

}

void editar_contato(){

}

void mostrar_contatos_existentes(){

}

void menu_opcoes(int opcao){
    switch(opcao){
        case 1:
            consultar_contato();
            break;
        case 2:
            adicionar_contato();
            break;
        case 3:
            apagar_contato();
            break;
        case 4:
            editar_contato();
            break;
        case 5:
            mostrar_contatos_existentes();
            break;
        case 6:
            cout << "encerrando...";
            break;
        default:
            cout << "opção inválida";
            break;
    }
}

int main(){

    while (true){
        imprimir_menu();
        int opcao = selecionar_opcao();
            if (opcao == 6){
            break;
            }
        menu_opcoes(opcao);
    }

    return 0;
}