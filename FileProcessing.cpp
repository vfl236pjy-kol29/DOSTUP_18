#include <fstream>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

class User
{
	string _name;
	string _login;
	string _pass;

public:
	User(string name, string login, string pass) :_name(name), _login(login), _pass(pass) {}

	friend fstream& operator >>(fstream& is, User& obj);
	friend ostream& operator <<(ostream& os, const User& obj);
};

fstream& operator >>(fstream& is, User& obj)
{
	is >> obj._name;
	is >> obj._login;
	is >> obj._pass;
	return is;
}
ostream& operator <<(ostream& os, const User& obj)
{
	os << obj._name;
	os << ' ';
	os << obj._login;
	os << ' ';
	os << obj._pass;
	return os;
}

class Message
{
	string _text;
	string _sender;
	string _receiver;

public:
	Message(string text, string sender, string receiver) :_text(text), _sender(sender), _receiver(receiver) {}

	friend fstream& operator >>(fstream& lup, Message& bip);
	friend ostream& operator <<(ostream& cup, const Message& bip);

};

fstream& operator >>(fstream& lup, Message& bip)
{
	lup >> bip._text;
	lup >> bip._sender;
	lup >> bip._receiver;
	return lup;
}
ostream& operator <<(ostream& cup, const Message& bip)
{
	cup << bip._text;
	cup << ' ';
	cup << bip._sender;
	cup << ' ';
	cup << bip._receiver;
	return cup;
}

void demo_perms (fs::perms p)
{
	std::cout << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
		<< ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
		<< ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-")
		<< ((p & fs::perms::group_read) != fs::perms::none ? "r" : "-")
		<< ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
		<< ((p & fs::perms::group_exec) != fs::perms::none ? "x" : "-")
		<< ((p & fs::perms::others_read) != fs::perms::none ? "r" : "-")
		<< ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
		<< ((p & fs::perms::others_exec) != fs::perms::none ? "x" : "-")
		<< '\n';
}


int main()
{
	fstream user_file = fstream("users.txt", ios::in | ios::out);
	if (!user_file)
		// Для создания файла используем параметр ios::trunc
		user_file = fstream("users.txt", ios::in | ios::out | ios::trunc);

	if (user_file) {
		User obj("Alex", "qwerty", "12345");

		demo_perms(fs::status("user.txt").permissions());
		fs::permissions("users.txt", fs::perms::owner_write | fs::perms::others_all, fs::perm_options::remove);

		// Запишем данные по в файл
		user_file << obj << endl;
		// Чтобы считать данные из файла, надо установить позицию для чтения в начало файла
		user_file.seekg(0, ios_base::beg);
		// Считываем данные из файла
		user_file >> obj;
		cout << obj << endl;
	}
	else
	{
		cout << "Could not open file users.txt !" << '\n';
	}


	return 0;
}