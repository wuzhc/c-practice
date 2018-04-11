#include <stdio.h>

int main(void) {
    int numbers[10] = {7,5,8,9,6,1,2,3,4,0};
    int i = 0; // 开始标识位置
    int j = 9; // 最后标识位置
    int n = 0;
    int temp; // 存放临时值

    while (i < j) {

        while (i < j) {
            // 从头开始找偶数的值
            if (numbers[i] % 2 == 0) {
                break;
            }
            i++; // 找不到向后移动一位，直到找到为止
        }

        while (i < j) {
            // 从尾开始找奇数的值
            if (numbers[j] % 2 != 0) {
                break;
            }
            j--;
        }

        // 更换前后两个值
        if (i != j) {
            temp = numbers[i];
            numbers[i] = numbers[j];
            numbers[j] = temp;
        }
    }

    for (n = 0; n < 10; n++) {
        printf("%d ," , numbers[n]);
    }

	return 0;
}
