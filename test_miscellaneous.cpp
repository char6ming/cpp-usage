#include <stdlib.h>
#include <stdio.h>

#include <miscellaneous.hpp>

using namespace std;

#define TM_STR_MAX_LEN			(40)

int test_time_func (void)
{
	char tm_str[TM_STR_MAX_LEN] = {0};
	int time_len = 0;

	time_len = make_time_str (tm_str, TM_STR_MAX_LEN, WITH_ALPHA);
	printf ("%s: %d: %.*s\n", __FILE__, __LINE__, time_len, tm_str);

	time_len = make_time_str (tm_str, TM_STR_MAX_LEN, WHOLE_DATA);
	printf ("%s: %d: %.*s\n", __FILE__, __LINE__, time_len, tm_str);

	return EXIT_SUCCESS;
}

int main (int arg_sum, char *args[])
{
	test_time_func ();

	return EXIT_SUCCESS;
}
