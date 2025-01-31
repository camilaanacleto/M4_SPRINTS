#include <iostream>
#include <string>
using namespace std; 

int Mmaior, Mmenor;

// 1 -  Faça uma função que recebe uma certa medida e ajusta ela percentualmente 
// entre dois valores mínimo e máximo e retorna esse valor

int converteSensor(int medida, int  menor, int maior) {
  cout << medida << " " << menor << " " << maior << endl;
  int sub, aux, regra3;
  sub = maior - menor; // Subtrai para eu conseguir trabalhar com três números e fazer uma regra de três
  cout << sub << endl;
  aux = medida - menor; // Subtrai para eu referenciar o novo "menor"
  regra3 = (aux * 100) / sub; // Aqui é a regra de três para chegar no resultado. 
  cout << "O valor em porcentagem do intervalo é: " << regra3 << "%" << endl;
  Mmaior = maior;
  Mmenor = menor;
  return regra3;
}

// 2 - Faça uma função que simule a leitura de um sensor lendo o 
// valor do teclado ao final a função retorna este valor
int leituraSensor() {
    int valor;
    cout << "Digite o valor do sensor: ";
    cin >> valor;
    return valor;

}

// 3 - Faça uma função que armazena uma medida inteira qualquer 
// em um vetor fornecido. Note que como C não possui vetores 
// nativos da linguagem, lembre-se que você precisa passar o 
// valor máximo do vetor assim como a última posição preenchida
// Evite também que, por acidente, um valor seja escrito em 
// uma área de memória fora do vetor

int armazenaValor(int *ponteiro, int tamanhoVetor, int posicaoAtual, int medida){
    *(ponteiro+posicaoAtual)=medida; 
	return posicaoAtual+1; 
}

// 4 - Faça uma função que recebe um vetor com 4 posições que contém 
// o valor da distância de um pequeno robô até cada um dos seus 4 lados.
// A função deve retornar duas informações: A primeira é a direção 
// de maior distância ("Direita", "Esquerda", "Frente", "Tras") e a 
// segunda é esta maior distância.


char *direcaoMenorCaminho(int *ponteiroVetor, int *ponteiroVariavel) {
    int maior = 0;
    int indice = 0;
    char *direita = "direita";
    char *esquerda = "esquerda";
    char *frente = "frente";
    char *tras = "tras";
    for (int n = 0; n < 4; n++) {
        if (*(ponteiroVetor+n) > maior) {
            maior = *(ponteiroVetor + n);
            indice = n;
        }
    }

    *ponteiroVariavel = maior;
    if (indice == 0) {
        return direita;
    }
    else if (indice == 1) {
        return esquerda;
    }
    else if (indice == 2) {
        return frente;
    }
    else {
        return tras;
    }
}


// 5 - Faça uma função que pergunta ao usuário se ele deseja continuar o mapeamento e 
// retorna verdadeiro ou falso
int leComando(){
	char comando;
	cout << "Deseja continuar o mapeamento? (s/n)" << endl;
	cin >> comando;
	if (comando == 's') {
		return 1;
	}
	else {
		return 0;
	}
}

// 6 - A função abaixo (que está incompleta) vai "dirigindo" virtualmente um robô 
// e através de 4 sensores em cada um dos 4 pontos do robo ("Direita", "Esquerda", 
// "Frente", "Tras"). 
//      A cada passo, ele verifica as distâncias aos objetos e vai mapeando o terreno 
// para uma movimentação futura. 
//      Ele vai armazenando estas distancias em um vetor fornecido como parâmetro 
// e retorna a ultima posicao preenchida do vetor.
//      Esta função deve ir lendo os 4 sensores até que um comando de pare seja enviado 
//
//      Para simular os sensores e os comandos de pare, use as funções já construídas 
// nos ítens anteriores e em um looping contínuo até que um pedido de parada seja 
// enviado pelo usuário. 
//
//      Complete a função com a chamada das funções já criadas
int dirige(int *v,int maxv){
	int maxVetor = maxv;
	int *vetorMov = v;
	int posAtualVetor = 0;
	int dirigindo = 1;		
	while(dirigindo){		
		int medida = leituraSensor();
		medida = converteSensor(medida,0,830);
		posAtualVetor = armazenaValor(vetorMov,maxVetor,posAtualVetor,medida);
        ///////////////////////////////////////////////////////////////////////////		
		// Repita as chamadas acima para a "Esquerda", "Frente", "Tras"
		// ................
		///////////////////////////////////////////////////////////////////////////
		dirigindo = leComando();		
	}
	return posAtualVetor;
}


// O trecho abaixo irá utilizar as funções acima para ler os sensores e o movimento
// do robô e no final percorrer o vetor e mostrar o movimento a cada direção baseado 
// na maior distância a cada movimento

void percorre(int *v,int tamPercorrido){	

	int *vetorMov = v;
	int maiorDir = 0;
	
	for(int i = 0; i< tamPercorrido; i+=4){
		char *direcao = direcaoMenorCaminho(&(vetorMov[i]),&maiorDir);
		printf("Movimentando para %s distancia = %i\n",direcao,maiorDir);
	}
}

int main(int argc, char** argv) {
	int maxVetor = 100;
	int vetorMov[maxVetor*4];
	int posAtualVet = 0;
	
	posAtualVet = dirige(vetorMov,maxVetor);
	percorre(vetorMov,posAtualVet);
	
	return 0;
}