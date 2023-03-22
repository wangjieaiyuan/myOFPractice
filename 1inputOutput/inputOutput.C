/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2023 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    inputOutput
    .H是头文件 也是函数的声明文件 
    .C 是函数的定义文件  也是函数的源文件  
    这一节课挺关键的  能够为后面的输入输出做基础  这是编程的基本功

Description
如果不写出来自己的求解器，那么学这个软件将毫无意义！！！
\*---------------------------------------------------------------------------*/

#include "fvCFD.H"  //头文件  包含类或者函数的定义  一堆东西 需要定义的都在里面  

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//这种写法源自于C的规定，第一个形参 (argument count 参数个数 )argc 必须是整型变量，
//第二个(argument vector 参数指针数组？)argv 必须是指向字符串的指针数组
// main函数的函数头应写为：
// main (argc,argv)
//     int argv;
//     char *argv[];
// int argc 代表的是参数的数量 至少为1  argv[0]即为.exe 文件的路径
//argv 为指针表示的参数，argv[0]表示第一个参数，argv[1]表示第二个参数，以此类推。
//命令行参数在程序开始运行时传递给程序 
int main(int argc, char *argv[])   //其实这句话我懂的真还不多  {传参接口，总个数 + 每一个是什么东西}
{
    #include "setRootCase.H"   //根目录
    #include "createTime.H"     //时间
    #include "createMesh.H"     //网格
    #include "createFields.H"   //创建场 并读取  也就是你手动输入的另一个.H 文件的输入被读取了 那这个取名字的规则还是个问题
    // 既然默认读压力场  那就需要压力场
    // 前面的版本中 还有个createPhi.H 这个of9版本中没发现  是不是说这个可以直接塞进去createFields.H 中
    // 倒是有一个correctPhi.H 和initCorrectPhi.H 
    // 前面的类是存在的  后面的对象名称是随机定义的

    // 这两句都是声明  
    dictionary customDict;     // 创建这个customDict 字典对象  
     
    const word dictName("customProperties");   //这是字典对象的名称 所以俩都得同时存在
    
    //这个字典文件名称必须  自己先去定义好，然后放在这里，要对应好 不然就能编译不能运行case了


    //常对象  其实和一个 5  (不能变的量) 类型一样 为什么这个常对象的文件名称处于 constant 文件夹下面？


    // 这是创建了输入输入对象  dictIO 是对象  dictName 是函数名   
    // 这个对象的作用是功能  输入输出的功能  现在在 customProperties 文件中还没有被写入，要通过终端写入
    IOobject dictIO   //输入输出   对象
    (
        dictName,               //定义文件名
        mesh.time().constant(), //文件路径                                      
        mesh,                   // 对构造函数所需网格的引用
        IOobject::MUST_READ     //强制读
    );

    // 检查你写入的文件是否存在并且符合OF格式  如果字典文件的头文件OK ？ dictIO是对象  
    // 为什么要检查头文件？使用 typeFilePath 去检查头文件。
    if (!dictIO.typeHeaderOk<dictionary>(true) )
    // 这个感叹号应该还非的意思  意思是如果不是  就进去了  如果是  那就没毛病 
        FatalErrorIn(args.executable()) << "Cannot open specified refinement dictionary 打不开你定义的 或者叫你定义的不对劲 (这个头文件是不是就是文件名? 那不应该叫Unable to open specified file bacause your file name is incorrect )" << dictName << exit(FatalError);
    // 这个if上面是不是可以加一个括号


    // 然后进行字典对象的初始化  意识就是检查了没问题 然后进行读取呗
    // IOdictionary 源自 dictionary 和 IOobject 给字典文件自动的输入输出 为了完成输入输出入,
    // IOdictionary 被提供了来自IOobject的 writeData  和 write 的构造函数
    // 赋值  让这个字典文件实现读取和写入的功能  
    customDict = IOdictionary(dictIO);    
    // 各种读取   有没有展示到终端上的这个功能？
    


    //////这部分是读取//////////////////////////////////////////////////////////////////////////

    // C++的使用方法 ：使用 LookUp 的好处是不需要提前告知 变量的类型    
    
    
    // 这句语言的结构是什么  功能是寻找customDict 中的字符型变量  
    // 这句话也说明使用的不是文件名查找，而是使用的文件属性进行查找

    // 这里的定义使用了不同的方法，对于不同的方法，只要格式正确即可 都能体现其中的意思  
    // 有些是直接查找  没有默认值 
    // 有些是查找不到使用默认值   总而言之就是不同的方法  但是殊途同归，都是对
    // 名字叫customProperties 的customDict 对象进行读取

    word someWord ;    //word 的父类是string  也就是OF中专门定义的字符型变量  前面是个类  后面是个对象  
    //这一句意思是让在 customDict 中的字符型变量  这个someWord 是自己定义的  用来接收 customDict 里面的字符型变量
    // 这个功能的前提是在前面定义了IOdictionary 并进行了初始化
    customDict.lookup("someWord") >> someWord; 

    // 上面这两句能不能换成这个？
    // word someWord(customDict.lookupOrDefault<word>("someWord,dagenijiaxiangyousibaijinyamasongdaobanama"));
    
    // 这个模板方法 需要知道变量的类型 并且
    // 当你在字典文件中没定义这个值的初值的时候 LookUp 可以给定你这个值一个默认的初值 （这是好事还是坏事？）
    scalar someScalar(customDict.lookupOrDefault<scalar>("someScalar",1.0) );  
    
    // 这种格式可以从字典文件中读取布尔型变量  布尔型  真 on/true  1  ， 不真 off/false  0
    bool someBool (customDict.lookupOrDefault<Switch>("someBool",true));

    // 列表型变量 List  (这应该是C++特有的东西)   还是同样的类似的方法去读取数值   但是这里如果不提供是不给默认值的 
    List<scalar> someList(customDict.lookup("someList"));

    // HashTable 哈希列表(基于数组的 数据结构，可快速查找操作 和 插入操作)  单向链表   要是复制哈希表会导致不同的 哈希顺序  类模板技术
    // 哈希列表 又叫散列表 是根据 Key而直接访问在内存存储位置的数据结构 是通过计算一个关于键值的函数
    // 狗日滴都不说人话  就是将不同条目和不同代表值单根连接  你引用前面的值 后面的值就出来了
    HashTable<vector,word> someHashTable ( customDict.lookup("someHashTable"));

    // nl= endl   换行符   
    // cin   >>  C++ OF 都使用的输入字眼
    // cout   <<     C++ OF 都使用的 输入字眼
    // 标准数学函数定义在标准库 cmath 中 并不是C++的一部分 
    // 判断语句形式为： if (variable1 > variable2) {...CODE...} else {...CODE...} 。 
    // 比较操作符包括：<、>、<=、>=、==、!=   。 
    // 循环语句形式为：for (int; condition; change) {...CODE...}  。
    // 局部变量：变量域由花括号限定 ，也就是只在花括号内部蹦跶，也就会出现 一个名字在不同变量域出现，但是其意思是各有各的  fortran 局部变量
    // 全局变量的设置方法是  :: 这东西能指定这个变量在哪些作用域中实现同一个变量
    // C++ 多态  多个函数同一个函数名 。
    // 如果函数中某个参数需要改变变量值，那么参数的类型必须是引用，例如  vodi change(double& x1)，
    // 此时对应的变量 x1 将为参数的引用，而非函数内的局部变量。
    // 在命名空间中定义的变量 仅在命名空间中可见 
    // 函数前面加上一个 inline 意思就是函数在使用的地方展开  而非普通的在内存空间跳转
    // 构造函数：类的对象在调用时使用的特殊的初始化函数  当未使用特定的构造函数时，使用null构造函数（这玩意儿所有的属性都是未定义的）,
    // 在初始化的时候根据给定的参数不同调用对应的构造函数
    // 析构函数  特别在使用new后要使用delete 
    // 友元 即关系好的。一个函数或者类可以访问某个类的私有属性 
    // 操作符 operatorX  这个x就是对应的操作符 应该被定义成成员函数或者友元函数    这东西就是对 特定的类型进行操作
    // static  前面加了这玩意儿  就是不属于任何一个特定的对象 className::staticFunction(parameters);
    // 继承 也就是从父类身上得到其属性 


    // 这个类的继承我还没看明白  C++书籍需要继续深入
    // template <class Cmpt> 
    // class Vector : public VectorSpace<Vector<Cmpt>, Cmpt, 3>
    // Vector 是 VectorSpace 的一个子类。

    // 虚函数 用于动态绑定 根据运行时调用的方式来确定具体的函数   这个也需要深入了解

    // 模板 代码重用工具 可实现类型参数化 即把类型定义为参数    这部分也需要一本钻进去  还是得买一本C++  好好整  
    // 大部分类的定义都是针对特性数据类型  更常用的是定义模板使之适用于任意类型  
    // 定义模板类（还是类）:  template<class T>    模板类里面的class 是类型的意思 表示可以接受一个类型参数  
    // 模板类对象：templateClass<type> templateClassObject; 
    // OpenFOAM使用typedef 重新定义模板类 （C++中的结构体搞法）  
    // typedef List<vector> vectorList;  vectorList 定义为 vector 数据类型的模板 List 类的别名
    // 上面那个template 也在使用  等于是多个方法 一种意思


    // 这地方是输出的控制   
    // 在终端输出一下:使用IOobject类的对象从dictionary类的对象名字叫customProperties 的 custonDict对象
    // 中读取到的数据结果 
    Info << nl << "读取下面的数值，（字符型算字符型值）" << nl << nl  //啥也不写就换行  等于是空一行 
    << nl   <<     "字符型的值"   << someWord <<nl  << nl  //啥也不写就换行  等于是空一行
    << nl   <<     "数量型"   << someScalar <<nl  << nl  //啥也不写就换行  等于是空一行
    << "someList" << someList << nl << nl  //啥也不写就换行  等于是空一行
    << "someHashTable" << someHashTable << nl << nl  //啥也不写就换行  等于是空一行
    <<"someBool" << someBool << nl << nl  //啥也不写就换行  等于是空一行
    << endl ;   //等于这一行到了这里才算完了

    
    ///////从这里开始写输出,也就是后处理////////////////////////////////////////////////////////////////////////////////
    
    
    
    // 创建custom dictionary （自定义目录）并编写输出文件

    // 创建输出文件（得把路径标明了）
    // fineName 这就是一个类  直接命名  好家伙 
    // outputDir 这是一个内联函数
    //在postProcessing 中存在这是路径
    // 这是自己创建的文件夹 注意路径的使用方法
    // 这一句是说的是创建的文件架名称 要是没有这一句，后面输出的文件就和案例顶层文件夹一级
    fileName outputDir = mesh.time().path()/"postProcessing"; 
    

    // Foam::fileName outputDir	()	const   foam是命名空间 fileName 是作用域  

    mkDir(outputDir); // mkdir是一个成员函数   等于是在postProcessing下面创建一个文件夹  创建输出文件夹 





    // autoPtr  An auto-pointer similar to the STL auto_ptr but with automatic casting to a reference 
    // to the type and with pointer allocation checking on access.
    // 自动转为对类型的引用 并在访问时检查指针分配 
    // OFstream 这是构造函数 (用完之后需要析构一下) 功能是：输出到文件流  也就是指针自动OF的输出文件 
    // 这里就是在输出到文件中的时候  自动指定输出到规定位置 这个指针指向输出文件
     autoPtr<OFstream> outputFilePtr; 
    
    // 打开新创建的文件（这个文件的目录没说明啊？）   这个是输出的文件名称
    outputFilePtr.reset(new OFstream(outputDir /"customOutputFiles.dat"));  

    //写入 随便写的 意思是从原文件中就能写入到输出文件
    // 这里的关键是outputFilePtr()  
    outputFilePtr() << "# 这 是 一 伙 子 字符 " << endl;
    outputFilePtr() << "0 1 2 3 4 5" <<  endl;
    
    // 也将其写入到哈希列表中 
    someHashTable.insert("newKey", vector(1.,0.,0.)); //插入到哈希列表
    outputFilePtr() << someHashTable << endl;        //输出到哈利列表   放进来在输出到后处理文件中
    //

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< nl << "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
        << "  ClockTime = " << runTime.elapsedClockTime() << " s"
        << nl << endl;

    Info<< "End\n" << endl;     // 编写代码结束

    return 0;
}


// ************************************************************************* //
