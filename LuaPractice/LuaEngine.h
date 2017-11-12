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

#define LUAENGINE_EXPORT_FACTORY_KEYS(factoryType, factory, name) \ //this function takes a factorytype and a factory and name as the parameters
    __LuaEngineFactoryKeyExporter<factoryType::KEY_TYPE, factoryType::BASE_TYPE> __factoryKeyExporter##name(#name, factory) // this is a factory key exporter and a template from the factory type namespce and with a key type and base type types and pastes the name token with a stringizer and a factory as a parameter

extern std::vector<std::pair<const std::string, const std::function<const LuaVariant()>>> __luaEngineExports; // this is a template concatenation with a extern vector key type and basetype which is another lua variant templates

class LuaEngine : public LuaPrimitive
{
  public:
    LuaEngine();
    ~LuaEngine();

    void doThink();

    /* EXPORTED FUNCTIONS */
    int settimeout();
    int ptrcast();

    int attach();
    int destroy();

    int readMemory();
    int writeMemory();

    int newScan();
    int runScan();
    int getScanResultsSize();
    int getScanResults();
    int getDataStructures();

  protected:
    virtual void displayError(std::string error, bool fatal) // this is a display error method virtual function fatal and error 
    {
        std::cout << (fatal ? "[FTL] " : "[ERR] ");
        std::cout << error << std::endl;
    }

  private:
    struct ScannerPair // structs which are private
    {
        ScannerTargetShPtr target;
        ScannerShPtr scanner;
    };
    typedef std::shared_ptr<ScannerPair> ScannerPairShPtr;
    typedef std::list<ScannerPairShPtr> ScannerPairList;
    ScannerPairList scanners;

    struct TimedEvent
    {
        LuaVariant function;
        std::chrono::time_point<std::chrono::steady_clock> executeTime;
    };
    std::list<TimedEvent> timedEvents;

    LuaVariant createLuaObject(const std::string &typeName, const void *pointer) const;
    bool getLuaObject(const LuaVariant &object, const std::string &typeName, void *&pointer) const;
    bool getScannerPair(const LuaVariant &object, ScannerPairList::const_iterator &iterator) const;

    ScannerPairShPtr getArgAsScannerObject(const std::vector<LuaVariant> &args) const;

    const ScanVariant getScanVariantFromLuaVariant(const LuaVariant &variant, const ScanVariant::ScanVariantType &type, bool allowBlank) const;
    LuaVariant getLuaVariantFromScanVariant(const ScanVariant &variant) const;
};
typedef std::shared_ptr<LuaEngine> LuaEngineShPtr;

class __LuaEngineExporter
{
  public:
    __LuaEngineExporter(const char *name, const LuaVariant &value)
    {
        __luaEngineExports.push_back(std::make_pair(name, [=]() -> const LuaVariant { return value; }));
    }
    ~__LuaEngineExporter() {}
};

template <typename K, typename A>
class __LuaEngineFactoryKeyExporter
{
  public:
    __LuaEngineFactoryKeyExporter(const char *name, const KeyedFactory<K, A> &factory)
    {
        auto func = [&factory]() -> const LuaVariant {
            auto keys = factory.getKeys();
            LuaVariant::LuaVariantITable lkeys;
            for (auto key = keys.cbegin(); key != keys.cend(); key++)
                lkeys.push_back(*key);
            return lkeys;
        };
        __luaEngineExports.push_back(std::make_pair(name, func));
    }
    ~__LuaEngineFactoryKeyExporter() {}
};