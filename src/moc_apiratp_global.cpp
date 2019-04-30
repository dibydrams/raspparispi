/****************************************************************************
** Meta object code from reading C++ file 'apiratp_global.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "apiratp_global.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'apiratp_global.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ApiRatp_Global_t {
    QByteArrayData data[8];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ApiRatp_Global_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ApiRatp_Global_t qt_meta_stringdata_ApiRatp_Global = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ApiRatp_Global"
QT_MOC_LITERAL(1, 15, 12), // "callFinished"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 27), // "QList<Abstract_API::GeoObj>"
QT_MOC_LITERAL(4, 57, 9), // "API_index"
QT_MOC_LITERAL(5, 67, 8), // "LoadJson"
QT_MOC_LITERAL(6, 76, 8), // "fileName"
QT_MOC_LITERAL(7, 85, 7) // "getInfo"

    },
    "ApiRatp_Global\0callFinished\0\0"
    "QList<Abstract_API::GeoObj>\0API_index\0"
    "LoadJson\0fileName\0getInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ApiRatp_Global[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   34,    2, 0x08 /* Private */,
       7,    0,   37,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4,    2,    2,

 // slots: parameters
    QMetaType::QJsonDocument, QMetaType::QString,    6,
    QMetaType::Void,

       0        // eod
};

void ApiRatp_Global::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ApiRatp_Global *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->callFinished((*reinterpret_cast< QList<Abstract_API::GeoObj>(*)>(_a[1])),(*reinterpret_cast< API_index(*)>(_a[2]))); break;
        case 1: { QJsonDocument _r = _t->LoadJson((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QJsonDocument*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->getInfo(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ApiRatp_Global::*)(QList<Abstract_API::GeoObj> , API_index );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ApiRatp_Global::callFinished)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ApiRatp_Global::staticMetaObject = { {
    &Abstract_API::staticMetaObject,
    qt_meta_stringdata_ApiRatp_Global.data,
    qt_meta_data_ApiRatp_Global,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ApiRatp_Global::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ApiRatp_Global::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ApiRatp_Global.stringdata0))
        return static_cast<void*>(this);
    return Abstract_API::qt_metacast(_clname);
}

int ApiRatp_Global::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Abstract_API::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ApiRatp_Global::callFinished(QList<Abstract_API::GeoObj> _t1, API_index _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
