#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H


#include <memory>
#include <dlfcn.h>
#include <vector>
#include <filesystem>
#include <memory>
#include <dlfcn.h>
#include <unordered_map>

#include "../item.h"

class DynamicLibrary {
public:
    DynamicLibrary() noexcept;

    DynamicLibrary(const std::string& path);

    ~DynamicLibrary();

    DynamicLibrary(const DynamicLibrary& o) = delete;

    DynamicLibrary&
    operator=(const DynamicLibrary& o) = delete;

    DynamicLibrary(DynamicLibrary&& o);

    DynamicLibrary& operator=(DynamicLibrary&& o);

    void open(const std::string& path);

    void close() noexcept;

    template<typename T>
    T symbol(const std::string& name) const requires std::is_pointer_v<T>;

private:
    void* lib;
};

namespace fs = std::filesystem;

class PluginManager {
public:

    struct PluginInfo {
        DynamicLibrary library;
        std::reference_wrapper<Item> plugin;
    };

    void scan(const std::string& path, const std::string& extension);

    void clear();

    std::unordered_map<std::string, PluginInfo>& getPlugins();

private:

    std::unordered_map<std::string, PluginInfo> plugins;

};
#endif
