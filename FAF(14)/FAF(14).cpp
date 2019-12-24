#include <iostream>
#include <clocale>
#include <string>
using namespace std;

struct Tree 
{
	int UDK;
	string autor;
	string name;
	int year;
	int amount;
	Tree* left;
	Tree* right;
};

Tree* InsertNode(Tree* node, int q, string w, string e, int r, int t);
void  PrintNode(ostream& _out, const Tree* node, int q, string w, string e, int r, int t);
void  ClearNode(Tree* node);

Tree* DeleteNode(Tree* node, int val) 
{
	if (node == NULL)
		return node;

	if (val == node->UDK)
	{

		Tree* tmp;
		if (node->right == NULL)
			tmp = node->left;
		else {

			Tree* ptr = node->right;
			if (ptr->left == NULL) 
			{
				ptr->left = node->left;
				tmp = ptr;
			}
			else {

				Tree* pmin = ptr->left;
				while (pmin->left != NULL)
				{
					ptr = pmin;
					pmin = ptr->left;
				}
				ptr->left = pmin->right;
				pmin->left = node->left;
				pmin->right = node->right;
				tmp = pmin;
			}
		}

		delete node;
		return tmp;
	}
	else if (val < node->UDK)
		node->left = DeleteNode(node->left, val);
	else
		node->right = DeleteNode(node->right, val);
	return node;
}

Tree* Default(Tree* node, int q, string w, string e, int r, int t)
{
	if (node == NULL)
	{
		node = new (nothrow) Tree();
		if (node != NULL)
		{
			node->UDK = q;
			node->autor = w;
			node->name = e;
			node->year = r;
			node->amount = t;
			node->left = node->right = NULL;
		}
		return node;
	}

	if (q < node->UDK)
		node->left = InsertNode(node->left, q, w, e, r, t);
	else
		node->right = InsertNode(node->right, q, w, e, r, t);
	return node;
}

void PrintNodeUDK(ostream& _out, const Tree* node, int q)
{
	if (node != NULL)
	{
		if (node->left != NULL)
			PrintNodeUDK(_out, node->left, q);

		_out << node->UDK << '\t';
		cout << endl;

		if (node->right != NULL)
			PrintNodeUDK(_out, node->right, q);
	}
}

void print_Tree(Tree* node, int level)
{
	if (node)
	{
		print_Tree(node->left, level + 1);
		for (int i = 0; i < level; i++) cout << "   ";
		cout << node->UDK << endl;
		print_Tree(node->right, level + 1);
	}
}

int main(void)
{
	setlocale(LC_ALL, "Russian");
	Tree* tree = NULL;
	int n, q, r, t;
	string w, e;

	q = 11, r = 2010, t = 6;
	w = "Пушкин А. С.", e = "Дубровский        ";
	tree = Default(tree, q, w, e, r, t);

	q = 15, r = 2016, t = 60;
	w = "Кирик Л. А.", e = "Задачи по физике";
	tree = Default(tree, q, w, e, r, t);

	q = 18, r = 2012, t = 14;
	w = "Гоголь Н. В.", e = "Мертвые души     ";
	tree = Default(tree, q, w, e, r, t);

	q = 5, r = 2000, t = 1;
	w = "Ден Абнетт", e = "Битва за Калт     ";
	tree = Default(tree, q, w, e, r, t);

	q = 1, r = 1999, t = 66;
	w = "Джек Лондон", e = "Белый Клык       ";
	tree = Default(tree, q, w, e, r, t);

	q = 8, r = 2020, t = 18;
	w = "Жюль Верн", e = "Таинственный остров";
	tree = Default(tree, q, w, e, r, t);

	cout << "Книги, которые содержатся в библиотеке:" << endl;
	PrintNode(cout, tree, q, w, e, r, t);
	system("pause");
	system("cls");

	int choice = 0;
	while (choice != 5)
	{
		cout << endl << "Выберите требуемое действие:" << endl << "1 - Добавить один или несколько элементов" << endl;
		cout << "2 - Удалить элемент" << endl << "3 - Отсортировать по УДК и вывести" << endl << "4 - Вывести УДК в виде дерева" << endl << "5 - Завершение работы программы" << endl;
		while (!(cin >> choice) || (cin.peek() != '\n'))
		{
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cout << "Некоректные данные, попробуйте снова" << endl;
		}
		if (choice == 1)
		{
			cout << "Введите количество добавляемых элементов: ";
			cin >> n;
			for (int i = 0; i < n; ++i)
			{
				cout << "Введите УДК:";
				while (!(cin >> q) || (cin.peek() != '\n'))
				{
					cin.clear();
					cin.ignore((numeric_limits<streamsize>::max)(), '\n');
					cout << "Некоректные данные, попробуйте снова" << endl;
				}
				cout << "Введите фамилию и инициалы автора:";
				cin >> w;
				cout << "Введите название книги:";
				cin >> e;
				cout << "Введите год издания:";
				while (!(cin >> r) || (cin.peek() != '\n'))
				{
					cin.clear();
					cin.ignore((numeric_limits<streamsize>::max)(), '\n');
					cout << "Некоректные данные, попробуйте снова" << endl;
				}
				cout << "Введите количество книг в библиотеке:";
				while (!(cin >> t) || (cin.peek() != '\n'))
				{
					cin.clear();
					cin.ignore((numeric_limits<streamsize>::max)(), '\n');
					cout << "Некоректные данные, попробуйте снова" << endl;
				}
				tree = InsertNode(tree, q, w, e, r, t);
			}
			system("pause");
			system("cls");
		}
		if (choice == 2)
		{
			int d;
			cout << endl;
			PrintNode(cout, tree, q, w, e, r, t);
			cout << endl;
			cout << "Введите элемент, который требуется удалить: ";
			cin >> d;
			cout << endl;
			tree = DeleteNode(tree, d);
			PrintNode(cout, tree, q, w, e, r, t);
			system("pause");
			system("cls");
		}
		if (choice == 3)
		{
			PrintNode(cout, tree, q, w, e, r, t);
			cout << endl;
			system("pause");
			system("cls");
		}
		if (choice == 4)
		{
			print_Tree(tree, q);
			system("pause");
			system("cls");
		}
		if (choice == 5)
		{
			ClearNode(tree);
			system("pause");
			system("cls");
		}
	}
	return 0;
}

Tree* InsertNode(Tree* node, int q, string w, string e, int r, int t)
{
	if (node == NULL)
	{
		node = new (nothrow) Tree();
		if (node != NULL)
		{
			node->UDK = q;
			node->autor = w;
			node->name = e;
			node->year = r;
			node->amount = t;
			node->left = node->right = NULL;
		}
		return node;
	}

	if (q < node->UDK)
		node->left = InsertNode(node->left, q, w, e, r, t);
	else
		node->right = InsertNode(node->right, q, w, e, r, t);
	return node;
}

void PrintNode(ostream& _out, const Tree* node, int q, string w, string e, int r, int t)
{
	if (node != NULL)
	{
		if (node->left != NULL)
			PrintNode(_out, node->left, q, w, e, r, t);

		_out << node->UDK << '\t';
		_out << node->autor << '\t';
		_out << node->name << '\t';
		_out << node->year << '\t';
		_out << node->amount << '\t';
		cout << endl;

		if (node->right != NULL)
			PrintNode(_out, node->right, q, w, e, r, t);
	}
}

void ClearNode(Tree* node)
{
	if (node != NULL)
	{
		if (node->left != NULL)
			ClearNode(node->left);
		if (node->right != NULL)
			ClearNode(node->right);
		delete node;
	}
}