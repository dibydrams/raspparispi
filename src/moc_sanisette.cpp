/****************************************************************************
** Meta object code from reading C++ file 'sanisette.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sanisette.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sanisette.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_sanisette_t {
    QByteArrayData data[8];
    char stringdata0[101];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_sanisette_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_sanisette_t qt_meta_stringdata_sanisette = {
    {
QT_MOC_LITERAL(0, 0, 9), // "sanisette"
QT_MOC_LITERAL(1, 10, 12), // "callFinished"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 27), // "QList<Abstract_API::GeoObj>"
QT_MOC_LITERAL(4, 52, 9), // "API_index"
QT_MOC_LITERAL(5, 62, 17), // "sanisetteAPI_Call"
QT_MOC_LITERAL(6, 80, 12), // "readJsonSani"
QT_MOC_LITERAL(7, 93, 7) // "getInfo"

    },
    "sanisette\0callFinished\0\0"
    "QList<Abstract_API::GeoObj>\0API_index\0"
    "sanisetteAPI_Call\0readJsonSani\0getInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_sanisette[] = {

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
       5,    0,   39,    2, 0x0a /* Public */,
       6,    0,   40,    2, 0x0a /* Public */,
       7,    0,   41,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void sanisette::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<sanisette *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->callFinished((*reinterpret_cast< QList<Abstract_API::GeoObj>(*)>(_a[1])),(*reinterpret_cast< API_index(*)>(_a[2]))); break;
        case 1: _t->sanisetteAPI_Call(); break;
        case 2: _t->readJsonSani(); break;
        case 3: _t->getInfo(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (sanisette::*)(QList<Abstract_API::GeoObj> , API_index );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&sanisette::callFinished)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject sanisette::staticMetaObject = { {
    &Abstract_API::staticMetaObject,
    qt_meta_stringdata_sanisette.data,
    qt_meta_data_sanisette,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *sanisette::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *sanisette::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_sanisette.stringdata0))
        return static_cast<void*>(this);
    return Abstract_API::qt_metacast(_clname);
}

int sanisette::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void sanisette::callFinished(QList<Abstract_API::GeoObj> _t1, API_index _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
