#pragma once
#include <vector>
#include <list>
#include <iostream>
#include <chrono>
//add the files here later once you make them
class __LuaEngineExporter
{
  public:
    __LuaEngineExporter(const char *name, const LuaVariant &value)//this is the constructor that takes a object
    {
        __luaEngineExports.push_back(std::make_pair(name, [=]() -> const LuaVariant { return value; }));
        //an object of the class with the push back method that calls make pair method with parameters of the name and a lambda function lua variant constructor with the value
    }//make a lambda function that points to the lua variant constructor
    ~__LuaEngineExporter() {}
};
#define LUAENGINE_EXPORT_VALUE(type, name, val) __LuaEngineExporter __exporter##name(#name, (type)val); 
//global function prototype with parameters and a class with the token pasting operator of name and the name parameter with  converts macro parameters to string literals without expanding the parameter definition and the value to type cast

#define LUAENGINE_EXPORT_FUNCTION(uniq, name)                \ //this is a function with types of uniq and name 
    int __exporter__func##uniq(lua_State *L)                 \ //this is a function with the export function with a pointer to the lua state class 
    {                                                        \ //it has an autovariable that stores the template of the lua engine of L from the lua primitive namespace and the get primitive function
        auto inst = LuaPrimitive::getInstance<LuaEngine>(L); \
        if (inst != nullptr)                                 \ //checking if the template is blank
            return inst->##uniq();                           \ //put it into the uniq which will be pasted to the tokens 
        return 0;                                            \
    }                                                        \
__LuaEngineExporter __exporter##uniq(name, LuaVariant(&__exporter__func##uniq)); //this is continuing after the function definition exporter token being pasted with the uniq which contains the templete of the lua engine and takes the name and the exporter unique token plus the uniq pasted

