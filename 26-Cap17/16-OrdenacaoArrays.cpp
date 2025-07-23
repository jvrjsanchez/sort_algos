/*

Ordenação de Arrays

O algoritmo de ordenação utilizado no programa é conhecido como Bubble Sort.

O Bubble Sort funciona comparando repetidamente pares adjacentes de elementos no array e trocando-os se estiverem na ordem errada. 

Este processo é repetido até que o array esteja completamente ordenado. No código abaixo, a lógica de comparação e troca 
é implementada dentro de dois laços for aninhados, onde a comparação de a[i] com a[j] e a subsequente troca de valores ocorrem.

*/ 

#include <iostream>
using namespace std;

int main()
{
    // Declara array de 5 posições
    int a[5];

    // Variável auxiliar para ordenação
    int temp = 0;
    
    cout << "Digite 5 Números" << endl;
    
    // Carrega os 5 números no array
    for(int i = 0; i < 5; i++)
    {
        cin >> a[i];
    }

    cout << "Ordenando..." << endl;

    // Ordenação do array em ordem ascendente
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if(a[i] < a[j])
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
    
    cout << "Array em Ordem Ascendente" << endl;
    
    for(int i = 0; i < 5; i++)
    {
        cout << endl;
        cout << a[i] << endl;
    }
    
    // Ordenação do array em ordem descendente
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if(a[i] > a[j])
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
    
    cout << "Array em Ordem Descendente" << endl;
    
    for(int i = 0; i < 5; i++)
    {
        cout << endl;
        cout << a[i] << endl;
    }

}