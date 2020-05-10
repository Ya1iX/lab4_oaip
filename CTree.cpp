#include "CTree.h"
#include <conio.h>
#include <stdio.h>
#include <math.h>

void CTree::view_all()
{
	view(root, 0);
}
CTree::CTree(const char* n_name, int n_n, int n_key)
{
	CVetv* t = new CVetv(n_n, n_key);
	root = t;
}
CTree::CTree(const char* fn, const char* n_name)
{
	FILE* f;
	fopen_s(&f, fn, "rt");
	if (!f)
	{
		printf("file not found");
		return;
	}
	char ts[255] = "";
	fgets(ts, 255, f);
	int inkey, ininf;
	sscanf_s(ts, "%i %i", &inkey, &ininf);
	CVetv* t = new CVetv(ininf, inkey);

	root = t;

	while (fgets(ts, 255, f)) {
		sscanf_s(ts, "%i %i", &inkey, &ininf);
		add(ininf, inkey);
	}
	fclose(f);
}

CVetv* CTree::find(int fnd)
{
	return find(fnd, root);
}
CVetv* CTree::find(int fnd, CVetv* dr)
{
	if (!dr) return  NULL;
	if (dr->key == fnd) return dr;
	if (dr->key > fnd) return find(fnd, dr->l);
	else if (dr->key < fnd) return find(fnd, dr->r);
}

CVetv* CTree::add(int n_inf, int n_key)
{
	int	find = 0;
	CVetv* prev = NULL;

	CVetv* t = root;
	while (t && !find) {
		prev = t;
		if (n_key == t->key)
			find = 1;
		else
			if (n_key < t->key) t = t->l;
			else   t = t->r;
	}

	if (!find) {
		t = new CVetv(n_inf, n_key);
		if (n_key < prev->key)
			prev->l = t;
		else    prev->r = t;
		return t;
	}
	else
		return NULL;
}

CVetv::CVetv(int inf, int key)
{
	this->inf = inf;
	this->key = key;
	l = r = NULL;
}

void CTree::view(CVetv* t, int lv)
{
	if (t) {
		view(t->r, lv + 1);
		for (int i = 0; i < lv; i++)  printf("    ");
		printf(" %i\n", t->key);
		view(t->l, lv + 1);
	}
}

CTree::~CTree()
{
	del_vet(root->r);
	del_vet(root->l);
	delete root;
}

void CTree::del_vet(CVetv* d)
{
	if (d) {
		del_vet(d->r); d->r = NULL; delete d->r;
		del_vet(d->l); d->l = NULL; delete d->l;
	}
}
int CTree::odd_cnt(CVetv* t)
{
	int c = 0;
	if (t) {
		c += odd_cnt(t->r);
		if (fmod(t->key, 2) == 0) c++;
		c += odd_cnt(t->l);
	}
	return c;
}
int CTree::odd_cnt()
{
	return odd_cnt(root);
}
int CTree::keySum(CVetv* dr)
{
	if (!dr) return NULL;
	
	int sum = dr->key;

	if (dr->l)
	{
		sum += keySum(dr->l);
	}
	if (dr->r)
	{
		sum += keySum(dr->r);
	}

	return sum;
}
int CTree::keyCount(CVetv* dr)
{
	if (!dr) return NULL;

	int count = 1;

	if (dr->l)
	{
		count += keyCount(dr->l);
	}
	if (dr->r)
	{
		count += keyCount(dr->r);
	}

	return count;
}
double CTree::average()
{
	return (double)keySum(root) / (double)keyCount(root);
}
int CTree::findNearest(CVetv* dr, double diff, int nrst)
{
	if (!dr) return NULL;
	double avrgKey = average();

	if (diff > fabs(avrgKey - dr->key))
	{
		diff = fabs(avrgKey - dr->key);
		nrst = dr->key;
	}

	if (dr->l)
	{
		nrst = findNearest(dr->l, diff, nrst);
	}
	if (dr->r)
	{
		nrst = findNearest(dr->r, diff, nrst);
	}

	return nrst;
}
int CTree::findNearest()
{
	double diff = fabs(root->key - average());
	return findNearest(root, diff, root->key);
}