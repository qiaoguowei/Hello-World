#include <iostream>
#include <cstdio>
#include <openssl/lhash.h>
#include <cstring>

using namespace std;

struct Student
{
	Student(char *a, int b, char *c) : age(b)
	{
		strncpy(name, a, 20);
		strncpy(otherInfo, c, 200);
	}

	char name[20];
	int age;
	char otherInfo[200];
};

static int Student_cmp(const void* a, const void* b)
{
	char *namea = ((Student *)a)->name;
	char *nameb = ((Student *)b)->name;
	return strcmp(namea, nameb);
}

static void PrintValue(void *a_)
{
	Student *a = (Student *)a_;
	cout << "name : " << a->name << endl;
	cout << "age  : " << a->age << endl;
	cout << "otherInfo : " << a->otherInfo << endl;
}

static void PrintValue_arg(void *a_, void *b)
{
	int flag = 0;

	Student *a = (Student *)a_;
	flag = *(int *)b;
	cout << "用户输入的参数为 : " << flag << endl;
	cout << "name : " << a->name << endl;
	cout << "age  : " << a->age << endl;
	cout << "otherInfo : " << a->otherInfo << endl;
}

int main()
{
	int flag = 11;
	_LHASH *h;
	Student s1((char *)"zcp", 28, (char *)"hu bei");
	Student s2((char *)"forxy", 28, (char *)"no info");
	Student s3((char *)"skp", 24, (char *)"student");
	Student s4((char *)"zhao_zcp", 28, (char *)"zcp's name");
	Student *s5;

	void *data;

	h = lh_new(NULL, Student_cmp);
	if (h == NULL)
	{
		cout << "error." << endl;
		return -1;
	}

	data = &s1;
	lh_insert(h, data);
	data = &s2;
	lh_insert(h, data);
	data = &s3;
	lh_insert(h, data);
	data = &s4;
	lh_insert(h, data);

	lh_doall(h, PrintValue);
	lh_doall_arg(h, PrintValue_arg, (void *)(&flag));
	data = lh_retrieve(h, (const void *)"skp");
	if (data == NULL)
	{
		cout << "can not look up skp." << endl;
		lh_free(h);
		return -1;
	}
	cout << "=================================================" << endl;
	cout << "find it." << endl;

	s5 = (Student *)data;
	cout << "student name : " << s5->name << endl;
	cout << "student age  : " << s5->age << endl;
	cout << "student otherInfo : " << s5->otherInfo << endl;
	lh_free(h);
	return 0;
}









