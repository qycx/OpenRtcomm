/****************************************************************************
** Meta object code from reading C++ file 'CDlgTalk_speaker_list.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../openRtComm-windows-sm/srcProjs/srcRoot/src6/qyMessenger_sm/qyMessenger_sm/CDlgTalk_speaker_list.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CDlgTalk_speaker_list.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN21CDlgTalk_speaker_listE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN21CDlgTalk_speaker_listE = QtMocHelpers::stringData(
    "CDlgTalk_speaker_list"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN21CDlgTalk_speaker_listE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject CDlgTalk_speaker_list::staticMetaObject = { {
    QMetaObject::SuperData::link<WinBaseDialog::staticMetaObject>(),
    qt_meta_stringdata_ZN21CDlgTalk_speaker_listE.offsetsAndSizes,
    qt_meta_data_ZN21CDlgTalk_speaker_listE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN21CDlgTalk_speaker_listE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<CDlgTalk_speaker_list, std::true_type>
    >,
    nullptr
} };

void CDlgTalk_speaker_list::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<CDlgTalk_speaker_list *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *CDlgTalk_speaker_list::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CDlgTalk_speaker_list::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN21CDlgTalk_speaker_listE.stringdata0))
        return static_cast<void*>(this);
    return WinBaseDialog::qt_metacast(_clname);
}

int CDlgTalk_speaker_list::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WinBaseDialog::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
