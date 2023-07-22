#include <stdio.h>
int main()
{
	int n;
	if (scanf_s("%d", &n) == 1) {
		//正常に入力できた場合
		printf("入力値は %d です。\n", n);
		//条件演算子
		//conditional operator
		//0以外であれば真 (True)
		// BASIC の AND, OR は2進数, & は ２進数だけど、&& と書くと論理演算し
		// BASIC では True は NOT -1, C/C++ で True は 1
		//0であれば偽 (False)
		// BASIC 言語、VB
		printf("入力された値は%sです。\n", n & 1 ? "奇数" : "偶数");
	}
	else {
		//正常に入力できなかった場合
		printf("入力値を読み取ることができませんでした。\n");
	}
}
