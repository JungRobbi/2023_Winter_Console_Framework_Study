#include <iostream>
#include <vector>

using namespace std;

typedef float GLFLOAT;
typedef unsigned int UINT;
typedef unsigned int 정수형;
typedef unsigned int 이동재;

정수형 a;
이동재 a;

enum E_MY_ENUM1 { // 열거형 상수형
	A, B, C, D, E,
	J = 110, U, I
};

enum class E_MY_ENUM2 { // 열거형 상수형 신버전
	A, B, C, D, E,
	J = 110, U, I
};


class MY_CLASS {
	int a = 1;
public:
	//기본 생성자
	MY_CLASS() { std::cout << "안녕하세요 기본 생성자입니다." << std::endl; }

	//생성자 (인자가 있는)
	MY_CLASS(int i) { 
		a = i;
		std::cout << "안녕하세요 생성자입니다." << std::endl; 
	}
	
	//복사 생성자
	MY_CLASS(const MY_CLASS& rhs) 
	{
		a = rhs.a;
		std::cout << "안녕하세요 복사 생성자입니다." << std::endl;
	}
	
	//복사 할당 연산자
	MY_CLASS& operator=(const MY_CLASS& rhs)
	{
		a = rhs.a;
		std::cout << "안녕하세요 복사 할당 연산자입니다." << std::endl;
		return *this;
	}

	//소멸자
	virtual ~MY_CLASS() { std::cout << "안녕하세요 소멸자입니다." << std::endl; }

};

class Child1 : public MY_CLASS {
};

class Child2 : public MY_CLASS {
};

class Child3 : public MY_CLASS {
};

int main()
{
	MY_CLASS a{ 2 }; // 생성자
	MY_CLASS b{ a }; // 복사 생성자

	MY_CLASS* object;

	MY_CLASS* object = new MY_CLASS{}; // 선호
	MY_CLASS* object = new MY_CLASS(); // 비선호
	
	MY_CLASS* monsterGoblin;
	MY_CLASS* monsterSkull;
	MY_CLASS* mosterOgre;

	// p == nullptr
	if (nullptr == dynamic_cast<Child1*>(objects[0])) {
		cout << "Child1 맞아유" << endl;
	}
	else {
		cout << "Child1 아닙니다." << endl;
	}

}























// #include "stdafx.h"
// #include "libxl.h"

//int main() {
//    // 엑셀 파일 열기
//    libxl::Book* book = xlCreateBook();
//    if (book->load(L"test.xlsx")) {
//        // 원하는 시트 선택
//        libxl::Sheet* sheet = book->getSheet(0); // 첫 번째 시트 선택
//
//        // 특정 셀에서 데이터 읽기
//        double data = sheet->readNum(0, 1); // 예: 두 번째 행, 두 번째 열의 숫자 데이터
//
//        // 데이터 출력
//        std::cout << "불러온 데이터: " << data << std::endl;
//    }
//    else {
//        std::cerr << "엑셀 파일 열기 실패" << std::endl;
//    }
//
//    // 메모리 해제
//    book->release();
//
//    return 0;
//}