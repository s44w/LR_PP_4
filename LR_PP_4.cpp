//10 вариант: найти отношение прописных букв к строчным
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;

//Посчитать процентное соотношение строчных и прописных букв. 

string file_choose()
{
	/*
	Функция, позволяет выбрать файл.
	Пользователь вводит название, если файл с таким названием существует, то вовзвращает его в string.
	*/
	string name;
	bool ok = true;
	while (ok)
	{

		getline(cin, name);

		ifstream file;
		file.open("d:\\texts\\" + name + ".txt");

		if (file)
		{
			file.close();
			return name;
		}
		else cout << '\n' << "Error! Input correct name!" << endl;
	}
}


vector <char> file_reading_vector(ifstream& file)
{
	/*
	Функция, читает содержимое файла и переносит его в вектор char пока не натыкается на EOF
	Аргументы:
	data: vector <char> - вектор, в который мы :
		file: ifstream& - ссылка на поток ввода
	Выводит:
		data: vector <char> - вектор текста из файла
	*/
	vector < char > data;
	char symb;
	while ((symb = file.get()) != EOF) 
		data.push_back(symb);
	file.close();

	return data;
}



string file_reading_string(ifstream& file)
{
	/*
	Функция, читает содержимое файла и переносит его в string symbols пока не натыкается на EOF
	Аргументы:
	data: vector <char> - вектор, в который мы :
		file: ifstream& - ссылка на поток ввода
	Выводит:
		symbols: string  - строка текста из файла
	*/
	char symb;
	string symbols;
	while ( (symb = file.get()) !=EOF)
		symbols.push_back(symb);
	
	file.close();
	return symbols;
}



void output(vector <char>& data) //выводим данные из файла через вектор
{
	cout << '\n' << "Your text is: " << endl;
	for (int i = 0; i < data.size(); ++i) {
		cout << data[i];
	}
}

void output(string& data) //выводим данные из файла через строку
{
	cout << '\n' << "Your string text is: " << '\n' << endl;
	for (auto c: data) {
		cout << c;
	}
}

pair <int, int> calculations_vec(vector <char>& data) //считаем символы в векторе
{
	int upper_count = 0, lower_count = 0;
	for (auto c : data)
	{
		if (isupper(c)) upper_count += 1;
		if (islower(c)) lower_count += 1;
	}
	return make_pair(upper_count, lower_count);
}


pair <int, int> calculations_str(string& symbols) //считаем символы в строке
{
	int upper_count = 0, lower_count = 0;
	for (auto c : symbols)
	{
		if (isupper(c)) upper_count += 1;
		if (islower(c)) lower_count += 1;
	}
	return make_pair(upper_count, lower_count);
}



void time_and_action(string& file_name, vector <char>& data, string& symbols, int& upper_count, int& lower_count, int& time_sum_vec, int& time_sum_str)
{
	/*
	Функция, считает время работы с файлом через vector <char>  и  через string
	Аргументы:
		data: vector <char> - вектор, в который мы загружаем символы из файла
		symbols: string - строка для того же
		***_count: int - счетчики прописных и строчных букв
		time_sum_***: int  -  суммы затраченного времени

	*/

	//считаем для vector 
	ifstream IVfile("d:\\texts\\" + file_name + ".txt");
	auto begin1 = chrono::steady_clock::now();

	data = file_reading_vector(IVfile);
	upper_count = calculations_vec(data).first; lower_count = calculations_vec(data).second;

	auto end1 = chrono::steady_clock::now();
	auto elapsed_ms1 = chrono::duration_cast<chrono::nanoseconds>(end1 - begin1);


	//считаем для string
	ifstream ISfile("d:\\texts\\" + file_name + ".txt");
	auto begin2 = chrono::steady_clock::now();

	symbols = file_reading_string(ISfile);
	upper_count = calculations_str(symbols).first; lower_count = calculations_str(symbols).second;

	auto end2 = chrono::steady_clock::now();
	auto elapsed_ms2 = chrono::duration_cast<chrono::nanoseconds>(end2 - begin2);

	time_sum_vec += elapsed_ms1.count();
	time_sum_str += elapsed_ms2.count();
}


void time_output(int& upper_count, int& lower_count, int& time_sum_vec, int& time_sum_str, ofstream& ofile)
{
	/*
	Функция, выводит информацию 

	Аргументы: 
		***_count: int - счетчики прописных и строчных букв
		time_sum_***: int  -  суммы затраченного времени
		ofile: ofstream&  -  поток ввода в файл
 	*/

	if (upper_count != 0) {
		cout << '\n' << '\n' << "Upper to all symbols percentage is: " << upper_count * 100 / (lower_count + upper_count) << "%" << endl;
		ofile << ' ' << upper_count * 100 / (lower_count + upper_count) << "%";
	}

	else cout << '\n' << "Error! There are no upper symbols in this file" << endl;

	double diff = (time_sum_vec / 10.0) / (time_sum_str / 10.0);

	cout << '\n' << "Average time of vector method is: " << time_sum_vec / 10 << "ns" << endl;
	cout << '\n' << "Average time of string method is: " << time_sum_str / 10 << "ns" << endl;
	cout << '\n' << "String method is " << diff << "x faster" << endl;
	ofile.close();
}


bool YN_function() {
	char buffer[100];
	bool ok = true;
	cout << "Do you want to continue? Write 'Y' or 'N': " << endl;
	while (ok) {

		cin >> buffer;
		if (buffer[0] == 'Y' && buffer[1] == '\0') return true;
		if (buffer[0] == 'N' && buffer[1] == '\0') return false;
		else cout << "Error! Try again!" << endl;
	}
}



int main()
{
	bool finish = true;
	while (finish)
	{
		int upper_count, lower_count, time_sum_vec = 0, time_sum_str = 0;

		cout << "Input file`s name:  ('input1' or 'input2' or 'input3')" << endl;
		string file_name = file_choose();

		vector <char> data; string symbols;


		for (int i = 0; i < 10; ++i)
			time_and_action(file_name, data, symbols, upper_count, lower_count, time_sum_vec, time_sum_str);

		output(data);
		//output(symbols);

		ofstream ofile("d:\\texts\\" + file_name + ".txt", ios::app);

		time_output(upper_count, lower_count, time_sum_vec, time_sum_str, ofile);
		

		finish = YN_function();
	}
}