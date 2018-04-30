#include <vector>
#include <iostream>
#include <random>
#include <cmath>
#include <algorithm>
#include <unordered_set>
#include <limits>

using namespace std;

using Point = vector<double>;



struct cluster
{
	Point center;

	vector<Point const*> old_points;
	vector<Point const*> points;

	bool stable()
	{
		if (old_points.size() != points.size())
			return false;
		else
			return (old_points == points);
	}
};



void init_clusters(size_t n, size_t k, size_t N, const vector<Point>& points, vector<cluster>& clusters)
{
	random_device rd;
	uniform_int_distribution<size_t> dist(0, N-1);
	unordered_set<size_t> used_points;

	for (size_t i = 0; i < k; i++)
	{
		size_t p_idx = dist(rd);
		Point p = points[p_idx];
		if (used_points.find(p_idx) == used_points.end())
		{
			clusters[i].center = p;
			used_points.insert(p_idx);
		}
		else
		{
			size_t q_idx = (p_idx < N - 1) ? p_idx + 1 : 0;
			Point q = points[q_idx];
			while (q_idx != p_idx && used_points.find(q_idx) != used_points.end())
			{
				q = points[q_idx];
				q_idx = (p_idx < N - 1) ? p_idx + 1 : 0;
			}
			
			if (q_idx == p_idx)
				throw std::runtime_error("N < k");
			else
			{
				clusters[i].center = q;
				used_points.insert(q_idx);
			}
		}
	}
}



double euclid(const Point& v1, const Point& v2)
{
	if (v1.size() != v2.size())
		throw std::runtime_error("vector sizes differ for euclidean distance function");

	double r = 0.0;

	for (size_t i = 0; i < v1.size(); i++)
		r += pow(v1[i] - v2[i], 2);

	return sqrt(r);
}



Point arithm_mean(vector<Point const*>& points)
{
	Point res(points[0]->size(), 0.0);
	size_t M = points.size();

	for (size_t i = 0; i < points.size(); i++)
		for (size_t j = 0; j < points[i]->size(); j++)
			res[j] += points[i]->at(j) / M;

	return res;
}



vector<cluster> k_means(size_t n, size_t k, size_t N, const vector<Point>& points)
{
	vector<cluster> clusters(k);
	init_clusters(n, k, N, points, clusters);

	bool clusters_stable = false;
	while (!clusters_stable)
	{
		for (auto& cl : clusters)
		{
			cl.old_points.clear();
			cl.old_points = cl.points;
			cl.points.clear();
		}
		clusters_stable = true;

		for (size_t i=0; i < points.size(); i++)
		{
			double F = numeric_limits<double>::max();
			size_t cl_idx;
			for (size_t j=0; j < k; j++)
			{
				double d = euclid(points[i], clusters[j].center);
				F = min(F, d);
				if (F == d) cl_idx = j;
			}

			clusters[cl_idx].points.push_back(&points[i]);
		}

		for (auto& cl : clusters)
		{
			cl.center = arithm_mean(cl.points);
			clusters_stable = clusters_stable && cl.stable();
		}			
	}

	return clusters;
}



void print(vector<cluster>& clusters, size_t n)
{
	for (auto& cl : clusters)
	{
		cout << "(";
		for (auto& x : cl.center)
			cout << x << " ";
		cout << ")";

		cout << "\n\t";

		for (size_t i = 0; i < cl.points.size(); i++)
		{
			cout << "(";

			for (size_t j = 0; j < n; j++)
				cout << cl.points[i]->at(j) << " ";

			cout << ") ";
		}

		cout << endl;
	}
}



int main()
{
	size_t n, k, N;
	cin >> n >> k >> N;

	vector<Point> points(N, Point(n));
	for (size_t i = 1; i < N; i++)
		for(size_t j = 0; j < n; j++)
		{
			cin >> points[i][j];
		}

	vector<cluster> clusters = k_means(n, k, N, points);

	print(clusters, n);

    return 0;
}

