template <typename Derived, typename T>

#include <cstring>
#include <unordered_map>

struct ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();
    
private:
    std::unordered_map<std::string, T*> resources;
};
