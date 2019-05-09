#pragma once
#include "_ZZH_.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class book {
public:
	int num;
	float price;
	book *next;
};
bool check_input_is_number(string str) {
	for (int i = 0; i < str.length(); i++) {
		if ((str[i] > '9' || str[i] < '0') && (str[i] != '.')) {
			return false;
		}
	}
	return true;
}
book *head = NULL;
book *creat() {//����ͼ���
	book *p1, *p2;
	p1 = new book;
	head = p1;
	p2 = p1;
	cout << "������ͼ��ı�ţ���0����" << endl;
	string str;
	cin >> str;
	while (!check_input_is_number(str)) {
		cout << "����������1-9" << endl;
		cin >> str;
	}
	p1->num = atoi(str.c_str());
	if (p1->num != 0) {
		cout << "������ͼ��ļ۸�" << endl;
		cin >> str;
		while (!check_input_is_number(str)) {
			cout << "����������1-9" << endl;
			cin >> str;
		}
		p1->price = atoi(str.c_str());
	}
	else {
		delete p1;
		p2 = NULL;
		head = NULL;
		return head;
	}
	while (p1->num != 0) {
		p2 = p1;
		p1 = new book;
		cout << "������ͼ��ı�ţ���0����" << endl;
		cin >> str;
		while (!check_input_is_number(str))
		{
			cout << "����������0-9" << endl;
			cin >> str;
		}
		p1->num = atoi(str.c_str());
		if (p1->num != 0) {
			cout << "������ͼ��ļ۸�" << endl;
			cin >> str;
			while (!check_input_is_number(str)) {
				cout << "����������1-9" << endl;
				cin >> str;
			}
			p1->price = atoi(str.c_str());
		}
		p2->next = p1;
	}
	delete p1;
	p2->next = NULL;
	return head;
}

void showbook(book *head) {
	while (head != NULL) {
		cout << "ͼ����:" << head->num << " " << "ͼ��۸�:" << head->price << endl;
		head = head->next;
	}
}

void Delete(book *head, int num) {
	book *l;
	if (head->num == num) {
		l = head;
		head = head->next;
		::head = head;
		delete l;
		cout << "ɾ�������ɹ�." << endl;
		return;
	}
	while (head) {
		if (head->next == NULL) {
			cout << "�Ҳ���Ҫɾ���Ľڵ�." << endl;
			return;
		}
		if (head->next->num == num) {
			l = head->next;
			head->next = l->next;
			delete l;
			cout << "ɾ�������ɹ�." << endl;
			return;
		}
		head = head->next;
	}
	cout << "�Ҳ���Ҫɾ���Ľڵ�" << endl;
}

void Insert_End(book *head, int num, float price) {
	book *list = new book;
	book *l = NULL;
	while (head) {
		l = head;
		head = head->next;
	}
	l->next = list;
	list->num = num;
	list->price = price;
	list->next = NULL;
}
void Insert_Head(book *head, int num, float price) {
	book *list = new book;
	list->num = num;
	list->price = price;
	list->next = head;
	::head = list;
}
void Insert_Mid(book *head, int num, float price) {
	book *list = new book;
	list->num = num;
	list->price = price;
	if (num <= head->num) {
		list->next = head;
		::head = list;
		return;
	}
	book *tem = NULL;
	while ((num > head->num) && (head->next != NULL)) {
		tem = head;
		head = head->next;
	}
	if (num > head->num) {
		head->next = list;
		list->next = NULL;
	}
	else {
		tem->next = list;
		list->next = head;
	}
}

int getBooknum(book *head) {
	int num = 0;
	while (head) {
		num++;
		head = head->next;
	}
	return num;
}
void main_book_system() {
	string str;
begin:
	cout << "1->�½�ͼ�� 2->��ʾͼ�� 3->����ͼ�� 4->ɾ��ͼ�� 5->ͼ����Ŀ Q->�˳�" << endl;
	cin >> str;
	if (str[0] == '1') {
		::head = creat();
		system("cls");
		goto begin;
	}
	else if (str[0] == '2') {
		if (head == NULL) {
			cout << "ͼ����ǿյģ������ͼ��" << endl << "���س�����������" << endl;
			cin.get();
			cin.get();
			system("cls");
			goto begin;
		}
		else {
			showbook(head);
			cout << "��ʾ��ϣ����س�����������" << endl;
			cin.get();
			cin.get();
			system("cls");
			goto begin;
		}
	}
	else if (str[0] == '3') {
		if (head == NULL) {
			cout << "ͼ����ǿյģ������ͼ��" << endl << "���س�����������" << endl;
			cin.get();
			cin.get();
			system("cls");
			goto begin;
		}
		int num;
		float price;
		cout << "������Ҫ�����ͼ���ţ���0����" << endl;
		string str;
		cin >> str;
		while (!check_input_is_number(str)) {
			cout << "����������1-9" << endl;
			cin >> str;
		}
		num = atoi(str.c_str());
		if (num != 0) {
			cout << "������ͼ��ļ۸�" << endl;
			cin >> str;
			while (!check_input_is_number(str)) {
				cout << "����������1-9" << endl;
				cin >> str;
			}
			price = atoi(str.c_str());
		}
		else {
			system("cls");
			goto begin;
		}
		Insert_Mid(head, num, price);
		cout << "�����ɹ�" << "���س�����������" << endl;
		cin.get();
		cin.get();
		system("cls");
		goto begin;
	}
	else if (str[0] == '4') {
		cout << "������ɾ����ͼ����:" << endl;
		if (head == NULL) {
			cout << "ͼ����ǿյģ������ͼ��" << endl << "���س�����������" << endl;
			cin.get();
			cin.get();
			system("cls");
			goto begin;
		}
		string num;
		cin >> num;
		while (!check_input_is_number(num)) {
			cout << "����������1-9" << endl;
			cin >> num;
		}
		int num1 = atoi(num.c_str());
		Delete(head, num1);
		cout << "�����ɹ�" << "���س�����������" << endl;
		cin.get();
		cin.get();
		system("cls");
		goto begin;
	}
	else if (str[0] == '5') {
		if (head == NULL) {
			cout << "ͼ����ǿյģ������ͼ��" << endl << "���س�����������" << endl;
			cin.get();
			cin.get();
			system("cls");
			goto begin;
		}
		cout << "ͼ����Ŀ����:" << getBooknum(head) << endl;
		cout << "���س�����������" << endl;
		cin.get();
		cin.get();
		system("cls");
		goto begin;
	}
	else {
		if (str[0] != 'Q'&&str[0] != 'q') {
			cout << "���������֣����س�������" << endl;
		}
	}
	if (str[0] != 'Q'&&str[0] != 'q') {
		cin.get();
		cin.get();
		system("cls");
		goto begin;
	}
}


//���������
class Human {
public:
	Human() {
		cout << "����Human" << endl;
	}
	virtual void smart() = 0;
	virtual void beautiful() = 0;
	virtual ~Human() {
		cout << "����Human" << endl;
	}
};
class father:virtual public Human {
public:
	father() {
		cout << "����father" << endl;
	}
	void smart() {
		cout << "���׺�����" << endl;
	}
	virtual void beautiful() {
		cout << "����Ҳ��˧" << endl;
	}
	virtual ~father() {
		cout << "����father" << endl;
	}
};
class mother:public virtual Human {
public:
	mother() {
		cout << "����mother" << endl;
	}
	virtual void beautiful() {
		cout << "ĸ�׺�Ư��" << endl;
	}
	virtual ~mother() {
		cout << "����mother" << endl;
	}
	virtual void smart() {
		cout << "ĸ��Ҳ�ܴ���." << endl;
	}
};

class son :public father,public mother {
public:
	son() {
		cout << "����son" << endl;
	}
	virtual void beautiful() {
		cout << "����Ҳ��˧" << endl;
	}
	virtual ~son() {
		 cout << "����son" << endl;
	}
	 virtual void smart() {
		 cout << "����Ҳ����" << endl;
	 }

};
void main_ABS() {
	//father *pf;
	//mother *pm;
	Human *p;
	int choice = 0;

	while (choice < 99) {
		bool quilt = false;
		cout << "0�˳�1����2����3ĸ��" << endl;
		cin >> choice;
		switch (choice) {
		case 0:
			quilt = true;
			break;
		case 1:
			p = new father;
			p->beautiful();
			p->smart();
			delete p;
			break;
		case 2:
			p = new son;
			//dynamic_cast<son *>(pf)->beautiful();
			p->beautiful();
			p->smart();
			delete p;
			break;
		case 3:
			p = new mother;
			p->beautiful();
			p->smart();
			delete p;
			break;

		default:
			cout << "������0-2֮�������" << endl;
			break;
		}
		if (quilt) {
			break;
		}

	}
	cout << "�������" << endl;
	cin.get();
	cin.get();
}



//������Ӧ��
class Shape {
public:
	virtual double area() = 0;

};
class Trigon :public Shape {
protected:
	double h, w;
public:
	Trigon(double H, double W) {
		h = H;
		w = W;
	}
	double area() {
		return w * h / 2;
	}

};
class Square :public Trigon {
public:
	Square(double H, double W) :Trigon(H, W) {}
	double area() {
		return h * w;
	}
};
class Circle :public Shape {
protected:
	double radius;
public :
	Circle(double r) {
		radius = r;
	}
	double area() {
		return radius * radius*3.14;
	}
};
int main_app_of_class() {
	Shape *p=NULL;
	int choice = 0;
	while (1) {
		bool quit = false;
		cout << "(0)�˳�(1)�����Σ�2��������(3)Բ��" << endl;
		cout << "��ѡ��:";
		cin >> choice;
		switch (choice) {
		case 0:
			quit = true;
			break;
		case 1:
			p = new Trigon(5.0,6.0);
			cout << "���������Ϊ:" << p->area() << endl;
			break;
			case 2:
				p = new Square(70.0,70.0);
				cout << "���������Ϊ:" << p->area() << endl;
				break;
			case 3:
				p = new Circle(9.0);
				cout << "Բ�����Ϊ:" << p->area() << endl;
				break;
			default:
				cout << "������0-3֮�������" << endl;
				break;
		}
		if (choice<4&&choice>0) {
			delete p;
		}
		if (quit) {
			break;
		}
	}
	cout << "���н�����" << endl;
	return 1;
}

//���ӵĳ�����
class Animal {
public:
	Animal(int); 
	virtual ~Animal() {
		cout << "����animal" << endl;
	}
	virtual int GetAge() { return itsage; }
	virtual void Sleep() = 0;
	virtual void Propagate() = 0;
	virtual void Move() = 0;
	virtual void Body() = 0;
	virtual void Eat() = 0;
	virtual void Show() = 0;
private:
	int itsage;
};
Animal::Animal(int age) :itsage(age) {
		cout << "��������..." << endl;
}

class Mammalia :public Animal {
public :
	Mammalia(int age) :Animal(age) {
		cout << "����������..." << endl;
	}
	virtual ~Mammalia() {
		cout << "����Mammalia" << endl;
	}
	virtual void Propagate() {
		cout << "��������̥�����ͨ����̥����ֳ���" << endl;
	}
};
class Brid :public Animal {
public:
	Brid(int age) :Animal(age) {
		cout << "��������..." << endl;
	}
	 ~Brid() {
		cout << "����Brid" << endl;
	}
	 void Sleep() { cout << "���ڲ���˯��" << endl; }
	 void Move() { cout << "����������·" << endl; }
	 void Propagate() { cout << "����ͨ��������" << endl; }
	 void Body() { cout << "���������" << endl; }
	 void Eat() { cout << "�����Ӳ�ʳ�ද��" << endl; }
	 void Show() { cout << "�����ܶ�ë" << endl; }

};

class Pig :public Mammalia {
public:
	Pig(int age) :Mammalia(age) {
		cout << "��������..." << endl;
	}
	 ~Pig() {
		cout << "����Pig" << endl;
	}
	  void Sleep() { cout << "��������˯��" << endl; }
	  void Move() { cout << "����������·" << endl; }
	  void Propagate() { cout << "��Ҳ��ͨ����̥��ֳ���" << endl; }
	  void Body() { cout << "������ܷ�" << endl; }
	  void Eat() { cout << "������ʳ�ද��" << endl; }
	  void Show() { cout << "�����ܶ�ë" << endl; }

};

class Human2 :public Mammalia {
public:
	Human2(int age) :Mammalia(age) {
		cout << "��������..." << endl;
	}
	 ~Human2() {
		cout << "����Huaman2" << endl;
	}
	 void Sleep() { cout << "���ڴ���˯��" << endl; }
	 void Move() { cout << "����������·" << endl; }
	 void Propagate() { cout << "��Ҳ��ͨ����̥��ֳ���" << endl; }
	 void Body() { cout << "������ܷ�" << endl; }
	 void Eat() { cout << "������ʳ�ද��" << endl; }
	 void Show() { cout << "��������ë" << endl; }
};

void main_fuzaclass() {
	Animal *p = NULL;
	int chosic = 0;
	while (1) {
		bool quilt = false;
		cout << "(0)�˳�(1)����(2)����(3)����" << endl;
		cin >> chosic;
		switch (chosic) {
		case 0:
			quilt = true;
			break;
		case 1:
			p = new Human2(80);
			cout << "��������Ϊ:" << p->GetAge() << endl;
			break;
		case 2:
			p = new Brid(50);
			cout << "��������Ϊ:" << p->GetAge() << endl;
			break;
		case 3:
			p = new Pig(1);
			cout << "��������Ϊ:" << p->GetAge() << endl;
			break;
		default:{
			cout << "������0-3֮�������" << endl;
			break;
			}
		}
		if (quilt) {
			break;
		}
		p->Body();
		p->Eat();
		p->Move();
		p->Propagate();
		p->Show();
		p->Sleep();
		cout << endl;
		delete p;
	}

}

class _my_string_ {
public:
	_my_string_(); //����һ���յ��ַ�����
	~_my_string_();
	_my_string_(const char * const ch);//���캯�����ַ�����ֵ
	char &operator[](unsigned short int len);//[]�����������������Խ��
	char operator[](unsigned short int len)const;//��������
	_my_string_ &operator=(const _my_string_ &s);//=��ֵ���������
	const char *_getstr_()const; 
	int _getlen_()const; 
	_my_string_(const _my_string_ &rs);//��д���ƹ��캯��ʵ���ַ����ĸ���
	friend ostream &operator<<(ostream &o, const _my_string_&s);//���������������أ����ܺ�_getstr_()һ��
	friend istream &operator>>(istream &i, _my_string_&s);
	friend bool operator<(const _my_string_ &str1, const _my_string_ &str2);
	friend bool operator>(const _my_string_ &str1, const _my_string_ &str2);
	friend bool operator==(const _my_string_ &str1, const _my_string_ &str2);//����������غ�������Ϊ��Ա�����ǣ���Ԫ�����ֻ��һ������������friend����Ϊ��Ԫ���������ǳ�Ա����
	_my_string_ operator+(const _my_string_ &s);
	void operator+=(const _my_string_ &s);
private:
	unsigned short int length;//���Ȳ�����ָ���������������Ա���
	char *str;
	_my_string_(unsigned short int);//����˽���У���ֹ�����������������ѿռ�
};

_my_string_::_my_string_() {//����һ���յ��ַ�����
	length = 0;
	str = new char[1];
	str[0] = '\0';
}
_my_string_::~_my_string_() {
	delete []str;
	length = 0;
}
_my_string_::_my_string_(const char * const ch) {//���캯�����ַ�����ֵ
	length = strlen(ch);
	str = new char[length + 1];
	for (int i = 0; i < length; i++) {
		str[i] = ch[i];
	}
	str[length] = '\0';
}

_my_string_::_my_string_(unsigned short int len) {
	length = len;
	str = new char[length + 1];
	for (int i = 0; i <= length; i++) {
		str[i] = '\0';
	}
}

char & _my_string_::operator[](unsigned short int len) {//[]�����������������Խ��
	if (len > length) {
		return str[length - 1];
	}
	else {
		return str[len];
	}
}
char _my_string_::operator[](unsigned short int len)const {
	if (len > length&&len<0) {
		return str[length - 1];
	}
	else {
		return str[len];
	}
}
_my_string_::_my_string_(const _my_string_ &rs) {
	length = rs._getlen_();
	str = new char[length + 1];
	for (int i = 0; i < length; i++) {
		str[i] = rs[i];
	}
	str[length] = '\0';
}
_my_string_ &_my_string_::operator=(const _my_string_ &s) {
	if (this == &s) {
		return *this;
	}
	else {
		delete[]str;
		length = s._getlen_();
		str = new char[length + 1];
		for (int i = 0; i < length; i++) {
			str[i] = s[i];
		}
		str[length] = '\0';
		return *this;
	}
}
ostream &operator<<(ostream &o, const _my_string_&s) {
	o << s.str;
	return o;
}
istream &operator>>(istream &i, _my_string_&s) {
	i >> s.str;
	return i;
}
bool operator<(const _my_string_ &str1, const _my_string_ &str2) {
	if (strcmp(str1.str, str2.str) < 0) {
		return 1;
	}
	else {
		return 0;
	}
}
bool operator>(const _my_string_ &str1, const _my_string_ &str2) {
	if (strcmp(str1.str, str2.str) > 0) {
		return 1;
	}
	else {
		return 0;
	}
}
bool operator==(const _my_string_ &str1, const _my_string_ &str2) {
	if (strcmp(str1.str, str2.str) == 0) {
		return 1;
	}
	else {
		return 0;
	}
}
_my_string_ _my_string_::operator+(const _my_string_ &s) {
	int total = length + s.length;
	_my_string_ temp(total);
	int i = 0;
	for (i; i < length; i++) {
		temp[i] = str[i];
	}
	for (int j = 0; j < s.length; j++,i++) {
		temp[i] = s[j];
	}
	temp[total] = '\0';
	return temp;
}

void _my_string_::operator+=(const _my_string_ &s) {
	int total = length + s.length;
	_my_string_ temp = str;
	str = new char[total + 1];
	int i = 0;
	for (i; i < length; i++) {
		str[i] = temp[i];
	}
	for (int j = 0; j < total; j++, i++) {
		str[i] = s[j];
	}
	str[total] = '\0';
}

const char *_my_string_::_getstr_()const {
	return str;
}
int _my_string_::_getlen_()const {
	return length;
}



int main_my_string() {
	_my_string_ s1 = "aaaaaaaaaaaaa";
	_my_string_ s2 = "bbb";
	char ch[] = "1121";
	s1 = ch;
	cout << s1 << endl;
	

	





	return 0;
}