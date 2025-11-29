#include <gnu/libc-version.h>
#include <features.h>
#include <stdio.h>
#include <unistd.h>

const char *gnu_get_libc_version(void);

int main(){

	// Detecting by macros using features.h
	if (__GLIBC__)
		printf("Libc version (compile-time) detected by __GLIBC__ is : %d.%d\n",__GLIBC__,__GLIBC_MINOR__);
	else
		printf("This program has not been compiled with glibc");


	// Detecting by function using gnu/libc-version.h
	printf("Libc version (runtime) detected by gnu_get_libc_version is : %s \n",gnu_get_libc_version());


	// Detecting by confstr using unistd.h for _CS_GNU_LIBC_VERSION
	long size = confstr(_CS_GNU_LIBC_VERSION,NULL,0);
	if(!size)
		printf("This system is not using glibc \n");

	else {
		char buffer[size];
		confstr(_CS_GNU_LIBC_VERSION,buffer,size);
		printf("Libc version (runtime) detected by confstr() is : %s \n",buffer);
	}

	return 0;
}

