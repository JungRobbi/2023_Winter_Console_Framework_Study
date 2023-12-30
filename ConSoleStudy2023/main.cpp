#include "stdafx.h"
#include "Input.h"
#include "Scene.h"

int main(int argc, char** argv)
{
	shared_ptr<Scene> scene = make_shared<Scene>();
	scene->Initialize();
	Input::Initialize();

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

		scene->Update();
		scene->Render();
	}
}