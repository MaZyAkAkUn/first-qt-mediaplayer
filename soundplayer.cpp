#include "soundplayer.h"

SoundPlayer::SoundPlayer(QWidget *parent)
    : QWidget(parent)
{
    QPushButton* pcmdOpen = new QPushButton("&Open");
    QDial* pdiaVolume = new QDial;

    m_pcmdPlay = new QPushButton;
    m_pcmdStop = new QPushButton;
    m_pcmdNext = new QPushButton;
    m_pcmdPrev = new QPushButton;
    m_psldPosition = new QSlider;
    m_plblCurrent = new QLabel(msecsToString(0));
    m_plblRemain = new QLabel(msecsToString(0));

    m_pmp = new QMediaPlayer;
    m_pmpl = new CustomPlaylist(this);

    m_pcmdPlay->setEnabled(false);
    m_pcmdPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    m_pcmdNext->setEnabled(false);
    m_pcmdNext->setIcon(style()->standardIcon(QStyle::SP_ArrowRight));
    m_pcmdPrev->setEnabled(false);
    m_pcmdPrev->setIcon(style()->standardIcon(QStyle::SP_ArrowLeft));
    m_pcmdStop->setEnabled(false);
    m_pcmdStop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));


    //m_pmp->setPlaylist(m_pmpl);



    m_psldPosition->setRange(0, 0);
    m_psldPosition->setOrientation(Qt::Horizontal);

    pdiaVolume->setRange(0, 100);
    int nDefaultVolume = 50;
    m_pmp->setVolume(nDefaultVolume);
    pdiaVolume->setValue(nDefaultVolume);

    connect(pcmdOpen, SIGNAL(clicked()), SLOT(slotOpen()));
    connect(m_pcmdPlay, SIGNAL(clicked()), SLOT(slotPlay()));
    connect(m_pcmdStop, SIGNAL(clicked()), m_pmp, SLOT(stop()));
    connect(m_pcmdNext, SIGNAL(clicked()), m_pmpl, SLOT(next()));
    connect(m_pcmdPrev, SIGNAL(clicked()), m_pmpl, SLOT(previous()));

    connect(pdiaVolume, SIGNAL(valueChanged(int)), m_pmp, SLOT(setVolume(int)));
    connect(m_psldPosition, SIGNAL(sliderMoved(int)), SLOT(slotSetMediaPosition(int)));
    connect(m_pmp, SIGNAL(positionChanged(qint64)), SLOT(slotSetSliderPosition(qint64)));
    connect(m_pmp, SIGNAL(durationChanged(qint64)), SLOT(slotSetDuration(qint64)));
    connect(m_pmp, SIGNAL(stateChanged(QMediaPlayer::State)), SLOT(slotStatusChanged(QMediaPlayer::State)));
    connect(this, SIGNAL(fileOpened(QStringList*)), m_pmpl, SLOT(filesOpened(QStringList*)));
    connect(m_pmpl, SIGNAL(currentIndexChanged(int)), m_pmpl, SLOT(slotCurrentIndexChanged(int)));
    connect(m_pmpl->m_plw, SIGNAL(itemDoubleClicked(QListWidgetItem*)), m_pmpl, SLOT(slotDoubleClickedListItem()) );//get index of current row
    connect(m_pmpl, SIGNAL(signalDoubleClickedListItem(int)), this, SLOT(slotDoubleCLickedListItem(int)));//set current row index as pl current index

    //Layout setup
    QHBoxLayout* phbxPlayControls = new QHBoxLayout;
    phbxPlayControls->addWidget(pcmdOpen);
    phbxPlayControls->addWidget(m_pcmdPrev);
    phbxPlayControls->addWidget(m_pcmdPlay);
    phbxPlayControls->addWidget(m_pcmdStop);
    phbxPlayControls->addWidget(m_pcmdNext);
    phbxPlayControls->addWidget(pdiaVolume);
    phbxPlayControls->addWidget(m_pmpl->m_plw);//adding our list widget to layout
    //phbxPlayControls->addWidget(play_list_gui);
    QHBoxLayout* phbxTimeControls = new QHBoxLayout;
    phbxTimeControls->addWidget(m_plblCurrent);
    phbxTimeControls->addWidget(m_psldPosition);
    phbxTimeControls->addWidget(m_plblRemain);

    m_pvbxMainLayout = new QVBoxLayout;
    m_pvbxMainLayout->addLayout(phbxPlayControls);
    m_pvbxMainLayout->addLayout(phbxTimeControls);

    setLayout(m_pvbxMainLayout);
}

SoundPlayer::~SoundPlayer()
{

}

void SoundPlayer::slotOpen(){
   // QString strFile = QFileDialog::getOpenFileName(this, "Open file");
    QStringList strFile = QFileDialog::getOpenFileNames(this,"Select file or files");//Получаем пути к выбраным файлам
    emit SoundPlayer::fileOpened(&strFile);
    if(!strFile.isEmpty()){
        m_pmp->setPlaylist(m_pmpl);
        m_pcmdPlay->setEnabled(true);
        m_pcmdStop->setEnabled(true);
        m_pcmdNext->setEnabled(true);
        m_pcmdPrev->setEnabled(true);
    }
}


void SoundPlayer::slotPlay(){
    switch (m_pmp->state()) {
    case QMediaPlayer::PlayingState:
        m_pmp->pause();
        break;
    default:
        m_pmp->play();
        break;
    }
}
void SoundPlayer::slotStatusChanged(QMediaPlayer::State state){
    switch (state) {
    case QMediaPlayer::PlayingState:
        m_pcmdPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        break;
    default:
        m_pcmdPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        break;
    }
}

void SoundPlayer::slotSetMediaPosition(int n){
    m_pmp->setPosition(n);
}

QString SoundPlayer::msecsToString(qint64 n){
    int nHours = (n/ (60 * 60 * 1000));
    int nMinutes = ((n % (60 *60 * 1000)) /(60 * 1000));
    int nSeconds = ((n % (60 * 1000)) / 1000);
    return QTime(nHours, nMinutes, nSeconds).toString("hh:mm:ss");
}

void SoundPlayer::slotSetDuration(qint64 n){
    m_psldPosition->setRange(0, n);
    m_plblCurrent->setText(msecsToString(0));
    m_plblRemain->setText(msecsToString(n));
}

void SoundPlayer::slotSetSliderPosition(qint64 n){
    m_psldPosition->setValue(n);

    m_plblCurrent->setText(msecsToString(n));
    int nDuration = m_psldPosition->maximum();
    m_plblRemain->setText(msecsToString(nDuration - n));
}

void SoundPlayer::slotDoubleCLickedListItem(int index){

    SoundPlayer::m_pmpl->setCurrentIndex(index);
}








