#include "stdafx.h"
#include "Input.h"



int main(int argc, char** argv)
{
	while (true) {
		Input::Update();
		
		if (Input::keys[224]) { // ��/��/��/��
			if (Input::keys[72]) {
				cout << "��" << endl;
			}
			if (Input::keys[80]) {
				cout << "�Ʒ�" << endl;
			}
			if (Input::keys[75]) {
				cout << "��" << endl;
			}
			if (Input::keys[77]) {
				cout << "��" << endl;
			}
		}
	}
}