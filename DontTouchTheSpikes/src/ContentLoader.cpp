#include "ContentLoader.h"

ContentLoader::ContentLoader(const std::filesystem::path& rootPath)
    : rootPath(rootPath)
{
}

void ContentLoader::load()
{
    loadTexture(TextureId::Player, "Bird.png");
}

void ContentLoader::loadTexture(TextureId id, const std::filesystem::path& path)
{
    sf::Texture texture;

    const auto fullPath = rootPath / path;
    auto _ = texture.loadFromFile(fullPath);

    textures.emplace(id, std::move(texture));
}

const sf::Texture& ContentLoader::getTexture(TextureId id) const
{
    return textures.at(id);
}