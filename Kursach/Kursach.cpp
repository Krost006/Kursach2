// Kursach.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
class cl_base {
private:
	std::string name;
	cl_base* head;
	std::vector<cl_base*> subordinate;
	int status;
public:
	cl_base(cl_base* head, std::string name = "root");
	bool Rename(std::string new_name);
	std::string GetName();
	cl_base* GetHead();
	//void PrintTree();
	cl_base* GetSub(std::string sub_name);
	~cl_base();

	cl_base* GetSubOnBranch(std::string sub_name);
	cl_base* GetSubOnTree(std::string sub_name);
	void PrintTreeFromThis();
	void PrintTreeFromThisWithStatus();
	void SetStatus(int stat);

	bool ChangeHead(cl_base* new_head);
	bool DeleteByName(std::string element);
	cl_base* GetObjectByPath(std::string path);
};

class cl2 : public cl_base {
public:
	cl2(cl_base* ptr, std::string name);
};

class cl3 : public cl_base {
public:
	cl3(cl_base* ptr, std::string name);
};

class cl4 : public cl_base {
public:
	cl4(cl_base* ptr, std::string name);
};
class cl5 : public cl_base {
public:
	cl5(cl_base* ptr, std::string name);
};
class cl6 : public cl_base {
public:
	cl6(cl_base* ptr, std::string name);
};
class cl_application :public cl_base {
public:
	cl_application(cl_base* ptr, std::string name);
	void build_tree_objects();
	int exec_app();
};

cl2::cl2(cl_base* ptr, std::string name) : cl_base(ptr, name) {}
cl3::cl3(cl_base* ptr, std::string name) : cl_base(ptr, name) {}
cl4::cl4(cl_base* ptr, std::string name) : cl_base(ptr, name) {}
cl5::cl5(cl_base* ptr, std::string name) : cl_base(ptr, name) {}
cl6::cl6(cl_base* ptr, std::string name) : cl_base(ptr, name) {}

void cl_application::build_tree_objects() {
	string root;
	cin >> root;
	this->Rename(root);												//Ввод и задание имени головного объекта

	string input_head_path, sub;
	int class_number;
	cl_base* last = this;
	while (1) {
		cin >> input_head_path;													//Вводим имя головного объекта
		if (input_head_path == "endtree") {
			break;													//Если имя головного объекта endtree то завершаем метод
		}
		cin >> sub >> class_number;										//Ввод имени нового объекта и его класса
		cl_base* head_obj = last->GetObjectByPath(input_head_path);
		if (head_obj->GetSub(sub) == nullptr && head_obj != nullptr) {
			switch (class_number) {									//Ести имя нового объекта уникально на дереве
				//то создаём его в зависимости от номера класса
			case 2:
			{
				last = new cl2(head_obj, sub);
				break;
			}
			case 3: {
				last = new cl3(head_obj, sub);
				break; }
			case 4: {
				last = new cl4(head_obj, sub);
				break; }
			case 5: {
				last = new cl5(head_obj, sub);
				break; }
			case 6: {
				last = new cl6(head_obj, sub);
				break; }
			}
		}
	}

}

int cl_application::exec_app() {
	/*string obj;
	int input_status;
	while(cin>>obj){											//Устанавка состояний считываемых объектов
		cin>>input_status;
		GetSubOnTree(obj)->SetStatus(input_status);
	}

	cout<<"Object tree\n";
	this->PrintTreeFromThis();									//Вывод дерева
	cout<<"The tree of objects and their readiness\n";
	this->PrintTreeFromThisWithStatus();
FIND .
FIND .object_7
FIND object_4/object_7
FIND /
FIND /object_1/object_7
FIND //object_2
FIND //object_4
	*/
	cout << "Object tree\n";
	this->PrintTreeFromThis();
	string comand, operator_path;
	cl_base* current_object = this;
	while (1) {
		//((cl_base*)nullptr)->GetName();
		cin >> comand;
		//cout<<comand;
		if (comand == "END") {
			cout << "Current object hierarchy tree\n";
			this->PrintTreeFromThis();
			return 0;
		}
		cin >> operator_path;
		if (comand == "SET") {
			auto tmp_object = current_object->GetObjectByPath(operator_path);
			if (tmp_object == nullptr) {
				cout << "The object was not found at the specified coordinate: " << operator_path << "\n";
			}
			else {
				current_object = tmp_object;
				cout << "Object is set: " << current_object->GetName() << "\n";
			}
		}
		else if (comand == "FIND") {
			cout << operator_path;
			auto tmp_object = current_object->GetObjectByPath(operator_path);
			if (tmp_object == nullptr) {
				cout << "     Object is not found\n";
			}
			else {
				cout << "     Object name: " << tmp_object->GetName() << "\n";
			}
		}
		else if (comand == "MOVE") {
			auto tmp_object = current_object->GetObjectByPath(operator_path);
			if (tmp_object == nullptr) {
				cout << operator_path << "     Head object is not found\n";
			}
			else {
				bool succes = current_object->ChangeHead(tmp_object);
				if (succes) {
					cout << "New head object: " << tmp_object->GetName() << "\n";
				}
				else if (tmp_object->GetSub(current_object->GetName()) != nullptr) {
					cout << operator_path << "     Dubbing the names of subordinate objects\n";
				}
				else {
					cout << operator_path << "     Redefining the head object failed\n";
				}
			}

		}
		else if (comand == "DELETE") {
			//cout<<operator_path;
			auto tmp_object = current_object->GetSub(operator_path);
			if (tmp_object != nullptr) {
				string absolute_path = "/" + tmp_object->GetName();

				auto tmp_head_object = tmp_object->GetHead();
				//cout<<tmp_object->GetName()<<"\n";
				//tmp_object -> GetHead() != nullptr &&
				if (current_object->DeleteByName(tmp_object->GetName())) {
					while (tmp_head_object->GetHead() != nullptr) {
						absolute_path = "/" + tmp_head_object->GetName() + absolute_path;
						tmp_head_object = tmp_head_object->GetHead();
					}
					//absolute_path = "/" + absolute_path;
					cout << "The object " << absolute_path << " has been deleted\n";
				}
			}
		}
	}
	cout << "Current object hierarchy tree\n";
	this->PrintTreeFromThis();
	cout << "END Programm";
	return 0;
}

cl_application::cl_application(cl_base* ptr = nullptr, std::string name = "root") :cl_base(ptr, name) {}

cl_base::cl_base(cl_base* head, string name) {			//Конструктор
	this->head = head;
	this->name = name;
	if (head != nullptr) {
		head->subordinate.push_back(this);			//Если текущий объект не корневой добавить текущий в подчинение головному
	}
	status = 0;
}

string cl_base::GetName() {								//Возврат имени
	return name;
};

cl_base* cl_base::GetHead() {							//Возврат адреса головного объекта
	return head;
};

cl_base* cl_base::GetSub(std::string sub_name) {			//Получение адреса подчиненённого объкута по имени
	auto it = subordinate.begin();
	while (it < subordinate.end()) {
		if ((*it)->GetName() == sub_name) {
			return *it;									//Возвращаем адрес подчинённого объекта еслт нашли с нужным именем
		}
		it++;
	}
	return nullptr;										//Если не нашли возвращаем нулевой указатель
}

bool cl_base::Rename(std::string new_name) {				//Переименовывание объекта
	if (head == nullptr || head->GetSub(new_name) == nullptr) {
		name = new_name;								//Переименовывание объекта если нет подчинённого с таким же именем
		return 1;
	}
	return 0;
}

cl_base* cl_base::GetSubOnBranch(std::string sub_name) {	//Получить адрес подчинённого объекта на ветке
	queue<cl_base*> q;
	q.push(this);										//Создание очереди и добавление туда текущего объекта
	int counter = 0;
	cl_base* answer = nullptr;
	while (!q.empty()) {								//Для каждого элемента в очереди
		cl_base* tmp = q.front();
		q.pop();
		auto it = tmp->subordinate.begin();
		if (tmp->GetName() == sub_name) {
			counter++;
			answer = tmp;								//Присвоить возвращаемой переменной адрес на оюрабатываемый объект
		}
		while (it != tmp->subordinate.end()) {
			q.push(*it++);
		}
	}

	if (counter != 1) {
		return nullptr;									//Если имя не найдено или не уникально возвращаем нулевой указатель
	}
	else {
		return answer;									//Иначе возвращаем адрес искомого объекта
	}
}

cl_base* cl_base::GetSubOnTree(std::string sub_name) {
	if (head != nullptr) {
		return head->GetSubOnTree(sub_name);			//Если текущий объект не головной ищем его
	}
	else {
		return GetSubOnBranch(sub_name);				//Когда нашли головной запускаем от него поиск по ветке
	}
}

void cl_base::PrintTreeFromThis() {
	cl_base* h = head;
	int level = 0;
	while (h != nullptr) {
		level++;										//Определение на каком уровне в дереве иерархии текущий объект
		h = h->head;
	}
	for (int i = 0; i < level; i++) {
		cout << "    ";									//Вывод необходимых отступы в зависимость от уровня в иерархии
	}
	cout << name << "\n";									//Вывод имени текущего объекта
	auto it = subordinate.begin();
	while (it < subordinate.end()) {
		(*it++)->PrintTreeFromThis();					//Рекурсивный вызов метода для каждого непосредственного подчинённого объекта
	}
}

void cl_base::PrintTreeFromThisWithStatus() {
	cl_base* h = head;
	int level = 0;
	while (h != nullptr) {
		level++;										//Определение на каком уровне в дереве иерархии текущий объект
		h = h->head;
	}
	for (int i = 0; i < level; i++) {
		cout << "    ";									//Вывод необходимых отступы в зависимость от уровня в иерархии
	}
	cout << name << " ";									//Вывод имени текущего объекта
	if (status) {											//Вывод готовность объекта
		cout << "is ready\n";
	}
	else {
		cout << "is not ready\n";
	}
	auto it = subordinate.begin();
	while (it < subordinate.end()) {
		(*it++)->PrintTreeFromThisWithStatus();			//Рекурсивный вызывов метода для каждого непосредственного подчинённого объекта
	}
}

void cl_base::SetStatus(int stat) {
	if (!status && (stat != 0)) {						//Смена готовности с неготового
		cl_base* tmp_head = head;
		bool can_change = 1;
		while (tmp_head != nullptr) {
			if (!(tmp_head->status)) {				//Если нашёлся объект на ветке вверх по иерархии неготовый
				can_change = 0;							//Не меняем готовность
				break;
			}
			tmp_head = tmp_head->head;
		}

		if (can_change) {									//Если все объекты на ветке вверх по иерархии готовы
			status = stat;								//Меняем готовность
		}
	}
	else if (status && (stat == 0)) {					//Сменв готовности с готового
		status = 0;										//Меняем готовность
		auto it = subordinate.begin();
		while (it < subordinate.end()) {
			(*it++)->SetStatus(0);						//Переводим все подчинённые объекты в неготовые состояния
		}
	}
}

bool cl_base::ChangeHead(cl_base* new_head) {
	if (head == nullptr || new_head == nullptr) {
		return false;
	}
	else if (new_head->GetSub(name) != nullptr) {
		//cout<<"Already deleted\n";
		return false;
	}
	/*else if( this -> GetSubOnBranch( new_head->GetName() ) == new_head ){
		return false;
	}*/
	else {
		//auto it = head -> subordinate.begin();
		//cout<<head -> GetName()<<"\n";
		//cout<<"Deliting from subordinates "<<(*it)->GetName()<<"\n";
		/*while( *it != this  ){
			it++;
			cout<<(*it)->GetName()<<"\n";
		}*/
		cl_base* ptr = new_head;
		while (ptr != this && ptr != nullptr) {
			/*if( ptr == this ){
				return 0;
			}*/
			ptr = ptr->head;
		}
		if (ptr == this) {
			return false;
		}

		for (int i = 0; i < head->subordinate.size(); i++) {
			//cout<<head -> subordinate[i]<<"\n";
			if (head->subordinate[i] == this) {
				//cout<<"found "<<head -> subordinate[i]->GetName();
				head->subordinate.erase(head->subordinate.begin() + i);
				//i--;
				break;
			}
		}
		//cout<<"Deleting element "<<(*it) -> GetName()<<"\n";
		//head -> subordinate.erase(it);
		//delete *it;  Under question
		head = new_head;
		new_head->subordinate.push_back(this);

		return true;
	}
}


cl_base::~cl_base() {
	//delete this;
	for (int i = 0; i < subordinate.size(); i++) {
		delete subordinate[i];
	}
}

bool cl_base::DeleteByName(string element_name) {
	/*cl_base* object = GetSubOnBranch(element);
	cl_base* new_head = head;

	auto it = subordinate.begin();
	while( it < subordinate.end() ){
		(*it) -> head = new_head;
	}

	it = head -> subordinate.begin();
	while( ( *it != this ) && ( it <  head -> subordinate.end() ) ){
		it++;
	}
	head -> subordinate.erase(it);

	delete this;*/
	//cout<<"-------------\n";
	cl_base* object = GetSub(element_name);
	if (object == nullptr) {
		return false;
	}
	/*auto it = subordinate.begin();
	while(it != subordinate.end() ){
		if( (*it) -> GetName() == element_name ){
			delete (*it);
			subordinate.erase( it );
			return 1;
		}
		it++;
	}*/
	for (int i = 0; i < subordinate.size(); i++) {
		if (object == subordinate[i]) {
			delete object;
			subordinate.erase(subordinate.begin() + i);
			return true;
		}
	}
	return false;

	//auto it = object -> subordinate.begin();
	//while(it != object -> subordinate.end() ){
		/*(*it) -> head = this;
		subordinate.push_back( *it++ );*/
		//cout<<"Reheading "<<(*it)<<"\n";
		//(*it) -> ChangeHead( this );
	//}
	/*for( int i = 0; i < object -> subordinate.size(); i++){
		cout<<"Reheading "<<object -> subordinate[i] -> GetName()<<"\n";
		object -> subordinate[i--] -> ChangeHead( this );
	}*/
	/*while( object -> subordinate.size() != 0 ){
		//cout<<"Reheading "<<object -> subordinate[0] -> GetName()<<" and size "<<subordinate.size()<<"\n";
		object -> subordinate[0] -> ChangeHead( this );
		//cout<<"New head is "<<object -> subordinate[0] -> GetHead() -> GetName()<<"\n";
	}
	for(int i = 0; i<object -> head -> subordinate.size(); i++){
		//cout<<object -> head -> subordinate[i]-> GetName()<<"\n";
		if( object -> head -> subordinate[i] -> GetName() == element_name ){
			object -> head -> subordinate.erase( object -> head -> subordinate.begin() + i );
			return;
		}
	}*/

	//delete object;

	//delete object;
}

cl_base* cl_base::GetObjectByPath(std::string path) {

	/*if( path[0] == '/' ){
		cl_base* root = this;
		while( root->GetHead() != nullptr ){
			root = root->GetHead();
		}

		if( path[1] == '/' ){
			return root -> GetSubOnBranch( path.substr(2) );
		}
		else if( path == "/" ){
			return this;
		}
		else{
			string name;
			cl_base* tmp = root;
			while( path.find('/') !=  string::npos ){
				path = path.substr(1);
				name = path.substr( 0, path.find('/') );
				path = path.substr( path.find('/') );
				tmp = tmp -> GetSub( name );
				if( tmp == nullptr ){
					return nullptr;
				}
			}
			return tmp;
		}
	}
	else{
		if( path == "." ){
			return this;
		}
		else if( path[0] == '.' ){
			return this -> GetSubOnBranch( path.substr(2) );
		}
		else{
			string name;
			cl_base* tmp = this;
			while( path != "" ){
				path = path.substr(1);
				name = path.substr( 0, path.find('/') );
				tmp = tmp -> GetSub( name );
				if( tmp == nullptr ){
					return nullptr;
				}
			}
			return tmp;
		}
	}*/

	char separator = '.';

	if (path[0] == '/') {
		if (head != nullptr)
			return head->GetObjectByPath(path);
		else {

			separator = '/';
			path = path.substr(1);
		}
	}


	if (path == "" || path == ".") {
		return this;
	}
	else if (path[0] == separator) {
		return GetSubOnBranch(path.substr(1));
	}
	else {
		//cout<<path<<"\n";
		int index = path.find('/');
		if (index == string::npos) {
			return GetSub(path);
		}
		string object_name = path.substr(0, index);
		if (GetSub(object_name) == nullptr) {
			return nullptr;
		}
		return GetSub(object_name)->GetObjectByPath(path.substr(index + 1));
	}

	/*
	if( path[0] == '/' ){
		if( head != nullptr){
			return head -> GetObjectByCoordinate(path);
		}
		if( path == "/" ){
			return this;
		}
		else if( path[1] == '/' ){
			string object_name = path.substr( 2 );
			return GetSubOnTree( object_name );
		}
		else{
			string sub_path = path.substr( path.find( '/') );
			if( sub_path.find('/') != string::npos ){
				return GetSub( sub_path.substr( 0, sub_path.find('/') )) -> GetObjectByCoordinate( sub_path );
			}
			else{
				return GetSub( sub_path );
			}
		}
	}
	else if( path[0] == '.' ){
		if( path == "."){
			return this;
		}
		else{
			return GetSub( path.substr( 1 ) );
		}
	}
	else{
		string sub_path = path.substr( path.find( '/') );
		if( sub_path.find('/') != string::npos ){
			return GetSub( sub_path.substr( 0, sub_path.find('/') )) -> GetObjectByCoordinate( sub_path );
		}
		else{
			return GetSub( sub_path );
		}
	}
	*/
}

int main()
{
	cl_application  ob_cl_application(nullptr, "root");// создание корневого объекта
	ob_cl_application.build_tree_objects();       // конструирование системы, построение дерева объектов
	return ob_cl_application.exec_app();         // запуск системы
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
