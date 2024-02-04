#pragma once
#include "stdafx.h"
#include "UI.h"
class UIMGR
{
	std::list<std::shared_ptr<UI>> uiList;

private:
	UIMGR() = default;
	UIMGR(const UIMGR&) = delete;
	UIMGR& operator=(const UIMGR&) = delete;
	UIMGR(UIMGR&&) = delete;
	UIMGR& operator=(UIMGR&&) = delete;
	~UIMGR() = default;
public:
	static UIMGR& GetInstance();
	void Initialize();
	void Update(double elapsedTime);

	template<class T>
	std::shared_ptr<T> AddUI();
};

template<class T>
inline std::shared_ptr<T> UIMGR::AddUI()
{
	std::shared_ptr<T> ui = make_shared<T>();
	ui->Start();
	uiList.emplace_back(ui);
	return ui;
}
