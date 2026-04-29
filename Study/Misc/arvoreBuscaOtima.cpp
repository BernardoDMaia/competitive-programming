#include<bits/stdc++.h>
using namespace std;

int main(){
    int n; cin >> n; //pega o número de chaves
    int fzero; cin >> fzero; //pega o f'0

    vector<tuple<int,int,int>> data(n); //vetor que armazena as entradas
    vector<vector<int>> dp(n+2, vector<int>(n+1,0)); //vetor que armazena a dp de duas dimensões
    vector<vector<int>> path(n+2, vector<int>(n+1,0)); //vetor que armazena o caminho
    vector<int>prefixsum(n+1,0); //vetor que armazena a soma dos valores naquele intervalo

    for(int i = 1; i <= n; i++){
        int key, f, fline; cin >> key >> f >> fline; 
        data[i] = {key,f,fline};
        path[i][i] = i; 
        dp[i][i] = f; //valor base de um intervalo de tamanho 1 é a própria frequência
        dp[i][i-1] = fline; //valor base de uma árvore vazia
        prefixsum[i] = prefixsum[i-1]+f+fline; //calcula a soma até o intervalo
    }

    for(int tam = 2; tam <= n; tam++){ //tamanho do intervalo

        for(int left = 1; left <= n-tam; left++){ //primeiro do intervalo
            int right = tam-left-1; //último do intervalo

            for(int k = left; k <= right; k++){ //percorre todas as chaves no intervalo
                int begin = (k == left? 0 : dp[left][k-left]); //arvore à esquerda, se for o primeiro não há árvore:0
                int end = (k == right? 0 : dp[k][right]); //árvore à direita, se for o último não há árvore:0
                int sum = prefixsum[right] - prefixsum[left-1]; //soma no intervalo
                int aux = begin + end + sum; //valor com a raiz como k

                if(aux < dp[left][right]){ //quer o minimo
                    dp[left][right] = aux; //armazena o mínimo
                    path[left][right] = k; //salva o índice da raiz daquele intervalo
                }
            }
        }
    }

    vector<int>path;
    auto rebuild_path = [&](auto &&self, int i, int j) -> void {
        if(i>j) return;

        int index = path[i][j]; //pega o indice da chave
        auto [key,f,fline] = data[i]; //pega os dados naquele indice -> pegando a chave
        
        path.push_back(key); // adicionando a chave ao caminho

        self(self, i, index-1); //chama pra árvore de esquerda
        self(self, index+1, j); //chama pra árvore da direita

    };

    rebuild_path(rebuild_path, 1, n);

    return 0;
}