#include <iostream>
#include <Windows.h>

using namespace std;

int main(){
    SetConsoleOutputCP(65001); // funcionalidade da biblioteca Windows.h que permite que o console trate os dados com utf-8 que é o formato dos caracteres do arquivo .csv

    return 0;
}