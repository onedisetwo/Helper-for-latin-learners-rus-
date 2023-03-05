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
���� ����� � ��������� ��������� ���������
in: dictionary_search.cpp
return WordRequest.code:
    999 - ������� � ����
    100 - ���������� ������ ���� �� �����
    200 - ��������� ������
**/

WordRequest form_determenition(WordRequest mainw);
/**
����������� ����� �����
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
            cout << "��������� ���������� �������? 1 - ��, 2 - ���" << endl;
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
        cout << "������� ...\n" <<
        "   Esc - ����� �� ���������\n     1 - ����� �� �������\n" <<
        "     2 - ����������� ����� �����\n     3 - ����������� ���������� �����\n";
        int choice = (int)(getch())-48;
        mainw.copyC(menu(choice));
        while(mainw.code > 1000)
            mainw.copyC(menu(mainw.code - 1000));
    }
    return 0;
}
