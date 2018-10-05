#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int main()
{
	float *valores;
	int nlinhas;
	int nclasses;

	//Abertura de ficheiro
	FILE *pfile; 
	char fileName[] = { "C:\\Users\\Henrique\\Desktop\\test.txt" }; 

	pfile = fopen(fileName, "r");
	if (pfile == NULL) // Erro na abertura do ficheiro
	{
		printf("Erro na abertura do ficheiro: %s\n", fileName);
		getchar();
	}

	//Leitura de ficheiro
	fscanf(pfile, "%d", &nclasses);
	fscanf(pfile, "%d", &nlinhas);
	

	valores = new float[nlinhas];
	float valMax, valMin,valSum;
	valMax = 0;
	valMin = 99999;
	valSum = 0;

	for (int i = 0; i < nlinhas; i++) {
		fscanf(pfile, "%f", &valores[i]);
		if (valores[i] > valMax) //valor maximo
			valMax = valores[i];
		if (valores[i] < valMin) //valor minimo
			valMin = valores[i];
		valSum += valores[i]; //somatorio de valores
	}
	
	int classSize = nlinhas / nclasses;
	int *valFreqabs;
	int *valFreqrel;

	valFreqabs = new int [nclasses];
	valFreqrel = new int[nclasses];
	
	//Cabeçalho tabela
	printf("\nIntervalo  Freq Abs  Freq Rel  Grafico\n______________________________________\n");


	for (int i = 0; i < nclasses; i++) {
		valFreqabs[i] =0;

		for (int j = 0; j < nlinhas; j++) { //Cálculo freq. absoluta

			if (valores[j]>= i*classSize && valores[j]< (i + 1)*classSize) 
			{
				valFreqabs[i] +=1;
			}
		}

		valFreqrel[i] = (100 * valFreqabs[i]) / nlinhas;

		if ((i + 1)*classSize > 99)//Repetido para o gráfico ficar bem formatado com numeros >100 e <1000
			printf("\n%d a %d\t %d\t%d%%\t", i*classSize, (i + 1)*classSize, valFreqabs[i], valFreqrel[i]);
		else
			printf("\n%d a %d\t\t %d\t%d%%\t",i*classSize,(i+1)*classSize,valFreqabs[i],valFreqrel[i]);

		for (int k = 0; k < valFreqrel[i] / 2;k++) {	//Gráfico, cada * ~=2%
			printf("*");
		}
	}h

	//Estatisticas
	float valAmp = valMax - valMin;
	float valMed = valSum / nlinhas;

	printf("\n\n# de classes: %d  # de linhas: %d", nclasses, nlinhas);
	printf("\nMax.=%g  Min.=%g  Sum.=%g  Amp.=%g\n", valMax, valMin, valSum, valAmp);


	//Desvio Padrão
	double valStdev;
	float sumStdev=0;
	for (int i = 0; i < nlinhas; i++) 
		sumStdev += pow(valores[i]-valMed,2);
	valStdev = sqrt((1 /double(nlinhas))*sumStdev);

	printf("Media: %g  Desvio Padrao: %.2f",valMed,valStdev);


	//Cleanup
	getchar();
	delete[] valores; 
	delete[] valFreqabs;
}