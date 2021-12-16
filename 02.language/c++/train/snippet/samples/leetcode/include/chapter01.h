#pragma once
#include "base.h"

namespace npt
{
    void algorithm_interview_summarize();

    // 1.只出现一次的数字
    // 给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。
    int singleNumber(vector<int> &nums);

    // 2.多数元素
    // 给定一个大小为 n 的数组，找到其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。
    // 你可以假设数组是非空的，并且给定的数组总是存在多数元素。
    int majorityElement(vector<int> &nums);
    int majorityElement2(vector<int> &nums);

    void quick_sort(vector<int> &arr, int begin, int end);
    int partition_hoare(vector<int> &arr, int begin, int end);
    int partition_lomuto(vector<int> &arr, int begin, int end);

    // 3.搜索二维矩阵 II
    // 编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target 。该矩阵具有以下特性：
    // 每行的元素从左到右升序排列。
    // 每列的元素从上到下升序排列。
    bool searchMatrix(vector<vector<int>> &matrix, int target);

    // 4.合并两个有序数组
    // 给你两个按非递减顺序排列的整数数组 nums1 和 nums2，另有两个整数 m 和 n ，分别表示 nums1 和 nums2 中的元素数目。
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n);
}