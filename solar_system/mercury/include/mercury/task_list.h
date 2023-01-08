#ifndef MERCUY_TASK_LIST_H_
#define MERCUY_TASK_LIST_H_

#include <tuple>
#include <vector>
using std::vector;

namespace mercury {


std::tuple<bool, int, int> GetItemsFromSum(int sum, int *data, int len);
std::tuple<bool, vector<vector<int>>> GetSerial(int sum);


} // namespace mercury


#endif // MERCUY_TASK_LIST_H_
