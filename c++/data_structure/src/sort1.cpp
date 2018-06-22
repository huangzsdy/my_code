/*
 * 1.各种排序算法
 *
 */
#include <iostream>
#include <unordered_map>
using namespace std;

void Swap(int& p,int & q){
    int temp = p;
    p = q;
    q = temp;
}

void printArr(int arr[],int length){
    for(int k = 0;k < length;k++)
        cout<<arr[k]<<" ";
    cout<<endl;
}

//冒泡 时间:O(n^2),空间:O(1),稳定
void BubbleSort(int arr[],int length){
    cout<<"冒泡排序:";
    for(int i = 0;i < length;++i){
        for(int j = length - 1;j > i;--j){
            if(arr[j] < arr[j-1])
                Swap(arr[j],arr[j-1]);
        }
    }
}

//简单排序 时间:O(n^2),空间:O(1),稳定
void SimpleSelectSort(int arr[],int length){
    cout<<"简单排序:";
    for(int i = 0;i < length;++i){
        int min = i;
        for(int j = i+1;j < length;++j){
            if(arr[j] < arr[min])
                min = j;
            Swap(arr[i],arr[min]);
        }
    }
}

//直接插入排序 时间:O(n^2),空间:O(1),稳定
void StraigtInsertSort(int arr[],int length){
    cout<<"直接插入排序:";
    int i,j;
    for(i = 1;i < length;++i){
        int temp = arr[i];
        for(j = i - 1;j >= 0 && arr[j] > temp;j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = temp;
    }
}

// 折半插入排序 时间:O(n^2),空间:O(1),稳定
void BinaryInsertSort(int arr[],int length){
    cout<<"折半插入排序"<<endl;
    int i,j,low,high,mid;
    for(int i = 1;i < length;i++){
        low = 0;high = i - 1;
        while(low <= high){
            mid = low + (high - low)/2;
            if(arr[mid] > arr[i]) high = mid - 1;
            else low = mid + 1;
        }
        int temp = arr[i];
        for(j = i - 1;j >= high + 1;j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = temp;
    }
}

//希尔排序 时间:O(nlogn) ~ O(n2),空间:O(1),不稳定
void ShellSort(int arr[],int length){
    cout<<"希尔排序"<<endl;
    //gap逐渐从length/2缩小到1
    for(int gap = length/2;gap > 0;gap /= 2){
        //从第gap个元素开始，逐个进行排序
        for(int i = gap;i < length;++i){
            int j = i;
            while(j - gap >= 0 && arr[j] < arr[j - gap]){
                Swap(arr[j],arr[j - gap]);
                j -= gap;
            }
        }
    }
}

// 快排要背。中间点必须从第一个开始。时间:O(nlogn),空间:O(nlogn) ~ O(n),不稳定
/*  
**  快排的思想是先固定一个点(以下代码temp必须要选第一个元素，否则就有问题)，执行以下操作
**  有两个指针i = 0,j = length - 1，temp = arr[i]
**  j 先从右往左，找到比temp小的元素，来填temp所在的坑arr[i]
**  i 从左往右，找到比temp大的元素，来填arr[j]这个坑
**  循环反复"填坑"，知道最后 i==j，就把temp填到arr[i]里
** 几个要点，while里边绝对不能写i <= j，必须是i < j，否则会出错，所有地方while都不能有等号
*/
void QuickSort(int arr[],int left,int right){
    if(left < right){
        int i = left,j = right,temp = arr[i];
        while(i < j){
            while(i < j && arr[j] >= temp)
                j--;
            arr[i] = arr[j];//因为arr[i]已经被拿走了，用arr[j]去填这个位置
            while(i < j && arr[i] <= temp)
                i++;
            arr[j] = arr[i];//因为arr[j]已经被拿走了，用arr[i]去填这个位置
        }
        // 最后 i == j时跳出循环，所以i或者j 都可以 和 left换
        /*
        arr[i] = temp;
        QuickSort(arr,left,i - 1);
        QuickSort(arr,i + 1,right);
        */
        arr[j] = temp;
        QuickSort(arr,left,j - 1);
        QuickSort(arr,j + 1,right);
    }
}

//这是种错误示范，建议采用QuickSort的方式
void qsort1(int *a, int low, int high) {
    if (low < high) {
        int i = low + 1;
        int j = high;
        int tmp = a[low];
        while (i <= j) {
            while (a[j] > tmp) {
                j--;
            }
            while (a[i] < tmp) {
                i++;
            }           
            if (i < j) {
                swap(a[i], a[j]);
            }
        }
        swap(a[low], a[i]);
        cout<<"i:"<<i<<" j:"<<j<<endl;
        qsort1(a, low, i - 1);
        qsort1(a, i + 1, high);
    }
}

//这是正确的，但是1，while里边 必须要 i <= j ，且最后必须是  swap(a[low], a[j])，不能是和a[i]换
void qsort(int *a, int low, int high) {
    if (low < high) {
        int i = low + 1;
        int j = high;
        int tmp = a[low];
        while (i <= j) {
            while (a[i] < tmp) {
                i++;
            }

            while (a[j] > tmp) {
                j--;
            }
            if (i <= j) {
                swap(a[i], a[j]);
            }
        }
        swap(a[low], a[j]);
        qsort(a, low, j - 1);
        qsort(a, j + 1, high);
    }
}

//基数排序 r为基数，d为位数。则基数排序的时间复杂度为O(d(n+r)),空间O(n+r),稳定
// 辅助函数，求得所有数中最高位能到多少
int maxDigit(int arr[],int length){
    int maxbit = 1,radix = 10;
    for(int i = 0;i < length;++i){
        while(arr[i] > radix || arr[i] < -radix){
            radix *= 10;
            maxbit++;
        }
    }
    return maxbit;
}
void RadixSort(int data[], int n) //基数排序，参考http://blog.csdn.net/u012580566/article/details/47702955，用map记录次数后，可以处理负数的情况
{  
    int d = maxDigit(data, n); 
    int tmp[n];  //做临时的数组，和data一样长
    unordered_map <int,int> count;//count作计数器，是个map，表示[-9,9]之间的每个元素对应出现的次数
    int i, j, k;  
    int radix = 1;  
    for(i = 1; i <= d; i++) //进行d次排序  
    {  
        for(j = -9; j < 10; j++)  
            count[j] = 0; //每次分配前清空计数器  
        for(j = 0; j < n; j++)  
        {  
            k = (data[j] / radix) % 10; //统计每个桶中的记录数  
            count[k]++;  
        }  
        for(j = -9; j < 10; j++)  
            count[j] = count[j - 1] + count[j]; //依次叠加，则count[k]表示对应k在tmp中的最高位置。比如-8在tmp中的最后一个数应该是-9的个数 + -8的个数
                                                //即将tmp中的位置依次分配给每个桶
        
        for(j = n - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中  
        {  
            k = (data[j] / radix) % 10;  
            tmp[count[k] - 1] = data[j];  
            count[k]--;  
        }  
        for(j = 0; j < n; j++) //将临时数组的内容复制到data中  
            data[j] = tmp[j];  
        radix = radix * 10;  
    }  
}  

//归并排序 时间:O(nlogn),空间:O(n),稳定
void merge(int* arr,int low,int mid,int high,int* temp){
    if(low == high)return;
    int i,j,k;
    i = low;
    j = mid + 1;
    k = low;
    while(i <= mid && j <= high){
        // 左边的比右边的小,先插入左边的
        if(arr[i] < arr[j]){
            temp[k] = arr[i];
            i++;
        }
        else{
            temp[k] = arr[j];
            j++;
        }
        k++;
    }
    //判断左序列是否到头
    while(i <= mid)
        temp[k++] = arr[i++];
    //判断有序列是否到头
    while(j <= high)
        temp[k++] = arr[j++];
    //将原先low到high的内容拷贝回原数组，temp数组只是中间过程，先给temp赋值再读取temp
    for(k = low;k <= high;++k){
        arr[k] = temp[k];
    }
}
void mergeSort(int arr[],int low,int high,int * temp){
    if(low < high){
        int mid = low + (high - low)/2;
        mergeSort(arr,low,mid,temp);
        mergeSort(arr,mid + 1,high,temp);
        merge(arr,low,mid,high,temp);
    }
    return;
}

// 堆排序 时间:O(nlogn),空间:O(1),不稳定
// 调整大顶堆（仅是调整过程，建立在大顶堆已构建的基础上）
void adjustHeap(int arr[],int i,int length){
    int temp = arr[i];//先取出要调整的节点
    for(int k = 2 * i + 1;k < length;k = 2 * k + 1){
        if(k + 1 < length && arr[k] < arr[k+1])
            k++;
        if(arr[k] > temp){
            arr[i] = arr[k];
            i = k;
        }
        else
            break;
    }
    arr[i] = temp;
}
void HeapSort(int arr[],int length){
    cout<<"堆排序"<<endl;
    for(int i = length/2 - 1;i >= 0;--i){
        //从第一个非叶子节点从下至上，从右至左调整结构，如此反复后得到一个大根堆
        adjustHeap(arr,i,length);
    }
    //此时已经调整成一个大根堆了
    for(int j = length - 1;j > 0;j--){
        swap(arr[0],arr[j]);//将堆顶元素与末尾元素进行交换
        adjustHeap(arr,0,j);//重新对堆进行调整
    }
}

int main(int argc,char ** argv){
    int length = 0;
    cout<<"请输入数组长度"<<endl;
    cin>>length;
    int array[length];
    for(int i = 0;i < length;++i)
        cin>>array[i];
    
    // BubbleSort(array,length);
    // SimpleSelectSort(array,length);
    // StraigtInsertSort(array,length);
    // ShellSort(array,length);
    // RadixSort(array,length);
    // HeapSort(array,length);
    // BinaryInsertSort(array,length);
    QuickSort(array,0,length-1);
    printArr(array,length);
    
    // cout<<"快速排序"<<endl;
    QuickSort(array,0,length - 1);
    printArr(array,length);

    QuickSort(array,0,length - 1);
    printArr(array,length);
    // cout<<"归并排序"<<endl;
    // int *tempArr = new int[length];
    // mergeSort(array,0,length - 1,tempArr);
    // printArr(array,length);
    // delete tempArr;
    return 0;
}
