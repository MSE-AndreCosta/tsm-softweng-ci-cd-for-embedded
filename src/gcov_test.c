/*
 * Copyright (c) 2023-2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "gcov_test.h"
#include <stdio.h>
#pragma GCC optimize("O3,inline")

static int Calc(int i, int j)
{
	int res;
	if (i == 0) {
		res = i + 1;
	} else if (i > 0 && j < 10) {
		res = i + j;
	}
	return res;
}

static int Value(int i)
{
	if (i == 3) {
		return 5;
	}
	return 1;
}

static void Test2(int *p)
{
	if (*p != 0) {
		if (Value(*p) == 5) {
			printf("value is 5\n");
			*p = 0;
		}
	}
}

static void gcov_test(int i)
{
	int j = Calc(i, i * 2);
	Test2(&j);
	if (j == 0) {
		printf("j is zero!\n");
	} else {
		printf("j is not zero!\n");
	}
}
void run_gcov_test(void)
{
	// Cover Calc branches
	gcov_test(0); // i==0 branch
	gcov_test(1); // i>0 && j<10 branch
	gcov_test(5); // i>0 && j>=10, neither branch

	// Cover Value directly
	Value(3); // return 5 branch
	Value(1); // return 1 branch

	// Cover Test2 directly
	int p = 0;
	Test2(&p); // *p==0, outer if not taken

	int p2 = 3;
	Test2(&p2); // *p!=0, Value(3)==5 → inner if taken, *p=0

	int p3 = 1;
	Test2(&p3); // *p!=0, Value(1)!=5 → inner if not taken
}
