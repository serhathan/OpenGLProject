#pragma once
#include <functional>
#include <vector>
#include <string>

namespace test
{
	class Test
	{
	public:
		Test(){}
		virtual ~Test(){}

		virtual void OnUpdate(float deltatime){}
		virtual void OnRender(){}
		virtual void OnImGuiRender(){}
	};
	
	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& currentTestPtr);

		void OnImGuiRender()override;
	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string,std::function<Test*()>>> m_Tests;
	};



}
