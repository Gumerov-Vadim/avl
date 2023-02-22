#include <iostream>
#include <conio.h>
#include <ctime>

struct node // структура для представления узлов дерева
{
	int key;
	int height;
	node* left;
	node* right;
	node() {
	}
	node(int k) {
		key = k; left = right = 0; height = 1;
	}
};
class TREE {
private:
	node* duk;
	void nlr(node* w);
	void add_search(int a, node*& t);
	//void add_avl(int a, node*& t);
	void show_me(node* t, int level, int key);
	//int check_right_height(node*& t);
	//int check_left_height(node*& t);
	int check_height(node* t);
	int set_height(node* t);
	void rr_rotate(node* t);
	void rl_rotate(node* t);
	void ll_rotate(node* t);
	void lr_rotate(node* t);
	void super_rl_rotate(node* t);
	void super_lr_rotate(node* t);
	void balance(node* t);
public:
	TREE() { duk = NULL; }
	node** GetDuk() {
		return &duk;
	}
	void nlr();
	void set_height();
	void balance();
	void add_search(int a);
	void add_avl(int a);
	void show_me();

};

//int TREE::check_right_height(node*& t) {
//	if (t == NULL) {
//		return 0;
//	}
//	else
//	{
//		return check_right_height(t->right) + 1;
//	}
//};
//int TREE::check_left_height(node*& t) {
//	if (t == NULL) {
//		return 0;
//	}
//	else
//	{
//		return check_left_height(t->left) + 1;
//	}
//};
int TREE::set_height(node* t) {
	if (t != NULL) {
		int rh = set_height(t->right);
		int lh = set_height(t->left);
		t->height = rh - lh;
		return rh + lh + 1;
	}
	return 0;
}
void TREE::set_height() {
	set_height(duk);
}
/*ФУНКЦИЯ ОТОБРАЖЕНИЯ ДЕРЕВА НА ЭКРАНЕ*/
void TREE::show_me(node* t, int u, int key) {
	if (t == NULL) return;                  //Если дерево пустое, то отображать нечего, выходим
	else //Иначе
	{
		show_me(t->right, ++u, t->key);                   //С помощью рекурсивного посещаем правое поддерево
		for (int i = 0; i < u - 1; ++i) {
			printf("      ");
			if (i == u - 2) {
				if (t->key > key) {
					printf("/");
				}
				else {
					printf("\\");
				}
			}
		};
		u--;
		if (u != 0) {
			printf("----< %d [%d]\n", t->key, t->height);            //И показываем элемент
		}
		else {
			printf("}---< %d [%d]\n", t->key, t->height);
		}
		show_me(t->left, ++u, t->key);                       //С помощью рекурсии посещаем левое поддерево

	}
}
void TREE::show_me()
{
	node* t = *this->GetDuk();
	if (t != NULL) {
		this->set_height();
		show_me(t, 0, t->key);
	}
}

int TREE::check_height(node* t) {
	if (t != NULL) {
		return check_height(t->right) + check_height(t->left) + 1;
	}
	return 0;
}
void TREE::rr_rotate(node* t) {
	if (t->left != NULL) {
		node* l_el = t->left;
		t->left = new node(t->key);
		t->left->left = l_el;
	}
	else
	{
		t->left = new node(t->key);
	}
	if (t->right->left != NULL) {
		t->left->right = t->right->left;
	}
	t->key = t->right->key;
	t->right = t->right->right;
}
void TREE::ll_rotate(node* t) {
	if (t->left != NULL) {
		node* r_el = t->right;
		t->right = new node(t->key);
		t->right->right = r_el;
	}
	else
	{
		t->right = new node(t->key);
	}
	if (t->left->right != NULL) {
		t->right->left = t->left->right;
	}
	t->key = t->left->key;
	t->left = t->left->left;
}
void TREE::rl_rotate(node* t) {
	if (t->left != NULL) {
		node* l_el = t->left;
		t->left = new node(t->key);
		t->left->left = l_el;
	}
	else
	{
		t->left = new node(t->key);
	}
	if (t->right->left->left != NULL) {
		t->left->right = t->right->left->left;
	}
	t->key = t->right->left->key;
	if (t->right->left->right != NULL) {
		t->right->left = t->right->left->right;
	}
	else {
		t->right->left = NULL;
	}
}
void TREE::lr_rotate(node* t) {
	if (t->right != NULL) {
		node* r_el = t->right;
		t->right = new node(t->key);
		t->right->right = r_el;
	}
	else
	{
		t->right = new node(t->key);
	}
	if (t->left->right->right != NULL) {
		t->right->left = t->left->right->right;
	}
	t->key = t->left->right->key;
	if (t->left->right->left != NULL) {
		t->left->right = t->left->right->left;
	}
	else {
		t->left->right = NULL;
	}
}

void TREE::super_rl_rotate(node* t) {
	if (t->left != NULL) {
		node* l_el = t->left;
		t->left = new node(t->key);
		t->left->left = l_el;
	}
	else
	{
		t->left = new node(t->key);
	}
	node* r_rll = t->right;
	node* rll = t->right->left;
	while (rll->left != NULL) {
		r_rll = rll;
		rll = rll->left;
	}
	t->key = rll->key;
	if (rll->right != NULL) {
		r_rll->left = rll->right;
	}
	else {
		r_rll->left = NULL;
	}
}
void TREE::super_lr_rotate(node* t) {
	if (t->left != NULL) {
		node* r_el = t->right;
		t->right = new node(t->key);
		t->right->right = r_el;
	}
	else
	{
		t->right = new node(t->key);
	}
	node* l_lrr = t->left;
	node* lrr = t->left->right;
	while (lrr->right != NULL) {
		l_lrr = lrr;
		lrr = lrr->right;
	}
	t->key = lrr->key;
	if (lrr->left != NULL) {
		l_lrr->right = lrr->left;
	}
	else {
		l_lrr->right = NULL;
	}
}
void TREE::balance(node* t) {
	if (t != NULL) {
		this->set_height(duk);

		if (t->height >= 2) {
			if (t->right->height >= 0) {
				if (t->right->left != NULL) {
					super_rl_rotate(t);
				}
				else {
					rr_rotate(t);
				}
				balance(t);
			}
			else if (t->right->height < 0) {
				rl_rotate(t);
				balance(t);
			}
		}
		else if (t->height <= -2) {
			if (t->left->height <= 0) {
				if (t->left->right != NULL) {
					super_lr_rotate(t);
				}
				else {
					ll_rotate(t);
				}
				balance(t);
			}
			else if (t->left->height > 0) {
				lr_rotate(t);
				balance(t);
			}
		}
		this->balance(t->right);
		this->balance(t->left);
	}
}
void TREE::balance() {
	this->set_height(duk);
	while ((duk->height > 1) || (duk->height < -1)) {
		this->set_height(duk);
		this->balance(duk);
	}
}
void TREE::add_search(int a, node*& t) {
	if (t == NULL)                   //Если дерева не существует
	{
		t = new node;                //Выделяем память
		t->key = a;                 //Кладем в выделенное место аргумент a
		t->left = t->right = NULL;       //Очищаем память для следующего роста
		return;                         //Заложили семечко, выходим
	}
	//Дерево есть
	if (a > t->key) add_search(a, t->right); //Если аргумент а больше чем текущий элемент, кладем его вправо
	else add_search(a, t->left);         //Иначе кладем его влево
}
void TREE::add_search(int a) {
	add_search(a, duk);
}

void TREE::nlr(node* w) {
	//Если корень существует, то
	if (w != NULL) {
		printf(", %d", w->key);
		this->nlr(&(*w->left));
		this->nlr(&(*w->right));
	}
}
void TREE::nlr() {
	if (duk != NULL) {
		printf("%d", duk->key);
		this->nlr(&(*duk->left));
		this->nlr(&(*duk->right));
	}
}

//void TREE::add_avl(int a, node*& t) {
//	if (t == NULL) {
//		t = new node(a);
//	}
//	else
//	{
//		this->add_search(a, t);
//	}
//}
//void TREE::add_avl(int a) {
//	this->add_avl(a, duk);
//}

//node* removemin(node* p) // удаление узла с минимальным ключом из дерева p
//{
//	if (p->left == 0)
//		return p->right;
//	p->left = removemin(p->left);
//	return balance(p);
//}
//
//node* remove(node* p, int k) // удаление ключа k из дерева p
//{
//	if (!p) return 0;
//	if (k < p->key)
//		p->left = remove(p->left, k);
//	else if (k > p->key)
//		p->right = remove(p->right, k);
//	else //  k == p->key 
//	{
//		node* q = p->left;
//		node* r = p->right;
//		delete p;
//		if (!r) return q;
//		node* min = findmin(r);
//		min->right = removemin(r);
//		min->left = q;
//		return balance(min);
//	}
//	return balance(p);
//}
void randomizer(int* m, int n, int min, int max) {
	time_t sec;
	sec = time(NULL);

	for (int i = 0; i < n; i++) {
		int r;
	rerand:
		r = (rand() * sec) % (max - min) + min;
		for (int j = 0; j < i - 1; j++) {
			if (r == m[i - j]) {
				goto rerand;
			}
		}
		m[i] = r;
	}
}

int main() {
	const int n = 10000;
	int m[n];
	int min = 100;
	int max = 99999;
	TREE* maintree = new TREE;
	node** tree = maintree->GetDuk();
	randomizer(m, n, min, max);
	//printf("%d", m[0]);
	for (int i = 0; i < n; i++) {
		maintree->add_search(m[i]);
		printf("%d ", m[i]);
	}
	printf("\n");
	maintree->set_height();
	maintree->show_me();
	printf("\n====================================================\n");
	maintree->balance();
	maintree->show_me();
	printf("\n\n\n");
	maintree->nlr();



	//maintree->add_search(10);
	//maintree->add_search(1);
	//maintree->add_search(2);
	//maintree->add_search(3);
	//maintree->add_search(4);
	//maintree->add_search(5);



	return 0;
}