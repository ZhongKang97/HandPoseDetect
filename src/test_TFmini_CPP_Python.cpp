#include<Python.h>
#include<iostream>
#include<string>

using namespace std;

int main(int argc,char** argv)
{
    Py_Initialize();
    const char * cstr_cmd = "sys.path.append('/home/pi/CODEing/HandPoseDetect/src')";
    PyRun_SimpleString("import sys");
    PyRun_SimpleString(cstr_cmd);
    //python 2.7 和 python 3.5是有区别的。
    //python 3.5需要用wchar_t
    PyObject * p_Moudle,* p_Func;
    PyObject *p_Value;
    p_Moudle = PyImport_ImportModule("get_Distance_TFmini_Plus");
    if(p_Moudle == NULL) cout<<"p_Moudle import failed"<<endl;
    else 
    {
        p_Func = PyObject_GetAttrString(p_Moudle,"getTFminiData");
        if(p_Func == NULL) cout<<"p_Func import failed"<<endl;
        else
       {
        int distance=0;
        while(true)
        {
          p_Value = PyObject_CallObject(p_Func,NULL);
          distance= PyInt_AsLong(p_Value);
          cout<<"dis: "<<distance<<endl;
        }
       }
    }  
    Py_Finalize();
    return 0;
}