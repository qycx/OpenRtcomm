

#ifndef   __customPlaylist_h__
#define   __customPlaylist_h__   //   {

#include <QObject>
#include <QMediaPlayer>
#include <QList>
#include <QUrl>
#include    <QRandomGenerator>
#include    <qlistwidget.h>


//
// 由于 Qt6 移除了 QMediaPlaylist，可以创建一个简单的替代类
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QList>
#include <QUrl>

//
#define     CustomPlaylist  SimpleMediaPlaylist


//
class SimpleMediaPlaylist : public QObject
{
    Q_OBJECT

public:
    enum PlaybackMode {
        Sequential,
        Loop,
        CurrentItemInLoop,
        Random
    };

    explicit SimpleMediaPlaylist(QObject* parent = nullptr);

    void setMediaPlayer(QMediaPlayer* player);
    void setAudioOutput(QAudioOutput* output);

    bool addMedia(const QUrl& url);
    void clear();
    int currentIndex() const;
    QUrl currentMedia() const;
    int mediaCount() const;
    void setCurrentIndex(int index);
    void setPlaybackMode(PlaybackMode mode);

public slots:
    void play();
    void playNext();
    void playPrevious();

signals:
    void currentIndexChanged(int index);
    void playbackModeChanged(PlaybackMode mode);

private slots:
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);

private:
    QMediaPlayer* m_player = nullptr;
    QAudioOutput* m_audioOutput = nullptr;
    QList<QUrl> m_mediaList;
    int m_currentIndex = -1;
    PlaybackMode m_playbackMode = Sequential;

    void playItem(int index);
};

#if  0
// 在你的代码中使用
m_pPlaylist = new SimpleMediaPlaylist(this);
m_pPlaylist->setMediaPlayer(m_pMediaPlayer);
m_pPlaylist->setAudioOutput(m_pAudioOutput);
m_pPlaylist->addMedia(QUrl::fromLocalFile(musicFile));
m_pPlaylist->setPlaybackMode(SimpleMediaPlaylist::CurrentItemInLoop);
m_pPlaylist->play();
#endif 


//
#endif  //   }




