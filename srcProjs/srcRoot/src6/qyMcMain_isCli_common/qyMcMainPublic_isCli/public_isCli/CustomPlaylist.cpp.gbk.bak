
//
#include	"stdafx.h"
#include	"CustomPlaylist.h"


//
//int CustomPlaylist::


// SimpleMediaPlaylist.cpp
//#include "SimpleMediaPlaylist.h"
#include <QDebug>
#include <QRandomGenerator>

SimpleMediaPlaylist::SimpleMediaPlaylist(QObject* parent)
    : QObject(parent)
{
}

void SimpleMediaPlaylist::setMediaPlayer(QMediaPlayer* player)
{
    if (m_player == player)
        return;

    m_player = player;
}

void SimpleMediaPlaylist::setAudioOutput(QAudioOutput* output)
{
    if (m_audioOutput == output)
        return;

    m_audioOutput = output;
}

bool SimpleMediaPlaylist::addMedia(const QUrl& url)
{
    if (!url.isValid())
        return false;

    m_mediaList.append(url);
    if (m_currentIndex == -1)
        m_currentIndex = 0;

    return true;
}

void SimpleMediaPlaylist::clear()
{
    m_mediaList.clear();
    m_currentIndex = -1;
    if (m_player)
        m_player->stop();
}

int SimpleMediaPlaylist::currentIndex() const
{
    return m_currentIndex;
}

QUrl SimpleMediaPlaylist::currentMedia() const
{
    if (m_currentIndex >= 0 && m_currentIndex < m_mediaList.size())
        return m_mediaList.at(m_currentIndex);
    return QUrl();
}

int SimpleMediaPlaylist::mediaCount() const
{
    return m_mediaList.size();
}

void SimpleMediaPlaylist::setCurrentIndex(int index)
{
    if (index < 0 || index >= m_mediaList.size())
        return;

    m_currentIndex = index;
    playItem(index);
    emit currentIndexChanged(index);
}

void SimpleMediaPlaylist::setPlaybackMode(PlaybackMode mode)
{
    if (m_playbackMode == mode)
        return;

    m_playbackMode = mode;
    emit playbackModeChanged(mode);
}

void SimpleMediaPlaylist::play()
{
    if (m_mediaList.isEmpty() || !m_player)
        return;

    if (m_currentIndex < 0 || m_currentIndex >= m_mediaList.size())
        m_currentIndex = 0;

    playItem(m_currentIndex);
}

void SimpleMediaPlaylist::playNext()
{
    if (m_mediaList.isEmpty())
        return;

    int nextIndex = -1;

    switch (m_playbackMode) {
    case Sequential:
        nextIndex = (m_currentIndex + 1) % m_mediaList.size();
        break;
    case Loop:
        nextIndex = (m_currentIndex + 1) % m_mediaList.size();
        break;
    case CurrentItemInLoop:
        nextIndex = m_currentIndex;  // 循环播放当前项
        break;
    case Random:
        nextIndex = QRandomGenerator::global()->bounded(m_mediaList.size());
        break;
    }

    if (nextIndex >= 0 && nextIndex < m_mediaList.size()) {
        m_currentIndex = nextIndex;
        playItem(nextIndex);
        emit currentIndexChanged(nextIndex);
    }
}

void SimpleMediaPlaylist::playPrevious()
{
    if (m_mediaList.isEmpty())
        return;

    int prevIndex = -1;

    switch (m_playbackMode) {
    case Sequential:
        prevIndex = (m_currentIndex - 1 + m_mediaList.size()) % m_mediaList.size();
        break;
    case Loop:
        prevIndex = (m_currentIndex - 1 + m_mediaList.size()) % m_mediaList.size();
        break;
    case CurrentItemInLoop:
        prevIndex = m_currentIndex;  // 循环播放当前项
        break;
    case Random:
        prevIndex = QRandomGenerator::global()->bounded(m_mediaList.size());
        break;
    }

    if (prevIndex >= 0 && prevIndex < m_mediaList.size()) {
        m_currentIndex = prevIndex;
        playItem(prevIndex);
        emit currentIndexChanged(prevIndex);
    }
}

void SimpleMediaPlaylist::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    // 当播放结束时，根据播放模式决定下一步
    if (status == QMediaPlayer::EndOfMedia) {
        switch (m_playbackMode) {
        case Sequential:
        case Loop:
        case Random:
            playNext();
            break;
        case CurrentItemInLoop:
            // 循环播放当前项
            if (m_currentIndex >= 0 && m_currentIndex < m_mediaList.size()) {
                playItem(m_currentIndex);
            }
            break;
        }
    }
}

void SimpleMediaPlaylist::playItem(int index)
{
    if (index < 0 || index >= m_mediaList.size() || !m_player || !m_audioOutput)
        return;

    m_player->setSource(m_mediaList.at(index));
    m_player->play();
}

