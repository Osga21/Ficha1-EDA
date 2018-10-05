#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//https://www.calculatorsoup.com/calculators/statistics/number-generator.php para gerar listas
int main()
{
	float *valores;
	int nlinhas;
	int nclasses;

	//Abertura de ficheiro
	FILE *pfile; 
	char fileName[] = { "test.txt" }; //abre ficheiro na mesma pasta do executavel(test.txt)

	pfile = fopen(fileName, "r");
	if (pfile == NULL) // Erro na abertura do ficheiro
	{
		printf("Erro na abertura do ficheiro: %s\n", fileName);
		getchar();
		exit(1);
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
	

	//Prompt classes inuteis
	printf("Dividir classes por valor maximo?(default n)(s/n)");
	printf("\n(Util se numero de dados for muito superior ao valor maximo)");
	char maxClass=getchar();
	switch (maxClass) {
		case 's':classSize = valMax / nclasses; break;
		case 'n':;
		default:;
	}
	system("cls");


	
	printf("Intervalo  Freq Abs  Freq Rel  Grafico\n______________________________________\n");	//Cabeçalho tabela

	//Construção tabela
	char showClass;
	for (int i = 0; i < nclasses; i++) {
		valFreqabs[i] =0;

		for (int j = 0; j < nlinhas; j++) { //Cálculo freq. absoluta

			if (valores[j]>= i*classSize && valores[j]< (i + 1)*classSize) 
			{
				valFreqabs[i] +=1;
			}
		}

		valFreqrel[i] = (100 * valFreqabs[i]) / nlinhas; //Cálculo Frequencia relativa

			printf("\n% 4d a % 4d\t %d\t%d%%\t",i*classSize,(i+1)*classSize,valFreqabs[i],valFreqrel[i]);

		for (int k = 0; k < valFreqrel[i] / 2;k++) {	//Gráfico, cada * ~=2%
			printf("*");
		}
	}

	//Estatisticas
	float valAmp = valMax - valMin;
	float valMed = valSum / nlinhas;

	printf("\n\n# de classes: %d  # de linhas: %d", nclasses, nlinhas);
	printf("\nMax.=%g  Min.=%g  Sum.=%g  Amp.=%g\n", valMax, valMin, valSum, valAmp);


	//Desvio Padrão
	double valStdev;
	double sumStdev = 0;
	for (int i = 0; i < nlinhas; i++) 
	sumStdev += pow(valores[i]-valMed,2);
	valStdev = sqrt((1 /double(nlinhas))*sumStdev);

	printf("Media: %g  Desvio Padrao: %.2f",valMed,valStdev);

	printf("\n\n");

	//Grafico Barras
	int grafRes = 15;
	int grafMulti = 10;
	for (int i = grafRes; i > 0; i--) {
		printf("% 3d%% | ",(i*grafRes)/grafMulti);
		for (int j = 0; j < nclasses; j++) {
			if (int(valFreqrel[j])*grafMulti >= i*grafRes) 
				printf("  ##  ");
			
			else printf("      ");
			}
		printf("\n");
		}
	for (int i = 0; i < nclasses; i++)
		printf("-------");
	printf("\n\t");
	for (int i = 0; i < nclasses; i++)
		printf(">%d  ", (i + 1)*classSize);

	
	//Cleanup
	printf("\n\n\n");
	system("pause");
	delete[] valores; 
	delete[] valFreqabs;
	delete[] valFreqrel;

}