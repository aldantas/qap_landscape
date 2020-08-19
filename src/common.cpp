#include "common.hpp"

#include <cmath>

void transpose(int &a, int &b) {long temp = a; a = b; b = temp;}

/*--------------------------------------------------------------*/
/*       compute the cost difference if elements i and j        */
/*         are transposed in permutation (solution) p           */
/*--------------------------------------------------------------*/
long compute_delta(int n, type_matrix & a, type_matrix & b,
                   type_vector & p, int i, int j)
{
	long d; int k;
	d = (a[i][i]-a[j][j])*(b[p[j]][p[j]]-b[p[i]][p[i]]) +
		(a[i][j]-a[j][i])*(b[p[j]][p[i]]-b[p[i]][p[j]]);
	for (k = 0; k < n; k = k + 1) if (k!=i && k!=j)
		d = d + (a[k][i]-a[k][j])*(b[p[k]][p[j]]-b[p[k]][p[i]]) +
			(a[i][k]-a[j][k])*(b[p[j]][p[k]]-b[p[i]][p[k]]);
	return(d);
}

/*--------------------------------------------------------------*/
/*      Idem, but the value of delta[i][j] is supposed to       */
/*    be known before the transposition of elements r and s     */
/*--------------------------------------------------------------*/
long compute_delta_part(type_matrix & a, type_matrix & b,
                        type_vector & p, type_matrix & delta,
                        int i, int j, int r, int s)
{
	return(delta[i][j]+(a[r][i]-a[r][j]+a[s][j]-a[s][i])*
			(b[p[s]][p[i]]-b[p[s]][p[j]]+b[p[r]][p[j]]-b[p[r]][p[i]])+
			(a[i][r]-a[j][r]+a[j][s]-a[i][s])*
			(b[p[i]][p[s]]-b[p[j]][p[s]]+b[p[j]][p[r]]-b[p[i]][p[r]]) );
}

int hamming_distance(type_point point1, type_point point2)
{
	int distance = 0;
	int n = point1.solution.size();
	for (int i = 0; i < n; i++) {
		if (point1.solution[i] != point2.solution[i]) {
			distance++;
		}
	}
	return distance;
}

void add_value_to_stat(type_stats &stat, long value)
{
	stat.values.push_back(value);
	stat.sum += value;
}

void set_mean_std(type_stats &stats)
{
	stats.mean = (double)stats.sum / stats.values.size();
	double variance = 0.0;
	for (long val: stats.values) {
		/* std::cout << val << " "; */
		variance += pow(val - stats.mean, 2);
	}
	/* std::cout << std::endl; */
	variance /= stats.values.size();
	stats.std_dev = sqrt(variance);
}

//TODO: use template argument
bool is_solution_present(type_solution_set solution_set, type_point point)
{
	if (solution_set.find(point) == solution_set.end()) return false;
	else return true;
}

bool is_solution_present(type_base_map base_map, type_point point)
{
	if (base_map.find(point) == base_map.end()) return false;
	else return true;
}

bool is_solution_present(type_opt_map opt_map, type_point point)
{
	if (opt_map.find(point) == opt_map.end()) return false;
	else return true;
}
