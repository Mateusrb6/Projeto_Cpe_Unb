#include <iostream>
#include <vector>
#include <regex>
using namespace std;

/*
 Agenda para armazenar nome, telefone e email
 deve ser possivel editar o conteudo

 Também deve ser possivel apagar e editar as entradas e a pesquisa de contatos por meio de qualquer uma de
suas informações
*/

struct Contato
{
    // armazena os dados dos contatos
    string nome;
    string telefone; // usar string pra telefone com objetivo de validar com facilidade
    string email;
};

vector<Contato> agenda;
/*
cria um vetor vazio que pode armazenar múltiplos objetos Contato. 
é um vetor dinamico com capacidade de aumentar ou diminuir de tamanho conforme a necessidade

*resumo: ele gerencia a memoria automaticamente*

*/

bool validar_nome(const string& nome){
    regex padrao_nome(R"([a-zA-Z\s]+)");

    // define que podem ser usadas letras maisculas (A-Z) e minusculas (a-z)
    
    return regex_match(nome, padrao_nome);
}

bool validar_telefone(const string& telefone){
    // valida o telefone usando a biblioteca regex
    regex padrao_telefone(R"(^9\d{4}-\d{4}$)"); 
    /*
    ^ = inicio da string
    9 = começa com o numero 9
    \d = qualquer numero de 0 a 9
    {4} = deve haver 4 digitos
    - = traço separando as duas partes
    $ = final da string
    */
   return regex_match(telefone, padrao_telefone);
}

bool validar_email(const string& email){
    // valida o email usando a biblioteca regex
    regex padrao_email(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    /*
    [a-zA-Z0-9._%+-]+ = define caracteres validos antes do @
    @ = separa o nome do usuario do dominio do email
    [a-zA-Z0-9.-]+ = caracteres validos pro dominio do email
    \. = separa dominio da extensão do dominio
    [a-zA-Z]{2,} = define caracteres validos pra extensão do dominio
    R"(...)" = delimitador da string
    */
    return regex_match(email, padrao_email);
}

void imprimir_menu(){
    // imprime opções para o usuário escolher o que quer fazer
    cout << "--------- Agenda de contatos --------- \n" << "Funcoes: \n" <<
         "(1) Consultar contatos adicionados \n" << "(2) adicionar contato \n" <<
         "(3) apagar contato \n" << "(4) editar contatos \n" << "(5) Mostrar contatos\n" << "(6) encerrar\n";
    cout << "Selecione uma das opcoes acima. \n";
}

int selecionar_opcao(){
    // pega a opção selecionada pelo usuario 
    int opcao;
    cin >> opcao;
    return opcao;
}
void consultar_contato(const vector<Contato>& agenda){
    // usar qualquer uma das informações dentre nome, telefone ou email para achar um contato

}

void adicionar_contato(){
    // adiciona contato pedindo ao usuario o nome, telefone e email
    Contato novo_contato;

    cout << "digite o nome do contato: " << endl;
    cin.ignore();
    getline(cin, novo_contato.nome);
    while(!validar_nome(novo_contato.nome)){
        cout << "nome invalido." << endl;
        getline(cin, novo_contato.nome);
    }

    cout << "digite o telefone do contato (formato 9XXXX-XXXX): " << endl;
    getline(cin, novo_contato.telefone);
    while(!validar_telefone(novo_contato.telefone)){
        cout << "número de telefone inválido." << endl;
        getline(cin, novo_contato.telefone);
    }
 
    cout << "digite o email do contato: " << endl;
    getline(cin, novo_contato.email);
    while (!validar_email(novo_contato.email))
    {
        cout << "email inválido." << endl;
        getline(cin, novo_contato.email);
    }
    

    agenda.push_back(novo_contato);
    // adiciona o novo_contato no final do vetor agenda
    cout << "Contato adicionado." << endl;

}

void apagar_contato(const vector<Contato>& agenda){
    // pede nome do contato para apagar o contato

}

void editar_contato(const vector<Contato>& agenda){
    // edita informacoes do contato (nome, telefone ou email)

}

void mostrar_contatos_existentes(const vector<Contato>& agenda){
    // lista todos os contatos da agenda
    if(agenda.empty()){
        // verifica se a agenda está vazia
        cout << "agenda vazia." << endl;
        return;
    } 
    
    for (int i = 0; i < agenda.size(); i++)
    {
        // ciclo de repetição de 0 até o tamanho total da agenda
        const Contato& contato = agenda.at(i);
        cout << "\t ---Agenda de contatos---" << endl;
        cout << "Contato número" << i+1 << " :"<< endl; // exibe o numero do contato (i+1 porque i começa com 0)
        cout << "Nome: " << contato.nome << endl;
        cout << "Email: " << contato.email << endl;
        cout << "Telefone: " << contato.telefone << endl;
    }
}

void menu_opcoes(int opcao){
    switch(opcao){
        case 1:
            consultar_contato(agenda);
            break;
        case 2:
            adicionar_contato();
            break;
        case 3:
            apagar_contato(agenda);
            break;
        case 4:
            editar_contato(agenda);
            break;
        case 5:
            mostrar_contatos_existentes(agenda);
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