/**
Error code 9909 - file didn't open
**/

#include <iostream>
#include <fstream>
#include <conio.h>
#include "libs\latino.h"

using namespace std;

WordRequest dictionary_search();
/**
Ввод слова и получение возможных переводов
in: dictionary_search.cpp
return WordRequest.code:
    999 - возврат в меню
    100 - продолжить анализ того же слова
    200 - повторить анализ
**/

WordRequest form_determenition(WordRequest mainw);
/**
Определение формы слова
in: form_determenition.cpp
return codes:
    0 if exit
    1 if repeat
**/

void outread(){
    cls;
    safeopen(output_file, "files/output.txt", ios::in);
    while(!output_file.eof()){
        string temp;
        getline(output_file, temp);
        if(temp != "-empty-");
        cout << temp << endl;
    }
    getch();
    output_file.close();
}

WordRequest mainw;

WordRequest menu(int choice){
    WordRequest temp;
    switch(choice){
        case -21:
            cls;
            cout << "Сохранить содержание словаря? 1 - да, 2 - нет" << endl;
            choice = (int)(getch())-48;
            if(choice == 2){
                fstream output_file;
                output_file.open("files/output.txt", ios::out);
                output_file.close();
            }
            cls;
            exit(100);
            break;
        case 1: return dictionary_search(); break;
        case 2: return form_determenition(mainw); break;
        case 3: outread(); break;
    }
    return temp;
}

int main()
{
    setlocale(LC_ALL,"Russian");
    fastopencheck(file1,SettingsPath);

    while(true){
        mainw.clearC();
        cls;
        cout << "Нажмите ...\n" <<
        "   Esc - выход из программы\n     1 - поиск по словарю\n" <<
        "     2 - определение формы слова\n     3 - просмотреть сохранённые слова\n";
        int choice = (int)(getch())-48;
        mainw.copyC(menu(choice));
        while(mainw.code > 1000)
            mainw.copyC(menu(mainw.code - 1000));
    }
    return 0;
}
