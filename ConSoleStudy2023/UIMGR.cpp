#include "UIMGR.h"

UIMGR& UIMGR::GetInstance()
{
	static UIMGR instance;
	return instance;
}

void UIMGR::Initialize()
{
	uiList = std::list<std::shared_ptr<UI>>{};
}

void UIMGR::Update(double elapsedTime)
{
	for (auto& ui : uiList) {
		ui->Update(elapsedTime);
	}
}

void UIMGR::Render()
{
	for (auto& ui : uiList) {
		ui->Render();
	}
}

void UIMGR::Clear()
{
	uiList.clear();
}
