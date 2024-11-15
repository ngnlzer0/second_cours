#include "Animation.h"
#include<iostream>

Animation::Animation(const std::string& textureFile, int frameCount, sf::IntRect frameSize, const std::string& animName)
    : name_texture(textureFile), currentFrame(0), duration(1.0f), elapsedTime(0.0f), frameCount(frameCount), name(animName)
{
    if (!texture.loadFromFile(name_texture)) {
        //throw std::runtime_error("Failed to load texture from file: " + textureFile);
    }

    if (frameCount <= 0) {
        throw std::invalid_argument("Frame count must be greater than 0");
    }

    for (int i = 0; i < frameCount; ++i) {
        frames[i] = sf::IntRect(frameSize.left + i * frameSize.width, frameSize.top, frameSize.width, frameSize.height);
    }
}

Animation::Animation(const Animation& other)
    : texture(other.texture), currentFrame(other.currentFrame),
    duration(other.duration), elapsedTime(other.elapsedTime), frameCount(other.frameCount)
{
    for (int i = 0; i < frameCount; ++i) {
        frames[i] = other.frames[i];
    }
}

Animation& Animation::operator=(const Animation& other)
{
    if (this == &other) return *this;

    texture = other.texture;
    currentFrame = other.currentFrame;
    duration = other.duration;
    elapsedTime = other.elapsedTime;
    frameCount = other.frameCount;

    for (int i = 0; i < frameCount; ++i) {
        frames[i] = other.frames[i];
    }

    return *this;
}

void Animation::update(float deltaTime) {
    if (isFinished()) {
        reset();
    }
    else {
        elapsedTime += deltaTime;
        if (elapsedTime >= duration / frameCount) {
            elapsedTime = 0.0f;
            currentFrame++;
            if (currentFrame >= frameCount) {
                currentFrame = 0;
            }
        }
    }
}

void Animation::reset() {
    currentFrame = 0;
    elapsedTime = 0.0f;
}

sf::IntRect Animation::getCurrentFrame() const {
    return frames[currentFrame];
}

sf::Texture* Animation::getTexture() {
    return &texture;
}

bool Animation::isFinished() const {
    if (frameCount == 0) {
        return true;  // Якщо кадри відсутні, анімація завершена
    }
    return currentFrame == frameCount - 1 && elapsedTime >= duration / frameCount;
}
