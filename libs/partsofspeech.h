#ifndef NOUN_H_INCLUDED
#define NOUN_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include "latino.h"

using namespace std;

#define success return 100;

#define print_member(text, member, stemp)\
                find_t = stemp.find(member) + 1;\
                cout << text\
                     << stemp.substr(find_t,\
                            stemp.find(';',find_t) - find_t)\
                     << " ; ";

class Noun{
private:
    /// Информация о файле с данными
    const string  Keyword = "INFO_NOUN";
    string        file_path;
    ifstream      file;

    /// Информация о слове
    string  word,         // Слово
            gen_end;
    char    declinatio,  // Склонение
            genus;        // Род

    vector<pair<char,char> > numcas; // Вектор с возможными формами в числовом виде
    vector<string> userinfo;

public:
    /// Функция, определяющая вид ошибки
    void error(int code){
        string message;
        if(code % 10 == 101){
            message = "Окончание введено неверно";
        }
        if(code == 1020){
            message = "Род и склонение несовместимы";
        }
        if(code == 1030){
            message = "Данной формы не найдено";
        }
        cout << "\nОшибка: \n" << message
             << " (" << code << ")\n";
    }

    /// Объявление класса пользователем
    Noun(){
        getpath(file_path, Keyword);
        safeopen2(file, file_path, ios::in);
        cout << "\n                         Введите слово: ";
        cin >> word;
        cout << "\n         Введите окончание в gen. sing: ";
        cin >> gen_end;
        cout << "\n Введите род (m,f,n,- если неизвестен): ";
        cin >> genus;
    }

    /// Подкласс с определением формы слова
    class Form{
    private:
        char  numerus,  // Число
              casus;    // Падеж

    public:
        Form(){} ;
        /// Объявление класса
        Form(char numerusN, char casusN){
            numerus = numerusN;
            casus = casusN;
        }

        void new_numerus(char new_numerus){
            numerus = new_numerus;
        }
        void new_casus(char new_casus){
            casus = new_casus;
        }

        /// Вывод элементов класса
        void print(string info[4]){
            size_t find_t;
            print_member(" Numerus ", numerus, info[2])
            print_member(" Casus ", casus, info[3])
            cout << endl;
        }
    };

    /// Вектор с возможными формами слова
    vector<Form> forms;

    /// Определение склонения
    int define_declinatio(){
        string stemp; // Строка для хранения временных данных
        getline(file, stemp);
        #define ifgen_endhere stemp.find(gen_end) == string::npos
        if(gen_end.size() == 1 && ifgen_endhere){
            cout << "Окончание введено неверно";
            return 1010;
        }
        else if(gen_end.size() == 2){
            if(ifgen_endhere)
                gen_end = gen_end.substr(1,1);
            if(ifgen_endhere)
                return 1011;
        }
        else{
            if(ifgen_endhere)
                gen_end = gen_end.substr(gen_end.size()-2,2);
            if(ifgen_endhere)
                gen_end = gen_end.substr(1,1);
            if(ifgen_endhere)
                return 1012;
        }
        declinatio = stemp[stemp.find(gen_end)-1];
        success
    }

    /// Определение формы слова
    int define_form(){
        string info_endings,
               stemp1, stemp2;
        stemp2 += declinatio;
        stemp2 += genus;
        while(true){
            getline(file, stemp1);
            if(stemp1.find(stemp2) != string::npos){
                getline(file, info_endings);
                break;
            }
            if(stemp1 == "")
                return 1020;
        }

        Form nform;
        // В файле число-падеж обозначены как две цифры:
        // первая - число (0,1), вторая - падеж (см. format в noun_info.txt)
        int beg = -1;
        for(int iter = 0; iter < info_endings.size(); iter++){
            if(info_endings[iter] == ',' | info_endings[iter] == ';' && beg != -1){
                size_t temppos = word.find(info_endings.substr(beg, iter - beg));
                if(temppos != string::npos && (temppos + iter - beg) == word.size())
                    forms.push_back(nform);
            }
            if(info_endings[iter] == ';'){
                nform.new_numerus(info_endings[iter + 1]);
                nform.new_casus(info_endings[iter + 2]);
                beg = iter + 4;
                iter += 4;
            }
        }

        // Исключение для нулевого окончания в третьем склонении
        if(forms.size() == 0){
            if(declinatio == '3'){
                forms.push_back(Form('0','0'));
                if(genus == 'n'){
                    forms.push_back(Form('0','3'));
                    forms.push_back(Form('0','4'));
                }
            } else
                return 1030;
        }
        success
    }

    /// Перевод информации для пользователя
    int user_print(){
        string  stemp,
                info[4]; // Массив с информацией из файла
        do{
            getline(file, stemp);
        } while(stemp != "_format") ;
        for(int i = 0; i < 4; i++){
            getline(file, info[i]);
        }

        size_t find_d = info[0].find(declinatio);
        cout << "\nDeclinatio "
             << info[0].substr(find_d + 1,
                               info[0].find(';',find_d+1) - find_d - 1)
             << endl;

        if(genus != '-'){
            size_t find_d = info[1].find(genus);
            cout << "\nGenus "
                 << info[1].substr(find_d + 1,
                                   info[1].find(';',find_d+1) - find_d - 1)
                 << endl;
        }

        for(int i = 0; i < forms.size(); i++){
            cout << i + 1 << ": ";
            forms[i].print(info);
        }

        success
    }

    int close_file(){
        file.close();
        success
    }
};

class Adj{
private:
    /// Информация о файле с данными
    const string  Keyword = "INFO_ADJ";
    string        file_path;
    ifstream      file;

    /// Информация о слове
    string  word,        // Слово
            dform[3],    // Словарные формы слова
            root;        // Корень слова
    char    declinatio;  // Склонение

    /// Определение основы прилагательного
    void define_root(){
        cout << "\n        Введите основу прилагательного: ";
        cin >> root;
    }

public:
    /// Функция, определяющая вид ошибки
    void error(int code){
        cout << "Ошибка: \n";

        if(code == 1010){
            cout << "Словарная форма введена неверно (1010)";
        }
        if(code == 1020){
            cout << "Данной формы не найдено (1020)";
        }

    }

    /// Объявление класса пользователем
    Adj(){
        getpath(file_path, Keyword);
        safeopen2(file, file_path, ios::in);
        cout << "\n                         Введите слово: ";
        cin >> word;
        cout << "\n           Введите его словарную форму: ";
        cin >> dform[0] >> dform[1] >> dform[2];
    }

    /// Подкласс с определением формы слова
    class Form{
    private:
        char  genus,    // Род
              numerus,  // Число
              casus;    // Падеж

    public:
        Form(){} ;
        /// Объявление класса
        Form(char genusN, char numerusN, char casusN){
            genus = genusN;
            numerus = numerusN;
            casus = casusN;
        }

        void new_genus(char new_genus){
            genus = new_genus;
        }
        void new_numerus(char new_numerus){
            numerus = new_numerus;
        }
        void new_casus(char new_casus){
            casus = new_casus;
        }

        /// Вывод элементов класса
        void print(string info[4]){
            size_t find_t;
            print_member(" Genus ", genus - 32, info[1])
            print_member(" Numerus ", numerus, info[2])
            print_member(" Casus ", casus, info[3])
            cout << endl;
        }
    };

    /// Вектор с возможными формами слова
    vector<Form> forms;

    /// Определение склонения
    int define_declinition(){
        string  stemp,
                ending0,         // Окончание в первой словарной форме
                nom_endings[4];  /* Окончания в casus nominativus
                                    0,1 - masculinum
                                    2 - femininum, 3 - neutrum*/

        ending0 = dform[0].substr(dform[0].size()-2, 2);
        dform[2] += " ";
        declinatio = '1';
        while(true){
            getline(file, stemp);
            declinatio++;
            if(stemp[0]=='.'){
                getline(file, stemp);
                nom_endings[0] = stemp.substr(0, 2);
                nom_endings[1] = stemp.substr(2, 2);
                nom_endings[2] = stemp.substr(4, 2);
                nom_endings[3] = stemp.substr(6, 2);
                if(ending0 == nom_endings[0] ||
                    ending0 == nom_endings[1])
                    if(dform[2].find(nom_endings[3]) != string::npos){
                        break;
                    }
            }
            if(stemp[0] == '_'){
                return 1010;
            }
        }
        dform[2].pop_back();
        success
    }

    /// Определение формы прилагательного
    int define_form(){
        string stemp;
        getline(file, stemp);
        while(stemp != "_declinatio"){
            getline(file,stemp);
        }

        do{
            getline(file, stemp);
            if(stemp[0] == 'd' && stemp[1] == declinatio){
                do{
                    Form nform;

                    getline(file, stemp);
                    if(stemp[0] == 'g'){
                        nform.new_genus(stemp[1]);
                        continue;
                    }
                    /* В файле число-падеж обозначены как две цифры:
                       первая - число (0,1), вторая - падеж
                       (см. format в adj_info.txt) */
                    int beg = -1;
                    for(int iter = 0; iter < stemp.size(); iter++){
                        if(stemp[iter] == ',' | stemp[iter] == ';' && beg != -1){
                            size_t temppos = word.rfind(stemp.substr(beg, iter - beg));
                            if(temppos != string::npos && (temppos + iter - beg) == word.size())
                                forms.push_back(nform);
                        }
                        if(stemp[iter] == ';'){
                            nform.new_numerus(stemp[iter + 1]);
                            nform.new_casus(stemp[iter + 2]);
                            beg = iter + 4;
                            iter += 4;
                        }
                    }
                }while(stemp[0] != 'd' && stemp[0] != '_');
                break;
            }
        }while(stemp[0] != '_') ;

        /// Исключение для нулевого окончания
        if(forms.size() == 0){
            define_root();
            if(word == root && declinatio == '5')
                forms = {Form('b','0','0'),
                         Form('n','0','0'),
                         Form('b','0','3')};
            else{
                return 1020;
            }
        }
        success
    }

    /// Вывод возможных форм пользователю
    int user_print(){
        string  stemp,
                info[4]; // Массив с информацией из файла
        do{
            getline(file, stemp);
        } while(stemp != "_format") ;
        for(int i = 0; i < 4; i++){
            getline(file, info[i]);
        }

        size_t find_d = info[0].find(declinatio);
        cout << "\nDeclinatio "
             << info[0].substr(find_d + 1,
                               info[0].find(';',find_d+1) - find_d - 1)
             << endl;

        for(int i = 0; i < forms.size(); i++){
            cout << i + 1 << ": ";
            forms[i].print(info);
        }
        success
    }

    /// Закрытие файла
    int close_file(){
        file.close();
        success
    }
};

class Verb{
private:
    /// Информация о файле с данными
    const string  Keyword = "INFO_VERB";
    string        file_path;
    ifstream      file;

    /// Информация о слове
    string  word,
            dform[4],
            rverbs[3];
    char    conjugatio;

public:
    /// Функция, определяющая вид ошибки
    void error(int code){
        string message;

        cout << "\nОшибка: \n" << message
             << " (" << code << ")\n";
    }

    /// Объявление класса пользователем
    Verb(){
        getpath(file_path, Keyword);
        safeopen2(file, file_path, ios::in);
        cout << "\n                         Введите слово: ";
        cin >> word;

    }
};

#endif // NOUN_H_INCLUDED
