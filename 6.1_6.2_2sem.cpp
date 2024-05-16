#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

class Exhibit {
protected:
	char* name;
public:
	Exhibit()           // конструктор без параметров
	{
		name = new char[100];
		name[0] = 0;
	}
	Exhibit(const char* name)   // конструктор с параметром
	{
		this->name = _strdup(name);
	}
	Exhibit(const Exhibit& exh)    // конструктор копирования
	{
		name = _strdup(exh.name);
	}
	Exhibit(Exhibit&& exh) noexcept {              // конструктор перемещения
		name = exh.name;
		exh.name = nullptr;
	}
	Exhibit& operator = (const Exhibit& exh) { // оператор копирования
		delete[] name;
		name = _strdup(exh.name);

		return *this;
	}
	Exhibit& operator = (Exhibit&& exh) noexcept { // оператор перемещения
		delete[] name;
		name = exh.name;
		exh.name = nullptr;

		return *this;
	}
	virtual ~Exhibit()              // деструктор
	{
		delete[] name;
		name = nullptr;
		cout << "Destructor exhibit" << endl;
	}
protected:
	virtual void fill(istream& in)   // ввод Name 
	{
		cout << "> Enter Name: ";
		in.ignore();
		in.getline(name, 100);
	}

	//получение инф об обьекте
	virtual void print(ostream& out) const {
		out << "Type: " << get_type() << endl;
		out << "Name: " << name << endl;
	}

	// получение имени типа объекта
	virtual const char* get_type() const {
		return "Exhibit";
	}

	friend istream& operator>>(istream& in, Exhibit& exh)
	{	// просто вызываем виртуальную функцию вывода
		exh.fill(in);
		return in;
	}

	friend ostream& operator<<(ostream& out, const Exhibit& exh)
	{
		exh.print(out);
		return out;
	}
};

class Items : public Exhibit {
protected:
	int beginDate;
	int endDate;
public:
	Items() : Exhibit() { // пустой констр
		beginDate = 0;
		endDate = 0;
	}
	Items(const char* name, int beginDate, int endDate) : Exhibit(name) { // с параметрами констр
		this->beginDate = beginDate;
		this->endDate = endDate;
	}
	Items(const Items& item) : Exhibit(item) { // констр копирования
		beginDate = item.beginDate;
		endDate = item.endDate;
	}
	Items(Items&& item) noexcept : Exhibit(move(item)) { // констр перемещения
		beginDate = item.beginDate;
		endDate = item.endDate;

		item.beginDate = 0;
		item.endDate = 0;
	}
	Items& operator = (const Items& item) { // operator copy
		if (this != &item) {
			Items::operator=(item);
			beginDate = item.beginDate;
			endDate = item.endDate;
		}

		return *this;
	}
	Items& operator = (Items&& item) noexcept { // operator move
		if (this != &item) {
			Items::operator=(move(item));
			beginDate = item.beginDate;
			endDate = item.endDate;

			item.beginDate = 0;
			item.endDate = 0;
		}

		return *this;
	}
	virtual ~Items() override {
		cout << "Destructor items" << endl;
	}
protected:
	virtual void fill(istream& in) override {
		Exhibit::fill(in);
		cout << "Enter begin Date: " << endl;
		in >> beginDate;
		in.ignore();
		cout << "Enter end Date: " << endl;
		in >> endDate;
	}
	virtual void print(ostream& out) const override {
		Exhibit::print(out);
		cout << "Begin Date: " << beginDate << " - End Date: " << endDate << endl;
	}
	virtual const char* get_type() const override {
		return "Items";
	}
};

class Coin : public Items {
protected:
	double denomination;
public:
	Coin() : Items() { // empty constr
		denomination = 0.0;
	}
	Coin(const char* name, int beginDate, int endDate, double denomination) : Items(name, beginDate, endDate) { // with parametr
		this->denomination = denomination;
	}
	Coin(const Coin& coin) : Items(coin) { // copy constr
		denomination = coin.denomination;
	}
	Coin(Coin&& coin) noexcept : Items(move(coin)) { // move constr
		denomination = coin.denomination;

		coin.denomination = 0.0;
	}
	Coin& operator = (const Coin& coin) { // operator copy
		if (this != &coin) {
			Items::operator=(coin);
			denomination = coin.denomination;
		}

		return *this;
	}
	Coin& operator = (Coin&& coin) noexcept { // operator move
		if (this != &coin) {
			Items::operator=(move(coin));
			denomination = coin.denomination;

			coin.denomination = 0.0;
		}

		return *this;
	}
	virtual ~Coin() override {
		cout << "Destructor coin" << endl;
	}
protected:
	virtual void fill(istream& in) override {
		Items::fill(in);
		cout << "Enter denomination: " << endl;
		in >> denomination;
		in.ignore();
	}
	virtual void print(ostream& out) const override {
		Items::print(out);
		cout << "Denomination: " << denomination << endl;
	}
	virtual const char* get_type() const override {
		return "Coin";
	}
};

class ColdWeapon : public Items {
protected:
	char* material;
public:
	ColdWeapon() : Items() { // empty constr
		material = new char[100];
		material[0] = 0;
	}
	ColdWeapon(const char* name, int beginDate, int endDate, const char* material) : Items(name, beginDate, endDate) { // with parametr
		this->material = _strdup(material);
	}
	ColdWeapon(const ColdWeapon& weapon) : Items(weapon) { // copy constr
		material = _strdup(weapon.material);
	}
	ColdWeapon(ColdWeapon&& weapon) noexcept : Items(move(weapon)) { // move constr
		material = weapon.material;
		weapon.material = nullptr;
	}
	ColdWeapon& operator = (const ColdWeapon& weapon) { // copy operator
		if (this != &weapon) {
			delete[] material;
			Items::operator=(weapon);
			material = _strdup(weapon.material);
		}

		return *this;
	}
	ColdWeapon& operator = (ColdWeapon&& weapon) noexcept { // move operator
		if (this != &weapon) {
			Items::operator=(move(weapon));
			delete[] material;
			material = weapon.material;
			weapon.material = nullptr;
		}

		return *this;
	}
	virtual ~ColdWeapon() override {
		delete[] material;
		material = nullptr;
		cout << "Destructor ColdWeapon" << endl;
	}
protected:
	virtual void fill(istream& in) override {
		Items::fill(in);
		cout << "Enter material: " << endl;
		in.ignore();
		in.getline(material, 100);
	}
	virtual void print(ostream& out) const override {
		Items::print(out);
		cout << "Material of weapon: " << material << endl;
	}
	virtual const char* get_type() const override {
		return "Cold Weapon";
	}
};

class Art : public Exhibit {
protected:
	char* painting;
	int date;
public:
	Art() : Exhibit() { //empty consrt
		painting = new char[100];
		painting[0] = 0;
		date = 0;
	}
	Art(const char* name, const char* painting, int date) : Exhibit(name) { //with parametr
		this->painting = _strdup(painting);
		this->date = date;
	}
	Art(const Art& art) : Exhibit(art) { // copy constr
		painting = _strdup(art.painting);
		date = art.date;
	}
	Art(Art&& art) noexcept : Exhibit(move(art)) { // move constr
		painting = art.painting;
		date = art.date;

		art.painting = nullptr;
		art.date = 0;
	}
	Art& operator = (const Art& art) { // copy operator
		if (this != &art) {
			delete[] painting;
			Exhibit::operator=(art);
			painting = _strdup(art.painting);
			date = art.date;
		}

		return *this;
	}
	Art& operator = (Art&& art) noexcept { // move operator
		if (this != &art) {
			Exhibit::operator=(move(art));
			delete[] painting;
			painting = art.painting;
			date = art.date;

			art.painting = nullptr;
			art.date = 0;
		}

		return *this;
	}
	virtual ~Art() override {
		delete[] painting;
		painting = nullptr;
		cout << "Destructor Art" << endl;
	}
protected:
	virtual void fill(istream& in) override {
		Exhibit::fill(in);
		cout << "Enter what is shown: " << endl;
		in.ignore();
		in.getline(painting, 100);
		cout << "Enter date (year): " << endl;
		in >> date;
	}
	virtual void print(ostream& out) const override {
		Exhibit::print(out);
		cout << "Shown: " << painting << endl;
		cout << "Date: " << date << endl;
	}
	virtual const char* get_type() const override {
		return "Art";
	}
};

class Paintings : public Art {
protected:
	char* author;
public:
	Paintings() : Art() { // empty 
		author = new char[100];
		author[0] = 0;
	}
	Paintings(const char* name, const char* painting, int date, const char* author) : Art(name, painting, date) { // with
		this->author = _strdup(author);
	}
	Paintings(const Paintings& pn) : Art(pn) { // copy constr
		author = _strdup(pn.author);
	}
	Paintings(Paintings&& pn) noexcept : Art(move(pn)) { // move constr
		author = pn.author;
		pn.author = nullptr;
	}
	Paintings& operator = (const Paintings& pn) { // copy operator
		if (this != &pn) {
			Art::operator=(pn);
			delete[] author;
			author = _strdup(pn.author);
		}

		return *this;
	}
	Paintings& operator = (Paintings&& pn) noexcept { // move operator
		if (this != &pn) {
			Art::operator=(move(pn));
			delete[] author;
			author = pn.author;
			pn.author = nullptr;
		}

		return *this;
	}
	virtual ~Paintings() override {
		delete[] author;
		author = nullptr;
		cout << "Destructor paintings" << endl;
	}
protected:
	virtual void fill(istream& in) override {
		Art::fill(in);
		cout << "Write an author: " << endl;
		in.ignore();
		in.getline(author, 100);
	}
	virtual void print(ostream& out) const override {
		Art::print(out);
		cout << "Author: " << author << endl;
	}
	virtual const char* get_type() const override {
		return "Paintings";
	}
};

class Figurines : public Art {
protected:
	char* author;
public:
	Figurines() : Art() { // empty
		author = new char[100];
		author[0] = 0;
	}
	Figurines(const char* name, const char* painting, int date, const char* author) : Art(name, painting, date) { // with parametr
		this->author = _strdup(author);
	}
	Figurines(const Figurines& figure) : Art(figure) { // copy constr
		this->author = _strdup(figure.author);
	}
	Figurines(Figurines&& figure) noexcept : Art(move(figure)) { // move constr
		author = figure.author;
		figure.author = nullptr;
	}
	Figurines& operator = (const Figurines& figure) { // copy operator
		if (this != &figure) {
			Art::operator=(figure);
			delete[] author;
			author = _strdup(figure.author);
		}

		return *this;
	}
	Figurines& operator = (Figurines&& figure) noexcept { // move operator
		if (this != &figure) {
			Art::operator=(move(figure));
			delete[] author;
			author = figure.author;
			figure.author = nullptr;
		}

		return *this;
	}
	virtual ~Figurines() override {
		delete[] author;
		author = nullptr;
		cout << "Destructor figurines" << endl;
	}
protected:
	virtual void fill(istream& in) override {
		Art::fill(in);
		cout << "Write an author: " << endl;
		in.ignore();
		in.getline(author, 100);
	}
	virtual void print(ostream& out) const override {
		Art::print(out);
		cout << "Author: " << author << endl;
	}
	virtual const char* get_type() const override {
		return "Figurines";
	}
};

class Photos : public Art {
protected:
	char* location;
public:
	Photos() : Art() { // empty
		location = new char[100];
		location[0] = 0;
	}
	Photos(const char* name, const char* painting, int date, const char* location) : Art(name, painting, date) { // with parametr
		this->location = _strdup(location);
	}
	Photos(const Photos& photo) : Art(photo) { // copy constr
		location = _strdup(photo.location);
	}
	Photos(Photos&& photo) noexcept : Art(move(photo)) { // move constr
		location = photo.location;
		photo.location = nullptr;
	}
	Photos& operator = (const Photos& photo) { // operator copy
		if (this != &photo) {
			Art::operator=(photo);
			delete[] location;
			location = _strdup(photo.location);
		}

		return *this;
	}
	Photos& operator = (Photos&& photo) noexcept { // move operator
		if (this != &photo) {
			Art::operator=(move(photo));
			delete[] location;
			location = photo.location;
			photo.location = nullptr;
		}

		return *this;
	}
	virtual ~Photos() override {
		delete[] location;
		location = nullptr;
		cout << "Destructor Photos" << endl;
	}
protected:
	virtual void fill(istream& in) override {
		Art::fill(in);
		cout << "Enter location of photo: " << endl;
		in.ignore();
		in.getline(location, 100);
	}
	virtual void print(ostream& out) const override {
		Art::print(out);
		cout << "Location: " << location << endl;
	}
	virtual const char* get_type() const override {
		return "Photos";
	}
};

void clearAll(vector<Exhibit*>& arr) {
	for (unsigned int i = 0; i < arr.size(); i++) {
		delete arr[i];
	}
	arr.clear();
}

void vvod(vector<Exhibit*>& arr, unsigned int n) {
	clearAll(arr);
	while (arr.size() < n) {
		int type = 0;
		cout << "Input an object:\n";
		cout << "Money - 1; ColdWeapon - 2; Paintings - 3; Figurines - 4; Photos - 5\n";
		cin >> type;
		switch (type) {
		case 1: { // moneta
			Coin* cn = new Coin();
			cin >> *cn;
			arr.push_back(cn);
			break;
		}
		case 2: {
			ColdWeapon* cw = new ColdWeapon();
			cin >> *cw;
			arr.push_back(cw);
			break;
		}
		case 3: {
			Paintings* pt = new Paintings();
			cin >> *pt;
			arr.push_back(pt);
			break;
		}
		case 4: {
			Figurines* figure = new Figurines();
			cin >> *figure;
			arr.push_back(figure);
			break;
		}
		case 5: {
			Photos* ph = new Photos();
			cin >> *ph;
			arr.push_back(ph);
			break;
		}
		default:
			cout << "Error" << endl;
		}
	}
}

void vyvod(const vector<Exhibit*>& arr) {
	for (unsigned int i = 0; i < arr.size(); i++) {
		cout << *arr[i];
	}
}

void deleteElement(vector<Exhibit*>& arr, int index) {
	delete arr[index];
	arr.erase(arr.begin() + index);
}


int main() {
	setlocale(LC_ALL, "RUS");

	//// Создаем объекты Art
	//Art a1("Artwork 1", "Painting", 2020);
	//Art a2;

	//// Проверка оператора присваивания
	//a2 = a1;
	//cout << "a2 after assignment:\n" << a2 << endl;

	//// Проверка конструктора копирования
	//Art a3(a1);
	//cout << "a3 (copy constructed):\n" << a3 << endl;

	//// Проверка оператора перемещения
	//Art a4 = move(a1);
	//cout << "a4 (move assigned):\n" << a4 << endl;

	//// Проверка конструктора перемещения
	//Art a5(move(a2));
	//cout << "a5 (move constructed):\n" << a5 << endl;

	//// Создаем объекты различных классов с использованием разных конструкторов
	//Coin coin1("Golden coin", 1800, 1850, 5.0);
	//Coin coin2("Silver Coin", 1700, 1750, 3.0);

	//ColdWeapon weapon1("Knife", 1600, 1650, "Metal");
	//ColdWeapon weapon2("Ax", 1500, 1550, "Metal");

	//Paintings painting1("Portrait", "Woomen", 1750, "Artist1");
	//Paintings painting2("Scenery", "Mountains", 1800, "Artist2");

	//Figurines figurine1("Figurine1", "Angel", 1700, "Master1");
	//Figurines figurine2("Figurine2", "Dog", 1600, "Master2");

	//Photos photo1("Photo1", "Nature", 1900, "Wood");
	//Photos photo2("Photo2", "City", 2000, "Belarus");

	////// Выводим свойства всех объектов
	//cout << coin1 << endl;
	//cout << coin2 << endl;

	//cout << weapon1 << endl;
	//cout << weapon2 << endl;

	//cout << painting1 << endl;
	//cout << painting2 << endl;

	//cout << figurine1 << endl;
	//cout << figurine2 << endl;

	//cout << photo1 << endl;
	//cout << photo2 << endl;

	//cout << "Modify photo1" << endl;
	//cin >> photo1;
	//cout << photo1;

	//return 0;

	vector <Exhibit*> objects;
	int n;
	cout << "Enter the amount of objects" << endl;
	cin >> n;
	vvod(objects, n);

	cout << "\nYour objects: " << endl;
	vyvod(objects);

	cout << "\nDo you want to delete someone? \n>1. Yes\n>2. No" << endl;
	int cont;
	cin >> cont;
	switch (cont) {
	case 1:
		cout << "Enter index" << endl;
		int index;
		cin >> index;
		deleteElement(objects, index);
		cout << "\nYour objects: " << endl;
		vyvod(objects);
		break;

	case 2:
		break;

	default:
		break;
	}

	clearAll(objects);
}


