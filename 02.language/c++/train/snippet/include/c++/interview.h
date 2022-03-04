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

    bool isPopOrder_31(const int *pPush, const int *pPop, int len);
    bool isPopOrder_31_ex(const int *pPush, const int *pPop, int len);

    void printBinaryTree_32();
    bool isSequenceOfBST(const int *p, int len);
    bool isSequenceOfBST(const int *p, int start, int end);
}