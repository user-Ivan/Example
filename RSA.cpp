// RSA
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
// функция нахождения остатка от деления возведения числа в степень
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
//функция шифрования сообщения
void funCipherText(char *getText, int OK, int M, int *cipherText) {
	int i = 0;
	while (getText[i]) {
		cipherText[i] = myPow((int)(getText[i]), OK, M);
		i++;
	}
}
// фукнция дешифрования сообщения
void funDecipherText(int *cipherText, int CK, int M, char *decipherText) {
    int i = 0;
	while (cipherText[i]) {
		decipherText[i] = (char)myPow(cipherText[i], CK, M);
		i++;
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");
	int num1 = 0, num2 = 0, modul, funEl, openKey, closeKey;
	char getText[100] = "", decipherText[100] = "";
	int cipherText[100] = {0};
	
	printf ("Игрок В");
	printf ("\nВведите первое простое число: ");
	scanf_s ("%d", &num1);
	while (testPrime(num1) == 0) //проверка на простоту
	{
		printf("Число не простое. Введите еще раз: ");
		scanf_s ("%d", &num1);
	}

	printf ("\nВведите второе простое число: ");
	scanf_s ("%d", &num2);
	while (testPrime(num2) == 0) //проверка на простоту
	{
		printf("Число не простое. Введите еще раз: ");
		scanf_s ("%d", &num2);
	}

	modul = num1 * num2; //находим модуль
	printf ("\nМодуль: %d", modul);
	funEl = (num1-1) * (num2-1); //вычисляем функцию Эйлера
	printf ("\nФункция Эйлера: %d", funEl);

	printf ("\n\nВыберите произвольный открытый ключ K. Условия: 1 < К <= %d и НОД(К, %d) = 1", funEl, funEl);
	printf ("\nОткрытый ключ: ");
	scanf_s ("%d", &openKey);
	while ((1 >= openKey) || (openKey > funEl) || (AlgoEuclid(openKey, funEl) != 1)) { //проверка условий Открытого ключа
		printf ("Открытый ключ не удовлетворяет условиям. Введите еще раз: ");
		scanf_s ("%d", &openKey);
	}
	
	closeKey = exAlgoEuclid(openKey, funEl); //вычисляем секретный ключ
	printf ("\nСекретный ключ: %d", closeKey);

	printf ("\n\nПересылаем Игроку А\nМодуль: %d\nОткрытый ключ: %d", modul, openKey); 

	printf ("\n\nИгрок A");
	
	printf ("\nВведите сообщение для передачи: ");
	char s[]=""; gets_s(s);
	gets_s(getText); //считываем сообщение
	
	funCipherText(getText, openKey, modul, cipherText); //шифруем сообщение
	
	printf ("\nПересылаем Игроку В зашифрованный текст");

	printf ("\n\nИгрок В");

	funDecipherText(cipherText, closeKey, modul, decipherText); //дешифруем сообщение
	
	printf ("\nДешифрованый текст: ");
	puts (decipherText);

	printf ("\n\n");

	return 0;
}
