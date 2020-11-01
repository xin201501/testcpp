#pragma once
#include<iostream>
#include<list>
#include<forward_list>
#include<concepts>
#include<algorithm>
template<std::equality_comparable T>
void deleteNodeInForwardList(std::forward_list<T>& list, const T& x) {
}