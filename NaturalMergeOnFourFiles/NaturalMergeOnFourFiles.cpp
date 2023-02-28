#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <ios>


bool createFileWithRandNum(const std::string& fileName, const int numCount, const int maxNum)
{
	std::ofstream file(fileName);
	if (!file.is_open())
		return false;
	for (int i = 0; i < numCount; i++)
	{
		int x = rand() % maxNum;
		file << x << ' ';
	}
}
bool fileSortedArray(const std::string& fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
		return false;

	int value;
	int count = 0;
	while (file >> value) {
		count++;
	}

	std::ifstream input(fileName);
	int* mas = new int[count];
	for (int i = 0; i < count; i++) {
		input >> mas[i];
	}

	for (int i = 1; i < count; i++) {
		//std::cout << mas[i];
		if (mas[i] < mas[i - 1])
			return false;
	}

}
bool checkOnSorted(const std::string& fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open()) {
		throw("Error open file");
		return false;
	}		
	int value;
	while (file >> value) {
		int tmp = value;
		while (file >> value) {
			if (tmp > value) {
				return false;
			}
			tmp = value;
		}
	}
}


int main()
{

}