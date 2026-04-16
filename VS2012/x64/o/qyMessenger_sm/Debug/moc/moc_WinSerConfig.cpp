/****************************************************************************
** Meta object code from reading C++ file 'WinSerConfig.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../openRtComm-windows-sm/srcProjs/srcRoot/src6/qyMessenger_sm/qyMessenger_sm/WinSerConfig.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WinSerConfig.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN12WinSerConfigE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN12WinSerConfigE = QtMocHelpers::stringData(
    "WinSerConfig",
    "signal_select_load",
    "",
    "editBtnClicked",
    "delBtnClicked",
    "cancelBtnClicked",
    "addBtnClicked",
    "saveBtnClicked",
    "uuid",
    "deleteBtnClicked",
    "onShowClose",
    "onShowMin",
    "onButtonMinClicked",
    "onButtonCloseClicked"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN12WinSerConfigE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   86,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   87,    2, 0x08,    2 /* Private */,
       4,    0,   88,    2, 0x08,    3 /* Private */,
       5,    0,   89,    2, 0x08,    4 /* Private */,
       6,    0,   90,    2, 0x08,    5 /* Private */,
       7,    0,   91,    2, 0x08,    6 /* Private */,
       3,    1,   92,    2, 0x08,    7 /* Private */,
       9,    1,   95,    2, 0x08,    9 /* Private */,
      10,    1,   98,    2, 0x08,   11 /* Private */,
      11,    1,  101,    2, 0x08,   13 /* Private */,
      12,    0,  104,    2, 0x08,   15 /* Private */,
      13,    0,  105,    2, 0x08,   16 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject WinSerConfig::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_ZN12WinSerConfigE.offsetsAndSizes,
    qt_meta_data_ZN12WinSerConfigE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN12WinSerConfigE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<WinSerConfig, std::true_type>,
        // method 'signal_select_load'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'editBtnClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'delBtnClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'cancelBtnClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addBtnClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveBtnClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'editBtnClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'deleteBtnClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'onShowClose'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onShowMin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onButtonMinClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onButtonCloseClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void WinSerConfig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<WinSerConfig *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->signal_select_load(); break;
        case 1: _t->editBtnClicked(); break;
        case 2: _t->delBtnClicked(); break;
        case 3: _t->cancelBtnClicked(); break;
        case 4: _t->addBtnClicked(); break;
        case 5: _t->saveBtnClicked(); break;
        case 6: _t->editBtnClicked((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->deleteBtnClicked((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->onShowClose((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 9: _t->onShowMin((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 10: _t->onButtonMinClicked(); break;
        case 11: _t->onButtonCloseClicked(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (WinSerConfig::*)();
            if (_q_method_type _q_method = &WinSerConfig::signal_select_load; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *WinSerConfig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WinSerConfig::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN12WinSerConfigE.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int WinSerConfig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void WinSerConfig::signal_select_load()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
