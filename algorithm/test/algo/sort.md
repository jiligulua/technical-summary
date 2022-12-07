//实现冒泡排序算法

		void bubble(int arr[],int len)
		{
		    int i = 0,j = 0;
		    //使用外层循环来控制比较的轮数
		    for(i = 1; i < len; i++)
		    {
		        //使用内层循环控制针对当前轮比较的元素下标
		        int flag = 1;
		        for(j = 0; j < len-i; j++)
		        {
		            //如果第一个元素大于第二个元素，则交换
		            if(arr[j] > arr[j+1])
		            {
		                int temp = arr[j];
		                arr[j] = arr[j+1];
		                arr[j+1] = temp;
		                //表明有数据元素发生了交换
		                flag = 0;
		            }
		        }
		        //表示刚才的一轮扫描中没有发生交换
		        if(1 == flag)
		        {
		            // 省略剩余的轮数
		            break;
		        }
		    }
		}


//实现快速排序

		void quick(int arr[],int left,int right)
		{
		    //1.寻找中间元素作为基准值，单独保存
		    int p = (left + right)/2;
		    int pivot = arr[p];
		    //2.分别使用左边元素和右边元素与基准值进行比较，将小于基准值的元素放在左边，将大于等于基准值的元素放在右边;
		    int i = 0,j = 0;
		    for(i = left,j = right; i < j; )
		    {
		        //如果左边元素存在并且小于基准值时
		        while(arr[i] < pivot && i < p)
		        {
		            i++;
		        }
		        //如果左边元素存在，但是大于等于基准值
		        if(i < p)
		        {
		            arr[p] = arr[i];
		            p = i;
		        }
		        //接下来处理右边的元素
		        while(pivot <= arr[j] && p < j)
		        {
		            j--;
		        }
		        if(p < j)
		        {
		            arr[p] = arr[j];
		            p = j;
		        }
		    }
		    //3.将基准值放在重合的位置上
		    arr[p] = pivot;
		    //4.分别对左边分组和右边分组重复以上过程，使用递归处理
		    if(p-left > 1)
		    {
		        quick(arr,left,p-1);
		    }
		    if(right-p > 1)
		    {
		        quick(arr,p+1,right);
		    }
		}

//实现插入排序算法

		void insert(int arr[],int len)
		{
		    int i = 0,j = 0;
		    //从第二个元素起，依次取出每个元素
		    for(i = 1; i < len; i++)
		    {
		        //使用临时变量记录取出的当前元素值
		        int temp = arr[i];
		        //使用取出的元素与左边的有序数列依次比较，如果左边的元素大，则左边元素右移;
		        for(j = i; arr[j-1] > temp && j >= 1; j--)
		        {
		            arr[j] = arr[j-1];
		        }
		        //直到左边元素不再大于取出元素时，插入取出元素
		        if(j != i)
		        {
		            arr[j] = temp;
		        }
		    }
		}
 
[参考1 十大排序算法](https://blog.csdn.net/zjwreal/article/details/99182117)
[参考2 简单插入排序](https://blog.csdn.net/qq_33289077/article/details/90370899)
[参考3 希尔排序](https://www.cnblogs.com/chengxiao/p/6104371.html)