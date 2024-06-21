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
    string opcao;
    getline(cin, opcao);

    for(char c : opcao){
        if (!isdigit(c))
        {
            return -1;
        }
        
    }

   return stoi(opcao);
}

//Imprime os dados do contato
void mostrar_contato(int i, const Contato& contato){
    cout << "\tContato número " << i+1 << " :"<< endl; // exibe o numero do contato (i+1 porque i começa com 0)
    cout << "Nome: " << contato.nome << endl;
    cout << "Email: " << contato.email << endl;
    cout << "Telefone: " << contato.telefone << endl;
}

//Retorna o indice do contato buscado, no vetor agenda ou menos -1 caso não achado
int busca_contato(string parametro_buscado, const vector<Contato>& agenda){
    //Percorre a agenda
    for(int i =0 ; i<agenda.size() ; i++){

        const Contato& contato = agenda.at(i);
        //Testa e se contiver um contato com esse nome, imprime ele no modelo da função "mostrar_contatos_existentes".
        if (contato.nome.compare(parametro_buscado) == 0)
          return i;
        else if (contato.telefone.compare(parametro_buscado) == 0)
          return i;
        else if (contato.email.compare(parametro_buscado) == 0)
          return i;
        else if(i ==( agenda.size() -1))
          return -1; // CAso não seja encontrado na ultima iteração
    }
    return 0;


}

void consultar_contato(const vector<Contato>& agenda){

    if(agenda.empty()){
        // verifica se a agenda está vazia
        cout << "Agenda vazia." << endl;
        return;
    }

    // usar qualquer uma das informações dentre nome, telefone ou email para achar um contato
    cout << "Escolha uma das opções de consulta: \n1) Nome\n2) Telefone\n3) Email." << endl;

    int opcao_consulta;
    bool valid = 1;
    string nome_consulta, telefone_consulta, email_consulta;
    while(valid){
    cin >> opcao_consulta;

        switch (opcao_consulta)
        {
            // consulta de acordo com a informação dada pelo usuario
            case 1:
                cout << "Digite o nome do contato: " << endl;

                cin.ignore();
                getline(cin, nome_consulta);

                while(!validar_nome(nome_consulta)){
                    cout << "Nome inválido. Tente novamente." << endl;
                    getline(cin, nome_consulta);
                }

                int busca;
                busca = busca_contato(nome_consulta,agenda);
                if(busca != -1) {
                    const Contato& contato = agenda.at(busca);
                    mostrar_contato(busca,contato);
                }

                else cout << "Nome não encontrado" << endl;
                valid = 0; //Quebra o loop principal ou seja uma opção valida foi escolhida

                break;
            case 2:
                cout << "Digite o telefone do contato(formato 9XXXX-XXXX): " << endl;

                cin.ignore();
                getline(cin, telefone_consulta);

                while(!validar_telefone(telefone_consulta)){
                    cout << "Telefone inválido. Tente novamente." << endl;
                    getline(cin, telefone_consulta);
                }

                busca = busca_contato(telefone_consulta,agenda);
                if(busca != -1) {
                    const Contato& contato = agenda.at(busca);
                    mostrar_contato(busca,contato);
                }
                else cout << "Telefone não encontrado" << endl;
                valid = 0; //Quebra o loop principal ou seja uma opção valida foi escolhida

                break;
            case 3:
                cout << "Digite o email do contato: " << endl;

                cin.ignore();
                getline(cin, email_consulta);

                while(!validar_email(email_consulta)){
                    cout << "Email inválido. Tente novamente." << endl;
                    getline(cin, email_consulta);
                }

                busca = busca_contato(email_consulta,agenda);
                if(busca != -1) {
                    const Contato& contato = agenda.at(busca);
                    mostrar_contato(busca,contato);
                }
                else cout << "Email não encontrado" << endl;
                valid = 0; //Quebra o loop principal ou seja uma opção valida foi escolhida

                break;
            default:
                cout << "Opção inválida. Tente novamente." << endl;
                valid = 1;
                break;
        }
    }


}

void adicionar_contato(){
    // adiciona contato pedindo ao usuario o nome, telefone e email
    Contato novo_contato;

    cout << "Digite o nome do contato: " << endl;
    cin.ignore();
    getline(cin, novo_contato.nome);
    while(!validar_nome(novo_contato.nome)){
        cout << "nome invalido." << endl;
        getline(cin, novo_contato.nome);
    }

    cout << "Digite o telefone do contato (formato 9XXXX-XXXX): " << endl;
    getline(cin, novo_contato.telefone);
    while(!validar_telefone(novo_contato.telefone)){
        cout << "Número de telefone inválido." << endl;
        getline(cin, novo_contato.telefone);
    }

    cout << "Digite o email do contato: " << endl;
    getline(cin, novo_contato.email);
    while (!validar_email(novo_contato.email))
    {
        cout << "Email inválido." << endl;
        getline(cin, novo_contato.email);
    }


    agenda.push_back(novo_contato);
    // adiciona o novo_contato no final do vetor agenda
    cout << "Contato adicionado." << endl;

}

void apagar_contato(vector<Contato>& agenda){

    if(agenda.empty()){
        // verifica se a agenda está vazia
        cout << "Agenda vazia." << endl;
        return;
    }

    // pede nome do contato para apagar o contato
    cout << "Escolha uma das opções para apagar o contato: \n1) Nome\n2) Telefone\n3) Email." << endl;
    // encontrar o contato a ser apagado por meio de uma das opções, em seguida apagar o contato correspondente

    int opcao_apagar;
    bool valid = 1;
    string nome, telefone, email;

    while(valid){
    cin >> opcao_apagar;
        switch (opcao_apagar)
        {
            // consulta de acordo com a informação dada pelo usuario
            case 1:
                cout << "Digite o nome do contato: " << endl;

                cin.ignore();
                getline(cin, nome);

                while(!validar_nome(nome)){
                    cout << "Nome inválido. Tente novamente." << endl;
                    getline(cin, nome);
                }

                int busca;
                busca = busca_contato(nome,agenda);
                if(busca != -1) {
                    agenda.erase(agenda.begin() +busca);
                    cout << "Contato apagado." << endl;
                }

                else cout << "Nome não encontrado" << endl;
                valid = 0; //Quebra o loop principal ou seja uma opção valida foi escolhida

                break;
            case 2:
                cout << "Digite o telefone do contato(formato 9XXXX-XXXX): " << endl;

                cin.ignore();
                getline(cin, telefone);

                while(!validar_telefone(telefone)){
                    cout << "Telefone inválido. Tente novamente." << endl;
                    getline(cin, telefone);
                }

                busca = busca_contato(telefone,agenda);
                if(busca != -1) {
                    agenda.erase(agenda.begin() +busca);
                    cout << "Contato apagado." << endl;
                }
                else cout << "Telefone não encontrado" << endl;
                valid = 0; //Quebra o loop principal ou seja uma opção valida foi escolhida

                break;
            case 3:
                cout << "Digite o email do contato: " << endl;

                cin.ignore();
                getline(cin, email);

                while(!validar_email(email)){
                    cout << "Email inválido. Tente novamente." << endl;
                    getline(cin, email);
                }

                busca = busca_contato(email,agenda);
                if(busca != -1) {
                    agenda.erase(agenda.begin() +busca);
                    cout << "Contato apagado."<< endl;
                }
                else cout << "Email não encontrado" << endl;
                valid = 0; //Quebra o loop principal ou seja uma opção valida foi escolhida

                break;
            default:
                cout << "Opção inválida. Tente novamente." << endl;
                valid = 1;
                break;
        }
    }
}

void editar_contato(vector<Contato>& agenda){

    if(agenda.empty()){
        // verifica se a agenda está vazia
        cout << "Agenda vazia." << endl;
        return;
    }
    // edita informacoes do contato (nome, telefone ou email)
    cout << "Digite o nome,telefone ou email do contato para editar suas informações: " << endl;
    cin.ignore();

    string informacao_contato;

    int busca = -1;
    while(busca == -1){
        getline(cin,informacao_contato);
        busca = busca_contato(informacao_contato,agenda);
        if(busca != -1)
            cout << "Contato encontado." << endl;

        else {
            cout << "Contato não encontrado \nTente denovo o nome, telefone ou email :" << endl;

        }
    }

    Contato& contato = agenda.at(busca); // Definindo o contato buscado

    // busca o contato

    int opcao_edicao;
    bool valid = 1;
    cout << "Selecione o que deseja alterar: \n1) Nome\n2) Telefone\n3) email" << endl;
    // pergunta qual informação o usuario deseja editar


    string novo_nome, novo_telefone, novo_email;
    
    while(valid){
        valid = 0;
        cin >> opcao_edicao;
        switch (opcao_edicao)
        {
        case 1:
            cout << "Digite o novo nome do contato: " << endl;
            cin.ignore();
            getline(cin, novo_nome);

            while(!validar_nome(novo_nome)){
                    cout << "Nome inválido. Tente novamente." << endl;
                    getline(cin, novo_nome);
                }


            contato.nome = novo_nome;
            cout << "Nome editado." << endl;
            break;
        case 2:
            cout << "Digite o novo telefone: " << endl;
            cin.ignore();
            getline(cin, novo_telefone);

            while(!validar_telefone(novo_telefone)){
                cout << "Telefone inválido. Tente novamente." << endl;
                getline(cin, novo_telefone);
            }

            contato.telefone = novo_telefone;
            cout << "Telefone editado." << endl;

            break;
        case 3:
            cout << "Digite o novo email: " << endl;

            cin.ignore();
            getline(cin, novo_email);
            while(!validar_email(novo_email)){
                  cout << "Email inválido. Tente novamente." << endl;
                  getline(cin, novo_email);
              }

            contato.email = novo_email;
            cout << "Email editado." << endl;
            break;
        default:
            cout << "Opção invalida. Tente novamente.";
            valid  = 1;
            cin >> opcao_edicao;
            break;
        }
    }
}


void mostrar_contatos_existentes(const vector<Contato>& agenda){
    // lista todos os contatos da agenda
    if(agenda.empty()){
        // verifica se a agenda está vazia
        cout << "Agenda vazia." << endl;
        return;
    }

    for (int i = 0; i < agenda.size(); i++)
    {
        // ciclo de repetição de 0 até o tamanho total da agenda
        const Contato& contato = agenda.at(i);

        mostrar_contato(i,contato);
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
                cout << "Encerrando...";
                break;
            default:
                cout << "Opção inválida" << endl;
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
