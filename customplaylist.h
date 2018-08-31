#ifndef CUSTOMPLAYLIST_H
#define CUSTOMPLAYLIST_H
#include <QtMultimedia>
#include <QtMultimediaWidgets>

class CustomPlaylist : public QMediaPlaylist
{
    Q_OBJECT
public:
    QStringList createNewPlaylist();
    CustomPlaylist(QWidget* pwgt = 0);
    QStringList* m_pstrltBasePlayList; //media will added here firstly
    QListWidget* m_plw;
public slots:
    void filesOpened(QStringList*);
    void slotDoubleClickedListItem();
    void slotCurrentIndexChanged(int index);
signals:
    void signalDoubleClickedListItem(int index);
    void signalCurrentIndexChanged(int index);

};

#endif // CUSTOMPLAYLIST_H
