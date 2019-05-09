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
book *creat() {//创建图书库
	book *p1, *p2;
	p1 = new book;
	head = p1;
	p2 = p1;
	cout << "请输入图书的编号，以0结束" << endl;
	string str;
	cin >> str;
	while (!check_input_is_number(str)) {
		cout << "请输入数字1-9" << endl;
		cin >> str;
	}
	p1->num = atoi(str.c_str());
	if (p1->num != 0) {
		cout << "请输入图书的价格" << endl;
		cin >> str;
		while (!check_input_is_number(str)) {
			cout << "请输入数字1-9" << endl;
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
		cout << "请输入图像的编号，以0结束" << endl;
		cin >> str;
		while (!check_input_is_number(str))
		{
			cout << "请输入数字0-9" << endl;
			cin >> str;
		}
		p1->num = atoi(str.c_str());
		if (p1->num != 0) {
			cout << "请输入图书的价格" << endl;
			cin >> str;
			while (!check_input_is_number(str)) {
				cout << "请输入数字1-9" << endl;
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
		cout << "图书编号:" << head->num << " " << "图书价格:" << head->price << endl;
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
		cout << "删除操作成功." << endl;
		return;
	}
	while (head) {
		if (head->next == NULL) {
			cout << "找不到要删除的节点." << endl;
			return;
		}
		if (head->next->num == num) {
			l = head->next;
			head->next = l->next;
			delete l;
			cout << "删除操作成功." << endl;
			return;
		}
		head = head->next;
	}
	cout << "找不到要删除的节点" << endl;
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
	cout << "1->新建图书 2->显示图书 3->插入图书 4->删除图书 5->图书数目 Q->退出" << endl;
	cin >> str;
	if (str[0] == '1') {
		::head = creat();
		system("cls");
		goto begin;
	}
	else if (str[0] == '2') {
		if (head == NULL) {
			cout << "图书库是空的，请添加图书" << endl << "按回车返回主界面" << endl;
			cin.get();
			cin.get();
			system("cls");
			goto begin;
		}
		else {
			showbook(head);
			cout << "显示完毕，按回车返回主界面" << endl;
			cin.get();
			cin.get();
			system("cls");
			goto begin;
		}
	}
	else if (str[0] == '3') {
		if (head == NULL) {
			cout << "图书库是空的，请添加图书" << endl << "按回车返回主界面" << endl;
			cin.get();
			cin.get();
			system("cls");
			goto begin;
		}
		int num;
		float price;
		cout << "请输入要插入的图书编号，以0返回" << endl;
		string str;
		cin >> str;
		while (!check_input_is_number(str)) {
			cout << "请输入数字1-9" << endl;
			cin >> str;
		}
		num = atoi(str.c_str());
		if (num != 0) {
			cout << "请输入图书的价格" << endl;
			cin >> str;
			while (!check_input_is_number(str)) {
				cout << "请输入数字1-9" << endl;
				cin >> str;
			}
			price = atoi(str.c_str());
		}
		else {
			system("cls");
			goto begin;
		}
		Insert_Mid(head, num, price);
		cout << "操作成功" << "按回车返回主程序" << endl;
		cin.get();
		cin.get();
		system("cls");
		goto begin;
	}
	else if (str[0] == '4') {
		cout << "请输入删除的图书编号:" << endl;
		if (head == NULL) {
			cout << "图书库是空的，请添加图书" << endl << "按回车返回主界面" << endl;
			cin.get();
			cin.get();
			system("cls");
			goto begin;
		}
		string num;
		cin >> num;
		while (!check_input_is_number(num)) {
			cout << "请输入数字1-9" << endl;
			cin >> num;
		}
		int num1 = atoi(num.c_str());
		Delete(head, num1);
		cout << "操作成功" << "按回车返回主程序" << endl;
		cin.get();
		cin.get();
		system("cls");
		goto begin;
	}
	else if (str[0] == '5') {
		if (head == NULL) {
			cout << "图书库是空的，请添加图书" << endl << "按回车返回主界面" << endl;
			cin.get();
			cin.get();
			system("cls");
			goto begin;
		}
		cout << "图书数目共有:" << getBooknum(head) << endl;
		cout << "按回车返回主界面" << endl;
		cin.get();
		cin.get();
		system("cls");
		goto begin;
	}
	else {
		if (str[0] != 'Q'&&str[0] != 'q') {
			cout << "请输入数字！按回车继续。" << endl;
		}
	}
	if (str[0] != 'Q'&&str[0] != 'q') {
		cin.get();
		cin.get();
		system("cls");
		goto begin;
	}
}


//抽象类介绍
class Human {
public:
	Human() {
		cout << "构造Human" << endl;
	}
	virtual void smart() = 0;
	virtual void beautiful() = 0;
	virtual ~Human() {
		cout << "析构Human" << endl;
	}
};
class father:virtual public Human {
public:
	father() {
		cout << "构造father" << endl;
	}
	void smart() {
		cout << "父亲很重名" << endl;
	}
	virtual void beautiful() {
		cout << "父亲也很帅" << endl;
	}
	virtual ~father() {
		cout << "析构father" << endl;
	}
};
class mother:public virtual Human {
public:
	mother() {
		cout << "构造mother" << endl;
	}
	virtual void beautiful() {
		cout << "母亲很漂亮" << endl;
	}
	virtual ~mother() {
		cout << "析构mother" << endl;
	}
	virtual void smart() {
		cout << "母亲也很聪明." << endl;
	}
};

class son :public father,public mother {
public:
	son() {
		cout << "构造son" << endl;
	}
	virtual void beautiful() {
		cout << "儿子也很帅" << endl;
	}
	virtual ~son() {
		 cout << "析构son" << endl;
	}
	 virtual void smart() {
		 cout << "儿子也聪明" << endl;
	 }

};
void main_ABS() {
	//father *pf;
	//mother *pm;
	Human *p;
	int choice = 0;

	while (choice < 99) {
		bool quilt = false;
		cout << "0退出1父亲2儿子3母亲" << endl;
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
			cout << "请输入0-2之间的数字" << endl;
			break;
		}
		if (quilt) {
			break;
		}

	}
	cout << "程序结束" << endl;
	cin.get();
	cin.get();
}



//抽象类应用
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
		cout << "(0)退出(1)三角形（2）正方形(3)圆形" << endl;
		cout << "请选择:";
		cin >> choice;
		switch (choice) {
		case 0:
			quit = true;
			break;
		case 1:
			p = new Trigon(5.0,6.0);
			cout << "三角形面积为:" << p->area() << endl;
			break;
			case 2:
				p = new Square(70.0,70.0);
				cout << "正方形面积为:" << p->area() << endl;
				break;
			case 3:
				p = new Circle(9.0);
				cout << "圆形面积为:" << p->area() << endl;
				break;
			default:
				cout << "请输入0-3之间的数字" << endl;
				break;
		}
		if (choice<4&&choice>0) {
			delete p;
		}
		if (quit) {
			break;
		}
	}
	cout << "运行结束。" << endl;
	return 1;
}

//复杂的抽象类
class Animal {
public:
	Animal(int); 
	virtual ~Animal() {
		cout << "析构animal" << endl;
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
		cout << "创建动物..." << endl;
}

class Mammalia :public Animal {
public :
	Mammalia(int age) :Animal(age) {
		cout << "创建哺乳类..." << endl;
	}
	virtual ~Mammalia() {
		cout << "析构Mammalia" << endl;
	}
	virtual void Propagate() {
		cout << "哺乳类是胎生动物，通过胚胎来繁殖后代" << endl;
	}
};
class Brid :public Animal {
public:
	Brid(int age) :Animal(age) {
		cout << "创建鸟类..." << endl;
	}
	 ~Brid() {
		cout << "析构Brid" << endl;
	}
	 void Sleep() { cout << "鸟在草里睡觉" << endl; }
	 void Move() { cout << "鸟两条腿走路" << endl; }
	 void Propagate() { cout << "鸟是通卵生动物" << endl; }
	 void Body() { cout << "鸟身体很瘦" << endl; }
	 void Eat() { cout << "鸟是杂草食类动物" << endl; }
	 void Show() { cout << "鸟体表很多毛" << endl; }

};

class Pig :public Mammalia {
public:
	Pig(int age) :Mammalia(age) {
		cout << "创建猪类..." << endl;
	}
	 ~Pig() {
		cout << "析构Pig" << endl;
	}
	  void Sleep() { cout << "猪在泥里睡觉" << endl; }
	  void Move() { cout << "猪四条腿走路" << endl; }
	  void Propagate() { cout << "猪也是通过胚胎繁殖后代" << endl; }
	  void Body() { cout << "猪身体很肥" << endl; }
	  void Eat() { cout << "猪是杂食类动物" << endl; }
	  void Show() { cout << "猪体表很多毛" << endl; }

};

class Human2 :public Mammalia {
public:
	Human2(int age) :Mammalia(age) {
		cout << "创建人类..." << endl;
	}
	 ~Human2() {
		cout << "析构Huaman2" << endl;
	}
	 void Sleep() { cout << "人在床上睡觉" << endl; }
	 void Move() { cout << "人两条腿走路" << endl; }
	 void Propagate() { cout << "人也是通过胚胎繁殖后代" << endl; }
	 void Body() { cout << "人身体很肥" << endl; }
	 void Eat() { cout << "人是杂食类动物" << endl; }
	 void Show() { cout << "人体表很少毛" << endl; }
};

void main_fuzaclass() {
	Animal *p = NULL;
	int chosic = 0;
	while (1) {
		bool quilt = false;
		cout << "(0)退出(1)人类(2)鸟类(3)猪类" << endl;
		cin >> chosic;
		switch (chosic) {
		case 0:
			quilt = true;
			break;
		case 1:
			p = new Human2(80);
			cout << "人类寿命为:" << p->GetAge() << endl;
			break;
		case 2:
			p = new Brid(50);
			cout << "鸟类寿命为:" << p->GetAge() << endl;
			break;
		case 3:
			p = new Pig(1);
			cout << "猪类寿命为:" << p->GetAge() << endl;
			break;
		default:{
			cout << "请输入0-3之间的数字" << endl;
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
	_my_string_(); //建立一个空的字符串类
	~_my_string_();
	_my_string_(const char * const ch);//构造函数给字符串赋值
	char &operator[](unsigned short int len);//[]运算符重载限制数组越界
	char operator[](unsigned short int len)const;//常量对象
	_my_string_ &operator=(const _my_string_ &s);//=赋值运算符重载
	const char *_getstr_()const; 
	int _getlen_()const; 
	_my_string_(const _my_string_ &rs);//重写复制构造函数实现字符串的复制
	friend ostream &operator<<(ostream &o, const _my_string_&s);//输入输出运算符重载，功能和_getstr_()一样
	friend istream &operator>>(istream &i, _my_string_&s);
	friend bool operator<(const _my_string_ &str1, const _my_string_ &str2);
	friend bool operator>(const _my_string_ &str1, const _my_string_ &str2);
	friend bool operator==(const _my_string_ &str1, const _my_string_ &str2);//当运算符重载函数定义为成员函数是，二元运算符只带一个参数，加上friend定义为友元函数，而非成员函数
	_my_string_ operator+(const _my_string_ &s);
	void operator+=(const _my_string_ &s);
private:
	unsigned short int length;//长度不会出现负数，这样定义可以避免
	char *str;
	_my_string_(unsigned short int);//放在私有中，防止其他函数调用声明堆空间
};

_my_string_::_my_string_() {//建立一个空的字符串类
	length = 0;
	str = new char[1];
	str[0] = '\0';
}
_my_string_::~_my_string_() {
	delete []str;
	length = 0;
}
_my_string_::_my_string_(const char * const ch) {//构造函数给字符串赋值
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

char & _my_string_::operator[](unsigned short int len) {//[]运算符重载限制数组越界
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