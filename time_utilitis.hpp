#ifndef __TIME_UTILITIS_HPP__
#define __TIME_UTILITIS_HPP__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>

typedef enum {
		WHOLE_DATA = 0
		, WITH_ALPHA
		, MAX_TYPE
} TimeStrType;

inline int make_time_raw_str (char *tm_str, int str_len)
{
	int tm_str_len = 0;
	time_t timer = time (NULL);

	return (tm_str_len = snprintf (tm_str, str_len, "%s", ctime (&timer))) <= 0 ? EXIT_FAILURE : tm_str_len - 1;
}

inline int make_time_data_str (char *tm_str, int str_len)
{
	struct tm *p_tm = NULL;
	time_t timer;
	int tm_str_len = 0;

	timer = time (NULL);
	errno = -1;
	p_tm = localtime (&timer);

	INSIST (p_tm != NULL, "localtime syscall error: %s", strerror (errno));

	tm_str_len = strftime (tm_str, str_len, "%Y/%m/%d %H:%M:%S", p_tm);
	*(tm_str + tm_str_len) = '\0';

	return tm_str_len;
}

inline int make_time_str (char *tm_str, int str_len, TimeStrType which_type)
{
	INSIST (tm_str != NULL, "tm_str is NULL");
	INSIST (str_len >= 30, "str_len longer than 30 but got %d", str_len);

	return WHOLE_DATA == which_type ? make_time_data_str (tm_str, str_len) : make_time_raw_str (tm_str, str_len);
}

#endif // __TIME_UTILITIS_HPP__

