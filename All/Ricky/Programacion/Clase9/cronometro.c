#include <sys/time.h>

int difMilli(struct timeval tiempo_start, struct timeval tiempo_end){

	int sec_start, micro_start;
	int start;
	int sec_end, micro_end;
	int end;

	sec_start   = tiempo_start.tv_sec & 0xFFF;
	micro_start = tiempo_start.tv_usec;
	start = (sec_start *1000) + (micro_start/1000);

	sec_end   = tiempo_end.tv_sec & 0xFFF;
	micro_end = tiempo_end.tv_usec;
	end = (sec_end *1000) + (micro_end/1000);
	return end - start;
}
