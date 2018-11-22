typedef struct {
	char name[20];
	unsigned long int studentId;
} Student;

int readList(Student* myclass, const int MAX_NUM);
void findList(Student* myclass, int i);