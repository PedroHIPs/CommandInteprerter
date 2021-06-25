#include <iostream>
#include <string>
#include <filesystem>
#include <unistd.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <dirent.h>

#include "commands.h"
#include "utils.h"

using namespace std;
using std::cout; using std::cin;
using std::endl; using std::string;
using std::filesystem::current_path;

std::string arg1;
std::string arg2;
std::string text;

Command TranslateCommand(string c){
    std::string type = to_upper(getCommand(c));
    arg1 = getArg1(c);
    arg2 = getArg2(c);
    text = getTextToInsert(c);
    cout << arg1 << endl;
    Command doThis;
    cout << "Comando inserido: " << type << endl;
    if(type.compare("AJUDA") == 0){
        cout << "Voce pediu ajuda" << endl;
        doThis = HELP;
    }else if(type.compare("VER") == 0){
        doThis = VERSION;
    }else if(type.compare("SAIR") == 0){
        doThis = EXIT;
    }else if(type.compare("LIMPAR") == 0){
        doThis = CLEAR;
    }else if(type.compare("DATA") == 0){
        doThis = _DATE;
    }else if(type.compare("HORA") == 0){
        doThis = TIME;
    }else if(type.compare("LISTAR") == 0){
        doThis = LIST;
    }else if(type.compare("CRIAR") == 0){
        doThis = CREATE;
    }else if(type.compare("INSERIR") == 0){
        doThis = INSERT;
    }else if((type.compare("DELETAR") == 0) || (type.compare("APAGAR") == 0)){
        doThis = _DELETE;
    }
    else{
        doThis = UNKNOWM;
    }
    return doThis;
}

void DoCommand(Command thisC){
    switch(thisC){
    case HELP:
        showHelp();
        break;
    case VERSION:
        showVersion();
        break;
    case EXIT:
        cout << "Saindo..." << endl;
        exit(0);
        break;
    case CLEAR:
        system("cls");
        cout << "!!!!!! Welcome to the DeltaOS v0.0.1 !!!!!!" << endl;
        cout << "Executing in " << current_path() << endl;
        break;
    case _DATE:
        showDate();
        break;
    case TIME:
        showTime();
        break;
    case LIST:
        listDirs();
        break;
    case CREATE:
        createDir();
        break;
    case INSERT:
        insertInArq();
        break;
    case _DELETE:
        deleteArqOrDir();
        break;
    default:
        cout << "Esse nao e um comando valido, por favor digite novamente ou digite AJUDA para ver a lista dos comandos validos" << endl;
    }
}

void showHelp(){
    cout << "!!!!!! COMANDOS DISPONIVEIS !!!!!!" << endl;
    cout << "______________ AJUDA _____________" << endl;
    cout << "AJUDA" << endl;
    cout << "O que faz: Mostra uma lista de todos os comandos disponiveis com detalhes sobre sua utilizacao" << endl;
    cout << "__________________________________" << endl;
    cout << "_______________ VER ______________" << endl;
    cout << "VER" << endl;
    cout << "O que faz: Mostra a versao do sistema operacional" << endl;
    cout << "__________________________________" << endl;
    cout << "______________ SAIR ______________" << endl;
    cout << "SAIR" << endl;
    cout << "O que faz: Finaliza a execucao do programa" << endl;
    cout << "__________________________________" << endl;
    cout << "______________ DATA ______________" << endl;
    cout << "DATA" << endl;
    cout << "O que faz: Mostra a data do sistema em formato dd/mm/aaaa" << endl;
    cout << "__________________________________" << endl;
    cout << "______________ HORA ______________" << endl;
    cout << "HORA" << endl;
    cout << "O que faz: Exibe a hora do sistema em formato hh:mm:ss" << endl;
    cout << "__________________________________" << endl;
    cout << "______________ LISTAR _____________" << endl;
    cout << "LISTAR <caminho do arquivo>" << endl;
    cout << "O que faz: Lista todos os arquivos dentro da pasta especificada, caso nao tenha um caminho especificado, lista os arquivos do diretorio atual de execucao" << endl;
    cout << "__________________________________" << endl;
    cout << "_______________ CRIAR _____________" << endl;
    cout << "CRIAR <-a>|<-d> <nome do arquivo ou diretorio>" << endl;
    cout << "O que faz: Cria um diretorio ou pasta de acordo com o primeiro parametro, <-a> para arquivo, <-d> para diretorio, com o nome especificado no segundo parametro (OBS: nome não pode conter espacos)" << endl;
    cout << "__________________________________" << endl;
    cout << "______________ INSERIR ____________" << endl;
    cout << "INSERIR <nome do arquivo ou diretorio> <texto a ser inserido>" << endl;
    cout << "O que faz: Insere um texto no arquivo especificado no parametro 1 (OBS: o caminho do arquivo não pode conter espacos)" << endl;
    cout << "__________________________________" << endl;
    cout << "______________ APAGAR ____________" << endl;
    cout << "APAGAR <-a>|<-d> <nome e/ou caminho do diretorio ou arquivo a ser apagado>" << endl;
    cout << "O que faz: Apaga um diretorio ou pasta de acordo com o primeiro parametro, <-a> para arquivo, <-d> para diretorio, com o nome especificado no segundo parametro (OBS: o caminho do arquivo não pode conter espacos)" << endl;
    cout << "__________________________________" << endl;
    cout << "______________ DELETAR ____________" << endl;
    cout << "DELETAR <-a>|<-d> <nome e/ou caminho do diretorio ou arquivo a ser Deletado>" << endl;
    cout << "O que faz: Deleta um diretorio ou pasta de acordo com o primeiro parametro, <-a> para arquivo, <-d> para diretorio, com o nome especificado no segundo parametro (OBS: o caminho do arquivo não pode conter espacos)" << endl;
    cout << "__________________________________" << endl;
}

void showVersion(){
    DWORD dwVersion = 0;
    DWORD dwMajorVersion = 0;
    DWORD dwMinorVersion = 0;
    DWORD dwBuild = 0;
    dwVersion = GetVersion();
    dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
    dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));
    if (dwVersion < 0x80000000)
        dwBuild = (DWORD)(HIWORD(dwVersion));
    printf("Versao do Windowns: %d.%d (%d)\n",dwMajorVersion,dwMinorVersion,dwBuild);
    cout << "Versao do DeltaOS: 0.0.1" << endl;
}

void showDate(){
    time_t dt = time(0);
    tm *dts = localtime(&dt);
    cout << dts->tm_mday << "/" << 1+dts->tm_mon << "/" << 1900+dts->tm_year << endl;
}

void showTime(){
    time_t dt = time(0);
    tm *dts = localtime(&dt);
    cout << dts->tm_hour << ":" << dts->tm_min << ":" << dts->tm_sec << endl;
}

//lista diretorios do sistema
void listDirs(){
    //Lembrete: necessário arquuivo do programa estar no drive c
    DIR *dir;
    struct dirent *lsdir;
    char path[256];
    if(arg1.compare("") == 0){
        getcwd(path, 256);
    }else{
        strcpy(path, arg1.c_str());
    }
    cout << "listando arquivos em: " << path << endl;
    dir = opendir(path);
    while ( ( lsdir = readdir(dir) ) != NULL )
    {
        printf ("\\%s\n", lsdir->d_name);
    }
    closedir(dir);
}

void createDir(){
    bool bDir;
    char nome[15];
    FILE *arq;
    if(arg1.compare("-d") == 0)
    {
        strcpy(nome, arg2.c_str());
        bDir = CreateDirectory(nome,NULL);
        if(bDir==false)
            cout << "ERRO: Houve um erro ao criar diretorio" << endl;
        else
            cout << "!!!!!!! Diretorio criado !!!!!!" << endl;
    }
    else if (arg1.compare("-a") == 0)
    {
        strcpy(nome, arg2.c_str());
        arq = fopen(nome,"a");
        if (arq == NULL)
        {
            cout << "ERRO: O arquivo nao foi aberto!\n" << endl;
        }
        else
        {
            cout << " !!!!!! O arquivo foi aberto com sucesso! !!!!!!" << endl;
        }
        fclose(arq);
    }
    else
        cout << "ERRO: Parametro invalido" << endl;
}

void insertInArq(){
    FILE *arq;
    char str[256],nome[50];
    strcpy(nome, arg1.c_str());
    arq = fopen(nome,"a");
    if(arq==NULL)
        cout << "Erro ao abrir arquivo" << endl;
    strcpy(str, text.c_str());
    fprintf(arq, "%s", str);
    fclose(arq);
    cout << "!!!!!! " << str << " gravado com sucesso !!!!!!!" << endl;
}

void deleteArqOrDir(){
    char nome[50];
    if(arg1.compare("-a") == 0)
    {
        strcpy(nome, arg2.c_str());
        remove(nome);
        cout << "!!!!!! Arquivo excluido com sucesso !!!!!!" << endl;
    }else if(arg1.compare("-d") == 0){
        strcpy(nome, arg2.c_str());
        RemoveDirectory(nome);
        cout << "!!!!!! Diretorio excluido com sucesso !!!!!!" << endl;
    }else{
        cout << "ERRO: Parametro invalido:" << endl;
    }
}
