/*****************************************************************/
// Adapted from the BLS source code.
//
// Copyright : Una Benlic, 2012
// This code can be freely used for non-commercial purpose.
// Any use of this implementation or a modification of the code
// must acknowledge the work of U. Benlic and J.K. Hao
/****************************************************************/
#include "best_improv.hpp"

type_matrix copy_matrix(type_matrix original, int n)
{
	type_matrix copy = new long*[n];
	for(int i = 0; i < n; i++) {
		copy[i] = new long[n];
		for(int j = 0; j < n; j++) {
			copy[i][j] = original[i][j];
		}
	}
	return copy;
}

void update_matrix_of_move_cost(int i_retained, int j_retained,long n, type_matrix & delta, type_vector & p, type_matrix & a, type_matrix & b)
{
     int i, j;
     for (i = 0; i < n-1; i = i+1) for (j = i+1; j < n; j = j+1)
        if (i != i_retained && i != j_retained &&
            j != i_retained && j != j_retained) {
		 delta[i][j] = compute_delta_part(a, b, p, delta, i, j,
				 i_retained, j_retained);
         } else {
		 delta[i][j] = compute_delta(n, a, b, p, i, j);
	 }
}

void apply_move(type_vector & p,long n, type_matrix & delta, long &
		current_cost, type_matrix a, type_matrix b,int i_retained, int
		j_retained)
{
	if(i_retained!=-1 && j_retained!=-1) // apply the selected perturbation move
	{
		transpose(p[i_retained], p[j_retained]);
		current_cost = current_cost + delta[i_retained][j_retained];
		update_matrix_of_move_cost(i_retained, j_retained, n, delta, p, a, b);
	}
}

void allocate_memory_and_initialize(type_vector & p, long n, type_matrix &
		delta, long & current_cost, type_matrix a, type_matrix b)
{
	int i, j;
	/***************** dynamic memory allocation *******************/
	delta = new long* [n+1];
	for (i = 0; i < n; i = i+1)
	{
		delta[i] = new long[n+1];
	}
	/********** initialization of current solution value ***********/
	/**************** and matrix of cost of moves  *****************/
	current_cost = 0;
	for (i = 0; i < n; i = i + 1) {
		for (j = 0; j < n; j = j + 1) {
			current_cost = current_cost + a[i][j] * b[p[i]][p[j]];
			if (i < j) {
				delta[i][j] = compute_delta(n, a, b, p, i, j);
			}
		}
	}
}

bool best_improvement_move(type_vector &p, long n, type_matrix & delta, long &
		current_cost, type_matrix a, type_matrix b)
{
	int i, j, i_retained, j_retained;
	long min_delta = infinite;   // retained move cost
	//select the best swap move for the descent local search phase
	for (i = 0; i < n-1; i = i + 1) {
		for (j = i+1; j < n; j = j+1) {
			if(delta[i][j] < min_delta) {
				i_retained = i; j_retained = j;
				min_delta = delta[i][j];
			}
		}
	}
	// apply the above selected move if it leads to a solution better than the current one
	if((current_cost + delta[i_retained][j_retained])<current_cost) {
		apply_move(p, n, delta, current_cost, a, b, i_retained, j_retained);
		return 1;
	} else {
		return 0;
	}
}

int best_improvement_ls(type_vector &solution, long &cost, type_matrix delta,
		type_matrix a, type_matrix b, int n)
{
	/* type_matrix delta = copy_matrix(initial_delta, n); */
	/* allocate_memory_and_initialize(solution, n, delta, cost, a, b); */
	int descent_count = 0;
	bool descent = best_improvement_move(solution, n, delta, cost, a, b);
	while(descent) { // while an improving solution in the neighborhood exists
		descent_count++;
		descent = best_improvement_move(solution, n, delta, cost, a, b);
	}
	return descent_count;
}
