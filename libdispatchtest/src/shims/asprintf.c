#include "config/config.h"

#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/types.h>

#ifndef HAVE_ASPRINTF
int vasprintf(char** str, const char* fmt, va_list ap)
{
	va_list original_ap = ap;
	size_t size = 32;
	int n;
	char* p = NULL;
	char* np = NULL;

	for(;;)
	{
		ap = original_ap;
		if((np = realloc(p, size)) == NULL)
		{
			free(p);
			return -1;
		}
		p = np;
		n = vsnprintf(p, size, fmt, ap);
		va_end(ap);

		if(n > -1 && n < size)
		{
			*str = p;
			return n;
		}
		size *= 2;
	}
}

int asprintf(char **str, const char *fmt, ...)
{
	va_list ap;
	int ret;

	*str = NULL;
	va_start(ap, fmt);
	ret = vasprintf(str, fmt, ap);
	va_end(ap);
	return ret;
}
#endif
