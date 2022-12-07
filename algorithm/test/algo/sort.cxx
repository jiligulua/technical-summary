#include "sort.h"

namespace mars
{
	void Sort::bubbleSort(int arr[], int len)
	{
		//ʹ�����ѭ�������ƱȽϵ�����
		for (int i = 0; i < len; ++i)
		{ 
			//ʹ���ڲ�ѭ��������Ե�ǰ�ֱȽϵ�Ԫ���±�
			bool remainOrder = true;
			for (int j = 0; j < len -i; ++j)
			{
				//�����һ��Ԫ�ش��ڵڶ���Ԫ�أ��򽻻�
				if (arr[j] > arr[j+1])
				{
					int temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;

					//����������Ԫ�ط����˽���
					remainOrder = false;
				}
			}

			// ��ʾ�ղŵ�һ��ɨ����û�з�������
			if (remainOrder)
			{
				// ʡ��ʣ�������
				break;
			}
		}
	}


	void Sort::quickSort(int arr[], int left, int right)
	{
		//1.Ѱ���м�Ԫ����Ϊ��׼ֵ����������
		int p = (left + right) / 2;
		int pivot = arr[p];

		//2.�ֱ�ʹ�����Ԫ�غ��ұ�Ԫ�����׼ֵ���бȽϣ���С�ڻ�׼ֵ��Ԫ�ط�����ߣ������ڵ��ڻ�׼ֵ��Ԫ�ط����ұ�;
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

		// 3.����׼ֵ�����غϵ�λ����
		arr[p] = pivot;

		// 4.�ֱ����߷�����ұ߷����ظ����Ϲ��̣�ʹ�õݹ鴦��
		if (p-left > 1)
		{
			quickSort(arr, left, p - 1);
		}

		if (right-p > 1)
		{
			quickSort(arr, p + 1, right);
		}
	}

	// ���ƶ����ٲ��롣����˼�룺ÿһ����һ������������ݲ��뵽ǰ���Ѿ��ź�������������У�ֱ����������Ԫ��Ϊֹ��
	void Sort::insertSort(int arr[], int len)
	{
		int i = 0, j = 0;
		//�ӵڶ���Ԫ��������ȡ��ÿ��Ԫ��
		for (i = 1; i < len; i++)
		{
			//ʹ����ʱ������¼ȡ���ĵ�ǰԪ��ֵ
			int temp = arr[i];

			//ʹ��ȡ����Ԫ������ߵ������������αȽϣ������ߵ�Ԫ�ش������Ԫ������;
			for (j = i; arr[j - 1] > temp && j >= 1; j--)
			{
				arr[j] = arr[j - 1];
			}

			//ֱ�����Ԫ�ز��ٴ���ȡ��Ԫ��ʱ������ȡ��Ԫ��
			if (j != i)
			{
				arr[j] = temp;
			}
		}
	}

	// ����˼�룺
	// ϣ�������ǰ����а��±��һ���������飬��ÿ��ʹ��ֱ�Ӳ��������㷨����
	// �����������𽥼��٣�ÿ������Ĺؼ���Խ��Խ�࣬����������1ʱ����������ǡ�ñ���Ϊһ�飬�㷨����ֹ��
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

	// ����˼���ǣ�
	// ������δ������������ҵ���С(or���)Ԫ�أ�Ȼ�����ŵ����е���ʼλ�ã�
	// ���ţ��ٴ�ʣ��δ�����Ԫ���м���Ѱ����С(or���)Ԫ�أ�Ȼ��ŵ����������е�ĩβ��
	// �Դ����ƣ�ֱ������Ԫ�ؾ�������ϡ�
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
