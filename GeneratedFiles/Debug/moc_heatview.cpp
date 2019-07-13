/****************************************************************************
** Meta object code from reading C++ file 'heatview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../view/heatview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'heatview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HeatView_t {
    QByteArrayData data[6];
    char stringdata0[42];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HeatView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HeatView_t qt_meta_stringdata_HeatView = {
    {
QT_MOC_LITERAL(0, 0, 8), // "HeatView"
QT_MOC_LITERAL(1, 9, 8), // "SendTime"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 3), // "val"
QT_MOC_LITERAL(4, 23, 7), // "ExitWin"
QT_MOC_LITERAL(5, 31, 10) // "ChangeTime"

    },
    "HeatView\0SendTime\0\0val\0ExitWin\0"
    "ChangeTime"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HeatView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    0,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   33,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void HeatView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HeatView *_t = static_cast<HeatView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SendTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->ExitWin(); break;
        case 2: _t->ChangeTime(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (HeatView::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HeatView::SendTime)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (HeatView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HeatView::ExitWin)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject HeatView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_HeatView.data,
      qt_meta_data_HeatView,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *HeatView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HeatView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HeatView.stringdata0))
        return static_cast<void*>(const_cast< HeatView*>(this));
    return QWidget::qt_metacast(_clname);
}

int HeatView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void HeatView::SendTime(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void HeatView::ExitWin()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
