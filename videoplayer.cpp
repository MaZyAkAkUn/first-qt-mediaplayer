#include <QtWidgets>
#include <QVideoWidget>
#include "videoplayer.h"


VideoPlayer::VideoPlayer(QWidget* pwgt) : SoundPlayer(pwgt)
{
    QVideoWidget* pvw = new QVideoWidget;
    pvw->setMinimumSize(300, 300);
    m_pvbxMainLayout->addWidget(pvw);
    m_pmp->setVideoOutput(pvw);

}
