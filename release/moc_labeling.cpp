/****************************************************************************
** Meta object code from reading C++ file 'labeling.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../untitled/labeling.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'labeling.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_labeling_t {
    QByteArrayData data[55];
    char stringdata0[580];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_labeling_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_labeling_t qt_meta_stringdata_labeling = {
    {
QT_MOC_LITERAL(0, 0, 8), // "labeling"
QT_MOC_LITERAL(1, 9, 19), // "pictureChangeSignal"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 3), // "img"
QT_MOC_LITERAL(4, 34, 18), // "openModeTypeSignal"
QT_MOC_LITERAL(5, 53, 4), // "type"
QT_MOC_LITERAL(6, 58, 16), // "setPictureSignal"
QT_MOC_LITERAL(7, 75, 2), // "pw"
QT_MOC_LITERAL(8, 78, 2), // "ph"
QT_MOC_LITERAL(9, 81, 11), // "setPicLabel"
QT_MOC_LITERAL(10, 93, 2), // "bx"
QT_MOC_LITERAL(11, 96, 2), // "by"
QT_MOC_LITERAL(12, 99, 2), // "ex"
QT_MOC_LITERAL(13, 102, 2), // "ey"
QT_MOC_LITERAL(14, 105, 16), // "setPicLabel_None"
QT_MOC_LITERAL(15, 122, 15), // "setLabelPercent"
QT_MOC_LITERAL(16, 138, 5), // "index"
QT_MOC_LITERAL(17, 144, 5), // "count"
QT_MOC_LITERAL(18, 150, 7), // "percent"
QT_MOC_LITERAL(19, 158, 10), // "resetCanvs"
QT_MOC_LITERAL(20, 169, 11), // "setListView"
QT_MOC_LITERAL(21, 181, 1), // "n"
QT_MOC_LITERAL(22, 183, 14), // "resetCameraBtn"
QT_MOC_LITERAL(23, 198, 12), // "startProcess"
QT_MOC_LITERAL(24, 211, 3), // "dir"
QT_MOC_LITERAL(25, 215, 14), // "sendTrainLabel"
QT_MOC_LITERAL(26, 230, 8), // "filepath"
QT_MOC_LITERAL(27, 239, 8), // "filename"
QT_MOC_LITERAL(28, 248, 9), // "trainText"
QT_MOC_LITERAL(29, 258, 15), // "stopTrainSignal"
QT_MOC_LITERAL(30, 274, 15), // "exportTrainData"
QT_MOC_LITERAL(31, 290, 12), // "setDetectDir"
QT_MOC_LITERAL(32, 303, 15), // "sendDetectImage"
QT_MOC_LITERAL(33, 319, 16), // "getPictureFloder"
QT_MOC_LITERAL(34, 336, 4), // "mode"
QT_MOC_LITERAL(35, 341, 16), // "pictureFloderUrl"
QT_MOC_LITERAL(36, 358, 12), // "getVideoFile"
QT_MOC_LITERAL(37, 371, 12), // "vidoeFileUrl"
QT_MOC_LITERAL(38, 384, 9), // "getCamera"
QT_MOC_LITERAL(39, 394, 13), // "changePicture"
QT_MOC_LITERAL(40, 408, 12), // "findSameName"
QT_MOC_LITERAL(41, 421, 4), // "name"
QT_MOC_LITERAL(42, 426, 12), // "addClassName"
QT_MOC_LITERAL(43, 439, 12), // "addLabelData"
QT_MOC_LITERAL(44, 452, 15), // "tryReleaseVideo"
QT_MOC_LITERAL(45, 468, 16), // "tryReleaseCamera"
QT_MOC_LITERAL(46, 485, 15), // "exportLabelData"
QT_MOC_LITERAL(47, 501, 11), // "getshowMode"
QT_MOC_LITERAL(48, 513, 10), // "beginTrain"
QT_MOC_LITERAL(49, 524, 9), // "stopTrain"
QT_MOC_LITERAL(50, 534, 8), // "beginUse"
QT_MOC_LITERAL(51, 543, 11), // "setLabeling"
QT_MOC_LITERAL(52, 555, 9), // "setDetect"
QT_MOC_LITERAL(53, 565, 1), // "m"
QT_MOC_LITERAL(54, 567, 12) // "detectChange"

    },
    "labeling\0pictureChangeSignal\0\0img\0"
    "openModeTypeSignal\0type\0setPictureSignal\0"
    "pw\0ph\0setPicLabel\0bx\0by\0ex\0ey\0"
    "setPicLabel_None\0setLabelPercent\0index\0"
    "count\0percent\0resetCanvs\0setListView\0"
    "n\0resetCameraBtn\0startProcess\0dir\0"
    "sendTrainLabel\0filepath\0filename\0"
    "trainText\0stopTrainSignal\0exportTrainData\0"
    "setDetectDir\0sendDetectImage\0"
    "getPictureFloder\0mode\0pictureFloderUrl\0"
    "getVideoFile\0vidoeFileUrl\0getCamera\0"
    "changePicture\0findSameName\0name\0"
    "addClassName\0addLabelData\0tryReleaseVideo\0"
    "tryReleaseCamera\0exportLabelData\0"
    "getshowMode\0beginTrain\0stopTrain\0"
    "beginUse\0setLabeling\0setDetect\0m\0"
    "detectChange"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_labeling[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      32,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      15,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  174,    2, 0x06 /* Public */,
       4,    1,  177,    2, 0x06 /* Public */,
       6,    2,  180,    2, 0x06 /* Public */,
       9,    5,  185,    2, 0x06 /* Public */,
      14,    0,  196,    2, 0x06 /* Public */,
      15,    3,  197,    2, 0x06 /* Public */,
      19,    0,  204,    2, 0x06 /* Public */,
      20,    1,  205,    2, 0x06 /* Public */,
      22,    0,  208,    2, 0x06 /* Public */,
      23,    1,  209,    2, 0x06 /* Public */,
      25,    3,  212,    2, 0x06 /* Public */,
      29,    0,  219,    2, 0x06 /* Public */,
      30,    0,  220,    2, 0x06 /* Public */,
      31,    1,  221,    2, 0x06 /* Public */,
      32,    1,  224,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
      33,    2,  227,    2, 0x02 /* Public */,
      36,    2,  232,    2, 0x02 /* Public */,
      38,    0,  237,    2, 0x02 /* Public */,
      39,    1,  238,    2, 0x02 /* Public */,
      40,    1,  241,    2, 0x02 /* Public */,
      42,    1,  244,    2, 0x02 /* Public */,
      43,    5,  247,    2, 0x02 /* Public */,
      44,    0,  258,    2, 0x02 /* Public */,
      45,    0,  259,    2, 0x02 /* Public */,
      46,    0,  260,    2, 0x02 /* Public */,
      47,    1,  261,    2, 0x02 /* Public */,
      48,    0,  264,    2, 0x02 /* Public */,
      49,    0,  265,    2, 0x02 /* Public */,
      50,    0,  266,    2, 0x02 /* Public */,
      51,    0,  267,    2, 0x02 /* Public */,
      52,    2,  268,    2, 0x02 /* Public */,
      54,    1,  273,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,    5,   10,   11,   12,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   16,   17,   18,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   24,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   26,   27,   28,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   24,
    QMetaType::Void, QMetaType::QImage,    3,

 // methods: parameters
    QMetaType::Void, QMetaType::SChar, QMetaType::QString,   34,   35,
    QMetaType::Void, QMetaType::SChar, QMetaType::QString,   34,   37,
    QMetaType::Void,
    QMetaType::Void, QMetaType::SChar,   24,
    QMetaType::Bool, QMetaType::QString,   41,
    QMetaType::Void, QMetaType::QString,   41,
    QMetaType::Void, QMetaType::Int, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,    5,   10,   11,   12,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   53,   24,
    QMetaType::Void, QMetaType::Int,   24,

       0        // eod
};

void labeling::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<labeling *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pictureChangeSignal((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 1: _t->openModeTypeSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setPictureSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->setPicLabel((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< float(*)>(_a[5]))); break;
        case 4: _t->setPicLabel_None(); break;
        case 5: _t->setLabelPercent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 6: _t->resetCanvs(); break;
        case 7: _t->setListView((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->resetCameraBtn(); break;
        case 9: _t->startProcess((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->sendTrainLabel((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 11: _t->stopTrainSignal(); break;
        case 12: _t->exportTrainData(); break;
        case 13: _t->setDetectDir((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: _t->sendDetectImage((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 15: _t->getPictureFloder((*reinterpret_cast< qint8(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 16: _t->getVideoFile((*reinterpret_cast< qint8(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 17: _t->getCamera(); break;
        case 18: _t->changePicture((*reinterpret_cast< qint8(*)>(_a[1]))); break;
        case 19: { bool _r = _t->findSameName((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 20: _t->addClassName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: _t->addLabelData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< float(*)>(_a[5]))); break;
        case 22: _t->tryReleaseVideo(); break;
        case 23: _t->tryReleaseCamera(); break;
        case 24: _t->exportLabelData(); break;
        case 25: _t->getshowMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->beginTrain(); break;
        case 27: _t->stopTrain(); break;
        case 28: _t->beginUse(); break;
        case 29: _t->setLabeling(); break;
        case 30: _t->setDetect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 31: _t->detectChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (labeling::*)(QImage );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&labeling::pictureChangeSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (labeling::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&labeling::openModeTypeSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (labeling::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&labeling::setPictureSignal)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (labeling::*)(int , float , float , float , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&labeling::setPicLabel)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (labeling::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&labeling::setPicLabel_None)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (labeling::*)(int , int , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&labeling::setLabelPercent)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (labeling::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&labeling::resetCanvs)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (labeling::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&labeling::setListView)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (labeling::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&labeling::resetCameraBtn)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (labeling::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&labeling::startProcess)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (labeling::*)(QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&labeling::sendTrainLabel)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (labeling::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&labeling::stopTrainSignal)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (labeling::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&labeling::exportTrainData)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (labeling::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&labeling::setDetectDir)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (labeling::*)(QImage );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&labeling::sendDetectImage)) {
                *result = 14;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject labeling::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_labeling.data,
    qt_meta_data_labeling,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *labeling::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *labeling::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_labeling.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int labeling::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 32)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 32;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 32)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 32;
    }
    return _id;
}

// SIGNAL 0
void labeling::pictureChangeSignal(QImage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void labeling::openModeTypeSignal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void labeling::setPictureSignal(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void labeling::setPicLabel(int _t1, float _t2, float _t3, float _t4, float _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void labeling::setPicLabel_None()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void labeling::setLabelPercent(int _t1, int _t2, float _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void labeling::resetCanvs()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void labeling::setListView(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void labeling::resetCameraBtn()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void labeling::startProcess(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void labeling::sendTrainLabel(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void labeling::stopTrainSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void labeling::exportTrainData()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void labeling::setDetectDir(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void labeling::sendDetectImage(QImage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
