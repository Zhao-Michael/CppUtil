#include <tuple>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <memory>

using namespace std;

/*
*
C++ 14:


�����ķ��������Ƶ�
���� lambda
lambda ��ʼ������
new/delete ����
constexpr �����Ϸ��ɵ�����
������������
��λ�ָ���
��Ĭ�ϳ�Ա��ʼ�����ľۺ��ࡣ
����ģ��

std::make_unique
std::shared_timed_mutex �� std::shared_lock
std::integer_sequence
std::exchange
std::quoted

C++ 17:

std::any, std::optional, std::string_view, std::apply, polymorphic allocators, searchers.

u8 �ַ�������
�� noexcept ��Ϊ����ϵͳ��һ����
�µ���ֵ˳�����
lambda ���ʽ���� *this
constexpr
	�����ڵ� constexpr if ���
	constexpr �� lambda ���ʽ
����
	inline ����
	�ṹ����
	if �� switch ����еĳ�ʼ����
	ǿ�Ƶĸ�������
	��ʱ��ʵ�ʻ�
ģ��
	�۵����ʽ
	��ģ��ʵ���Ƶ�
	auto ռλ�ķ�����ģ���β�
�����ռ�
	�򻯵�Ƕ�������ռ�
	using ���������������������
	���������ռ䲻���ظ�
�����ԣ�
	[[fallthrough]]
	[[nodiscard]]
	[[maybe_unused]]
__has_include

*/

int DigitSeparators()
{
	int i = 100'000'000;
	return i;
}

void BinaryLiterals()
{
	auto i = 0b01'000'111;
}

auto AutoReturn()
{
	map<string, int> result;
	return result;
}

constexpr int Fibonacci(int n)
{
	switch (n)
	{
	case 0: return 0;
	case 1: return 1;
	default:
		return Fibonacci(n - 1) + Fibonacci(n - 2);
	}
}

void ConstexprInCompile()
{
	static_assert(Fibonacci(10) == 55);
	// static_assert(Fibonacci(10) == 2);  // compile failed
}

template<typename T>
constexpr T maxValue = T(1000);

template<>
constexpr double maxValue<double> = 2000;

template<>
constexpr char maxValue<char> = 'a';

void VariableTemplate()
{
	cout << maxValue<int> << endl;
	cout << maxValue<double> << endl;
	cout << maxValue<char> << endl;
}

[[deprecated("This is deprecated")]]
void deprecatedFunc()
{
	cout << "deprecated func" << endl;
}

void StructBinding()
{
	tuple<double, int> G = { 1.3,2 };
	auto& [a, b] = G;
	cout << a << endl;

	map<int, string> mapA;
	auto& [i, j] = mapA.insert({ 1,"bd" });
	cout << i->first << i->second << j << endl;

	for (const auto& [i, j] : mapA) {
		cout << i << j << endl;
	}

}

void GenicLambda()
{
	vector<int> lines = { 8, 1,6,7,3,7,9,3,6 };

	sort(begin(lines), end(lines),
		[](const auto& a, const auto& b) {
			return a < b;
		});

	cout << lines.front() << endl;
}

void LambdaMove()
{
	auto a = make_unique<int>(1754);

	auto lambda = [ptr = move(a)]()
	{
		cout << *ptr << endl;
	};

	lambda();

	if (a == nullptr) {
		cout << "a is empty" << endl;
	}
}

namespace A {
	namespace B {
	}
}

namespace A::B {
}

void DefineVariableInIfSwith()
{
	string a = "abc123";

	if (const auto it = find(a.begin(), a.end(), 'b'); it != end(a))
	{
		cout << "Find : " << *it << endl;
	}
	else {
		cout << "Not Find : " << *it << endl;
	}


	switch (int it = 1; it)
	{
	case 0: return;
	case 1: return;
	default:
		return;
	}
}

template<typename T>
auto length(const T& value)
{
	if constexpr (is_integral<T>::value) {
		return value;
	}
	else {
		return value.length();
	}
}


struct MyClass
{
	static const int sValue;
};

inline int const MyClass::sValue = 777;

void RunCpp14()
{
	deprecatedFunc();
	VariableTemplate();
	StructBinding();
	GenicLambda();
	LambdaMove();
	DefineVariableInIfSwith();

	int len1 = length(123);
	int len2 = length(string("abc"));

	cin.get();
}