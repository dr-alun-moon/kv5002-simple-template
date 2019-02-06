/* File age */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <time.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main ( int argc, char *argv[] )
{
	int n;
	struct stat metadata;
	time_t now;
	const size_t len=80;
	char buffer[len];

	now = time(NULL);

	for( n=1 ; n<argc ; n++ ) {
		int err = stat( argv[n], &metadata );
		if( err == -1 ) {
			perror("stat failed");
			exit(EXIT_FAILURE);
		}
		else { 
			time_t access = metadata.st_atime;
			time_t age = (time_t)difftime( now, access );
			printf("file %s has age %ds\n", argv[n], (int)age);
			strftime(buffer, len, "%j days %k hours %M minutes and %S seconds", localtime( &age ) );
			printf("%s\n", buffer);
		}
	}
}

