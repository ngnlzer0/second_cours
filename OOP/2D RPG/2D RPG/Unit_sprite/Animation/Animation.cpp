﻿#include "Animation.h"
#include<iostream>

Animation::Animation(const std::string& textureFile, int frameCount, sf::IntRect frameSize, const std::string& animName, bool looping)
    : name_texture(textureFile), currentFrame(0), duration(1.0f), elapsedTime(0.0f), frameCount(frameCount), name(animName),isLooping(looping)
{
    if (!texture.loadFromFile(name_texture)) {
        throw std::runtime_error("Failed to load texture from file: " + textureFile);
    }

    if (frameCount <= 0) {
        throw std::invalid_argument("Frame count must be greater than 0");
    }

    frames.reserve(frameCount ); // Резервуємо місце для кадрів
    std::cout << "Creating Animation: " << animName << ", frameCount: " << frameCount << std::endl;
    for (int i = 0; i < frameCount ; ++i) {
        frames.emplace_back(frameSize.left + i * frameSize.width, frameSize.top, frameSize.width, frameSize.height);
        std::cout << "Frame " << i << ": " << frames[i].left << ", " << frames[i].top << ", "
            << frames[i].width << ", " << frames[i].height << std::endl;
    }
}

Animation::Animation(const Animation& other)
    : texture(other.texture), currentFrame(other.currentFrame),
    duration(other.duration), elapsedTime(other.elapsedTime),
    frameCount(other.frameCount)
{
    frames.reserve(other.frames.size());  // резервуємо пам'ять для frames
    for (const auto& frame : other.frames) {
        frames.push_back(frame);
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
    elapsedTime += deltaTime;
    if (elapsedTime >= duration / frames.size()) {
        elapsedTime = 0;
        currentFrame++;
        if (currentFrame >= frames.size()) {
            if (isLooping) {
                currentFrame = 0; // Зациклюємо анімацію
            }
            else {
                currentFrame = frames.size() - 1; // Залишаємо на останньому кадрі
            }
        }
    }
}

void Animation::reset() {
    currentFrame = 0;
    elapsedTime = 0.0f;
}

sf::IntRect Animation::getCurrentFrame() const {
    if (frames.empty()) {
        return sf::IntRect(); // Повертаємо порожній прямокутник, якщо кадрів немає
    }
    return frames[currentFrame];
}

sf::Texture* Animation::getTexture() {
    return &texture;
}

