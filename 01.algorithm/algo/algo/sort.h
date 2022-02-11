#pragma once

namespace mars
{
	class Sort
	{
	public:
		// �Ƚ�������
		// ��������
		void bubbleSort(int arr[], int len);
		void quickSort(int arr[], int left, int right);

		// ��������
		void insertSort(int arr[], int len); // �򵥲�������
		void shellSort(int arr[], int len); // ��������ı���

		// ѡ������
		void selectSort(int arr[], int len); // ��ѡ������
		void heapSort(int arr[], int n, int i); // ������
		
		// �鲢����
		void mergeSort(int arr[], int l, int m, int r);

		// �ǱȽ�������
		// ��������
		void countSort(int arr[], int len, int maxValue);

		// Ͱ����
		void bucketSort(int arr[], int len);

		// ��������
		void radixSort(int arr[], int len, int maxValue);

	};
}
