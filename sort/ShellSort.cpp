void ShellSort(int a[], int n)
{
	for (int gap = n / 2; gap > 0; gap /= 2)
	{
		for (int i = 0; i < gap; ++i)
		{
			for (int j = i + gap; j < n; j += gap)
			{
				if (a[j] < a[j - gap])
				{
					int temp = a[j];
					int k = j - gap;
					while (k >= 0 && a[k] > temp)
					{
						a[k + gap] = a[k];
						k -= gap;
					}
					a[k + gap] = temp;
				}
			}
		}
	}
}