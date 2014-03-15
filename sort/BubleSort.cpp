void bubleSort(int a[], int n)
{
	int j, k;
	int flag;

	flag = n;
	while (flag > 0)
	{
		k = flag;
		flag = 0;
		for (j = 1; j < k; ++j)
		{
			if (a[j - 1] > a[j])
			{
				swap(a[j - 1], a[j]);
				flag = j;
			}
		}
	}
}