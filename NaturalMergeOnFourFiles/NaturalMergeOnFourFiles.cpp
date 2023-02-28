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
bool checkOnSorted(const std::string& fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open()) {
		throw("Error open file");
		return false;
	}		
	int value;
	int tmp;
	file >> tmp;
	while (file >> value) {
		if (tmp > value) {
			return false;
		}
		tmp = value;
	}
}
int split(const std::string& fileName)
{
	int x, y;
	int flag = 0;
	const int n = 2;
	std::ifstream file(fileName);
	if (!file.is_open()) {
		throw("Ошибка открытия");
	}
	std::ofstream* fileA = new std::ofstream[n];
	for (int i = 0; i < n; i++) {
		std::string fileNameA = "fileA" + std::to_string(i) + ".txt";
		fileA[i].open(fileNameA);
	}
	for (int i = 0; i < n; i++) {
		if (!fileA[i].is_open())
			throw("Ошибка открытия");
	}
	file >> x; // 1 7 4 0 9 4 8 8 2 4 
	while (!file.eof()) {
		fileA[flag] << x << ' ';
		while (file >> y and x <= y) { // 1 7 0 9 2 4
			fileA[flag] << y << ' ';   // 4 4 8 8 
			x = y;
		}
		x = y;
		flag = 1 - flag;
	}
	file.close();
	for (int i = 0; i < n; i++) {
		fileA[i].close();
	}
	std::cout << "split is done\n";
}
void merge(std::fstream* fileA, std::fstream* fileB)
{

	int h;
	int flag = 0;
	const int n = 2;
	int x[n];
	int y[n];
	
	//F:  1 7 4 0 9 4 8 8 2 4 			
	//A0: 1 7 | 0 9 | 2 4 | 
	//A1: 4 | 4 8 | 8 |		
	//B0: 1 4 7 | 2 4 8 |	->	A0: 0 1 4 4 7 8 9	->	B0: 0 1 2 4 4 7 8 8 9
	//B1: 0 4 8 9 |				A1: 2 4 8

	fileA[0] >> x[0];
	fileA[1] >> x[1];
	while (!fileA[0].eof() || !fileA[1].eof()) {
		std::cout << "merging..\n";
		if (x[0] < x[1]) {
			h = 0;
		}
		else {
			h = 1;
		}
		fileB[flag] << x[h] << ' ';
		fileA[h] >> y[h];
		if (x[h] < y[h]) {
			x[h] = y[h];
		}
		else {
			fileB[flag] << x[1 - h] << ' ';
			fileA[1 - h] >> y[1 - h];
			while (x[1 - h] < y[1 - h]) {
				x[1 - h] = y[1 - h];
				fileB[flag] << x[1 - h] << ' ';
				fileA[1 - h] >> y[1 - h];
			}
			x[1 - h] = y[1 - h];
			x[h] = y[h];
			flag = 1 - flag;
		}	
	}
	if (!fileA[0].eof()) {
		while (!fileA[0].eof()) {
			fileB[flag] << x[0] << ' ';
			fileA[0] >> x[0];
		}
	}
	if (!fileA[1].eof()) {
		while (!fileA[1].eof()) {
			fileB[flag] << x[1] << ' ';
			fileA[1] >> x[1];
		}
	}
	for (int i = 0; i < n; i++) {
		fileA[i].close();
		fileB[i].close();
	}
	std::cout << "merge is done\n";
}
void sortFile(const std::string& fileName)
{
	const int n = 2;
	std::ifstream file(fileName);
	if (!file.is_open()) {
		throw("Ошибка открытия\n");
	}	
	std::fstream* fileA = new std::fstream[n];
	std::fstream* fileB = new std::fstream[n];

	split(fileName);

	
	for (int i = 0; i < n; i++) {
		std::string fileNameA = "fileA" + std::to_string(i) + ".txt";
		std::string fileNameB = "fileB" + std::to_string(i) + ".txt";
		fileA[i].open(fileNameA, std::ios::in);
		fileB[i].open(fileNameB, std::ios::out);
	}
	for (int i = 0; i < n; i++) {
		if (!fileB[i].is_open() || !fileA[i].is_open())
			throw("Ошибка открытия");
	}
	merge(fileA, fileB);
	for (int i = 0; i < n; i++) {
		fileA[i].close();
		fileB[i].close();
	}


	for (int i = 0; i < n; i++) {
		std::string fileNameA = "fileA" + std::to_string(i) + ".txt";
		std::string fileNameB = "fileB" + std::to_string(i) + ".txt";
		fileA[i].open(fileNameA, std::ios::out);
		fileB[i].open(fileNameB, std::ios::in);
	}
	for (int i = 0; i < n; i++) {
		if (!fileB[i].is_open() || !fileA[i].is_open())
			throw("Ошибка открытия");
	}
	merge(fileB, fileA);
	for (int i = 0; i < n; i++) {
		fileA[i].close();
		fileB[i].close();
	}
	for (int i = 0; i < n; i++) {
		std::string fileNameA = "fileA" + std::to_string(i) + ".txt";
		std::string fileNameB = "fileB" + std::to_string(i) + ".txt";
		fileA[i].open(fileNameA, std::ios::in);
		fileB[i].open(fileNameB, std::ios::out);
	}
	for (int i = 0; i < n; i++) {
		if (!fileB[i].is_open() || !fileA[i].is_open())
			throw("Ошибка открытия");
	}
	merge(fileA, fileB);
	for (int i = 0; i < n; i++) {
		fileA[i].close();
		fileB[i].close();
	}
}

int main()
{
	int numCount = 10;
	int maxNum = 10;
	std::string fileName = "file.txt";
	//std::string fileName = "test.txt";
	createFileWithRandNum(fileName, numCount, maxNum);
	sortFile(fileName);
}