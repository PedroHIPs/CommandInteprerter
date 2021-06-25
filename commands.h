#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED
#include <string>

typedef enum{
    HELP,EXIT,VERSION,UNKNOWM,CLEAR,_DATE,TIME,LIST,CREATE,INSERT,_DELETE
} Command;

Command TranslateCommand(std::string c);
void DoCommand(Command Dothis);
void showHelp();
void showVersion();
void showExit();
void showDate();
void showTime();
void listDirs();
void createDir();
void insertInArq();
void deleteArqOrDir();

#endif // COMMANDS_H_INCLUDED
