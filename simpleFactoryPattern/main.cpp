#include "operationFactory.h"

int main(int argc, char *argv[])
{
    OperationFactoryContext *context = new OperationFactoryContext();
    if (context->setInfo(10, '+', 20))
        cout << 10 << '+' << 20 << "=" << context->contextGetResult() << endl;
    delete context;
    return 0;
}