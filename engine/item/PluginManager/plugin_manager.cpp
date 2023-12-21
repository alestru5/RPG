#include "plugin_manager.h"

template<typename T>
T DynamicLibrary::symbol(const std::string& name) const requires std::is_pointer_v<T> {
    auto ret = reinterpret_cast<T>(dlsym(lib, name.c_str()));
    if(ret == nullptr) {
        throw std::runtime_error(dlerror());
    }
    return ret;
}
DynamicLibrary::DynamicLibrary() noexcept: lib(nullptr) {}

DynamicLibrary::DynamicLibrary(const std::string& path): lib(nullptr) {
    open(path);
}

DynamicLibrary::~DynamicLibrary() {
    close();
}

DynamicLibrary::DynamicLibrary(DynamicLibrary&& o):lib(o.lib)
{
    o.lib = nullptr;
}

DynamicLibrary& DynamicLibrary::operator=(DynamicLibrary&& o)
{
    std::swap(lib, o.lib); return *this;
}

void DynamicLibrary::open(const std::string& path) {
    if(lib != nullptr) {
        throw std::runtime_error("Already open");
    }
    lib = dlopen(path.c_str(), RTLD_NOW);
    if(lib == nullptr) {
        throw std::runtime_error(dlerror());
    }
}

void DynamicLibrary::close() noexcept {
    if(lib != nullptr) {
        dlclose(lib);
    }
    lib = nullptr;
}

void PluginManager::scan(const std::string& path, const std::string& extension) {
    fs::path dirPath(path);
    for(auto& file : fs::directory_iterator(dirPath)) {
        if((file.is_regular_file() || file.is_symlink()) && file.path().extension() == extension) {
            DynamicLibrary lib(file.path());
            std::string name = std::string(file.path().filename().stem());
            Item& plug = lib.symbol<Item&(*)()>("load_" + name)();
            plugins.emplace(name, PluginInfo(std::move(lib), std::ref(plug)));
        }
    }
}

void PluginManager::clear() {
    plugins.clear();
}

std::unordered_map<std::string, PluginManager::PluginInfo>& PluginManager::getPlugins() {
    return plugins;
}
