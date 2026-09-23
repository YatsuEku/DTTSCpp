#include "ContentLoader.h"

ContentLoader::ContentLoader(const std::filesystem::path& rootPath)
    : rootPath(rootPath)
{
    load();
}

void ContentLoader::load()
{
    loadTexture(TextureId::PlayerDown, "Bird.png");
    loadTexture(TextureId::PlayerUp, "Bird_flapped.png");
    loadTexture(TextureId::PlayerDead, "Bird_dead.png");
    loadTexture(TextureId::BackgroundSpikes, "Spikes.png");
    loadTexture(TextureId::BackgroundScore, "ScoreCircle.png");
    loadTexture(TextureId::PlayerDead, "Bird_dead.png");
    loadTexture(TextureId::Spike, "Spike.png", true);
    loadFont(FontId::Menu, "menu.otf");
    loadFont(FontId::Score, "score.ttf");
    loadSfx(SfxId::Point, "point.wav");
    loadSfx(SfxId::Jump, "jump.wav");
    loadSfx(SfxId::Death, "dead.wav");
}

void ContentLoader::loadTexture(TextureId id, const std::filesystem::path& path, bool smooth)
{
    sf::Texture texture;

    const auto fullPath = rootPath / path;
    if (!texture.loadFromFile(fullPath))
    {
        throw std::runtime_error(
            "Failed to load texture: " + fullPath.string()
            );
    }

    texture.setSmooth(smooth);
    textures.emplace(id, std::move(texture));
}

void ContentLoader::loadFont(FontId id, const std::filesystem::path &path)
{
    sf::Font font;

    const auto fullPath = rootPath / path;
    if (!font.openFromFile(fullPath))
    {
        throw std::runtime_error(
            "Failed to load font: " + fullPath.string()
            );
    }

    fonts.emplace(id, std::move(font));
}

void ContentLoader::loadSfx(SfxId id, const std::filesystem::path &path)
{
    sf::SoundBuffer soundBuffer;

    const auto fullPath = rootPath / path;
    if (!soundBuffer.loadFromFile(fullPath))
    {
        throw std::runtime_error(
            "Failed to load sfx: " + fullPath.string()
            );
    }

    sounds.emplace(id, std::move(soundBuffer));
}

const sf::Texture& ContentLoader::getTexture(TextureId id) const
{
    return textures.at(id);
}

const sf::Font& ContentLoader::getFont(FontId id) const
{
    return fonts.at(id);
}

const sf::SoundBuffer & ContentLoader::getSfx(SfxId id) const
{
    return sounds.at(id);
}
