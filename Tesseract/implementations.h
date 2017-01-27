bool cstrcmp(const char* s1, const char* s2)
{
	while (*s1 && (*s1 == *s2))
		s1++, s2++;
	if (*(const unsigned char*)s1 - *(const unsigned char*)s2 == 0)
		return true;
	else
		return false;
}
int getstrLen(const char* str) { int i = 0; for (i = 0; i < 0x600; i++) { if (*(str + i) == 0x00) break; }return i; }
int strCmp(const char* str1, const char* str2)
{
	int diff = 0;

	if (*(str1) == 0x00 || *(str2) == 0x00) { return -1; }

	for (int i = 0; i < 0x600; i++)
	{
		if (*(str1 + i) == 0x00 || *(str2 + i) == 0x00) { break; }
		if (*(str1 + i) != *(str2 + i)) { diff++; }
	}

	return diff;
}
void memSet(char* ptr, char value, size_t size)
{
	for (int i = 0; i < size; i++)
	{
		ptr[i] = value;
	}
}
int _Atoi(char *str)
{
	int res = 0;
	for (int i = 0; str[i] != '\0'; ++i)
		res = res * 10 + str[i] - '0';
	return res;
}
char *_strcat(char* s, const char* t)
{
	int i = 0;

	while (s[i] != '\0')
		i++;
	while (*t != '\0')
		s[i++] = *t++;
	s[i] = '\0';
	return (s);
}
static const int A = 15342; // any number in (0, RAND_MAX)
static const int C = 45194; // any number in [0, RAND_MAX)
static const int max_rand = 100000;
int _rand()
{
	static int prev = 0; //seed. any number in [0, RAND_MAX)
	prev = (prev * A + C) % max_rand;
	return prev;
}