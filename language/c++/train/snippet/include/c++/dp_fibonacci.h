#pragma once

namespace mars
{
    class Fabonacci
    {
    public:
        Fabonacci();
        ~Fabonacci();

        void run();

    private:
        int calculate_(int i);

    private:
        int n;
    };
}