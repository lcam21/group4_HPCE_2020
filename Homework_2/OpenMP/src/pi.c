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

//gcc -fopenmp pi.c -o pi
//./pi

#include <omp.h>
#include <stdio.h>

static long num_steps = 1000000000;
double step;

void main() {
	int i;
	double x, pi, sum = 0.0;
	double start_time, run_time;
	
	step = 1.0 / (double)num_steps;
	start_time = omp_get_wtime();
	
	for (i = 1; i <= num_steps; i++) {
		x = (i - 0.5) * step;
		sum = sum + 4.0 / (1.0 + x * x);
	}
		
		pi = step * sum;
		run_time = omp_get_wtime() - start_time;
		printf("pi with %ld steps is %lf in %lf seconds\n", num_steps, pi, run_time);
}
