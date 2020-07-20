

#include "printf.h"

#include <wchar.h>

// This is all the stuff i need to add back in if I want to have %ls or %lc work
// It was pretty much all 'borrowed' from Pascal...


void		*ftpf_memset(void *b, int c, size_t n)
{
	size_t  i;

	i = 0;
	while (i < n)
	{
		*(unsigned char*)(b + i) = (unsigned char)c;
		++i;
	}
	return (b);
}


char		ftpf_wchar_len(wchar_t c)
{
	char    len;

	if (c <= 0xff && MB_CUR_MAX == 1)
		len = 1;
	else
		len = 1 + (c > 0x7f) + (c > 0x7ff) + (c > 0xffff);
	return ((c < -1 || c > 0x10ffff || (c >= 0xd800 && c <= 0xdfff)
			|| len > MB_CUR_MAX) ? -1 : len);
}

int			ftpf_convert_wchar(wchar_t c, char *str)
{
	if (c < -1 || (c >= 0xd800 && c <= 0xdfff) || c > 0x10ffff)
		return (0);
	else if (c <= 0x7F || (MB_CUR_MAX == 1 && c <= 0xFF))
		str[0] = c ? (char)c : 0;
	else if (c <= 0x7FF && MB_CUR_MAX >= 2)
	{
		str[0] = (c >> 6 | 0xC0) & 0xDF;
		str[1] = (c | 0x80) & 0xBF;
	}
	else if (c <= 0xFFFF && MB_CUR_MAX >= 3)
	{
		str[0] = (c >> 12 | 0xE0) & 0xEF;
		str[1] = (c >> 6 | 0x80) & 0xBF;
		str[2] = (c | 0x80) & 0xBF;
	}
	else if (c <= 0x10FFFF && MB_CUR_MAX >= 4)
	{
		str[0] = (c >> 18 | 0xF0) & 0xF7;
		str[1] = (c >> 12 | 0x80) & 0xBF;
		str[2] = (c >> 6 | 0x80) & 0xBF;
		str[3] = (c | 0x80) & 0xBF;
	}
	else
		return (0);
	return (1);
}


int			ft_cast_s(va_list *ap, t_param *p, char **str)
{
	wchar_t *s;
	char    tmp[5];
	char    *atmp;
	char    char_len;
	size_t  i;

	i = 0;
	if (p->size & C_L)
	{
		s = va_arg(*ap, wchar_t*);
		printf("s: |%ls|\n", s);
		while (*s)
		{
			ftpf_memset(tmp, 0, 5);
			ftpf_convert_wchar(*s, tmp);
			printf("tmp: |%s|\n", tmp);
			char_len = ftpf_wchar_len(*s);
			atmp = ft_fstrdup(tmp);
			printf("atmp: |%s|\n", atmp);
			*str = ft_fstrjoin(str, &atmp);
			i += char_len;
			++s;
		}
		printf("str: |%s|\n", *str);
	}
	else
		*str = ft_fstrdup(va_arg(*ap, char*));
	return (1);
}




