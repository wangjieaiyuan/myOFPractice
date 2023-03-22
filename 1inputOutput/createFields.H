//等于是  我使用foamNewApp 的时候,不论是不是可压缩,都需要在原来的初始条件中读取压力p
//所以每次都是默认建立 标量压力场p
Info<< "Reading field p\n" << endl;
volScalarField p
(
    IOobject
    (
        "p",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);
//ubuntu 比win好用的点就是在终端中能够对任何一个位置进行操作
//编制这个求解器没说使用啥 直接就写源文件 等于是在初试场中没有输入任何额外的值
Info<< "这是foamApp-自动添加的 一般这里是需要修改的\n" << endl;
