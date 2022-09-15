void	mapempty(char **str, size_t i)
{
	str[0] = ft_calloc(sizeof(char), i);
	i -= 1;
	while (i > 0)
	{
		str[0][i - 1] = ' ';
		i--;
	}
}

void	mapcpy(char **a)
{
	int	i;

	i = 0;
	while (a[0][i] && a[1][i])
	{
		if (a[1][i] != '\n')
			a[0][i] = a[1][i];
		i++;
	}
	free(a[1]);
}

void	mapstrcpy(t_game *game, int i)
{
	char	**str;

	str = malloc(sizeof(char *) * 2);
	str[1] = game->map[i];
	mapempty(str, game->width + 1);
	mapcpy(str);
	game->map[i] = *str;
	free(str);
}