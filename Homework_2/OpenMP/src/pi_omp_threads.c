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

//gcc -fopenmp pi_omp_threads.c -o pi_omp_threads
//./pi_omp_threads

#include <omp.h>
#include <stdio.h>

static long num_steps = 1000000000; 
double step;

void main () { 
	int i, a; 
	double x, pi, sum = 0.0;
	double start_time, run_time;
	int num_threads = 4;
	
	step = 1.0/(double) num_steps;
	
	for (a=1; a <= num_threads; a++){
		
		start_time = omp_get_wtime();
		sum = 0;
		
		//Creates a team of OpenMP threads that execute the region
		//num_threads -> Sets the nthreads-var ICV for the number of threads to use for parallel regions
		#pragma omp parallel num_threads(a)
		{
			//reduction -> Specifies a reduction-identifier and one or more list items
			//	In order to specify the reduction in OpenMP, we must provide
			//		an operation (+ / * / o)
			//		and a reduction variable 
			//private -> Declares list items to be private to a task
			#pragma omp for reduction(+:sum) private(x) 
			for (i=0; i< num_steps; i++){
				x = (i+0.5)*step;
				sum = sum + 4.0/(1.0+x*x);
			}
		}
		pi = step * sum;
		run_time = omp_get_wtime() - start_time;
		printf("num_threads = %d\n", a);
		printf("pi with %ld steps is %lf in %lf seconds\n", num_steps, pi,run_time);
	}
}

