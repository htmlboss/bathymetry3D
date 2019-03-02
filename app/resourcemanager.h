#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <filesystem>

class ResourceManager {
    ResourceManager() = default;
    ~ResourceManager() = default;
public:

    static auto& GetInstance() {
        static ResourceManager instance;
        return instance;
    }

    ResourceManager(ResourceManager&&) = default;
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(ResourceManager&&) = default;
    ResourceManager& operator=(const ResourceManager&) = delete;


    /// Load a text file and return as a string.
    [[nodiscard]] std::string LoadTextFile(const std::filesystem::path& path, const bool strip = false) const;

};

#endif // RESOURCEMANAGER_H
