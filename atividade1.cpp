#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

//Algoritmos de ordenacao
class AlgShort{
public:
    //tempo: O.n^2 em todos os casos
    static void selectionSort(vector<int>& arr){
        int n = arr.size();
        for (int i = 0; i < n - 1; i++){
            int min_idx = i;
            for (int j = i + 1; j < n; j++)
                if (arr[j] < arr[min_idx])
                    min_idx = j;
            swap(arr[min_idx], arr[i]);
        }
    }

    //tempo: O.n no melhor e O.n^2 no medio e ruim
    static void insertionSort(vector<int>& arr){
        int n = arr.size();
        for (int i = 1; i < n; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key){
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
    }
};

//printa o vetor
void printArray(const vector<int>& arr){
    for (int num : arr)
        cout << num << " ";
    cout << endl;
}

//menu de exibicao
void menu(){
    cout << "\n\n---------------------- Menu ----------------------\n\n";
    cout << "\t 1 - Selection Sort\n";
    cout << "\t 2 - Insertion Sort\n";
    cout << "\t 3 - Sair\n\n";
    cout << "Opcao: ";
}

//D:\EstruturaDeDados>ativiade1.exe instancias-numericas/instancias-num/num.100000.4.in

int main(int argc, char* argv[]) {

    //verificar se o nome esta correto
    if (argc < 2) {
        cerr << "Use: " << argv[0] << " nome_do_arquivo\n";
        return 1;
    }

    //abrir arq 
    ifstream file(argv[1]);
    if (!file.is_open()){
        cerr << "Erro ao abrir o arquivo: " << argv[1] << endl;
        return 1;
    }

    //ler o arq
    vector<int> original;
    string line;
    
    while (getline(file, line)){
        istringstream iss(line);
        int number;
        
        //colocar os numeros no vector
        while (iss >> number){
            original.push_back(number);
        }
    }

    //fechar arq
    file.close();
    
    //loop para escolha de qual alg 
    while(1){
        int op;

        menu();
        cin >> op;

        if (op == 3){
            cout << "Fechando o programa\n";
            break;
        }
        
        //copiar para outro vetor
        vector<int> copia = original;

        switch (op){
            
            case 1:{ //ordenar usando selection sort

                //calcular o tempo de execucao
                auto start = chrono::steady_clock::now();
                AlgShort::selectionSort(copia);
                auto stop = chrono::steady_clock::now();
                auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
                cout << "\nSelection Sort:\n";
                printArray(copia);
                cout << "\nTempo de execucao: " << duration.count() << " milliseconds\n";
                break;
            }

            case 2:{ //ordenar usando insertion sort
            
                //calcular o tempo de execucao
                auto start = chrono::steady_clock::now();
                AlgShort::insertionSort(copia);
                auto stop = chrono::steady_clock::now();
                auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
                cout << "\nInsertion Sort:\n";
                printArray(copia);
                cout << "\nTempo de execucao: " << duration.count() << " milliseconds\n";
                break;
            }

            default:{
                cout << "\nOpcao invalida\n";
                break;
            }

        }
        
    }
    return 0;
}