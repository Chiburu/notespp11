#include "nlstest.h"

#include <notespp11/notes/nls/xlate.hpp>
#include <notespp11/notes/lmbcs.hpp>

void NlsTest::test_unicodeToLmbcs()
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
  auto xlated = npp::nls::unicodeToLmbcs(unicode);
  QVERIFY(lmbcs == xlated);
  QVERIFY(lmbcs == npp::nls::qstringToLmbcs(qs));

  auto lmbcs2 = npp::Lmbcs::fromQString(qs);
  QVERIFY(lmbcs == lmbcs2);
}
