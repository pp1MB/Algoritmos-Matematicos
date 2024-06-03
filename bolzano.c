#include <stdio.h>
#include <stdlib.h>

void printarEquação(int grau, int *coeficientes);
double calcularEquação(double x, int grau, int *coeficientes);
void encontrarX(int grau, int *coeficientes);
int modulo(int numero);
float fmodulo(float numero);

int main(void){
	int grau, *coeficientes;

	printf("Insira o grau da equação: ");
	scanf("%d", &grau);

	// Alocando Memória: a equação vai de x^(grau) até x^0, logo são grau+1 coeficientes.
	coeficientes = (int *) malloc((grau + 1) * sizeof(int));
	if(coeficientes == NULL){
		printf("Erro em alocar memória.\n");
		exit(1);
	}
 
	// Lendo os coeficientes da equação: índice [grau] recebe o coeficiente de x^(grau).
	printf("Insira %d coeficientes: ", grau + 1);
	for(int i = grau; i >= 0; i--)
		scanf("%d", &coeficientes[i]);

	printf("A equação selecionada é:\n");
	printarEquação(grau, coeficientes);
	calcularEquação(0, grau, coeficientes);

	printf("Qual f(x) você deseja encontrar por Teorema de Bolzano/Teorema do Valor Intermediário?\n");
	encontrarX(grau, coeficientes);

	// Liberando a memória
	free(coeficientes);
	coeficientes = NULL;

	return 0;
}

void printarEquação(int grau, int *coeficientes){

	for(int i = grau+1; i >= 0; i--){
		if(coeficientes[i] != 0){

			if(modulo(coeficientes[i]) != 1 || i == 0)
				printf("%d", modulo(coeficientes[i]));
	
			if(i > 1) 
				printf("x^%d ", i);

			if(i == 1) 
				printf("x ");
		}

		if(coeficientes[i-1]>0) 
			printf("+ ");

		if(coeficientes[i-1]<0)
			printf("- ");
	}

	printf("\n");

	return;
}

double calcularEquação(double x, int grau, int *coeficientes){
	double resultado = 0;
    double x_potencia = 1; 

    for (int i = 0; i <= grau; i++) {
        resultado += coeficientes[i] * x_potencia; 
        x_potencia *= x; 
    }

	printf("Resultado: %lf\n", resultado);
    return resultado;
}

void encontrarX(int grau, int *coeficientes){
	int tentativa, contador = 0;
	double fx, alcance, resultado, x = 0.000000;

	scanf("%lf", &fx);
	printf("Insira o alcance da busca em X (|alcance>=0|): \n");
	scanf("%lf", &alcance);
	printf("Insira o número máximo de tentativas: \n");
	scanf("%d", &tentativa);

	float positivo = alcance;
	float negativo = -alcance;

	do {
		resultado = calcularEquação(x, grau, coeficientes);
		if(resultado > fx){
			positivo = x;
			x = (x + negativo)/2;
			printf("maior %lf\n", x);
		}
		if(resultado < fx){
			negativo = x;
			x = (x + positivo)/2;
			printf("menor %lf\n", x);
		}
		contador++;
		tentativa--;
	} while(fmodulo(resultado - fx) > 0.000001 && tentativa>0);

	if(fmodulo(resultado - fx) < 0.000001)
		printf("O x encontrado foi %lf com %d tentativa(s)\n", x, contador);
}

int modulo(int numero){
	// |numero|
	if(numero<0) 
		numero = -numero;

	return numero;
}

float fmodulo(float numero){
	// |numero|
	if(numero<0) 
		numero = -numero;

	return numero;
}