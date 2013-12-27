#ifndef __FILE_UTILITIS_HPP__
#define __FILE_UTILITIS_HPP__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>


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

inline int exec_cmd (const char *cmd, char *ret_buf, int max_buf_size)
{
	FILE* fp = popen (cmd, "r");

	if (NULL == fp) {

		return -1;
	}

	int len = 0;
	char *p = NULL;
     
	while (1) {
		if ((NULL == (p = fgets (ret_buf + len, max_buf_size - len, fp))) || (len + 1 == max_buf_size)) {

			break;
		}

		len += strlen (p);
	}

	pclose (fp);

	return len + 1 == max_buf_size ? -2 : len;
}

int daemonize (void)
{
	pid_t pid = fork ();

	if (pid < 0) {

		return -1;
	} else if (pid > 0) {

		exit (-1);
	}

	umask (0);

	pid_t sid = setsid ();

	if (sid < 0) {

		return -2;
	}

	if (chdir ("/") < 0) {

		return -3;
	}

	close (STDIN_FILENO);
	close (STDOUT_FILENO);
	close (STDERR_FILENO);

	open ("/dev/null", O_RDONLY);
	open ("/dev/null", O_RDWR);
	open ("/dev/null", O_RDWR);

	// we should block sigpipe if use socket syscall
	sigset_t signal_mask;
	sigemptyset (&signal_mask);
	sigaddset (&signal_mask, SIGPIPE);
	if (pthread_sigmask (SIG_BLOCK, &signal_mask, NULL)) {
		printf ("%s: %d: block sigpipe failure\n", __FILE__, __LINE__);

		return -4;
	}

	return 0;
}

#endif // __FILE_UTILITIS_HPP__
