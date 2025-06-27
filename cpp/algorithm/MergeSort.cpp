#include <iostream>

int min(int x, int y)
{
    return x < y ? x : y;
}

void mergeSort(int arr[], int len)
{
    int *a = arr;
    int *b = (int *)malloc(len * sizeof(int));
    int seg, start;

    for (seg = 1; seg < len; seg += seg)
    {
        for (start = 0; start < len; start += seg * 2)
        {
            int low = start;
            int mid = min(start + seg, len);
            int high = min(start + seg * 2, len);
            int k = low;
            int start1 = low, end1 = mid;
            int start2 = mid, end2 = high;
            while (start1 < end1 && start2 < end2)
                b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
            while (start1 < end1)
                b[k++] = a[start1++];
            while (start2 < end2)
                b[k++] = a[start2++];
        }
        int *temp = a;
        a = b;
        b = temp;
    }

    if (a != arr)
    {
        for (int i = 0; i < len; i++)
            b[i] = a[i];
    }
    b = a;
    free(b);
}

int main(int argc, char * argv[])
{
    int a[] = {50, 10, 20, 30, 70, 40, 80, 60, 11, 22, 33, 44, 55, 66, 77, 88, 99};
    int array_size = sizeof(a) / sizeof(int);

    for (int i = 0; i < array_size; i++)
    {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;

    mergeSort(a, array_size);

    for (int i = 0; i < array_size; i++)
    {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;

}





