#include "nlstest.h"

#include <notespp11/notes/nls/info.hpp>

void NlsTest::test_countString1()
{
  // LMBCS文字列を対象にする。
  auto lmbcsInfo = npp::nls::LmbcsInfo();

  { // 対象文字列: abc123ABC
    auto target = QByteArray("abc123ABC");
    const WORD chars = 9; const WORD length = target.length();
    QVERIFY(length == lmbcsInfo.getStringWordBytes(target.constData(), chars));
    QVERIFY(chars == lmbcsInfo.getStringWordChars(target.constData(), length));
  }
  { // 対象文字列: あいうaiuｱｲｳ
    auto target = QByteArray("\x10\x82\xa0\x10\x82\xa2\x10\x82\xa4"
                             "\x61\x69\x75"
                             "\x10\x10\xb1\x10\x10\xb2\x10\x10\xb3");
    const WORD chars = 9; const WORD length = target.length();
    QVERIFY(length == lmbcsInfo.getStringWordBytes(target.constData(), chars));
    QVERIFY(chars == lmbcsInfo.getStringWordChars(target.constData(), length));
    QVERIFY((length - 3) == lmbcsInfo.getStringWordBytes(target.constData(), chars - 1));
    QVERIFY((length - 6) == lmbcsInfo.getStringWordBytes(target.constData(), chars - 2));
    QVERIFY((length - 9) == lmbcsInfo.getStringWordBytes(target.constData(), chars - 3));
    QVERIFY((length - 10) == lmbcsInfo.getStringWordBytes(target.constData(), chars - 4));
    QVERIFY((length - 11) == lmbcsInfo.getStringWordBytes(target.constData(), chars - 5));
    QVERIFY((length - 12) == lmbcsInfo.getStringWordBytes(target.constData(), chars - 6));
    QVERIFY((length - 15) == lmbcsInfo.getStringWordBytes(target.constData(), chars - 7));
    QVERIFY((length - 18) == lmbcsInfo.getStringWordBytes(target.constData(), chars - 8));
    QVERIFY((length - 21) == lmbcsInfo.getStringWordBytes(target.constData(), chars - 9));
    QVERIFY((chars - 1) == lmbcsInfo.getStringWordChars(target.constData(), length - 1));
    QVERIFY((chars - 1) == lmbcsInfo.getStringWordChars(target.constData(), length - 2));
    QVERIFY((chars - 1) == lmbcsInfo.getStringWordChars(target.constData(), length - 3));
  }
}
