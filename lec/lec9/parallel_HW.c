#include <stdio.h>
#include <omp.h>
int main(){
	int nthreads, tid;
	/* Fork team of threads with private var tid */
	#pragma omp parallel private(tid)
	{
		tid = omp_get_thread_num();
		printf("Hello World from thread = %d\n", tid);
		/* Only master thread does this */
		if(tid == 0){
			nthreads = omp_get_num_threads();
			printf("Numbers of threads = %d\n", nthreads);
		}
	} /* All threads join master and terminate */
}
