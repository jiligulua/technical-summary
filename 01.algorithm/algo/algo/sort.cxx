#include "sort.h"

namespace mars
{
	void Sort::bubbleSort(int arr[], int len)
	{
		//使用外层循环来控制比较的轮数
		for (int i = 0; i < len; ++i)
		{ 
			//使用内层循环控制针对当前轮比较的元素下标
			bool remainOrder = true;
			for (int j = 0; j < len -i; ++j)
			{
				//如果第一个元素大于第二个元素，则交换
				if (arr[j] > arr[j+1])
				{
					int temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;

					//表明有数据元素发生了交换
					remainOrder = false;
				}
			}

			// 表示刚才的一轮扫描中没有发生交换
			if (remainOrder)
			{
				// 省略剩余的轮数
				break;
			}
		}
	}


	void Sort::quickSort(int arr[], int left, int right)
	{
		//1.寻找中间元素作为基准值，单独保存
		int p = (left + right) / 2;
		int pivot = arr[p];

		//2.分别使用左边元素和右边元素与基准值进行比较，将小于基准值的元素放在左边，将大于等于基准值的元素放在右边;
		int i = left, j = right;
		while (i < j)
		{
			while (arr[i] < pivot && i < p) ++i;
			if (i < p)
			{
				arr[p] = arr[i];
				p = i;
			}
			while (pivot < arr[j] && p < j) --j;
			if (p < j)
			{
				arr[p] = arr[j];
				p = j;
			}
		}

		// 3.将基准值放在重合的位置上
		arr[p] = pivot;

		// 4.分别对左边分组和右边分组重复以上过程，使用递归处理
		if (p-left > 1)
		{
			quickSort(arr, left, p - 1);
		}

		if (right-p > 1)
		{
			quickSort(arr, p + 1, right);
		}
	}

	// 先移动，再插入。基本思想：每一步将一个待排序的数据插入到前面已经排好序的有序序列中，直到插完所有元素为止。
	void Sort::insertSort(int arr[], int len)
	{
		int i = 0, j = 0;
		//从第二个元素起，依次取出每个元素
		for (i = 1; i < len; i++)
		{
			//使用临时变量记录取出的当前元素值
			int temp = arr[i];

			//使用取出的元素与左边的有序数列依次比较，如果左边的元素大，则左边元素右移;
			for (j = i; arr[j - 1] > temp && j >= 1; j--)
			{
				arr[j] = arr[j - 1];
			}

			//直到左边元素不再大于取出元素时，插入取出元素
			if (j != i)
			{
				arr[j] = temp;
			}
		}
	}

	// 基本思想：
	// 希尔排序是把序列按下标的一定增量分组，对每组使用直接插入排序算法排序；
	// 随着增量的逐渐减少，每组包含的关键词越来越多，当增量减至1时，整个序列恰好被分为一组，算法便终止。
	void Sort::shellSort(int arr[], int len)
	{
		int base = 2;
		int gap = len / base;
		while (gap)
		{
			for (int i = 0; i < gap; ++i)
			{
				for (int j = i + gap; j < len; j += gap)
				{
					int temp = arr[j];
					int m = 0;
					for (m = j; arr[m - gap] > temp && j >= gap; m -= gap)
					{
						arr[m] = arr[m - gap];
					}

					if (m != j)
					{
						arr[m] = temp;
					}
				}
			}
			gap /= base;
		}
	}

	// 基本思想是：
	// 首先在未排序的数列中找到最小(or最大)元素，然后将其存放到数列的起始位置；
	// 接着，再从剩余未排序的元素中继续寻找最小(or最大)元素，然后放到已排序序列的末尾。
	// 以此类推，直到所有元素均排序完毕。
	void Sort::selectSort(int arr[], int len)
	{

	}












	void Sort::heapSort(int arr[], int n, int i)
	{

	}

	void Sort::mergeSort(int arr[], int l, int m, int r)
	{

	}

	void Sort::countSort(int arr[], int len, int maxValue)
	{

	}

	void Sort::bucketSort(int arr[], int len)
	{

	}

	void Sort::radixSort(int arr[], int len, int maxValue)
	{

	}

}
