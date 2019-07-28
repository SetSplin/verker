#include "match_string.h"


int match_string(const char * const *array, size_t n, const char *string)
{
	int index;
	const char *item;

	/*@ loop invariant 0 <= index <= real_len(array, n) <= n;
	    loop invariant \forall size_t k;
	       0 <= k < index ==> strcmp(array[k], string) != 0;
	    loop invariant \forall size_t k;
	       0 <= k < index ==> valid_str(array[k]);
	    loop assigns index, item;
	    loop variant INT_MAX - index;
	 */
	for (index = 0; index < n; index++) {
		item = array[index];
		if (!item)
			break;
		//@ assert valid_str(array[index]);
		if (!strcmp(item, string))
			return index;

		/*@ assert \exists size_t i;
		       0 <= i <= \min(strlen(item), strlen(string)) &&
		       item[i] != string[i];
		 */
	}

	return -EINVAL;
}


#ifdef DUMMY_MAIN

int main(int argc, char *argv[])
{
	const char *str = "12345";
	const char *list[] = {
		"TEST",
		"TST",
		"TS",
		"T",
		"12345",
		NULL
	};

	match_string(list, -1, str);
	match_string(list, 3, str);

	return 0;
}
#endif
