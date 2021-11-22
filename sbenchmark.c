#include<stdlib.h>
#include<stdio.h>
#include<time.h>

struct timespec time_start = {0, 0}, time_end = {0, 0};
struct timespec time_start_in = {0, 0}, time_end_in = {0, 0};

void write_to_file(char* filename, int N, int S, float time_spent_all);
int main(int argc, char* argv[])
{
	if(argc!=4){printf("Input error!\n"); return -1;}
	
	int N = atoi(argv[1]); //N*4bytes array to measure D*4bytes CACHE
	int S = atoi(argv[2]);
	int n_times = atoi(argv[3]);
	float n_times_f = n_times;

	printf("\nN=%d S=%d n_times=%d\n", N, S, n_times);
	

	float* Narray = (float*)malloc(N*4);
	for(int i=0; i<N; i++)
	{
		Narray[i] = 1/(i+1);
	}
	
	//main part
	
	float time_spent_all[100]={0},time_spent_all_sum=0;
	int k=0;
	for(int j=0;j<n_times;j++){
		time_spent_all[j] = 0;
//		clock_gettime(CLOCK_REALTIME, &time_start);
		for(int i=0; i<N; i+=S)
		{
		       
			clock_gettime(CLOCK_REALTIME, &time_start_in);
			while(time_start_in.tv_nsec>90000000){
				clock_gettime(CLOCK_REALTIME, &time_start_in);
			}

			Narray[i] = Narray[i] + time_start.tv_nsec/100000.0;
			
			clock_gettime(CLOCK_REALTIME, &time_end_in);
			
			if((time_end_in.tv_nsec-time_start_in.tv_nsec)>1000){
				k++;
			}
			
			time_spent_all[j] = (time_spent_all[j]*i + time_end_in.tv_nsec- 
			time_start_in.tv_nsec)/(i+1);
						
		}
		//clock_gettime(CLOCK_REALTIME, &time_end);
		time_spent_all_sum += time_spent_all[j];
		
	}	
	free(Narray);
//	printf("re:%lf\n",time_spent_avg[0]);
	float time_spent_all_ll = time_spent_all_sum / n_times_f;
	printf("time_spent_avg : %f, %d more than 1weis\n",time_spent_all_ll,k);
	
	write_to_file("result_s_4_1.5.csv", S, k, time_spent_all_ll);
/*
	printf("%lu ns \n",time_start.tv_nsec);
	printf("%lu ns \n",time_end.tv_nsec);
	printf("spend %lu ns\n", time_spent_alln);
	*/
	
	printf("spend avg %f ns\n", (time_spent_all_ll)); 
	

	return 0;
}

void write_to_file(char* filename, int S, int K, float time_spent_all)
{
	FILE* fp = NULL;
	printf("haha\n");
	char data[100];
	printf("hehe\n");
	sprintf(data,"%d,%d,%f\n",S, K,time_spent_all);
	fp = fopen(filename,"ab+");
	fputs(data,fp);
	fclose(fp);
	return;
	
}











