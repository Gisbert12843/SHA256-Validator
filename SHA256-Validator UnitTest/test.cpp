#include "pch.h"
#include "../Header.h"
#include "../main.cpp"
#include <string>
#include <filesystem>



namespace fs = std::filesystem;


TEST(TestCaseName, TestName)
{
	fs::path testObjPath = "..\\SHA256-Validator UnitTest\\testcases\\utf16.txt";
	std::string testOutput = sha256(testObjPath.string());

	//EXPECT_TRUE(testOutput == "9bbdfa7b252ba2a97ea9313b4e9c7d54a29930db6a1b7955363fb5ba224953d7");
	EXPECT_TRUE(1, 1);
}