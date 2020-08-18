/*
 * Tecnologico de Costa Rica (www.tec.ac.cr)
 * Course: MP-6171 High Performance Embedded Systems
 * Developers Name: Verny Morales and Luis Carlos Alvarez
 * Developers email: verny.morales@gmail.com and lcam03@gmail.com
 * General purpose: 
 * Input: 
 * Output: 
 *
 */

//gcc -fopenmp pi_omp_teams.c -o pi_omp_teams
//./pi_omp_teams

#include <omp.h>
#include <stdio.h>

static long num_steps = 1000000000; 
double step;

void main () { 
	int i; 
	double x, pi, sum = 0.0;
	double start_time, run_time;
	int num_teams = 3;
	
	step = 1.0/(double) num_steps;
	start_time = omp_get_wtime();

	//target -> Map variables to a device data environment and execute the construct on that device
	//teams distribute parallel for -> Shortcut for specifying a teams construct containing a distribute parallel worksharing-loop construct and no other statements. 
	//num_teams -> Sets the number of teams in the current teams region
	//reduction -> Specifies a reduction-identifier and one or more list items
	//	In order to specify the reduction in OpenMP, we must provide
	//		an operation (+ / * / o)
	//		and a reduction variable 
	//private -> Declares list items to be private to a task
	//map -> Map an original list item from the current task’s data environment to a corresponding list item in the device data environment of the device identified by the construct.

	#pragma omp target teams distribute parallel for num_teams(num_teams) reduction(+:sum) private(x) map(tofrom:sum)
	for (i=0; i< num_steps; i++){
		x = (i+0.5)*step;
		sum = sum + 4.0/(1.0+x*x);
	}
	
	pi = step * sum;
	run_time = omp_get_wtime() - start_time;
	printf("pi with %ld steps is %lf in %lf seconds\n", num_steps, pi,run_time);
}

