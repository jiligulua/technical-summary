#pragma once

namespace mars
{
	class Sort
	{
	public:
		// 比较类排序
		// 交换排序
		void bubbleSort(int arr[], int len);
		void quickSort(int arr[], int left, int right);

		// 插入排序
		void insertSort(int arr[], int len); // 简单插入排序
		void shellSort(int arr[], int len); // 插入排序的变种

		// 选择排序
		void selectSort(int arr[], int len); // 简单选择排序
		void heapSort(int arr[], int n, int i); // 堆排序
		
		// 归并排序
		void mergeSort(int arr[], int l, int m, int r);

		// 非比较类排序
		// 计数排序
		void countSort(int arr[], int len, int maxValue);

		// 桶排序
		void bucketSort(int arr[], int len);

		// 基数排序
		void radixSort(int arr[], int len, int maxValue);

	};
}
