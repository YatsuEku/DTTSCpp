#pragma once

#include <filesystem>
#include <unordered_map>
#include <SFML/Graphics.hpp>

enum class TextureId
{
    PlayerDown,
    PlayerUp,
    BackgroundSpikes,
    Spike
};

class ContentLoader
{
public:
    explicit ContentLoader(const std::filesystem::path& foorPath);

    void load();

    const sf::Texture& getTexture(TextureId id) const;

private:
    std::filesystem::path rootPath;
    std::unordered_map<TextureId, sf::Texture> textures;

    void loadTexture(TextureId id, const std::filesystem::path& path);
};
