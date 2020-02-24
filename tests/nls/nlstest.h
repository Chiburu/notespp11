#ifndef NLSTEST_H
#define NLSTEST_H

#include <QtTest>

#include <notespp11/notes/global.hpp>
namespace npp = notespp11::notes;

class NlsTest : public QObject
{
  Q_OBJECT

  STATUS status_;

public:
  NlsTest(){}
  ~NlsTest(){}

private slots:
  void initTestCase()
  {
    status_ = NotesInitExtended(__argc, __argv);
    QVERIFY(ERR(status_) == NOERROR);
  }

  void cleanupTestCase()
  {
    if (ERR(status_) == NOERROR) NotesTerm();
  }

  void test_countString1();
  void test_countString2();
  void test_lmbcsToUnicode();
  void test_unicodeToLmbcs();
};

#endif // NLSTEST_H
