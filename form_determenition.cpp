#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>
#include "libs/latino.h"
#include "libs/partsofspeech.h"

using namespace std;

#define check(part,function)\
        rcode = function;\
        if(rcode != 100){\
            part.error(rcode);\
            return rcode;\
        }

WordRequest mainRequest;

/** int define_noun()
Ввод: слово (word), окончание в gen. sing. (словарная форма, gen_end), род
Вывод: Склонение, род, возможные формы в виде падеж - число
**/
int define_noun(){
    int rcode = 100;
    Noun mainNoun;
    cout<<"1";
    check(mainNoun,mainNoun.define_declinatio());
    cout<<"1";
    check(mainNoun,mainNoun.define_form());
    cout<<"1";
    check(mainNoun,mainNoun.user_print());
    cout<<"1";
    check(mainNoun,mainNoun.close_file());
    cout<<"1";
    return rcode;
}

/** int define_adj()
Ввод: слово (word), словарная форма
Вывод: склонение (+тип если 3е), род, число, падеж
**/

int define_adj(){
    int rcode = 100;
    Adj mainAdj;
    check(mainAdj,mainAdj.define_declinition());
    check(mainAdj,mainAdj.define_form());
    check(mainAdj,mainAdj.user_print());
    check(mainAdj,mainAdj.close_file());
    return rcode;
}

void define_verb(){
    Verb mainVerb;
}


/// Основная функция
WordRequest form_determenition(WordRequest givenRequest){

    mainRequest.copyC(givenRequest);
    fastopencheck(file1,"files/info_noun.txt");
    fastopencheck(file2,"files/info_adj.txt");

    cls;
    if(mainRequest.code != -1){
        cout << mainRequest.word << endl << mainRequest.definition << endl;
    }
    cout << "Выберите часть речи:\n     1 - существительное\n"
         << "     2 - прилагательное\n     3 - глагол" << endl;

    int temp,
        return_code;
    temp = getch() - 48;
    switch (temp){
        case 1: define_noun(); break;
        case 2: define_adj(); break;
        case 3: define_verb(); break;
    }

    cout << "\nДля выхода нажмите Esc"
         << "\nДля нового запроса нажмите 2\n";
    char c = getch();
    if(c == 27) // Код клавиши для Esc
        mainRequest.code = 999;
    else
        mainRequest.code = 1000 + (int)(c)-48;
    return mainRequest;
}
