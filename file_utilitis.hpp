#ifndef __FILE_UTILITIS_HPP__
#define __FILE_UTILITIS_HPP__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#define BUF_SIZE			((1024)*(1))

inline const long long get_file_size (const char *const file)
{
	if (NULL == file) {

		return -1;
	}

	if (access (file, F_OK)) {

		return -2;
	}
	
	struct stat file_stat;

	return stat (file, &file_stat) ? 0 : file_stat.st_size;
}

inline int get_file_content (const char *const file, char *out_buf, int out_buf_size, int &out_buf_len)
{
	if ((NULL == file) || (NULL == out_buf) || (out_buf_size <= 0)) {

		return -1;
	}

	if (access (file, F_OK)) {

		return -2;
	}
	
	int tmp_len = 0;
	int all_len = 0;
	long long content_size = 0LL;
	int rt_val = 0;
	FILE *fp = NULL;
	char tmp_buf[BUF_SIZE];

	if (0 >= (content_size = get_file_size (file))) {

		return content_size; 
	}

	if (out_buf_size < content_size) {

		return -3;
	}

	if (NULL == (fp = fopen (file, "rb"))) {

		return -4;
	}

	while (all_len < content_size) {
		tmp_len= fread (tmp_buf, 1, BUF_SIZE, fp);
		errno = 0;
		if (tmp_len <= 0) {
			printf ("fread :%d\n", errno);

			break;
		}

		memcpy (out_buf, tmp_buf, tmp_len);
		out_buf += tmp_len;
		all_len += tmp_len;
	}

	out_buf_len = all_len;
	fclose (fp);
	fp = NULL;

	return rt_val;
}

#endif // __FILE_UTILITIS_HPP__

