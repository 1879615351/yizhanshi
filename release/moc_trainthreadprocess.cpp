/****************************************************************************
** Meta object code from reading C++ file 'trainthreadprocess.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../untitled/trainthreadprocess.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'trainthreadprocess.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_trainthreadProcess_t {
    QByteArrayData data[7];
    char stringdata0[70];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_trainthreadProcess_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_trainthreadProcess_t qt_meta_stringdata_trainthreadProcess = {
    {
QT_MOC_LITERAL(0, 0, 18), // "trainthreadProcess"
QT_MOC_LITERAL(1, 19, 9), // "trainDone"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 10), // "startTrain"
QT_MOC_LITERAL(4, 41, 7), // "dirPath"
QT_MOC_LITERAL(5, 49, 9), // "stopTrain"
QT_MOC_LITERAL(6, 59, 10) // "closeTrain"

    },
    "trainthreadProcess\0trainDone\0\0startTrain\0"
    "dirPath\0stopTrain\0closeTrain"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_trainthreadProcess[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   35,    2, 0x0a /* Public */,
       5,    0,   38,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
       6,    0,   39,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,

       0        // eod
};

void trainthreadProcess::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<trainthreadProcess *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->trainDone(); break;
        case 1: _t->startTrain((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->stopTrain(); break;
        case 3: _t->closeTrain(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (trainthreadProcess::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&trainthreadProcess::trainDone)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject trainthreadProcess::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_trainthreadProcess.data,
    qt_meta_data_trainthreadProcess,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *trainthreadProcess::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *trainthreadProcess::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_trainthreadProcess.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int trainthreadProcess::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void trainthreadProcess::trainDone()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
