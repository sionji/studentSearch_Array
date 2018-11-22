#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "searchHEAD.h"

int readList(Student* myclass, const int MAX_NUM){
	FILE *flist;
	int i=0;			//i�� student.txt �� �л� ���� ǥ���ϴ� ����

	flist = fopen("student.txt", "r");
	while (!feof(flist))
	{
		fscanf_s(flist, "%lu %s", &(myclass[i].studentId), &myclass[i].name, sizeof(myclass[i].name));
		printf("%s %lu \n", myclass[i].name, myclass[i].studentId);
		i++;
		if(i>=MAX_NUM) break; // ���� Student ����ü �迭�� �ִ밹������ ũ�ٸ� break;
	} // �������, "student.txt" ������ �о�� myclass ����ü�� �����Ѵ�.
	fclose(flist);
	printf("----- student.txt �� ������ ����ü�� �����߽��ϴ�. ----- \n\n");

	return i;
}

void findList(Student* myclass, int i){
	FILE *fin, *fout;
	unsigned long int inputNum; // input.txt���� ���� �й��� �Է¹޾Ҵٸ� ���⿡ ����
	char buf[20];
	int d=0, result;

	fin = fopen("input.txt", "r");
	printf("----- input.txt ������ �о�ɴϴ�. -----\n\n");
	fout = fopen("output.txt", "w");

	while (!feof(fin))
	{
		fscanf_s(fin, "%s", buf, sizeof(buf));
		printf("%s \n", buf);
		if (buf[0] >= -1 && buf[0] <= 255) {
			inputNum = atoi(buf);
			/* input.txt ������ ��� buf �� ���� �Է¹���
			���� �Է¹��� ���� ���ڶ�� atoi(buf) �Լ��� ���ڷ� ��ȯ*/

			for (d = 0; d < i; d++) {
				// i�� student.txt���� �о�� ���� ���� �л� ������ 1 ����.
				result = myclass[d].studentId - inputNum;
				if (!result) {
					fprintf(fout, "%s \n", myclass[d].name);
					break;
				} // �ݺ����� �̿��� ���� ���� ã�� �� �̸��� ���
			}
			if (d >= i) fprintf(fout, "����ü�� ���� �й��Դϴ�.\n");
			// �� ã�� �й��� ���ٸ� ����ó��

		}
		else {			/* �Է¹��� ���� ���ڰ� �ƴ� ��� */
			for (d = 0; d < i; d++) {
				// i�� student.txt���� �о�� ���� ���� �л� ������ 1 ����.

				result = strcmp(buf, myclass[d].name);
				/* buf[0]�� ���ڶ�� ���ڿ��� ���ؼ� ��ġ�ϸ� 0, ����ġ�ϸ� 1
				��ġ�Ѵٸ� studentId�� ����ϰ� break; */
				if (!result) {
					fprintf(fout, "%d \n", myclass[d].studentId);
					break;
				}
			}

			if (d >= i) fprintf(fout, "����ü�� ���� �̸��Դϴ�.\n");
			// �� ã�� �̸��� ���ٸ� ����ó��
		}

	} 
	// �������, "input.txt" ������ �о�� "output.txt" �� �����Ѵ�.

	
	fclose(fin);
	fclose(fout);
	printf("\n\n----- output.txt ������ �ۼ��߽��ϴ�. ���α׷��� �����մϴ�. -----\n\n");
	// ���� �����͸� �ݴ´�.
}