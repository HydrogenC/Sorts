#include <ctime>
#include "main.h"

int inputElement(llong in[], llong length) {
    for (llong i = 0; i < length; i += 1) {
        cin >> in[i];
    }
}

bool isSame(char *a, const string b) {
    return (strcmp(a, b.data() + '\0') == 0);
}

llong bubbleSort(llong array[], llong n) {
    for (llong i = 0; i < n - 1; i += 1) {
        for (llong j = 0; j < n - 1 - i; j += 1) {
            if (array[j] > array[j + 1]) {
                swap(array[j], array[j + 1]);
            }
        }
    }
}

llong insertSort(llong array[], llong n) {
    llong temp, j;
    for (llong i = 1; i < n; i += 1) {
        temp = array[i];
        for (j = i; (j > 0) && (array[j - 1] > temp); j -= 1) {
            array[j] = array[j - 1];
        }
        array[j] = temp;
    }
}

llong selectSort(llong array[], llong n) {
    llong min;
    for (llong i = 0; i < n - 1; i++) {
        min = i;
        for (llong j = i + 1; j < n; j++) {
            if (array[min] > array[j]) {
                min = j;
            }
        }
        if (min != i) {
            swap(array[min], array[i]);
        }
    }
}

void Merge(llong sourceArr[], llong tempArr[], llong startIndex, llong midIndex, llong endIndex) {
    llong i = startIndex;
    llong j = midIndex + 1;
    llong k = startIndex;
    while (i != midIndex + 1 && j != endIndex + 1) {
        if (sourceArr[i] >= sourceArr[j]) {
            tempArr[k++] = sourceArr[j++];
        } else {
            tempArr[k++] = sourceArr[i++];
        }
    }
    while (i != midIndex + 1) {
        tempArr[k++] = sourceArr[i++];
    }
    while (j != endIndex + 1) {
        tempArr[k++] = sourceArr[j++];
    }
    for (i = startIndex; i <= endIndex; i += 1) {
        sourceArr[i] = tempArr[i];
    }
}

llong MergeSort(llong sourceArr[], llong tempArr[], llong startIndex, llong endIndex) {
    llong midIndex;
    if (startIndex < endIndex) {
        midIndex = (startIndex + endIndex) / 2;
        MergeSort(sourceArr, tempArr, startIndex, midIndex);
        MergeSort(sourceArr, tempArr, midIndex + 1, endIndex);
        Merge(sourceArr, tempArr, startIndex, midIndex, endIndex);
    }
}

void quickSort(llong a[], llong low, llong high) {
    if (low >= high) {
        return;
    }
    llong first = low;
    llong last = high;
    llong key = a[first];

    while (first < last) {
        while (first < last && a[last] >= key) {
            --last;
        }

        a[first] = a[last];

        while (first < last && a[first] <= key) {
            ++first;
        }

        a[last] = a[first];
    }
    a[first] = key;
    quickSort(a, low, first - 1);
    quickSort(a, first + 1, high);
}

void HeapAdjust(llong array[], llong i, llong length) {
    llong nChild;
    llong nTemp;
    for (; 2 * i + 1 < length; i = nChild) {
        nChild = 2 * i + 1;
        if (nChild < length - 1 && array[nChild + 1] > array[nChild]) {
            ++nChild;
        }
        if (array[i] < array[nChild]) {
            nTemp = array[i];
            array[i] = array[nChild];
            array[nChild] = nTemp;
        } else {
            break;
        }
    }
}

//堆排序算法
void heapSort(llong array[], llong length) {
    llong i;
    for (i = length / 2 - 1; i >= 0; --i) {
        HeapAdjust(array, i, length);
    }
    for (i = length - 1; i > 0; --i) {
        array[i] = array[0] ^ array[i];
        array[0] = array[0] ^ array[i];
        array[i] = array[0] ^ array[i];
        HeapAdjust(array, 0, i);
    }
}

llong maxBit(llong data[], llong n) //辅助函数，求数据的最大位数
{
    llong d = 1; //保存最大的位数
    llong p = 10;
    for (llong i = 0; i < n; ++i) {
        while (data[i] >= p) {
            p *= 10;
            ++d;
        }
    }
    return d;
}

void radixSort(llong data[], llong n) //基数排序
{
    llong d = maxBit(data, n);
    llong tmp[n];
    llong count[10];
    llong i, j, k;
    llong radix = 1;
    for (i = 1; i <= d; i++) //进行d次排序
    {
        for (j = 0; j < 10; j++) {
            count[j] = 0; //每次分配前清空计数器
        }
        for (j = 0; j < n; j++) {
            k = (data[j] / radix) % 10; //统计每个桶中的记录数
            count[k]++;
        }
        for (j = 1; j < 10; j++) {
            count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
        }
        for (j = n - 1; j >= 0; j--) {
            k = (data[j] / radix) % 10;
            tmp[count[k] - 1] = data[j];
            count[k]--;
        }
        for (j = 0; j < n; j++) {
            data[j] = tmp[j];
            radix = radix * 10;
        }
    }
    delete[] count;
    delete[] tmp;
}

int main(int argc, char *argv[]) {
    llong length;
    cout << "Please input the length of the array: ";
    cin >> length;
    long long m[length];
    cout << "Please input the elements: " << endl;
    inputElement(m, length);
    llong index = 0;
    if (argc == 2) {
        if (isSame(argv[1], "bubble")) {
            index = 1;
        } else if (isSame(argv[1], "select")) {
            index = 2;
        } else if (isSame(argv[1], "insert")) {
            index = 3;
        } else if (isSame(argv[1], "merge")) {
            index = 4;
        } else if (isSame(argv[1], "quick")) {
            index = 5;
        } else if (isSame(argv[1], "heap")) {
            index = 6;
        } else if (isSame(argv[1], "radix")) {
            index = 7;
        } else if (isSame(argv[1], "all")) {
            index = 8;
        } else if (isSame(argv[1], "help")) {
            cout << "args: bubble, select, shell, insert, merge, quick, heap, radix, all" << endl;
            getchar();
            return 0;
        }
    } else {
        cout << "1. Bubble Sort" << endl;
        cout << "2. Selection Sort" << endl;
        cout << "3. Insertion Sort" << endl;
        cout << "4. Merge Sort" << endl;
        cout << "5. Quick Sort" << endl;
        cout << "6. Heap Sort" << endl;
        cout << "7. Radix Sort" << endl;
        cout << "8. All" << endl;
        cin >> index;
    }
    long long b[length];
    switch (index) {
        case 1:
            bubbleSort(m, length);
            break;
        case 2:
            selectSort(m, length);
            break;
        case 3:
            insertSort(m, length);
            break;
        case 4:
            MergeSort(m, b, 0, length - 1);
            break;
        case 5:
            quickSort(m, 0, length - 1);
            break;
        case 6:
            heapSort(m, length);
            break;
        case 7:
            radixSort(m, length);
            break;
        default:
            cout << "Incorrect input! " << endl;
            getchar();
            break;
    }
    for (llong i = 0; i < length; i += 1) {
        cout << m[i] << " ";
    }
    getchar();
    system("pause>nul");
    return 0;
}