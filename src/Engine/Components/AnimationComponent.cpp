#include "Engine/Components/AnimationComponent.hpp"
#include "Engine/Components/SpriteComponent.hpp"
#include "Engine/GameObject.hpp"

AnimationComponent::AnimationComponent(int frameWidth, int frameHeight)
    : m_frameWidth(frameWidth), m_frameHeight(frameHeight)
{
}

void AnimationComponent::SetFrameDimensions(int width, int height)
{
    m_frameWidth = width;
    m_frameHeight = height;
}

void AnimationComponent::Init()
{
 
    if (owner)
    {
        m_sprite = owner->GetComponent<SpriteComponent>();
        
    }
    UpdateSrcRect();
}

void AnimationComponent::AddClip(const std::string &name, int row, int totalFrames, float frameDuration, bool loop, int startFrame)
{

    AnimationClip clip{name, row, startFrame, totalFrames, frameDuration, loop};
    m_clips[name] = clip;

    if (m_clips.size() == 1)
    {
        Play(name);
    }
}

bool AnimationComponent::Play(const std::string &name)
{

    auto it = m_clips.find(name);
    if (it == m_clips.end())
    {
        return false;
    }

    if (m_currentClip == name && m_isPlaying)
    {
        return true;
    }

   
    m_currentClip = name;
    m_currentFrameIndex = 0;
    m_elapsedTime = 0.0f;
    m_isPlaying = true;
    
    UpdateSrcRect();
    return true;
}

void AnimationComponent::Stop()
{
    m_isPlaying = false;
}

void AnimationComponent::Resume()
{
    if (!m_currentClip.empty())
    {
        m_isPlaying = true;
    }
}

void AnimationComponent::Update(float dt)
{
   
    if (!m_isPlaying || m_currentClip.empty())
    {
        return;
    }

    auto it = m_clips.find(m_currentClip);
    if (it == m_clips.end())
    {
        return;
    }

    const AnimationClip &clip = it->second;


    m_elapsedTime += dt;

    while (m_elapsedTime >= clip.frameDuration)
    {
        m_elapsedTime -= clip.frameDuration;
        m_currentFrameIndex++;

        if (m_currentFrameIndex >= clip.totalFrames)
        {
            if (clip.loop)
            {
                m_currentFrameIndex %= clip.totalFrames;
            }
            else
            {
              
                m_currentFrameIndex = clip.totalFrames - 1;
                m_isPlaying = false;
                break;
            }
        }
    }

    UpdateSrcRect();
}
void AnimationComponent::ResetToFirstFrame()
{
    m_currentFrameIndex = 0;
    m_elapsedTime = 0.0f;
    UpdateSrcRect(); 
}
void AnimationComponent::UpdateSrcRect()
{
    if (!m_sprite || m_currentClip.empty())
    {
        return;
    }

    auto it = m_clips.find(m_currentClip);
    if (it == m_clips.end())
    {
        return;
    }

    const AnimationClip &clip = it->second;

    int col = clip.startFrame + m_currentFrameIndex;
    int row = clip.row;

    SDL_FRect rect{
        static_cast<float>(col * m_frameWidth),
        static_cast<float>(row * m_frameHeight),
        static_cast<float>(m_frameWidth),
        static_cast<float>(m_frameHeight)
    };

    m_sprite->SetSrcRect(rect);
}


