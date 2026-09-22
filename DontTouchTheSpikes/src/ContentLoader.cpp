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
    loadTexture(TextureId::BackgroundSpikes, "Spikes.png");
}

void ContentLoader::loadTexture(TextureId id, const std::filesystem::path& path)
{
    sf::Texture texture;

    const auto fullPath = rootPath / path;
    if (texture.loadFromFile(fullPath))
    {
        throw std::runtime_error(
            "Failed to load texture: " + fullPath.string()
            );
    }

    textures.emplace(id, std::move(texture));
}

const sf::Texture& ContentLoader::getTexture(TextureId id) const
{
    return textures.at(id);
}