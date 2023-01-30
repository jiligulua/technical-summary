def search(sequence, num, low=0, upper=None):
    if upper is None:
        upper = len(sequence)-1
    if low == upper:
        assert num == sequence[low]
        return low
    else:
        mid = (low+upper) // 2
        if num > sequence[mid]:
            return search(sequence, num, mid+1, upper)
        else:
            return search(sequence, num, low, mid)


