#include <iostream>
#include <cstdio>

void Merge(int sourceArr[],int tempArr[], int startIndex, int midIndex, int endIndex)
{
    int i = startIndex, j = midIndex + 1, k = startIndex;
    while (i != midIndex + 1 && j != endIndex + 1)
    {
        if (sourceArr[i] > sourceArr[j])
            tempArr[k++] = sourceArr[j++];
        else
            tempArr[k++] = sourceArr[i++];
    }
    while (i != midIndex + 1)
        tempArr[k++] = sourceArr[i++];
    while (j != endIndex + 1)
        tempArr[k++] = sourceArr[j++];
    for (i = startIndex; i <= endIndex; i++)
    {
        sourceArr[i] = tempArr[i];
        std::cout << tempArr[i] << " ";
    }
    std::cout << std::endl;
}

//内部使用递归
void MergeSort(int sourceArr[], int tempArr[], int startIndex, int endIndex)
{
    int midIndex;
    if (startIndex < endIndex)
    {
        midIndex = startIndex + (endIndex-startIndex) / 2;//避免溢出int
        MergeSort(sourceArr, tempArr, startIndex, midIndex);
        MergeSort(sourceArr, tempArr, midIndex+1, endIndex);
        Merge(sourceArr, tempArr, startIndex, midIndex, endIndex);
    }
}
 
int main(int argc, char * argv[]) {
    int a[] = {50, 10, 20, 30, 70, 40, 80, 60, 11, 22, 33, 44, 55, 66, 77, 88, 99};
    int array_size = sizeof(a) / sizeof(int);
    int i, b[array_size];

    for (int i = 0; i < array_size; i++)
    {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;

    MergeSort(a, b, 0, array_size - 1);

#if 0
    for(i=0; i<8; i++)
        printf("%d ", a[i]);
    printf("\n");
#endif

    return 0;
}
