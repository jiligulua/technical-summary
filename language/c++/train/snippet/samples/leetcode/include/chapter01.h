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

    // 5.给你 k 枚相同的鸡蛋，并可以使用一栋从第 1 层到第 n 层共有 n 层楼的建筑。已知存在楼层 f ，满足 0 <= f <= n ，
    // 任何从 高于 f 的楼层落下的鸡蛋都会碎，从 f 楼层或比它低的楼层落下的鸡蛋都不会破。每次操作，你可以取一枚没有碎的
    // 鸡蛋并把它从任一楼层 x 扔下（满足 1 <= x <= n）。如果鸡蛋碎了，你就不能再次使用它。如果某枚鸡蛋扔下后没有摔碎，
    // 则可以在之后的操作中 重复使用 这枚鸡蛋。请你计算并返回要确定 f 确切的值 的 最小操作次数 是多少？
    int superEggDrop(int k, int n);
}