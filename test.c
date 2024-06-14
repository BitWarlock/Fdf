#include "libft/libft.h"
#include <libc.h>
int	search_comma(char *str)
{
	while (*str)
	{
		if (*str == ',')
			return (1);
		str++;
	}
	return (0);
}
void	parse_color(char **strs, int **color)
{
	char	**str;
	int	i;

	i = 0;
	*color = malloc(sizeof(int) * 4);
	while (strs[i])
	{
		if (search_comma(strs[i]))
		{
			str = ft_split(strs[i], ',');
			if (str[1] != NULL)
				(*color)[i] = atoi_base(str[1], 16);
		}
		else
			(*color)[i] = 0xFFFFFF;
		i++;
	}
}

int main(void)
{
	char *strs[5] = {"0,0xa", "6", "3,0xb", "2,0xa", NULL};
	int *c;
	parse_color(strs, &c);
	for (int i = 0; i < 4; i++)
		printf("%d\n", c[i]);

	return EXIT_SUCCESS;
}
