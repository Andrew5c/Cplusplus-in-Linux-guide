# 《Essential c++》——第四章

基于对象的编程风格

### 如何实现一个class？
- **理解**：class名称被视为一个类型（type）名称，就像内置的int、double一样。是一种自定义的、扩充的数据类型；
- class组成的两部分：一组公开的（public）操作函数和运算符（成员函数member function）； 一组私有的（private）实现细节；
- 构造函数：名称与class相同，不指定返回值，可以被重载；
	- 当class object被定义的时候，编译器自动调用构造函数对该object进行初始化；
- 析构函数：名称与class相同，前面加上`~`符号，不指定返回值，没有参数，不能重载；
	- 当object结束声明时，编译器自动调用析构函数来释放在构造函数中（或者对象声明周期中）分配的资源。

#### 成员初始化列表

```c++
class Triangular{
public:
	Triangular(const Triangular &rhs);
private:
	int _length;
	int _beg;
	int _next;
}
// 采用成员初始化列表对成员变量进行初始化
Triangular::Triangular(const Triangular &rhs)
  :_length(rhs._length), _beg(rhs._beg), _next(rhs._next){}
```

#### 成员逐一初始化（拷贝构造函数）
- 当我们以一个对象的初值作为另一个对象的初始的时候，类数据成员会被依次复制。比如：

```c++
Triangular tril1(8);
Triangular tril2(tril1);
```
这时，`tril1`中的值会被依次复制到`tril2`;

- 但是需要注意的是，当一个类中有**申请内存**的操作时，不能够这样进行直接初始化；
比如下面这个类的设计：
```c++
class Matrix{
    public:
    Matrix(int row, int col):_row(row), _col(col){
        // 进行动态内存申请
        _pmat = new double[row*col];
    }
    ~Matrix(){
        delete [] _pmat;
    }
    private:
    int _row, _col;
    double* _pmat;
}
```

> 因为这样的话，被实例化的两个对象会同时指向同一块内存，而当其中一个对象析构后，该内存就被释放，而此时另一个对象中的某个成员还在指向这块内存。这时危险的！

- 这种情况下，我们可以为这样的类提供一个**拷贝构造函数**。它的唯一参数是一个 const reference，指向自己类的对象。比如：
```c++
Matrix::Matrix(const Matrix &rhs)
    :_row(rhs._row), _col(rhs._col)
{
    // 拷贝构造函数实现
    int elem = _row*_col;
    _pmat = new double[elem];
    for(int i=0; i<elem; i++){
        _pmat[i] = rhs._pmat[i];
    }
}
```


#### 可变（mutable）和不变（const）
- 在成员函数的参数列表之后，紧跟一个``const``修饰符时，是为了告诉编译器，这个成员函数不会修改对象的内容；
- 如果成员函数定义在在class主体之外，那么需要在声明和定义处同时指定const；
```c++
class a{
    public:
    // 类内声明const
    A
    int length const {return length};
}
```
- 编译器会检查每个声明为const的成员函数。

- 如果一个类的某个私有成员变量不属于**抽象概念一环**，也就是它的改变其实不会改变不会改变这个类的状态，那么，可以用``mutable``关键字来修饰。
- 此时，可以在const成员函数中，对这种变量做出修改。

### this指针（[本节代码展示](../code/essential/this.cpp)）
- this指针是在成员函数内部用来指向其调用者（一个对象）的一个指针。
- this指针可以让我们访问调用者的一切；
- 内部工作过程：这种机制的实现是因为编译器内部会自动的在每个成员函数的参数列表中加入一个名为**this**的指针。然后在调用时，this指针被传入该对象的一个引用。比如：
```c++
Triangular& Triangular::copy(const Triangular &rhs){
    // 函数实现
}
// 会被编译器修改为：
Triangular& Triangular::copy(Triangular *this, const Triangular &rhs){
    // 函数实现
}

Triangular tr1;
Triangular tr2;
tr1.copy(tr2);
// 上面这个函数会被修改为
copy(&tr1, tr2);
// 这个时候，不难理解this指针为什么会指向其调用者。
```

- `return \*this` 返回指针所指的对象；

- 这会在我们要复制一个对象给另一个对象的时候用到。


### 静态（static）类成员
- 静态数据成员表示**唯一的、可共享的**成员。它可以在同一个类的所有对象中被访问。
- 对于某一个类来说，静态数据成员只有唯一的一个实体，需要在全局定义，并且定义的时候加上class scope运算符，比如：
```c++
class Triangular{
    private:
    static vector<int> _elems;
}
// 类外进行定义
vector<int> Triangular::_elems;
```
- 它的访问方式和一般非静态数据成员的访问方式一样。

#### 静态成员函数
- 不访问任何非静态数据成员的成员函数，才能够被声明成static。

> 一般情况下，成员函数需要通过类的某个对象来调用。调用时，这个对象会被绑定至该成员函数的this指针。

- 但是，静态成员函数的工作和任何对象都没有关系，所以它内部是没有this指针的。在类定义完成后，既可以直接调用静态函数成员。只是调用时，需要在前面加上class scope。比如：
```c++
class Triangular{
    public:
    // 类内声明
    static bool is_elem(int );
    ... // 其他
}
// 类外定义， 无需加上static
bool Triangular::is_elem(int a){
    ... // 定义
}
// 其他函数中调用
int main(){
    if(Triangular::is_elem(val))
        ... // 细节
}
```
- 注意在class主体之外定义静态数据成员或者静态成员函数的时候，不需要在带上static运算符。


### 打造一个迭代类（Itreator Class）（[本节代码展示](../code/operatorOverload/)）

> 目的在于利用运算符重载技术，让类具有迭代的性质。

#### **运算符重载**
- 为类定义运算符，可以像定义成员函数一样来定义。区别是运算符不用指定函数名称，只需要在运算符前面加上`operator`；
- 对于前置递增和后置递增运算符，因为他们函数原型基本一致，根据重载规则，参数列表不同相同，因此，我们常在后置递增运算符的参数列表中加入一个`int`参数，但是调用时，并不传入。由编译器自动为其置0；

- 任何运算符如果和另一个运算符性质相反，比如`==`和`!=`，实现时，可以先实现`==`运算符的重载，然后再以它来实现`!=`。（具体见本节代码展示）

- 重载运算符的定义方式，可以像定义成员函数一样来定义，也可以像非成员函数一样来定义。但是非成员函数定义方式的参数列表里面，一定要比成员函数定义方式多一个参数，也就是this指针。
```
// 成员函数定义方式
inline int Triangular_iterator::operator*() const {
    // ...
}

// 非成员函数定义方式
inline int operator*(const Triangular_iterator& rhs) {
    // ...
}
```


#### 嵌套类型
- `typedef`可以为某个类型设定另一个不同的名称；
```c++
typedef existing_type new_name;
// 在我们的例子中
class Triangular{
typedef Triangular_iterator itreator;
}
// 使用
Triangular::itreator it = trian.begin();
// 其中，这里使用的class scope，是用来告诉编译器，遇到这个iterator时，去Triangular内部寻找定义
```

#### 友元函数
- 想要类A中的成员函数访问类B中的私有数据成员的话，一种方式是将这个数据成员在类B中声明为 friend 。
- 如果A和B的定义不在同一个头文件中，那么需要在B中对A进行超前声明。就是在B所在文件的顶部写下`class A`；
- 这个friend声明可以出现在类B定义中的任何位置，不受public和private影响；

- 也可以直接让A和B直接建立friend关系。这时A中的所有成员函数都能够访问B中的数据成员。

- friend的建立通常是为了效率考虑。有时候，也可以直接提供一个具有public访问权限的inline函数直接为其他类提供需要的数据。

### 拷贝赋值运算符

> 在前面实现拷贝构造函数的时候，我们没有考虑重载Matrix类的赋值运算符。

- 拷贝赋值运算符的实现会取代默认数据成员的拷贝操作。
```c++
class Matrix{
    public:
    // 构造与析构函数实现
    private:
    int _row, _col;
    double* _pmat;
};
// 拷贝构造函数的实现见前面
// 实现拷贝赋值运算符
Matrix& Matrix::operator=(const Matrix &rhs){
    if(*this != rhs){
        _row = rhs._row;
        _col = rhs._col;
        int elem_cnt = _row * _col;
        delete [] _pmat;
        _pmat = new double[elem_cnt];
        for(int i=0; i<elem_cnt; i++){
            _pmat[i] = rhs._pmat[i];
        }
    }
    return *this;
}

```

### 实现一个function object（[本节代码展示](../code/essential/functionCall.cpp)）

> function object是某种class的实例对象，并且这类class对function call运算符做了重载。这样，可以将function object 作为一般函数使用。

- 之所以使用function object，而不是一般函数，主要是为了效率。可以令call运算符成为inline，可以消除“通过函数指针来调用函数”时产生的额外开销。
- function call运算符可以接受任意多个参数。这样可以被用来作为Matrix的多维度下标操作。（因为c++下面的下标操作只能够接受一个参数）
- 标准库定义了 算术、关系、逻辑三类function object。
- 需要包含 functional 头文件。

### 重载iostream运算符
- 目的在于想要对某一个class object进行读取与写入操作；

比如：
```c++
Triangular trian;
cout << trian;
```
此时，需要为 Triangular类提供output重载运算符
```c++
// 最好以非成员函数的形式实现
ostream& operator<< (ostream &os, const Triangular &rhs){
    cout << "(" << rhs.beg_pos() << "," << rhs.length() << ")";
    // 调用类的显示函数进行输出
    rhs.display(rhs.length(), rhs.beg_pos(), os);
    return os;
}
```
- 这里重载函数传入的ostream又被返回，是为了能够串接多个output运算符。
- 之所以使用非成员函数的形式实现，是为了避免造成困惑。因为如果设计成成员函数的话，`<<`运算符的左操作数必须是属于同一个类的对象才行，这时，输出一个类可能需要这样写：`trian << cout << '\n';`，会造成困惑。


### 指向类成员函数的指针

- 直观印象
```c++
class num_sequence{
    // ...
};
// 定义一个指向上述类的成员函数的指针
// 注意需要指明它所指的是哪一个类
void (num_sequence::*pt) (int ) = 0;
```
- 上面这段代码定义了 num_sequence 类的一个成员函数指针，该函数的返回值为void，接受一个int型参数， 并且初始化pt的值为0.

- 通过 typedef 简化上述定义: 
```c++
typedef void (num_sequence::*PtrType) (int);
PtrType pt = 0;
```

