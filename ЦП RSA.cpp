// �� RSA

#include "stdafx.h"
#include <locale.h>
#include "stdio.h"
#include <string.h>

int funMax (int a, int b) {
	if (a > b) {
		return a;
	} else {
		return b;
	}
}

int funMin (int a, int b) {
	if (a < b) {
		return a;
	} else {
		return b;
	}
}

int AlgoEuclid (int num1, int num2) {
	int c = 0;
	if ((num1 == 0) || (num2 == 0))
		return (c = 0);

	int a = funMax(num1, num2);
	int b = funMin(num1, num2);
	
	do {
		c = a % b;
		a = b;
		b = c;
	} while (c != 0);

	return a;
}

int exAlgoEuclid (int num, int mod) {
	if ((num == 0) || (AlgoEuclid(num, mod) != 1) || (mod == 1)) 
		return 0;
	
	int exNum = 1;
	while (((exNum * num) % mod) != 1) 
        exNum++; 

    return exNum; 
}

int myPow(int num, int exp, int mod) { 
    int c = 1; 
    for (int i = 0; i < exp; i++) { 
        c = (c * num) % mod; 
    } 
    return c; 
}

int testPrime(int num1) { //�-� �������� ����� �� ��������
    int testPr = 1; //���� 
    for (int i = 2; i < num1; i++) { //���� �� ������ �����
        if ((num1 % i) == 0) { //�������� ������� �� ��� ��� ���������
            testPr = 0; //���� ���� �� ���, ������� ��� �������
            break; //�� �������� �� ������ � ������� �� �����
        }
    }
    return testPr; //������� �������� �������/���������
}
//������� ���������� ���� ������
int hashText (char *getText, int openKay, int modul) {
	int i = 0;
	int hash = 0;
	while (getText[i]) {
		hash = hash ^ (myPow(getText[i], openKay, modul));
		i++;
	}
	return hash;
}
// �������� �������
void checkLabel (int hash, int labelB) {
	if (hash == labelB) 
		printf("\n������� �����");
	else 
		printf("\n������� �� �����");
}

int main()
{
	setlocale(LC_ALL, "Rus");
	int num1 = 0, num2 = 0, modul, funEl, openKey, closeKey, hash, labelA, labelB;
	char getText[100] = "";
	
	printf ("����� �");
	printf ("\n������� ������ ������� �����: ");
	scanf_s ("%d", &num1);
	while (testPrime(num1) == 0)
	{
		printf("����� �� �������. ������� ��� ���: ");
		scanf_s ("%d", &num1);
	}

	printf ("\n������� ������ ������� �����: ");
	scanf_s ("%d", &num2);
	while (testPrime(num2) == 0)
	{
		printf("����� �� �������. ������� ��� ���: ");
		scanf_s ("%d", &num2);
	}

	modul = num1 * num2;
	printf ("\n������: %d", modul);
	funEl = (num1-1) * (num2-1);
	printf ("\n������� ������: %d", funEl);

	printf ("\n\n�������� ������������ �������� ���� K. �������: 1 < � <= %d � ���(�, %d) = 1", funEl, funEl);
	printf ("\n�������� ����: ");
	scanf_s ("%d", &openKey);
	while ((1 >= openKey) || (openKey > funEl) || (AlgoEuclid(openKey, funEl) != 1)) {
		printf ("�������� ���� �� ������������� ��������. ������� ��� ���: ");
		scanf_s ("%d", &openKey);
	}
	
	closeKey = exAlgoEuclid(openKey, funEl);
	printf ("\n��������� ����: %d", closeKey);

	printf ("\n������� ��������� ��� ��������: ");
	char s[]=""; gets_s(s);
	gets_s(getText);
	int len = strlen(getText);

	hash = hashText(getText, openKey, modul);
	labelA = myPow(hash, closeKey, modul);
	printf("%d", hash);
	printf ("\n---> ���������� ������ �\n������: %d\n�������� ����: %d", modul, openKey); 
	printf ("\n���������: %s\n�������� �������: %d", getText, labelA, len);

	printf ("\n\n����� �");

	hash = hashText(getText, openKey, modul);
	labelB = myPow(labelA, openKey, modul);
	printf("\n������ ������ ������: %d\n������ ������ ������: %d", hash, labelB);

	checkLabel(hash, labelB);

	printf ("\n\n");

	return 0;
}

