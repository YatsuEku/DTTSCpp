#pragma once

#include <filesystem>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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

enum class SfxId
{
    Point,
    Jump,
    Death,
    Button
};

class ContentLoader
{
public:
    explicit ContentLoader(const std::filesystem::path& foorPath);

    void load();

    const sf::Texture& getTexture(TextureId id) const;
    const sf::Font& getFont(FontId id) const;
    const sf::SoundBuffer& getSfx(SfxId id) const;

private:
    std::filesystem::path rootPath;
    std::unordered_map<TextureId, sf::Texture> textures;
    std::unordered_map<FontId, sf::Font> fonts;
    std::unordered_map<SfxId, sf::SoundBuffer> sounds;

    void loadTexture(TextureId id, const std::filesystem::path& path);
    void loadFont(FontId id, const std::filesystem::path& path);
    void loadSfx(SfxId id, const std::filesystem::path& path);
};
