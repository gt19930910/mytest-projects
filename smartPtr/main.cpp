/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include "src/smartPtr.h"


int main(int arg0, char** arg1)
{
       
    CPoint *pa = new CPoint(10, 20);
    //int *pa = new int(2);
    
    {
	    CSmartPtr<CPoint> spr1(pa);
	    
    	CSmartPtr<CPoint> spr2(spr1);
	    	
	  	CSmartPtr<CPoint> spr3 = spr1;   

  	    cout << pa->getX() << endl; 	

  	    cout << spr1->getX() << endl;

  	    cout << (*spr1).getX() << endl;
    }
    //这边大括号结束对象就释放了

    cout << pa->getX() << endl;

    return 0;
}
