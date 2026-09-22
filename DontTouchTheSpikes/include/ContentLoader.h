#pragma once

#include <filesystem>
#include <unordered_map>
#include <SFML/Graphics.hpp>

enum class TextureId
{
    PlayerDown,
    PlayerUp,
    PlayerDead,
    BackgroundSpikes,
    BackgroundScore,
    Spike
};

enum class FontId
{
    Menu,
    Score
};

class ContentLoader
{
public:
    explicit ContentLoader(const std::filesystem::path& foorPath);

    void load();

    const sf::Texture& getTexture(TextureId id) const;
    const sf::Font& getFont(FontId id) const;

private:
    std::filesystem::path rootPath;
    std::unordered_map<TextureId, sf::Texture> textures;
    std::unordered_map<FontId, sf::Font> fonts;

    void loadTexture(TextureId id, const std::filesystem::path& path);
    void loadFont(FontId id, const std::filesystem::path& path);
};
