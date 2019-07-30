// ����������� �������� �������
//

#include "stdafx.h"
#include <locale.h>

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
	if ((num == 0) || (AlgoEuclid(num, mod) != 1) || (mod == 1)) //�������� ������� ������������� ��������� ��������
		return 0;
	
	int exNum = 1; //������ �������� ��������� �������� � �������
	while (((exNum * num) % mod) != 1) //�������� ���������� �����������
        exNum++; 

    return exNum; 
}

int main()
{
	setlocale(LC_ALL, "Rus");
	int a, b, c;

	printf ("������� �����: ");
	scanf_s ("%d" , &a);

	printf ("\n������� ������: ");
	scanf_s ("%d" , &b);
	
	c = exAlgoEuclid(a, b);

	if (c == 0) {
		printf("��������� �������� �� ����������\n");
	} else {
		printf("�������� �������: %d\n", c); 
	}

	printf ("\n\n");
	return 0;
}
