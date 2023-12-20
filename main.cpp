#include <QMainWindow>
#include <QApplication>
#include <QLabel>
#include <chrono>
#include<fstream>
#include <QTimer>
#include <thread>
#include <dlfcn.h>
#include <dirent.h>
#include <QSplashScreen>
#include "./graphics/mainwindow.h"
#include "./engine/game.h"
#include "./engine/item/item.h"

#include <memory>
#include <dlfcn.h>
#include <vector>
#include <filesystem>
#include <memory>
#include <dlfcn.h>

class DynamicLibrary {
public:
    DynamicLibrary() noexcept;

    DynamicLibrary(const std::string& path);

    ~DynamicLibrary();

    // Нельзя копировать, иначе закроем 2 раза
    DynamicLibrary(const DynamicLibrary& o) = delete;

    DynamicLibrary&
    operator=(const DynamicLibrary& o) = delete;

    //Но можно перемещать
    DynamicLibrary(DynamicLibrary&& o);

    DynamicLibrary& operator=(DynamicLibrary&& o);

    void open(const std::string& path);

    void close() noexcept;

    template<typename T>
    T symbol(const std::string& name) const requires std::is_pointer_v<T>;

private:
    void* lib; // Лучше хранить умный казатель
};

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


namespace fs = std::filesystem;

class PluginManager {
public:

    struct PluginInfo {
        DynamicLibrary library;
        std::reference_wrapper<const Item> plugin;
    };

    void scan(const std::string& path, const std::string& extension);

    void clear();

    const std::unordered_map<std::string, PluginInfo>& getPlugins() const;

private:

    std::unordered_map<std::string, PluginInfo> plugins;
};
void PluginManager::scan(const std::string& path, const std::string& extension) {
    fs::path dirPath(path);
    for(auto& file : fs::directory_iterator(dirPath)) {
        if((file.is_regular_file() || file.is_symlink()) && file.path().extension() == extension) {
            DynamicLibrary lib(file.path());
            std::string name = std::string(file.path().filename().stem());
            const Item& plug = lib.symbol<Item&(*)()>("load_" + name)();
            plugins.emplace(name, PluginInfo(std::move(lib), std::ref(plug)));
        }
    }
}

void PluginManager::clear() {
    plugins.clear();
}

const std::unordered_map<std::string, PluginManager::PluginInfo>& PluginManager::getPlugins() const {
    return plugins;
}

namespace fs = std::filesystem;

int main(int argc, char *argv[]){
    std::string dlExt = ".so";
    std::string searchDir = "/home/alestru/PetProjects/RPG/engine/item/plugins";
    PluginManager manager;
    manager.scan(searchDir, dlExt);

    for(const auto& pluginInfo : manager.getPlugins()) {
        const Item& plugin = pluginInfo.second.plugin;
        std::cout <<pluginInfo.first<<" "<<plugin.getItemType()<< std::endl;
    }
    srand(time(NULL));
    QApplication a(argc, argv);
    QPixmap pixmap("/home/alestru/PetProjects/RPG/img/splash.png");
    QSize PicSize(512, 384);
    pixmap = pixmap.scaled(PicSize,Qt::KeepAspectRatio);
    QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);
    splash.show();
    QTimer::singleShot(3000, &splash, &QWidget::close);

    MainWindow w;
    w.setSize();
    QTimer::singleShot(3000, &w,SLOT(showFullScreen()));
    return a.exec();
}
