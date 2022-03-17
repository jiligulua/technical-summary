#pragma once

namespace mars
{
    void interview();

    void printSpiral();

    class Spiral
    {
        public:
            Spiral(int row, int col);
            ~Spiral();
            void genSprial();
            void print();

        private:
            int **mat;
            int row_;
            int col_;
    };

    class GetMedian
    {
    public:
        void Insert(int num);
        double getMedian();

    private:
        vector<int> maxheap;
        vector<int> minheap;
    };

    bool isPopOrder_31(const int *pPush, const int *pPop, int len);
    bool isPopOrder_31_ex(const int *pPush, const int *pPop, int len);

    void printBinaryTree_32();
    bool isSequenceOfBST(const int *p, int len);
    bool isSequenceOfBST(const int *p, int start, int end);

    void permutation(char *pStr, char *pBeg);
    void printPermutation(char *pStr, int len);

    void swap(int* p, int* q);
    int randomInRange(int start, int end);
    int partition(int str[], int length, int start, int end);

    void quickSort(int data[], int length, int low, int high);

    void testHeap();

    void testMiddle();

    void findNthDigit_44(int n);

    void printMinNumber_45(vector<int> numbers);
}