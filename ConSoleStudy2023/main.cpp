#include "stdafx.h"
#include "Input.h"



int main(int argc, char** argv)
{
	while (true) {
		Input::Update();
		

		if (Input::keys['q']) {
			cout << "qqqqqqqq" << endl;
		}
	}
}