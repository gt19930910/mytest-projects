#ifndef OPERATIONFACTORY
#define OPERATIONFACTORY

#include <iostream>
using namespace std;

class Operation
{
public:
    Operation():numA(0),numB(0){cout << "Operation" << endl;}
    virtual ~Operation(){cout << "~Operation" << endl;}

    double getnumA(){return numA;}
    double getnumB(){return numB;}

    void setnumA(int A){numA = A;}
    void setnumB(int B){numB = B;}

    double virtual getResult() = 0;

protected:
    double numA;
    double numB;
};

class OperationAdd : public Operation
{
public:
    OperationAdd(){cout << "OperationAdd" << endl;}
    ~OperationAdd(){cout << "~OperationAdd" << endl;}
    double getResult(){return (double)(numA+numB);}
};

class OperationSub : public Operation
{
public:
    OperationSub(){cout << "OperationSub" << endl;}
    ~OperationSub(){cout << "~OperationSub" << endl;}
    double getResult(){return double(numA-numB);}
};

class OperationMul : public Operation
{
public:
    OperationMul(){cout << "OperationMul" << endl;}
    ~OperationMul(){cout << "~OperationMul" << endl;}
    double getResult(){return (double)(numA*numB);}
};

class OperationDiv : public Operation
{
public:
    OperationDiv(){cout << "OperationDiv" << endl;}
    ~OperationDiv(){cout << "~OperationDiv" << endl;}
    double getResult(){return (double)(numA/numB);}
};

class OperationFactoryContext
{
public:
    OperationFactoryContext(){oper = NULL;}
    /* 动态联编时delete基类的指针，需要基类有虚析构函数，不然会调到基类的析构函数而不调用派生类的 */
    ~OperationFactoryContext(){delete oper;}

    bool setInfo(double A, char operate, double B)
    {
        cout << "operate=" << operate << endl;
        switch(operate)
        {
            case '+':
                this->oper = new OperationAdd();break;
            case '-':
                this->oper = new OperationSub();break;
            case '*':
                this->oper = new OperationMul();break;
            case '/':
                this->oper = new OperationDiv();break;
            default:
                cout << "input operate " << operate << " error" << endl;
                return false;
        }
        oper->setnumA(A);
        oper->setnumB(B);
        return true;
    }
    double contextGetResult(){return oper->getResult();}

private:
    Operation *oper; 
};

#endif