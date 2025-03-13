#ifndef OBJECTS
#define OBJECTS

#include <memory>
#include <variant>
class FuncObj;
class Instance;
class BuiltinFunc;

using FuncObjPtr = std::shared_ptr<FuncObj>;
using InstancePtr = std::shared_ptr<Instance>;
using BuiltinFuncPtr = std::shared_ptr<BuiltinFunc>;

using Object = std::variant<int, std::string, char, double, bool, FuncObjPtr,
                            InstancePtr, BuiltinFuncPtr>;

class FuncObj {};

class Instance {};

class BuiltinFunc {};

// Start working on this tomorrow

#endif // !
