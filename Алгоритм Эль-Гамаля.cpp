// �������� ���-������
//

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

void funCipherText(char *getText, int openKey, int prime, int closeKeyA, int num, int *cipherText) {
	int i = 0;
	int firstA = myPow(num, closeKeyA, prime);
	cipherText[i] = firstA;
	while (getText[i]) {
		cipherText[i+1] = (((int)getText[i] * myPow(openKey, closeKeyA, prime)) % prime);
		i++;
	}
} 

void funDecipherText(int *cipherText, int closeKay, int prime, char *decipherText) {
    int i = 0;
	int firstA = exAlgoEuclid(myPow(cipherText[i], closeKay, prime), prime);
	while (cipherText[i+1]) {
		decipherText[i] = (char)((cipherText[i+1] * firstA) % prime);
		i++;
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");
	int prime = 0, num = 0, openKey, closeKey, closeKeyA, firstA;
	char getText[100] = "", decipherText[100] = "";
	int cipherText[100] = {0};
	
	printf ("����� �");
	printf ("\n������� ������ ������� �����: ");
	scanf_s ("%d", &prime);
	while (testPrime(prime) == 0)
	{
		printf("����� �� �������. ������� ��� ���: ");
		scanf_s ("%d", &prime);
	}

	printf ("\n������� ������ �����: ");
	scanf_s ("%d", &num);
	while (num > prime)
	{
		printf("����� ������ %d. ������� ��� ���: ", prime);
		scanf_s ("%d", &num);
	}

	printf ("\n������� ��������� ����: ");
	scanf_s ("%d", &closeKey);
	while (closeKey > prime)
	{
		printf ("����� ������ %d. ������� ��� ���: ", prime);
		scanf_s ("%d", &closeKey);
	}

	openKey = myPow(num, closeKey, prime);
	printf ("\n�������� ����: %d", openKey);

	printf ("\n\n���������� ������ �\n������: %d\n�������� ����: %d\n�����: %d", prime, openKey, num); 

	printf ("\n\n����� A");
	
	printf ("\n�������� ������������ �������� ���� C. �������: 1 < C < %d, ���(�, %d) = 1", prime-1, prime-1);
	printf ("\n�������� ����: ");
	scanf_s ("%d", &closeKeyA);
	while ((1 >= openKey) || (openKey > prime-1) || (AlgoEuclid(closeKeyA, prime-1) != 1))
	{
		printf ("�������� ���� �� ������������� ��������. ������� ��� ���: ");
		scanf_s ("%d", &closeKeyA);
	}

	printf ("\n������� ��������� ��� ��������: ");
	char s[]=""; gets_s(s);
	gets_s(getText);
	
	funCipherText(getText, openKey, prime, closeKeyA, num, cipherText);
	
	printf ("\n���������� ������ � ������������� �����");

	printf ("\n\n����� �");

	funDecipherText(cipherText, closeKey, prime, decipherText);
	
	printf ("\n������������ �����: ");
	puts (decipherText);

	printf ("\n\n");

	return 0;
}
