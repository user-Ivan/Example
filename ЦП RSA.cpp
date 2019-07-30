// ЦП RSA

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
//функция вычисление Хеша текста
int hashText (char *getText, int openKay, int modul) {
	int i = 0;
	int hash = 0;
	while (getText[i]) {
		hash = hash ^ (myPow(getText[i], openKay, modul));
		i++;
	}
	return hash;
}
// проверка подписи
void checkLabel (int hash, int labelB) {
	if (hash == labelB) 
		printf("\nПодпись верна");
	else 
		printf("\nПодпись НЕ верна");
}

int main()
{
	setlocale(LC_ALL, "Rus");
	int num1 = 0, num2 = 0, modul, funEl, openKey, closeKey, hash, labelA, labelB;
	char getText[100] = "";
	
	printf ("Игрок А");
	printf ("\nВведите первое простое число: ");
	scanf_s ("%d", &num1);
	while (testPrime(num1) == 0)
	{
		printf("Число не простое. Введите еще раз: ");
		scanf_s ("%d", &num1);
	}

	printf ("\nВведите второе простое число: ");
	scanf_s ("%d", &num2);
	while (testPrime(num2) == 0)
	{
		printf("Число не простое. Введите еще раз: ");
		scanf_s ("%d", &num2);
	}

	modul = num1 * num2;
	printf ("\nМодуль: %d", modul);
	funEl = (num1-1) * (num2-1);
	printf ("\nФункция Эйлера: %d", funEl);

	printf ("\n\nВыберите произвольный открытый ключ K. Условия: 1 < К <= %d и НОД(К, %d) = 1", funEl, funEl);
	printf ("\nОткрытый ключ: ");
	scanf_s ("%d", &openKey);
	while ((1 >= openKey) || (openKey > funEl) || (AlgoEuclid(openKey, funEl) != 1)) {
		printf ("Открытый ключ не удовлетворяет условиям. Введите еще раз: ");
		scanf_s ("%d", &openKey);
	}
	
	closeKey = exAlgoEuclid(openKey, funEl);
	printf ("\nСекретный ключ: %d", closeKey);

	printf ("\nВведите сообщение для передачи: ");
	char s[]=""; gets_s(s);
	gets_s(getText);
	int len = strlen(getText);

	hash = hashText(getText, openKey, modul);
	labelA = myPow(hash, closeKey, modul);
	printf("%d", hash);
	printf ("\n---> Пересылаем Игроку В\nМодуль: %d\nОткрытый ключ: %d", modul, openKey); 
	printf ("\nСообщение: %s\nЦифровая подпись: %d", getText, labelA, len);

	printf ("\n\nИгрок В");

	hash = hashText(getText, openKey, modul);
	labelB = myPow(labelA, openKey, modul);
	printf("\nПервая оценка текста: %d\nВторая оценка текста: %d", hash, labelB);

	checkLabel(hash, labelB);

	printf ("\n\n");

	return 0;
}

