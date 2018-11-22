# studentSearch_Array
 Print the name when entering the student number, and print the student number when entering the name. (Array implementation)
 <br />
 student.txt 파일을 읽어와 배열에 학번과 이름을 저장하고, input.txt 파일에 학번이 있다면 이름을, 이름이 있다면 학번을 출력하는 프로그램입니다. 
 출력은 output.txt 파일을 생성하여 처리합니다.  
 <br />
 <br />
 
## 들어가기 전에
 정상적인 동작을 위해 프로젝트 또는 .exe 파일이 있는 위치에 student.txt 파일과 input.txt 파일이 있어야 합니다.  
 student.txt 파일은 학생의 학번과 이름이 적혀있는 파일입니다.  
 input.txt 파일은 내가 찾고싶은 이름 또는 학번이 적힌 파일입니다.  
 <br />
 출력은 output.txt 파일을 main.c 파일이 있는 위치에 생성하여 처리합니다.  
 <br />
 <br />
 
## main.c
```
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
```
 배열은 유한한 크기를 가지므로 최대 크기를 선언해줍니다.  
 readList 함수에서 student.txt 파일을 읽어 배열에 입력할 것입니다.  
 만약 이 과정에서 배열의 최대크기(MAX_NUM)보다 크다면 입력을 중단합니다.  
 <br />
 findList 함수는 input.txt 파일을 읽어 output.txt 파일을 생성합니다.  
 <br />
 <br />
 
## readList 함수
```
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
```
 student.txt 파일을 읽어 배열에 순차적으로 저장합니다.  
 구조체 배열의 최대갯수보다 더 많은 값을 읽어들이면 break 합니다.  
 <br />
 student.txt에서 읽어들인 학생의 숫자를 반환합니다.  
 (만약, student.txt에 학생 3명의 정보가 있었다면 i=3 을 반환합니다.)  
 <br />
 <br />
 
## findList 함수
```
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
```
 input.txt 파일을 한 줄 씩 읽어 숫자인지 문자인지 검사해 서로 다른 알고리즘을 적용합니다.  
 학번을 입력받으면 일치하는 학번에 해당하는 이름을, 이름을 입력받으면 일치하는 이름에 해당하는 학번을 출력합니다. 
 만약 입력받은 학번 또는 이름과 일치하는 값이 배열에 없다면, 없는 값임을 알려줍니다.  
 <br />
 <br />
 
## 실행 결과
![ssearch_result_array](https://user-images.githubusercontent.com/41851641/48907375-8c454100-eeaa-11e8-966e-e3f04b4432d5.png)  
<br />
<br />

## 고찰
일반적인 경우, 배열과 linked list 중에서 수행속도는 배열이 더 빠르다고 알려져 있습니다.  
하지만 배열의 경우 메모리 공간 낭비의 문제가 있습니다.  
<br />
구조체를 배열로 선언할 때 최대 크기를 명시해 주어야 하고, 이 최대 크기를 넘어서려 하면 예외 처리를 해줘야 합니다.  
만약 최대 크기가 넘지 않는다면, 메모리의 공간이 낭비되는 문제점이 있고 또한 내가 불러올 파일의 크기가 언제든지 변할 수 있기 때문에 많은 제약이 따릅니다.  
이 메모리 관리와 공간 낭비 문제는 동적 할당(malloc)을 이용하면 해결할 수 있습니다.
<br />
