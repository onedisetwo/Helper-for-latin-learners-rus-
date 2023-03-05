#ifndef LATINO_H_INCLUDED
#define LATINO_H_INCLUDED

#include <vector>
using namespace std;

const string SettingsPath = "files/settings.txt";

#define cls system("cls")

#define safeopen(file, path, modus) \
        fstream file; \
        file.open(path,modus); \
        if(!file.is_open()){ \
        cout << "Не удалось открыть файл " << path;\
        exit(9909);}

#define safeopen2(file, path, modus) \
        file.open(path,modus); \
        if(!file.is_open()){ \
        cout << "Не удалось открыть файл " << path;\
        exit(9909);}

#define fastopencheck(file,path) \
        safeopen(file,path,ios::in) \
        file.close(); \

#define getpath(file_path,keyword)\
    safeopen(settings, SettingsPath, ios::in);\
    string stemp;\
    do{\
        getline(settings,stemp);\
    } while(stemp.find(keyword) == string::npos);\
    file_path = stemp.substr(stemp.find(':') + 1, stemp.size() - stemp.find(':') - 1);\
    settings.close();

class WordRequest{
public:
    string word = "empty";
    string definition = "empty";
    vector<string> form = {"empty"};
    int code = -1;
    void copyC(WordRequest b){
        word = b.word;
        definition = b.definition;
        form = b.form;
        code = b.code;
    }
    void clearC(){
        word = "empty";
        definition = "empty";
        form = {"empty"};
        code = -1;
    }
    void printC(){
        cout << word << endl;
        if(definition != "empty")
            cout << definition << endl;
        if(form[0] != "empty")
            for(int i=0; i<form.size();i++)
                cout<<i+1<<": "<<form[i]<<endl;
    }
};

#endif // LATINO_H_INCLUDED
