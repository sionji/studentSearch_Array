#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "searchHEAD.h"

int readList(Student* myclass, const int MAX_NUM){
	FILE *flist;
	int i=0;			//i는 student.txt 의 학생 수를 표시하는 숫자

	flist = fopen("student.txt", "r");
	while (!feof(flist))
	{
		fscanf_s(flist, "%lu %s", &(myclass[i].studentId), &myclass[i].name, sizeof(myclass[i].name));
		printf("%s %lu \n", myclass[i].name, myclass[i].studentId);
		i++;
		if(i>=MAX_NUM) break; // 만약 Student 구조체 배열의 최대갯수보다 크다면 break;
	} // 여기까지, "student.txt" 파일을 읽어와 myclass 구조체에 저장한다.
	fclose(flist);
	printf("----- student.txt 의 내용을 구조체에 저장했습니다. ----- \n\n");

	return i;
}

void findList(Student* myclass, int i){
	FILE *fin, *fout;
	unsigned long int inputNum; // input.txt에서 만약 학번을 입력받았다면 여기에 저장
	char buf[20];
	int d=0, result;

	fin = fopen("input.txt", "r");
	printf("----- input.txt 파일을 읽어옵니다. -----\n\n");
	fout = fopen("output.txt", "w");

	while (!feof(fin))
	{
		fscanf_s(fin, "%s", buf, sizeof(buf));
		printf("%s \n", buf);
		if (buf[0] >= -1 && buf[0] <= 255) {
			inputNum = atoi(buf);
			/* input.txt 파일을 열어서 buf 에 값을 입력받음
			만약 입력받은 값이 숫자라면 atoi(buf) 함수로 숫자로 변환*/

			for (d = 0; d < i; d++) {
				// i는 student.txt에서 읽어온 파일 안의 학생 수보다 1 많다.
				result = myclass[d].studentId - inputNum;
				if (!result) {
					fprintf(fout, "%s \n", myclass[d].name);
					break;
				} // 반복문을 이용해 같은 값을 찾은 후 이름을 출력
			}
			if (d >= i) fprintf(fout, "구조체에 없는 학번입니다.\n");
			// 다 찾고도 학번이 없다면 예외처리

		}
		else {			/* 입력받은 값이 숫자가 아닐 경우 */
			for (d = 0; d < i; d++) {
				// i는 student.txt에서 읽어온 파일 안의 학생 수보다 1 많다.

				result = strcmp(buf, myclass[d].name);
				/* buf[0]가 문자라면 문자열을 비교해서 일치하면 0, 불일치하면 1
				일치한다면 studentId를 출력하고 break; */
				if (!result) {
					fprintf(fout, "%d \n", myclass[d].studentId);
					break;
				}
			}

			if (d >= i) fprintf(fout, "구조체에 없는 이름입니다.\n");
			// 다 찾고도 이름이 없다면 예외처리
		}

	} 
	// 여기까지, "input.txt" 파일을 읽어와 "output.txt" 를 생성한다.

	
	fclose(fin);
	fclose(fout);
	printf("\n\n----- output.txt 파일을 작성했습니다. 프로그램을 종료합니다. -----\n\n");
	// 파일 포인터를 닫는다.
}