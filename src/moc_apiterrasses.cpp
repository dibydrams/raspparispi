/****************************************************************************
** Meta object code from reading C++ file 'apiterrasses.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "apiterrasses.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'apiterrasses.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ApiTerrasses_t {
    QByteArrayData data[10];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ApiTerrasses_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ApiTerrasses_t qt_meta_stringdata_ApiTerrasses = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ApiTerrasses"
QT_MOC_LITERAL(1, 13, 12), // "callFinished"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 27), // "QList<Abstract_API::GeoObj>"
QT_MOC_LITERAL(4, 55, 9), // "API_index"
QT_MOC_LITERAL(5, 65, 8), // "API_Call"
QT_MOC_LITERAL(6, 74, 11), // "API_Results"
QT_MOC_LITERAL(7, 86, 14), // "QNetworkReply*"
QT_MOC_LITERAL(8, 101, 5), // "reply"
QT_MOC_LITERAL(9, 107, 7) // "getInfo"

    },
    "ApiTerrasses\0callFinished\0\0"
    "QList<Abstract_API::GeoObj>\0API_index\0"
    "API_Call\0API_Results\0QNetworkReply*\0"
    "reply\0getInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ApiTerrasses[] = {

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
       1,    2,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   39,    2, 0x08 /* Private */,
       6,    1,   40,    2, 0x08 /* Private */,
       9,    0,   43,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,

       0        // eod
};

void ApiTerrasses::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ApiTerrasses *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->callFinished((*reinterpret_cast< QList<Abstract_API::GeoObj>(*)>(_a[1])),(*reinterpret_cast< API_index(*)>(_a[2]))); break;
        case 1: _t->API_Call(); break;
        case 2: _t->API_Results((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 3: _t->getInfo(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ApiTerrasses::*)(QList<Abstract_API::GeoObj> , API_index );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ApiTerrasses::callFinished)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ApiTerrasses::staticMetaObject = { {
    &Abstract_API::staticMetaObject,
    qt_meta_stringdata_ApiTerrasses.data,
    qt_meta_data_ApiTerrasses,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ApiTerrasses::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ApiTerrasses::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ApiTerrasses.stringdata0))
        return static_cast<void*>(this);
    return Abstract_API::qt_metacast(_clname);
}

int ApiTerrasses::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Abstract_API::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ApiTerrasses::callFinished(QList<Abstract_API::GeoObj> _t1, API_index _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
