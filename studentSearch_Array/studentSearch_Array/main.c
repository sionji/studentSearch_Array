#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "searchHEAD.h"


void main()
{
	Student myclass[7];
	const int MAX_NUM=7;

	int i = 0;
	/* i는 student.txt 의 학생 수를 표시하는 숫자*/

	i = readList(myclass, MAX_NUM);
	findList(myclass, i);

	system("pause");
	return;
}
