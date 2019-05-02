/****************************************************************************
** Meta object code from reading C++ file 'uiratp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/uiratp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uiratp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Uiratp_t {
    QByteArrayData data[9];
    char stringdata0[107];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Uiratp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Uiratp_t qt_meta_stringdata_Uiratp = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Uiratp"
QT_MOC_LITERAL(1, 7, 20), // "SetUniTransportIndex"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 6), // "_codeT"
QT_MOC_LITERAL(4, 36, 18), // "SetUniStationIndex"
QT_MOC_LITERAL(5, 55, 6), // "_codeS"
QT_MOC_LITERAL(6, 62, 14), // "ShowTransports"
QT_MOC_LITERAL(7, 77, 23), // "ShowTransportStopPoints"
QT_MOC_LITERAL(8, 101, 5) // "_code"

    },
    "Uiratp\0SetUniTransportIndex\0\0_codeT\0"
    "SetUniStationIndex\0_codeS\0ShowTransports\0"
    "ShowTransportStopPoints\0_code"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Uiratp[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x08 /* Private */,
       4,    1,   37,    2, 0x08 /* Private */,
       6,    0,   40,    2, 0x08 /* Private */,
       7,    1,   41,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,

       0        // eod
};

void Uiratp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Uiratp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SetUniTransportIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->SetUniStationIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->ShowTransports(); break;
        case 3: _t->ShowTransportStopPoints((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Uiratp::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_Uiratp.data,
    qt_meta_data_Uiratp,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Uiratp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Uiratp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Uiratp.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Uiratp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
