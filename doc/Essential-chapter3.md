# 《Essential c++》——第三章

## 泛型编程风格

### 泛型编程（[本节代码展示](../code/essential/genericVector.cpp)）

- STL的两种组件：`容器`、`泛型算法`；
- 泛型算法与他要操作的元素的类型无关，其使用【函数模板】技术，达到【与操作对象的类型相互独立】的目的；
- 思想：不要直接在容器身上进行操作。而是由一对iterator标示要进行迭代的范围。指示容器读取操作终点的值（其最后一个元素的下一个地址）被称为【标兵】；
- vector和array容器中，都是以一块连续内存来存储其所有元素。而list中的元素是以一组指针相互链接成的。分为前向指针和后向指针；

>这本书的3.1节中，第一段代码有点问题，在codeblocks下面编译出错。原因是第一个形参他声明为了const类型，在函数内部他又将这个变量返回了，但是定义的函数返回值却不是const的。因此编译报错。解决方法可以在函数的定义时，将返回值类型改为const。
>

### 泛型指针--iterator
> 思想: 在底层指针的行为之上,提供一层抽象,取代程序原本的指针直接操作.让用户无需直接面对指针操作.

每一个标准容器都会提供一个名为``begin（）``的操作函数，该函数返回一个iterator(迭代器)，指向容器的第一个元素；``end（）``操作函数指向最后一个元素的下一个位置；

- 定义iterator:
```c++
vector<string> svec;
vector<string>::iterator iter = svec.begin();
```
**解释**：定义``iter``为一个iterator， 其指向vector，且该vector的元素类型为string， ``iter``当前指向svec的第一个元素；通过iterator调用底部的string元素所提供的操作时，可以使用【箭头运算符``->``】；通过迭代器取得元素值的时候，采用指针的取用方式(*号操作符)。 


- 在下面这个函数中, 依据泛型指针的背景, 使用模板函数技术实现更加具有弹性的查找函数
```c++
template <typename iteratorType, typename elemType>
iteratorType findIterator(iteratorType first, iteratorType last, elemType &num)
{
    for(; first!=last; first++){
        if(*first == num)
            return first;
    }
    return last;
}
```
但是上面的实现中, 还是使用了底层元素所属类型的 equality(=,相等) 运算符, 但是如果底部元素所属类型没有提供这个运算符,比如用户自定义数据类型,没有进行这个运算符的重载,那么这个函数可能就无法直接使用. 


### 使用顺序性容器
#### vector
- 顺序容器 用来维护一组 排列有序/类型相同的元素;
- `vector` 和  `list` 是比较重要的两个顺序容器;
- vector使用连续内存来存放元素, 随机访问的效率很高,但是插入值的时候,插入点后面的元素都需要依次重新复制,比较低效;

#### list
- list以双向链接而非连续内存来存储内容
- list中的每个元素都包含三个字段: value, back pointer(指向前一个元素), front pointer(指向下一个元素)
`0 -> A -> B -> ... -> 1`
- list的特性和vector正好相反;

#### deque
- 特性和vector很相似, 连续内存存放元素
- 不同的是, deque对于最前端元素或者末端元素的插入和删除操作,效率更高


#### 定义顺序容器
```c++
vector<int> vec; // 产生空的容器
list<string> st;

vector<int> vec(1024);  // 产生特定大小的容器

vector<int> vec(10, -1);  // 产生特定大小的容器,并为每个元素赋初值

list<string> st1;
list<string> st2(st1); // 将st1赋值给st2
```

### 使用泛型算法
- 包含头文件 ``algorithm``；
- 泛型算法中的每个函数的参数基本上都是接收泛型指针，常常使用每个容器的``begin（）``或者``end（）``操作来返回需要的指针。


### 设计泛型算法
我的理解是设计具有高复用性的函数. 但是需要利用泛型指针技术.
```c++
/*
- 利用泛型算法实现 统计一个容器中某个元素出现的个数
*/
int countOccurs(const vector<int> &vec, int num) {
    typename vector<int>::const_iterator iter = vec.begin();
    int num_count = 0;

    while((iter = find(iter, vec.end(), num)) != vec.end()) {
        num_count++;
        iter++; // 从当前找到的位置的下一个元素开始 新一轮的查找
    }
    return num_count;
}
```


#### 函数对象(function object)
- 有点类似于函数指针的作用
- 是某种class的实例对象,这类class对函数调用运算符进行了重载,这样,就可以将这个函数对象当成一般函数来使用.
- 目的: 将某一种**行为**传递给函数,而不是传统的参数.
- 为了效率考虑. 因为这个运算符重载可以以inline的方式给出,从而消除通过函数指针来调用的代价.
- STL中定义了一组function object, 分别是
    - 算术运算, plus<type>, minus<type>...
    - 关系运算, less<type>, great<type>...
    - 逻辑运算, logical_and<type>, logical_or<type>...
```c++
// 将两个vector中的元素顺序相加,放到第三个vector中
void callFunctional(vector<int> &vec_sum) {
    vector<int> vec_a(3, 1);
    vector<int> vec_b(3, 2);
    // 下面最后一个参数调用了function object    
    transform(vec_a.begin(), vec_a.end(), vec_b.begin(), vec_sum.begin(), plus<int>());
}
```

#### 函数对象适配器(function object adapter)
- 该适配器会对函数对象进行特定的修改操作,使其满足一定的要求.
- 绑定适配器(binder adapter)会将函数对象的参数绑定至特定值,使二元参数转化为一元参数.


### 使用map([代码展示](../code/essential/map_and_set.cpp))
- map被定义为一对数值对，一个key对应一个value；
- 定义方式： 
```c++
map<string, int> words;
words["andrew"] = 25;
```
- map对象有一个``first``成员，对应key。另一个``second``成员，对应value；当使用中括号操作符``[ ]``查询某个key是否存在于map中时，如果这个key不存在，那么这个操作之后，该key会被自动添加到这个map中，并给出默认值0；
- 可以使用``find（）``函数或者``count（）``函数来进行查找某个key；``find（）``返回这个key的一个iterator， ``count（）``返回这个key在map中出现的次数

### 使用set
- set由一群key组成，其中的元素会依据其所属类型默认的less-than运算符进行排列，并自动去除重复的元素；
- 如果想知道某个值是否被遍历过，可以将所有遍历过的值存放于一个set中，然后每次遍历之前都查找一下他是否存在于这个set之中。set的检索效率比较高；

### 使用iostream iterator
这一章没什么好说的，把iterator应用到iostream中，获取标准输入输出 或者 文件的输入与输出。
