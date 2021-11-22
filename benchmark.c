#include<stdlib.h>
#include<stdio.h>
#include<time.h>

struct timespec time_start = {0, 0}, time_end = {0, 0};
struct timespec time_start_in = {0, 0}, time_end_in = {0, 0};

void write_to_file(char* filename, int N, int S, float time_spent_avg);
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
	
	double time_spent_avg[100]={0},time_spent_avg_sum=0;
			int k=0;
	for(int j=0;j<n_times;j++){
		time_spent_avg[j] = 0;

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
			
			time_spent_avg[j] = 
			(time_spent_avg[j]*i + time_end_in.tv_nsec- 
			time_start_in.tv_nsec)/(i+1);
						
		}
		//clock_gettime(CLOCK_REALTIME, &time_end);
		time_spent_avg_sum += time_spent_avg[j];
		
	}	
//	printf("re:%lf\n",time_spent_avg[0]);
	float time_spent_avg_f = time_spent_avg_sum / n_times_f;
	printf("time_spent_avg : %lf, %d more than 1weis\n",time_spent_avg_f,k);
	
	write_to_file("result_time11_withoutN_changeN.csv", N, k, time_spent_avg_f);
/*
	printf("%lu ns \n",time_start.tv_nsec);
	printf("%lu ns \n",time_end.tv_nsec);
	printf("spend %lu ns\n", time_spent_alln);
	*/
	
	printf("spend average %lf ns\n", (time_spent_avg_f)); 
	
	free(Narray);
	return time_spent_avg[0];
}

void write_to_file(char* filename, int N, int K, float time_spent_avg)
{
	FILE* fp = NULL;
	printf("haha\n");
	char data[100];
	printf("hehe\n");
	sprintf(data,"%d,%d,%f\n",N, K,time_spent_avg);
	fp = fopen(filename,"ab+");
	fputs(data,fp);
	fclose(fp);
	return;
	
}











