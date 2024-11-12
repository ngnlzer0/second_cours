#include "Animation.h"

Animation::Animation(const std::string name_file, int number_frames, sf::IntRect parametrs_frame,float duration)
    :name_texture_animation(name_file), duration(duration), elapsedTime(0.0f), currentFrame(0), frameTime(0.1f)
{
    int left = parametrs_frame.left;
    int width = parametrs_frame.width;
    int height = parametrs_frame.height;
    for (int i = 0; i < number_frames; i++)
    {
        frames.push_back({ left + i * width, 0, width, height });
    }
}

void Animation::update(float deltaTime)
{
    if (!finished && !frames.empty())
    {
        elapsedTime += deltaTime;
        if (elapsedTime >= frameTime)
        {
            elapsedTime -= frameTime;
            currentFrame = (currentFrame + 1) % frames.size();
            finished = (currentFrame == frames.size() - 1);
        }
    }
}

void Animation::reset()
{
    currentFrame = 0;
    elapsedTime = 0;
    finished = false;
}
