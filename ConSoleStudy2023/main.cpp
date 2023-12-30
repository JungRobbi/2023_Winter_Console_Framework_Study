#include "stdafx.h"
#include "Input.h"



int main(int argc, char** argv)
{
	while (true) {
		Input::Update();
		
		if (Input::keys[224]) { // ¡è/¡é/¡ç/¡æ
			if (Input::keys[72]) {
				cout << "À§" << endl;
			}
			if (Input::keys[80]) {
				cout << "¾Æ·¡" << endl;
			}
			if (Input::keys[75]) {
				cout << "¿Þ" << endl;
			}
			if (Input::keys[77]) {
				cout << "¿À" << endl;
			}
		}
	}
}