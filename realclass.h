#pragma once
#include <string> // подключаем строки string
#include <iostream> // подключаем cout
#include <set>
#include <iterator>
#include <ctime>

using namespace std;

class Dogs //создаем класс 
{
	multiset<int> years; //возраст собак с повторяющимися данными
	set<int> years_; //возраст собак без повторяющихся данных
	multiset<string> name; //клички
public:
	Dogs() {}
	Dogs(multiset<int> years, set<int> years_, multiset<string> name) {
		this->years = years;
		this->years_ = years_;
		this->name = name;
	}
	void Years() //метод возраста
	{
		system("color E");
		cout << "Возраста собак" << endl;
		for (int i = 0; i < 20; i++) {
			int random = rand() % 15 + 1; //рандомная генерация возраста
			years.insert(random); 
			years_.insert(random);
			cout << i + 1 << "(dog)- " << random << " y.o." << endl; 
			//выводим ^ сгенерированный возраст
			if (i % 2 == 0)
			{
				cout << "\t\t"; //добавляем пробелы при четности
			} 
		}

		multiset <int> ::iterator it = years.begin();
		// добавляем ^ итератор

		multiset <int> ::reverse_iterator is = years_.rbegin();
		//реверсивный ^ итератор

		cout << "\nСортировка по возрастанию: " << endl;
		for (int i = 1; it != years.end(); i++, it++) {
			cout << *it << " ";
		}
		cout << endl;
		int x;
		cout << "\nВведите любой возраст для манипуляций\n";
		cin >> x;
		it = years_.upper_bound(x);
		/* итератору присваивается значение по возрастанию
		следующего числа после заданного пользователем */	
	
		if (*is != x)
		{
			cout << "\nВозраста собак старше:\n ";
			for (int i = 1; it != years_.end(); i++, it++)
			{
				cout << *it << "  ";
			}
		}
		else
			cout << "\nСобак старше в приюте не наблюдается!\n";

		//if (*is < x)
		int h = 0;
			cout << "\nВозраста собак младше:\n ";
				for (int i = 1; is != years_.rend(); ++is, i++)
				{
					if (*is < x)
					{
						cout << *is << " ";
						h++;
					}
				}
			if( h == 0)
			{ 
				cout << "Собак младше в приюте не наблюдается!\n";
			}
		cin.get();
	}


	void Name()
	{
		system("color B");
		name.insert("Keyly"); name.insert("Hell"); name.insert("Luky");	name.insert("Hope");
		name.insert("Dag");	 name.insert("Hell");	name.insert("Ketty");  	name.insert("Luky");
		name.insert("Joj");  name.insert("Dag");	name.insert("Oni");  name.insert("Luky");
		name.insert("Olli"); name.insert("Ketty"); name.insert("Mone"); name.insert("Lip");
		name.insert("Hope"); name.insert("Bag"); name.insert("Hell"); name.insert("Kok");

		string n;
		cout << "Введите имя собаки, которую хотите найти\n";
		cin >> n;
		multiset  <string> ::iterator it = name.begin();

		int k;
		for (int i = 1; it != name.end(); i++, it++)
		{
			if (name.find(n) == name.end())
			{
				cout << "\nСобаки с такой кличкой в приюте не наблюдается\n";
				cin.get();
				break;
			}
			else
			{
				it = name.find(n);
				cout << "Собака по кличке " << *it << " существует\n";
				cin.get();
				break;
			}
		}
		it = name.begin();
		cout << "\nВсе имена собак" << endl;
		for (int i = 1; it != name.end(); i++, it++)
		{
			cout << *it << " ";
		}
		cout << "\n\nВведите имя собаки, которая нашла свой дом\n";
		string nm;
		cin >> nm; 
		it = name.find(nm);

		if (!name.count(nm)) {
			cout << "\nСобаки с такой кличкой в приюте не наблюдается\n" << endl;
		}
		name.erase(it);
		it = name.begin();

		cout << "\nОбновленный список\n";
		for (int i = 1; it != name.end(); i++, it++)
		{
			cout << *it << " ";
		}
		cin.get();
	}
};
