#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include "libs/latino.h"

using namespace std;

/// Подсчёт количества строк в файле
int strfile(fstream &file){
    int counter = 0;
    string stemp;
    while(!file.eof()){
        getline(file,stemp);
        if(stemp != "")
            counter++;
    }
    return counter;
}

vector<string> definitions;
bool ifdef = 0;

bool word_search(string word, int num){
    safeopen(dictionary, "files/dictionary.txt", ios::in)

    while(!dictionary.eof()){
        string definition;
        getline(dictionary, definition);
        if(definition.find(word) != string::npos){
            if(num > 3 || word.size() < 3){
                return 0;
            }
            if(ifdef == 0 && num > 0)
                cout << "Может, вы имели в виду " << word << "?\n\n";
            if(ifdef == 0 && num == 0)
                cout << "Результаты по запросу " << word << ":\n\n";
            definitions.push_back(definition);
            ifdef = 1;
        }
    }
    if(ifdef == 0){
        if(num == 0)
            cout << "Результаты по запросу " << word << " не найдены\n";
        word.pop_back();
        word_search(word, num + 1);
    } else{
        for(int i = 0; i < definitions.size(); i++)
            cout << i + 1 << ": " << definitions[i] << endl;
    }
    dictionary.close();
    return ifdef;
}

WordRequest dictionary_search(){
    fastopencheck(file1,"files/dictionary.txt");
    fastopencheck(file2,"files/output.txt");

    WordRequest ans;
    definitions.clear();

    system("cls");
    cout << "Введите слово для перевода: ";
    cin >> ans.word;

    system("cls");
    cout << "Поиск по запросу: " << ans.word << "..." << endl << endl;

    bool ifdef = word_search(ans.word, 0);

    if(ifdef != 0){
        cout << endl << "Выберите наиболее подходящее определение, если не хотите его сохранять - 0" << endl;
        int temp; cin >> temp;
        if(temp != 0){
            ans.definition = definitions[temp-1];

            safeopen(output_file, "files/output.txt", ios::in);
            int num = strfile(output_file);
            output_file.close();

            safeopen2(output_file, "files/output.txt", ios::app | ios::ate);
            cout << definitions[temp-1];
            output_file << num + 1 << ": " << definitions[temp-1] << endl;
            output_file.close();
        }
    }

    cout << endl << "Для выхода в меню нажмите Esc" << endl << "Для нового запроса по словарю 1" << endl;
    if(ifdef != 0)
        cout << "Для анализа данного слова - 2" << endl;
    char c = getch();
    if(c == 27) // Код клавиши для Esc
        ans.code = 999;
    else
        ans.code = 1000 + (int)(c)-48;
//    cout<<ans.code;
    return ans;
}
