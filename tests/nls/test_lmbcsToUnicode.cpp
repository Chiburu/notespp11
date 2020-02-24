#include "nlstest.h"

#include <notespp11/notes/lmbcs.hpp>

void NlsTest::test_lmbcsToUnicode()
{
  // 対象文字列: あいうaiuｱｲｳ
  auto lmbcs = QByteArray("\x10\x82\xa0\x10\x82\xa2\x10\x82\xa4"
                           "\x61\x69\x75"
                           "\x10\x10\xb1\x10\x10\xb2\x10\x10\xb3");
  auto qs = QString("あいうaiuｱｲｳ");
  auto unicode = QByteArray(
        reinterpret_cast<const char*>(qs.utf16()),
        qs.size() * 2
        );
  auto xlated = npp::nls::lmbcsToUnicode(lmbcs);
  QVERIFY(unicode == xlated);
  QVERIFY(npp::nls::qstringToLmbcs(qs) == lmbcs);

  auto lmbcs2 = npp::Lmbcs(lmbcs);
  QVERIFY(qs == lmbcs2.qs());
}
