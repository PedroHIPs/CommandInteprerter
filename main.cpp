#include <iostream>
#include <string>
#include <filesystem>
#include <unistd.h>

#include "commands.h"
#include "utils.h"

using namespace std;
using std::cout; using std::cin;
using std::endl; using std::string;
using std::filesystem::current_path;

int main()
{
    string command;
    Command type;
    cout << "!!!!!! Welcome to the DeltaOS v0.0.1 !!!!!!" << endl;
    cout << "Executing in " << current_path() << endl;
    do{
    cout << ">C$: ";
    getline(cin, command);
    type = TranslateCommand(command);
    DoCommand(type);
    }while(type != EXIT);
    return 0;
}
