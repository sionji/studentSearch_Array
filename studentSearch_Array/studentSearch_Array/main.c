#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "searchHEAD.h"


void main()
{
	Student myclass[7];
	const int MAX_NUM=7;

	int i = 0;
	/* i�� student.txt �� �л� ���� ǥ���ϴ� ����*/

	i = readList(myclass, MAX_NUM);
	findList(myclass, i);

	system("pause");
	return;
}
