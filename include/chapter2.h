#pragma once
#include<concepts>
#include<vector>
#include<numeric>
#include<algorithm>
namespace myAlgorithm {
    template<std::integral T>
    T findMin(const std::vector<T>& v) {
        T curMin;
        for (const auto x : v) {
            if (x < curMin) {
                curMin = x;
            }
        }
        return curMin;
    }
    template<std::integral T>
    T deleteMin(std::vector<T>& v) {
        auto curMinIndex = v.begin();
        for (auto i = v.begin();i != v.end();i++) {
            if ((*i) < *curMinIndex) {
                curMinIndex = i;
            }
        }
        auto curMin = *curMinIndex;
        v.erase(curMinIndex);
        return curMin;
    }
    template<std::bidirectional_iterator T>
    void reverse(T& i1, T& i2) {
        if (i1 == i2) {
            return;
        }
        i2--;
        for (;i1 != i2;i1++, i2--) {
            std::swap(*i1, *i2);
        }
    }
    template<typename T>
    void reverse(std::vector<T>& v) {
        reverse(v.begin(), v.end());
    }
    template<std::equality_comparable T>
    void deleteIfEqual(std::vector<T>& v, T x) {
        size_t size = v.size(), movePos = 0;
        for (size_t curPos = 0;curPos < size;curPos++) {
            if (v[curPos] == x) {
                movePos++;
            }
            else
            {
                v[curPos - movePos] = v[curPos];
            }
        }
        v.resize(size - movePos);
    }
    //delete all elements meet x<=elem<=y for Ordered vector.
    template<std::three_way_comparable T>
    void deleteRangeInOrderedVector(std::vector<T>& v, T x, T y) {
        if (x >= y || v.empty()) {
            throw std::invalid_argument("x must < y!");
        }
        size_t size = v.size(), movePos = 0, curPos = 0;
        for (;curPos < size && v[curPos] < x;curPos++)
            ;
        for (;curPos < size && v[curPos] <= y;curPos++) {
            movePos++;
        }
        for (;curPos < size;curPos++) {
            v[curPos - movePos] = v[curPos];
        }
        v.resize(size - movePos);
    }
    template<std::three_way_comparable T>
    void deleteRangeInUnOrderedVector(std::vector<T>& v, T x, T y) {
        if (x >= y || v.empty()) {
            throw std::invalid_argument("x must < y!");
        }
        size_t size = v.size(), movePos = 0;
        for (size_t curPos = 0;curPos < size;curPos++) {
            if (v[curPos] >= x && v[curPos] <= y) {
                movePos++;
            }
            else
            {
                v[curPos - movePos] = v[curPos];
            }
        }
        v.resize(size - movePos);
    }
    template<std::equality_comparable T>
    void deleteEqualElementsInOrderedVector(std::vector<T>& v, T x) {
        size_t size = v.size(), movePos = 0, curPos = 0;
        for (;curPos < size && v[curPos] < x;curPos++)
            ;
        for (;curPos < size && v[curPos] == x;curPos++) {
            movePos++;
        }
        for (;curPos < size;curPos++) {
            v[curPos - movePos] = v[curPos];
        }
        v.resize(size - movePos);
    }
    template<std::three_way_comparable T>
    [[nodiscard("merge result must be kept.")]]
    auto mergeTwoOrderedVectors(const std::vector<T>& v1, const std::vector<T>& v2) {
        std::vector<T> result;
        size_t curPos1 = 0, curPos2 = 0, size1 = v1.size(), size2 = v2.size(), compareCount = size1 < size2 ? size1 : size2;
        while (curPos1 < compareCount && curPos2 < compareCount) {
            if (v1[curPos1] <= v2[curPos2]) {
                result.push_back(v1[curPos1++]);
            }
            else {
                result.push_back(v2[curPos2++]);
            }
        }
        while (curPos1 < size1) {
            result.push_back(v1[curPos1++]);
        }
        while (curPos2 < size2) {
            result.push_back(v2[curPos2++]);
        }
        return result;
    }
    //vector[0,m)[m+1-最后]分别为两个有序序列，将两个序列交换位置，内部顺序不变
    template<typename T>
    void reverseSubVector(std::vector<T>& v1, size_t m) {
        [[unlikely]] if (m >= v1.size()) {
            throw std::out_of_range("m is beyond the size of this vector.");
        }
        reverse(v1.begin(), v1.end());
        reverse(v1.begin(), v1.begin() + m + 1);
        reverse(v1.begin() + m + 1, v1.end());
    }
    template<std::three_way_comparable T>
    void findThenSwapOrInsertInOrderedVector(std::vector<T>& v1, T num) {
        int mid, begin = 0, end = v1.size() - 1;
        while (begin <= end) {
            mid = std::midpoint(begin, end);
            if (v1[mid] < num) {
                begin = mid + 1;
            }
            else if (v1[mid] > num) {
                end = mid - 1;
            }
            else {
                break;
            }
        }
        if (begin <= end) {
            std::swap(v1[mid], v1[mid + 1]);
        }
        else {
            v1.insert(v1.begin() + end + 1, num);
        }
    }
    template<std::integral T>
    void roundShift(std::vector<T>& v, size_t roundShiftNum) {
        reverse(v.begin(), v.begin() + roundShiftNum);
        reverse(v.begin() + roundShiftNum, v.end());
        reverse(v);
    }
    template<std::three_way_comparable T>
    T findMidpointInTwoVectors(const std::vector<T>& v1, const std::vector<T>& v2) {
        int s1 = 0, d1 = v1.size() - 1, m1, s2 = 0, d2 = d1, m2;
        while (s1 != d1 || s2 != d2) {
            m1 = std::midpoint(s1, d1);
            m2 = std::midpoint(s2, d2);
            if (v1[m1] == v2[m2]) {
                return m1;
            }
            if (v1[m1] < v2[m2]) {
                s1 = 0 == (s1 + d1) % 2 ? m1 : m1 + 1;
                d2 = m2;
            }
            else {
                s2 = 0 == (s2 + d2) % 2 ? m2 : m2 + 1;
                d1 = m1;
            }
        }
        return v1[s1] < v2[s2] ? v1[s1] : v2[s2];
    }
    template<std::integral T>
    T findMinPostiveInterger(const std::vector<T>& v) {
        std::vector isAppear(v.size(), false);
        for (auto&& x : v) {
            if (x > 0) {
                isAppear[x - 1] = true;
            }
        }
        size_t i = 0;
        for (size_t size = isAppear.size();i < size;i++) {
            if (!isAppear[i]) {
                return i + 1;
            }
        }
        return i + 1;
    }
}