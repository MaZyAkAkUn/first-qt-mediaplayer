#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <QWidget>
#include <QtMultimedia>
#include <QtMultimediaWidgets>
#include "customplaylist.h"
class SoundPlayer : public QWidget
{
    Q_OBJECT
protected:
    QMediaPlayer* m_pmp;
    CustomPlaylist* m_pmpl;//Method Pointer Media PlayList
    QBoxLayout* m_pvbxMainLayout;
private:
    QPushButton* m_pcmdPlay;
    QPushButton* m_pcmdStop;
    QPushButton* m_pcmdNext;
    QPushButton* m_pcmdPrev;
    QSlider* m_psldPosition;
    QLabel* m_plblCurrent;
    QLabel* m_plblRemain;


    QString msecsToString(qint64 n);
public:

    SoundPlayer(QWidget *parent = 0);
    ~SoundPlayer();
private slots:
    void slotOpen();

    void slotPlay();
    void slotSetSliderPosition(qint64);
    void slotSetMediaPosition(int);
    void slotSetDuration(qint64);
    void slotStatusChanged(QMediaPlayer::State);
    void slotDoubleCLickedListItem(int);
signals:
    void fileOpened(QStringList* file_list);

};

#endif // SOUNDPLAYER_H
