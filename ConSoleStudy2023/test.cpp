#include <iostream>
#include <vector>

using namespace std;

typedef float GLFLOAT;
typedef unsigned int UINT;
typedef unsigned int ������;
typedef unsigned int �̵���;

������ a;
�̵��� a;

enum E_MY_ENUM1 { // ������ �����
	A, B, C, D, E,
	J = 110, U, I
};

enum class E_MY_ENUM2 { // ������ ����� �Ź���
	A, B, C, D, E,
	J = 110, U, I
};


class MY_CLASS {
	int a = 1;
public:
	//�⺻ ������
	MY_CLASS() { std::cout << "�ȳ��ϼ��� �⺻ �������Դϴ�." << std::endl; }

	//������ (���ڰ� �ִ�)
	MY_CLASS(int i) { 
		a = i;
		std::cout << "�ȳ��ϼ��� �������Դϴ�." << std::endl; 
	}
	
	//���� ������
	MY_CLASS(const MY_CLASS& rhs) 
	{
		a = rhs.a;
		std::cout << "�ȳ��ϼ��� ���� �������Դϴ�." << std::endl;
	}
	
	//���� �Ҵ� ������
	MY_CLASS& operator=(const MY_CLASS& rhs)
	{
		a = rhs.a;
		std::cout << "�ȳ��ϼ��� ���� �Ҵ� �������Դϴ�." << std::endl;
		return *this;
	}

	//�Ҹ���
	virtual ~MY_CLASS() { std::cout << "�ȳ��ϼ��� �Ҹ����Դϴ�." << std::endl; }

};

class Child1 : public MY_CLASS {
};

class Child2 : public MY_CLASS {
};

class Child3 : public MY_CLASS {
};

int main()
{
	MY_CLASS a{ 2 }; // ������
	MY_CLASS b{ a }; // ���� ������

	MY_CLASS* object;

	MY_CLASS* object = new MY_CLASS{}; // ��ȣ
	MY_CLASS* object = new MY_CLASS(); // ��ȣ
	
	MY_CLASS* monsterGoblin;
	MY_CLASS* monsterSkull;
	MY_CLASS* mosterOgre;

	// p == nullptr
	if (nullptr == dynamic_cast<Child1*>(objects[0])) {
		cout << "Child1 �¾���" << endl;
	}
	else {
		cout << "Child1 �ƴմϴ�." << endl;
	}

}























// #include "stdafx.h"
// #include "libxl.h"

//int main() {
//    // ���� ���� ����
//    libxl::Book* book = xlCreateBook();
//    if (book->load(L"test.xlsx")) {
//        // ���ϴ� ��Ʈ ����
//        libxl::Sheet* sheet = book->getSheet(0); // ù ��° ��Ʈ ����
//
//        // Ư�� ������ ������ �б�
//        double data = sheet->readNum(0, 1); // ��: �� ��° ��, �� ��° ���� ���� ������
//
//        // ������ ���
//        std::cout << "�ҷ��� ������: " << data << std::endl;
//    }
//    else {
//        std::cerr << "���� ���� ���� ����" << std::endl;
//    }
//
//    // �޸� ����
//    book->release();
//
//    return 0;
//}