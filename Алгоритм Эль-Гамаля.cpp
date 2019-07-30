// Алгоритм Эль-Гамаля
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

int testPrime(int num1) { //ф-я проверки числа на простоту
    int testPr = 1; //флаг 
    for (int i = 2; i < num1; i++) { //цикл по нашему числу
        if ((num1 % i) == 0) { //проверка деления на все его множители
            testPr = 0; //если один из них, делится без остатка
            break; //то проверку не прошел и выходим из цикла
        }
    }
    return testPr; //возврат проверки простое/составное
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
	
	printf ("Игрок В");
	printf ("\nВведите больше простое число: ");
	scanf_s ("%d", &prime);
	while (testPrime(prime) == 0)
	{
		printf("Число не простое. Введите еще раз: ");
		scanf_s ("%d", &prime);
	}

	printf ("\nВведите просто число: ");
	scanf_s ("%d", &num);
	while (num > prime)
	{
		printf("Число больше %d. Введите еще раз: ", prime);
		scanf_s ("%d", &num);
	}

	printf ("\nВведите секретный ключ: ");
	scanf_s ("%d", &closeKey);
	while (closeKey > prime)
	{
		printf ("Число больше %d. Введите еще раз: ", prime);
		scanf_s ("%d", &closeKey);
	}

	openKey = myPow(num, closeKey, prime);
	printf ("\nОткрытый ключ: %d", openKey);

	printf ("\n\nПересылаем Игроку А\nМодуль: %d\nОткрытый ключ: %d\nЧисло: %d", prime, openKey, num); 

	printf ("\n\nИгрок A");
	
	printf ("\nВыберите произвольный закрытый ключ C. Условия: 1 < C < %d, НОД(С, %d) = 1", prime-1, prime-1);
	printf ("\nЗакрытый ключ: ");
	scanf_s ("%d", &closeKeyA);
	while ((1 >= openKey) || (openKey > prime-1) || (AlgoEuclid(closeKeyA, prime-1) != 1))
	{
		printf ("Закрытый ключ не удовлетворяет условиям. Введите еще раз: ");
		scanf_s ("%d", &closeKeyA);
	}

	printf ("\nВведите сообщение для передачи: ");
	char s[]=""; gets_s(s);
	gets_s(getText);
	
	funCipherText(getText, openKey, prime, closeKeyA, num, cipherText);
	
	printf ("\nПересылаем Игроку В зашифрованный текст");

	printf ("\n\nИгрок В");

	funDecipherText(cipherText, closeKey, prime, decipherText);
	
	printf ("\nДешифрованый текст: ");
	puts (decipherText);

	printf ("\n\n");

	return 0;
}
