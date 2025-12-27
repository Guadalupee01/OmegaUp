#include <iostream>
#include <string>

using namespace std;

int recursivida(string& numeros, int & i) {
    int suma = 0;
    int contador = 0;
    
    while(i < numeros.length()) {
        i++; 
        if (numeros[i] == '(') {
            suma += recursivida(numeros, i);
            contador++;
        } else if (numeros[i]  == ')') {
            if(contador == 0) return 0;
            return suma/contador;
        } else {
            suma += (numeros[i]  - '0');
            contador++;
        }
    }

}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string numeros;
    cin >> numeros;
    int i = 0;
    cout << recursivida(numeros, i);
    return 0;
}