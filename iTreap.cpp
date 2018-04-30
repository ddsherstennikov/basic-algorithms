#include <iostream>

using namespace std;



typedef struct node
{
	int val;	// value stored in the array on the implicit idx of this node
	int prior;

	int size;
	int lazy;	// whatever lazy update you want to do

	int sum;	// whatever info you want to maintain in segtree for each node

	struct node *l, *r;
} node;

using pnode = struct node*;



int sz(pnode t)
{
	return t ? t->size : 0;
}

void upd_sz(pnode t)
{
	if (t)
		t->size = sz(t->l) + 1 + sz(t->r);
}



// push
void lazy(pnode t)
{
	if (!t || !t->lazy)
		return;

	t->val += t->lazy; // operation of lazy

	t->sum += t->lazy * sz(t); // placeholder value

	if (t->l)
		t->l->lazy += t->lazy; // propagate lazy
	if (t->r)
		t->r->lazy += t->lazy;
	t->lazy = 0;
}

void reset(pnode t)
{
	if (t)
		t->sum = t->val; // no need to reset lazy because at the place where we call this, lazy would be propagated itself
}

//combining two ranges of segtree
void combine(pnode& t, pnode l, pnode r)
{
	if (!l || !r)
		return void(t = l ? l : r);
	t->sum = l->sum + r->sum;
}

//operation of segtree
void operation(pnode t)
{
	if (!t)
		return;

	reset(t); // reset the value of current node, assuming it now represents a single element of the array
	lazy(t->l); lazy(t->r); // propagate lazy before combining t->l, t->r
	combine(t, t->l, t);
	combine(t, t, t->r);
}



void split(pnode t, pnode& l, pnode& r, int pos, int add = 0)
{
	if (!t)
		return void(l = r = NULL);

	lazy(t);

	int curr_pos = add + sz(t->l);
	if (curr_pos <= pos) //element at pos goes to left subtree(l)
		split(t->r, t->r, r, pos, curr_pos + 1), l = t;
	else
		split(t->l, l, t->l, pos, add), r = t;

	upd_sz(t);
	operation(t);
}

// l->leftarray, r->rightarray, t->resulting array
void merge(pnode& t, pnode l, pnode r)
{
	lazy(l); lazy(r);

	if (!l || !r)
		t = l ? l : r;
	else if (l->prior>r->prior)
		merge(l->r, l->r, r), t = l;
	else
		merge(r->l, l, r->l), t = r;

	upd_sz(t);
	operation(t);
}



pnode init(int val)
{
	pnode ret = (pnode)malloc(sizeof(node));

	ret->prior = rand(); ret->size = 1;
	ret->val = val;
	ret->sum = val; ret->lazy = 0;

	return ret;
}

void insert(pnode& t, pnode it, int pos)
{
	if (!t)
		t = it;
	else
	{
		pnode t1, t2;

		split(t, t1, t2, pos);
		merge(t1, t1, it);
		merge(t, t1, t2);
	}
}

void erase(pnode& t, int val)
{
	if (t->val == val)
		merge(t, t->l, t->r);
	else
		erase(val < t->val ? t->l : t->r, val);
}

void insert(pnode t, int idx, int val)
{
	if (idx > t->size)
		return;

	pnode n1, n2;
	split(t, n1, n2, idx);
	merge(t, n1, init(val));
	merge(t, t, n2);
}



//[l,r]
int range_query(pnode t, int l, int r)
{
	pnode L, mid, R;

	split(t, L, mid, l - 1);
	split(mid, t, R, r - l); // note: r-l!!

	int ans = t->sum;

	merge(mid, L, t);
	merge(t, mid, R);

	return ans;
}

//[l,r]
void range_update(pnode t, int l, int r, int val)
{
	pnode L, mid, R;

	split(t, L, mid, l - 1);
	split(mid, t, R, r - l); // note: r-l!!

	t->lazy += val; // lazy_update

	merge(mid, L, t);
	merge(t, mid, R);
}



int main()
{
	size_t test_cases;
	cin >> test_cases;

	for (size_t i = 0; i < test_cases; i++)
	{
		size_t N; // number of elements in the array
		size_t C; // number of commands

		cin >> N >> C;

		pnode root = init(1);

		// build iTreap
		for (i = 2; i <= N; i++)
			insert(root, i, 0);

		for (int j = 0; j < C; j++)
		{
			int command_code;
			size_t p, q, v;

			cin >> command_code;

			switch (command_code)
			{
			case 0: // 0 p q v - add v to all numbers in the range of p to q (inclusive), where p and q are two indexes of the array.
				cin >> p >> q >> v;

				range_update(root, p, q, v);

				break;
			case 1: // 1 p q - output a line containing a single integer, which is the sum of all the array elements between p and q (inclusive)
				cin >> p >> q;

				int ans = range_query(root, p, q);
				cout << ans << endl;

				break;
			}
		}
	}

	return 0;
}

