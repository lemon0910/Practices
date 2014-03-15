void InsertSort(int a[], int n)
{
	for (int i = 1; i < n; ++i)
	{
		if (a[i - 1] > a[i])
		{
			int j = i;
			while (j > 0)
			{
				if (a[j - 1] > a[j])
				{
					swap(a[j - 1], a[j]);
					j--;
				}
				else
				{
					break;
				}
			}
		}
	}
}