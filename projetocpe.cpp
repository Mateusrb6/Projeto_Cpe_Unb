#include <iostream> // biblioteca padrão de entrada e saída
#include <vector>   // biblioteca para usar vetores
#include <regex>    // biblioteca para usar expressões com o objetivo de validar nome, email e telefone
#include <fstream>  // biblioteca para manipular arquivos
#include <sstream>  // biblioteca para manipular strings
#include <string>   // biblioteca para manipular strings


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

    Contato() = default; // compilador cria um construtor padrao automaticamente
    // torna possivel criar objetos 'Contato' sem dar valores iniciais

    Contato(const string &nome, const string &telefone, const string &email) // construtor parametrizado
        // define que o construtor aceita tres parametros sendo todos eles tipo string
        : nome(nome), telefone(telefone), email(email)
    {
    } // inicializa os membros da estrutura com os valores passados como argumentos.
};

vector<Contato> agenda;
/*
cria um vetor vazio que pode armazenar múltiplos objetos Contato.
é um vetor dinamico com capacidade de aumentar ou diminuir de tamanho conforme a necessidade

*resumo: ele gerencia a memoria automaticamente*

*/

void salvar_dados(const vector<Contato> &agenda, const string &agendaContatos)
{
    ofstream arquivo(agendaContatos); // abre o arquivo para escrita (ofstream - output file stream (o output vai para o arquivo e não para o usuario))

    if (!arquivo.is_open())
    {                                     // verifica se o arquivo foi aberto
        cerr << "Erro ao abrir arquivo."; // cerr mostra mensagem de erro
        return;
    }

    // escrever cabeçalho do arquivo csv (nome das colunas)
    arquivo << "Nome,Telefone,Email" << endl;

    for (const auto &contato : agenda)
    {
        arquivo << contato.nome << "," << contato.telefone << "," << contato.email << endl;
        // imprime as linhas de informação do contato no arquivoseparando os dados por virgulas
    }

    arquivo.close(); // fecha o arquivo

    cout << "Arquivos salvos com sucesso." << endl;
}

bool validar_nome(const string &nome)
{
    regex padrao_nome(R"(^[A-Z][a-z]*$)");

    // define que podem ser usadas como primeiro cararacter(^) letras maisculas (A-Z), e apenas minusculas (a-z) no restante 

    return regex_match(nome, padrao_nome); // retorna funcao que compara o nome como o padrao do regex
}

bool validar_telefone(const string &telefone)
{
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
    return regex_match(telefone, padrao_telefone); // retorna funcao que compara o telefone como o padrao do regex
}

bool validar_email(const string &email)
{
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
    return regex_match(email, padrao_email); // retorna funcao que compara o email como o padrao do regex
}

void imprimir_menu()
{
    // imprime opções para o usuário escolher o que quer fazer
    cout <<"\n--------- Agenda de contatos --------- \n\n"
         << "Funcoes: \n"
         << "(1) Consultar contatos adicionados \n"
         << "(2) Adicionar contato \n"
         << "(3) Apagar contato \n"
         << "(4) Editar contatos \n"
         << "(5) Mostrar contatos\n"
         << "(6) Encerrar \n\n"
         << "Selecione uma das opcoes acima. \n\n";
}

int selecionar_opcao()
{
    // pega a opção selecionada pelo usuario
    string opcao;
    getline(cin, opcao);

    for (char c : opcao)
    {                    // for que percorre cada item (char c) da opcao 
        if (!isdigit(c)) // analisa se a string é um digito
        {
            return -1; // se não é um digito retorna -1
        }
    }

    if (opcao.empty()){
        return -1; // se a string estiver vazia retorna -1
    }

    return stoi(opcao); // se é digito retorna a opcao transformada de string para inteiro (int)
}

//Para retornar ao menu principal 
bool retornar_menu_principal(){
    string retornar_menu;
    cout << "\nDeseja voltar ao menu principal ? (s/n):";
    getline(cin,retornar_menu);
    if(retornar_menu == "n"){
        return false;
    }
    return true;
}

string primeira_letra_maiuscula(const string& str){
    if(str.empty()){
        return str; // se a string estiver vazia retorna ela mesma (sem modificações)
    }
    string result = str; // cria uma string result que recebe a string str (cria uma cópia)
    result[0] = toupper(result[0]); // transforma a primeira letra da string em maiuscula
    return result; // retorna a string com a primeira letra em maiuscula
}

// Imprime os dados do contato
void mostrar_contato(int i, const Contato &contato)
{
    cout << "\tContato numero " << i << " :" << '\n'
         << "Nome: " << primeira_letra_maiuscula(contato.nome) << '\n'
         << "Email: " << contato.email << '\n'
         << "Telefone: " << contato.telefone << '\n';
}

// declarando a função split para usar em mostrar_contato_csv
vector<string> split(const string &s, char delimiter)
{ // delimiter é a virgula entre os campos

    vector<string> tokens;        // vetor de strings que armazenará os campos separados
    string token;                 // o token é a string que será separada
    istringstream tokenStream(s); // istringstream é uma stream de strings que será usada para separar a string s

    while (getline(tokenStream, token, delimiter))
    {                            // enquanto houver tokens a serem separados
        tokens.push_back(token); // adiciona o token ao vetor de strings
    }

    return tokens; // retorna o vetor de strings
}

void mostrar_contato_csv(const string &agendaContatos)
{
    ifstream arquivo(agendaContatos); // abre o arquivo para leitura (ifstream - input file stream (o input vem dos dados do arquivo e não do usuario))

    if (!arquivo.is_open())
    { // verifica se o arquivo foi aberto com sucesso
        cerr << "Erro ao abrir arquivo" << endl; // se o arquivo não foi aberto, exibe mensagem de erro
        return;
    }

    string linha; // string que armazena as linhas do arquivo
    getline(arquivo, linha); // pula a primeira linha do arquivo (cabeçalho)

    int i = 0;
    while (getline(arquivo, linha)) // enquanto houver linhas no arquivo faz a leitura
    {
        vector<string> campos = split(linha, ','); // separa os campos da linha com a virgula
        if (campos.size() != 3) // se a linha não tiver 3 campos (nome, telefone e email) exibe mensagem de erro
        {
            cerr << "Linha invalida no arquivo" << endl;
            continue; // pula para a proxima linha
        }

        string nome = campos[0]; // pega o nome do contato
        string telefone = campos[1]; // pega o telefone do contato
        string email = campos[2]; // pega o email do contato

        Contato contato(nome, telefone, email); // cria um objeto Contato com os campos separados
        mostrar_contato(++i, contato); // chama a função mostrar_contato passando o indice e o contato como argumentos
    }
    
    if (agenda.empty()){ // verifica se a agenda está vazia
        cout << "Agenda vazia." << endl;
        return; // se a agenda estiver vazia, a função é encerrada
    }

    arquivo.close(); // fecha o arquivo
}

// Retorna o indice do contato buscado, no vetor agenda ou menos -1 caso não achado
int busca_contato(const string &parametro_buscado, const vector<Contato> &agenda)
{   
    // Percorre a agenda
    for (int i = 0; i < agenda.size(); ++i)
    {
        const Contato &contato = agenda[i];
        // Testa e se contiver um contato com esse nome, imprime ele no modelo da função "mostrar_contatos_existentes".
        if (contato.nome == parametro_buscado || contato.telefone == parametro_buscado || contato.email == parametro_buscado)
        {
            return i; // retorna o indice do contato
        }
    }
    return -1; // parametro nao encontrado
}

bool contato_duplicado(const Contato &novo_contato, const vector<Contato> &agenda)
{ // recebe o novo contato da funcao adicionar contato e os contatos da agenda
    for (const auto &contato : agenda)
    { // for que percorre os contatos da agenda
        if (contato.nome == novo_contato.nome || contato.telefone == novo_contato.telefone || contato.email == novo_contato.email)
        {                // compara informacoes do contato com as do novo contaoto
            return true; // contato ja existe
        }
    }
    return false; // contato nao existe
}

void consultar_contato(const vector<Contato> &agenda)
{
    // consulta um contato na agenda
    if (agenda.empty())
    {
        // verifica se a agenda está vazia
        cout << "Agenda vazia." << endl;
        return; // se a agenda estiver vazia, a função é encerrada
    }

    // usar qualquer uma das informações dentre nome, telefone ou email para achar um contato
    cout << "\nEscolha uma das opções de consulta: \n(1) Nome\n(2) Telefone\n(3) Email." << endl;
    int opcao_consulta = selecionar_opcao();

    string parametro_consulta;
    int busca = -1; // funcao busca_contato retorna -1 quando o contato não é encontrado

    switch (opcao_consulta)
    {
    // consulta de acordo com a informação dada pelo usuario
    case 1:
        cout << "Digite o nome do contato (formato Nome): " << endl;
        getline(cin, parametro_consulta); // pega o nome do contato

        while (!validar_nome(parametro_consulta)) // valida o nome
        {
            cout << "Nome inválido. Tente novamente." << endl;
            getline(cin, parametro_consulta); // pega o nome do contato novamente
        }

        busca = busca_contato(parametro_consulta, agenda); // busca o contato na agenda
        break;
    case 2:
        cout << "Digite o telefone do contato(formato 9XXXX-XXXX): " << endl;

        getline(cin, parametro_consulta); // pega o telefone do contato

        while (!validar_telefone(parametro_consulta)) // valida o telefone
        {
            cout << "Telefone inválido. Tente novamente." << endl;
            getline(cin, parametro_consulta); // pega o telefone do contato novamente
        }
      
        busca = busca_contato(parametro_consulta, agenda); // busca o contato na agenda
        break;
    case 3:
        cout << "Digite o email do contato: " << endl;
        getline(cin, parametro_consulta); // pega o email do contato

        while (!validar_email(parametro_consulta)) // valida o email
        {
            cout << "Email inválido. Tente novamente." << endl;
            getline(cin, parametro_consulta); // pega o email do contato novamente
        }

        busca = busca_contato(parametro_consulta, agenda); // busca o contato na agenda
        break;
    default:
        cout << "Opção inválida. Tente novamente." << endl;
        return; // se a opção não for válida, a função é encerrada
    }

    if (busca != -1)
    { // se o contato tiver sido encontrado
        mostrar_contato(busca, agenda[busca]); // chama a função mostrar_contato passando o indice e o contato como argumentos
    }
    else
    {
        cout << "Contato não encontrado." << endl;
    }

    if(!retornar_menu_principal()){
        consultar_contato(agenda); 
    }
}

void adicionar_contato()
{ // adiciona contato pedindo ao usuario o nome, telefone e email

    Contato novo_contato;

    cout << "\nDigite o nome do contato (formato Nome): " << endl;
    getline(cin, novo_contato.nome); // pega o nome do contato

    while (!validar_nome(novo_contato.nome)) // valida o nome
    {
        cout << "Nome invalido." << endl;
        getline(cin, novo_contato.nome); // pega o nome do contato novamente
    }

    cout << "Digite o telefone do contato (formato 9XXXX-XXXX): " << endl;
    getline(cin, novo_contato.telefone); // pega o telefone do contato

    while (!validar_telefone(novo_contato.telefone)) // valida o telefone
    {
        cout << "Número de telefone inválido." << endl;
        getline(cin, novo_contato.telefone); // pega o telefone do contato novamente
    }

    cout << "Digite o email do contato: " << endl;
    getline(cin, novo_contato.email); // pega o email do contato

    while (!validar_email(novo_contato.email)) // valida o email
    {
        cout << "Email inválido." << endl;
        getline(cin, novo_contato.email); // pega o email do contato novamente
    }

    if (contato_duplicado(novo_contato, agenda)) // verifica se o contato já existe na agenda
    {
        cout << "Contato já existente na agenda." << endl;
    }
    else
    {
        agenda.push_back(novo_contato); // adiciona o novo_contato no final do vetor agenda
        
        cout << "Contato adicionado.\n" << endl;
        salvar_dados(agenda, "agendaContatos.csv"); // salva os dados da agenda no arquivo
    }
           
    if(!retornar_menu_principal()){
        adicionar_contato();
    }
}

void apagar_contato(vector<Contato> &agenda)
{
    if (agenda.empty())
    { // verifica se a agenda está vazia
        cout << "Agenda vazia." << endl;
        return; // se a agenda estiver vazia, a função é encerrada
    }

    cout << "\nEscolha uma das opções para apagar o contato: \n(1) Nome\n(2) Telefone\n(3) Email.\n" << endl;
    int opcao_apagar = selecionar_opcao();

    string parametro_apagar;
    int busca = -1; // funcao busca_contato retorna -1 quando o contato não é encontrado

    switch (opcao_apagar)
    { // apaga o contato de acordo com a informação dada pelo usuario
    case 1:
        cout << "Digite o nome do contato (formato Nome): " << endl;
        getline(cin, parametro_apagar); // pega o nome do contato

        while (!validar_nome(parametro_apagar)) // valida o nome
        {
            cout << "Nome inválido. Tente novamente." << endl;
            getline(cin, parametro_apagar); // pega o nome do contato novamente
        }

        busca = busca_contato(parametro_apagar, agenda); // busca o contato na agenda
        break;
    case 2:
        cout << "Digite o telefone do contato (formato 9XXXX-XXXX): " << endl;
        getline(cin, parametro_apagar); // pega o telefone do contato

        while (!validar_telefone(parametro_apagar)) // valida o telefone
        {
            cout << "Telefone inválido. Tente novamente." << endl;
            getline(cin, parametro_apagar); // pega o telefone do contato novamente
        }

        busca = busca_contato(parametro_apagar, agenda); // busca o contato na agenda
        break;
    case 3:
        cout << "Digite o email do contato: " << endl;
        getline(cin, parametro_apagar); // pega o email do contato

        while (!validar_email(parametro_apagar)) // valida o email
        {
            cout << "Email inválido. Tente novamente." << endl;
            getline(cin, parametro_apagar); // pega o email do contato novamente
        }

        busca = busca_contato(parametro_apagar, agenda); // busca o contato na agenda
        break;
    default:
        cout << "Opção inválida. Tente novamente." << endl;
        return; // se a opção não for válida, a função é encerrada
    }

    if (busca != -1)
    { // se o contato tiver sido encontrado
        agenda.erase(agenda.begin() + busca); // apaga o contato da agenda com agenda.begin() para indicar o inicio do vetor e busca para indicar a posição do contato
        cout << "Contato apagado com sucesso." << endl;
        salvar_dados(agenda, "agendaContatos.csv"); // salva os dados da agenda no arquivo
    }
    else
    { // se o contato não foi encontrado
        cout << "Contato não encontrado." << endl;
    }

    if(!retornar_menu_principal()){
        apagar_contato(agenda);
    }
}

void editar_contato(vector<Contato> &agenda)
{ // edita o contato pedindo ao usuario o nome, telefone e email
    if (agenda.empty())
    { // verifica se a agenda está vazia
        cout << "Agenda vazia." << endl;
        return; // se a agenda estiver vazia, a função é encerrada
    }

    cout << "\nEscolha uma das opções para editar o contato: \n1) Nome\n2) Telefone\n3) Email." << endl;
    int opcao_editar = selecionar_opcao();

    string parametro_editar; // nome, telefone ou email do contato existente que deseja editar
    int busca = -1;          // funcao busca_contato retorna -1 quando o contato não é encontrado

    switch (opcao_editar)
    {
    case 1: // edita o contato de acordo com o nome
        cout << "Digite o nome do contato (formato Nome): " << endl;
        getline(cin, parametro_editar); // pega o nome do contato

        while (!validar_nome(parametro_editar))
        {
            cout << "Nome inválido. Tente novamente." << endl;
            getline(cin, parametro_editar); // pega o nome do contato novamente
        }

        busca = busca_contato(parametro_editar, agenda); // busca o contato na agenda

        if (busca != -1)
        {
            Contato &contato = agenda[busca];

            cout << "Digite o novo nome do contato (formato Nome): \n";
            getline(cin, parametro_editar); // pega o novo nome do contato

            if (!parametro_editar.empty())
            {
                while (!validar_nome(parametro_editar))
                {
                    cout << "Nome inválido. Tente novamente." << endl;
                    getline(cin, parametro_editar); // pega o novo nome do contato novamente
                }
                contato.nome = parametro_editar; // atribui o novo nome ao contato
                cout << "Nome do contato editado com sucesso." << endl;
            }
        }
        break;
    case 2: // edita o contato de acordo com o telefone
        cout << "Digite o telefone do contato (formato 9XXXX-XXXX): " << endl;
        getline(cin, parametro_editar); // pega o telefone do contato

        while (!validar_telefone(parametro_editar)) // valida o telefone
        {
            cout << "Telefone inválido. Tente novamente." << endl;
            getline(cin, parametro_editar); // pega o telefone do contato novamente
        }

        busca = busca_contato(parametro_editar, agenda); // busca o contato na agenda

        if (busca != -1)
        {
            Contato &contato = agenda[busca];

            cout << "Digite o novo telefone do contato: \n";
            getline(cin, parametro_editar); // pega o novo telefone do contato

            if (!parametro_editar.empty()) 
            {
                while (!validar_telefone(parametro_editar)) // valida o telefone
                {
                    cout << "Telefone inválido. Tente novamente." << endl;
                    getline(cin, parametro_editar); // pega o novo telefone do contato novamente
                }
                contato.telefone = parametro_editar; // atribui o novo telefone ao contato
                cout << "Telefone do contato editado com sucesso." << endl;
            }
        }
        break;
    case 3: // edita o contato de acordo com o email
        cout << "Digite o email do contato: " << endl;
        getline(cin, parametro_editar);

        while (!validar_email(parametro_editar))
        {
            cout << "Email inválido. Tente novamente." << endl;
            getline(cin, parametro_editar);
        }

        busca = busca_contato(parametro_editar, agenda); // busca o contato na agenda

        if (busca != -1)
        {
            Contato &contato = agenda[busca]; // pega o contato na posição busca

            cout << "Digite o novo email do contato: \n";
            getline(cin, parametro_editar); // pega o novo email do contato

            if (!parametro_editar.empty())
            {
                while (!validar_email(parametro_editar)) // valida o email
                {
                    cout << "Email inválido. Tente novamente." << endl;
                    getline(cin, parametro_editar); // pega o novo email do contato novamente
                }
                contato.email = parametro_editar; // atribui o novo email ao contato
                cout << "Email do contato editado com sucesso." << endl;
            }
        }
        break;

    default:
        cout << "Opção inválida. Tente novamente." << endl;
        return; // se a opção não for válida, a função é encerrada
    }

    if (busca != -1)
    {
        salvar_dados(agenda, "agendaContatos.csv"); // salva os dados da agenda no arquivo caso o contato tenha sido editado
    }
    else
    {
        cout << "Contato não encontrado." << endl;
    }
    if(!retornar_menu_principal()){
        editar_contato(agenda);
    }

}

void menu_opcoes(int opcao)
{ // função que chama as funções de acordo com a opção escolhida pelo usuario

    switch (opcao)
    {
    case 1:
        consultar_contato(agenda); // chama a função consultar_contato passando a agenda como argumento
        break;
    case 2:
        adicionar_contato(); // chama a função adicionar_contato
        break;
    case 3:
        apagar_contato(agenda); // chama a função apagar_contato passando a agenda como argumento
        break;
    case 4:
        editar_contato(agenda); // chama a função editar_contato passando a agenda como argumento
        break;
    case 5:
        mostrar_contato_csv("agendaContatos.csv"); // chama a função mostrar_contato_csv passando o nome do arquivo como argumento
        break;
    case 6:
        cout << "Encerrando..."; // encerra o programa
        break;
    default:
        cout << "Opção inválida" << endl; // se a opção não for válida, exibe mensagem de erro
        break;
    }
}

void carregar_dados(const string &agendaContatos)
{ // funcao para carregar informacoes do arquivo no inicio do programa

    ifstream arquivo(agendaContatos); // abre o arquivo para leitura (ifstream - input file stream (o input vem dos dados do arquivo e não do usuario))

    if (!arquivo.is_open())
    { // verifica se o arquivo foi aberto com sucesso
        cerr << "Erro ao abrir arquivo" << endl;
        return; // se o arquivo não foi aberto, a função é encerrada
    }

    string linha;            // string que armazenará as linhas do arquivo
    getline(arquivo, linha); // pula a primeira linha do arquivo (cabeçalho)

    while (getline(arquivo, linha))
    { // enquanto houver linhas no arquivo

        vector<string> campos = split(linha, ','); // separa os campos da linha com a virgula
        if (campos.size() == 3)                    // se a linha tiver 3 campos (nome, telefone e email)
        {
            Contato contato(campos[0], campos[1], campos[2]); // cria um objeto Contato com os campos separados
            agenda.push_back(contato);                        // adiciona o contato no final do vetor agenda
        }
    }
    arquivo.close(); // fecha o arquivo
}

int main()
{
    carregar_dados("agendaContatos.csv"); // carrega os dados do arquivo no inicio do programa

    while (true)
    { // loop que exibe o menu de opções para o usuario escolher o que fazer até que ele escolha a opção 6
        imprimir_menu();

        int opcao = selecionar_opcao(); // pega a opção selecionada pelo usuario
        if (opcao == 6)
        {
            break;
        }

        menu_opcoes(opcao); // chama a função menu_opcoes passando a opção escolhida pelo usuario como argumento
    }

    return 0;
}
