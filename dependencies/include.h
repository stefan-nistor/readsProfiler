//
// Created by stefan on 06.01.2022.
//

#ifndef READSPROFILER_INCLUDE_H
#define READSPROFILER_INCLUDE_H

#define CDS_QT

#include <QMainWindow>
#include <QWidget>
#include <QLayout>
#include <QLineEdit>
#include <QLabel>
#include <QDateEdit>
#include <QSpinBox>
#include <QScrollArea>
#include <QPushButton>
#include <QSplitter>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "../client/AbstractDrawable.h"
#include <CDS/Pointer>
#include <CDS/List>
#include <CDS/Thread>
#include <CDS/Function>
#include <CDS/JSON>

#define PORT 42069
#define IP "127.0.0.1"
#define MAX_CLIENTS 10
using namespace cds;

enum RequestType {
    CREATE_ACCOUNT,
    LOGIN,
    FILTER_BOOKS,
    READ,
    DOWNLOAD,
    RECOMMEND
};


#endif //READSPROFILER_INCLUDE_H
