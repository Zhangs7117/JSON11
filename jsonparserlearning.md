# json11 学习

采用了名称空间的写法。

#### 名称空间(namespace)

​	隨著程式碼撰寫越來越多，程式內容越來越大，您會發現管理程式中的變數名稱、函式名稱、類別名稱也會是一件麻煩的事，尤其是一些同名問題的發生，例如在程 式中，您也許會定義一個Point類別代表2維空間的點，也許在程式的某個地方，您也會定義一個Point類別來表示一個3維空間的點，其它像函式同名、 共用變數同名的情況也可能發生，當這種情況發生時，其中一個定義就可能將另一個定義給覆寫掉了。     

​	C++提供名稱空間的概念，它就像是一個管理容器，可以將您所定義的名稱區域在名稱空間之下，而不會有相互衝突的發生，例如您定義了一個 dimension2d與dimension3d的名稱空間，在它們之下都有一個Point類別，但由於屬於不同的名稱空間，所以這兩個名稱並不會有所衝突。 

名称空间的写法：

```c
namespace 名稱 {
    // 類別、函式或變數宣告
};
```

---

在json11中，采用了名称空间的写法。

namespace json11 包括了主体部分所有的代码。

---

#### 函数重载

采用函数重载的方法，对dump函数的输入为不同情况做统一的转化为字符串的处理。

```c
static void dump(NullStruct, string &out)
static void dump(double value, string &out)
static void dump(int value, string &out)
static void dump(bool value, string &out)
static void dump(const string &value, string &out)
static void dump(const Json::array &values, string &out) 
static void dump(const Json::object &values, string &out) 
void Json::dump(string &out) const {
    m_ptr->dump(out);
}
```

在对字符串处理过程中，采用static_cast进行类型转换。

用法：static_cast < type-id > ( exdivssion ) 

该运算符把exdivssion转换为type-id类型，但没有运行时类型检查来保证转换的安全性。它主要有如下几种用法：

①用于类层次结构中基类和子类之间指针或引用的转换。

​	进行上行转换（把子类的指针或引用转换成基类表示）是安全的；

　　进行下行转换（把基类指针或引用转换成子类表示）时，由于没有动态类型检查，所以是不安全的。

②用于基本数据类型之间的转换，如把int转换成char，把int转换成enum。这种转换的安全性也要开发人员来保证。

③把空指针转换成目标类型的空指针。

④把任何类型的表达式转换成void类型。

注意：static_cast 不能转换掉exdivssion的const、volitale、或者__unaligned属性。

代码中使用如下：

```c
else if (static_cast<uint8_t>(ch) <= 0x1f) {
            char buf[8];
            snprintf(buf, sizeof buf, "\\u%04x", ch);
            out += buf;
} 
else if (static_cast<uint8_t>(ch) == 0xe2 && static_cast<uint8_t>(value[i+1]) == 0x80
         && static_cast<uint8_t>(value[i+2]) == 0xa8) {
            out += "\\u2028";
            i += 2;} 
else if (static_cast<uint8_t>(ch) == 0xe2 && static_cast<uint8_t>(value[i+1]) == 0x80
         && static_cast<uint8_t>(value[i+2]) == 0xa9) {
         out += "\\u2029";
         i += 2;
}
```



类value继承自Jsonvalue,即下列代码：

```c
double           JsonValue::number_value()              const { return 0; }
int              JsonValue::int_value()                 const { return 0; }
bool             JsonValue::bool_value()                const { return false; }
const string &            JsonValue::string_value()              const 
{ return statics().empty_string; }
const vector<Json> &      JsonValue::array_items()               const 
{ return statics().empty_vector; }
const map<string, Json> & JsonValue::object_items()              const 
{ return statics().empty_map; }
const Json &              JsonValue::operator[] (size_t)         const 
{ return static_null(); }
const Json &              JsonValue::operator[] (const string &) const 
{ return static_null(); }
```



在构造类value的构造函数时，为了避免隐式转换，采用了explict关键字。

```c
template <Json::Type tag, typename T>
class Value : public JsonValue {
protected:
    // Constructors
    explicit Value(const T &value) : m_value(value) {}
    explicit Value(T &&value)      : m_value(move(value)) {}
    // Get type tag
    Json::Type type() const override {
        return tag;
    }
    // Comparisons
    bool equals(const JsonValue * other) const override {
        return m_value == static_cast<const Value<tag, T> *>(other)->m_value;
    }
    bool less(const JsonValue * other) const override {
        return m_value < static_cast<const Value<tag, T> *>(other)->m_value;
    }
    const T m_value;
    void dump(string &out) const override { json11::dump(m_value, out); }
};
```

采用了move函数。



动态内存的使用上采用make_shared函数

**make_shared的用法**

make_shared 在动态内存中分配一个对象并初始化它，返回指向此对象的shared_ptr，与智能指针一样，make_shared也定义在头文件memory中；
 当要用make_shared时，必须指定想要创建的对象类型，定义方式与模板类相同，在函数名之后跟一个尖括号，在其中给出类型；

 ```c
make_shared<int> p3 = make_shared<int>(42)；
 ```

 一般采用auto定义一个对象来保存make_shared的结果，如

```c 
auto p1 =make_shared<int>(42); 
```

整体的结构基于jsonparse这个结构体进行。

---

如果传递指针需要在子函数中进行动态分配内存，那么必须进行引用传递或者传递指针的地址。

```c
int string2buffer (const std::string  &json_in, const std::string  &json_out, char*& buffer, int*& len);
```

---

gcc 编译 选项 

-fno-rtti 禁用运行时类型信息  -fno-exceptions 禁用异常机制

加快运行速度