#ifndef NOTESPP11_NOTES_NLS_XLATE_HPP
#define NOTESPP11_NOTES_NLS_XLATE_HPP

#include "./info.hpp"
#include <QByteArray>
#include <QString>
#include <type_traits>

namespace notespp11 {
namespace notes {
namespace nls {

/**
 * @brief キロバイトをバイトにします。
 * @tparam T 数値型
 * @param n キロバイト
 * @return バイト
 */
template <typename T>
T KBtoB(T n) noexcept { return n * 1024; }

/**
 * @brief バイト配列を元の文字セットから目的の文字セットに変換します。
 * @tparam mode 変換モード(NLSベース)
 * @tparam ratio 準備するバッファの、元のバイト配列と比較した倍率
 * @param array 変換元のバイト配列
 * @param fromInfo 元の文字セットのNLS情報
 * @param toInfo 目的の文字セットのNLS情報
 * @return 変換結果
 * @throw Status
 */
template <WORD mode, int ratio>
QByteArray translate(
    const QByteArray &array,
    const Info &fromInfo,
    const Info &toInfo
    ) noexcept(false)
{
  // バイト配列の長さ
  auto maxSize = array.length();

  // バイト配列の長さによって変換する単位バイトを決定
  // 16KB以上であれば8KB単位、より小さければ1KB単位
  auto CHUNK_SIZE = (maxSize >= KBtoB<int>(16)) ? KBtoB<int>(8) : KBtoB<int>(1);

  // オフセット位置
  int offset = 0;

  // 変換結果の格納先
  QByteArray result;

  // オフセット位置が長さを超えるまでループ
  while (offset < maxSize) {

    // 変換対象が単位バイトを超えた場合は単位バイト、
    // 超えていなければ変換対象全体の長さをチャンクサイズにする。
    auto chunkSize = std::min<int>(maxSize - offset, CHUNK_SIZE);

    // チャンクサイズが文字の途中にならないように調整
    chunkSize = fromInfo.adjustedByteSize(
          array.constData() + offset,
          chunkSize
          );

    // チャンクサイズが0になったら終了
    if (chunkSize <= 0) break;

    // バイト配列からチャンクサイズ分だけ取得
    auto chunk = array.mid(offset, chunkSize);

    // 変換したバイト配列を格納するバッファを準備
    auto bufSize = chunkSize * ratio;
    QByteArray buffer(bufSize, '\0');

    // 変換する
    auto len = static_cast<WORD>(bufSize);
    Status status = NLS_translate(
            reinterpret_cast<BYTE*>(chunk.data()),
            static_cast<WORD>(chunkSize),
            reinterpret_cast<BYTE*>(buffer.data()),
            &len,
            mode,
            toInfo.get()
            );

    // エラーなら例外をスロー
    if (status.hasError()) throw status;

    // 変換したバイト配列を格納先に追加
    result.append(buffer.left(static_cast<int>(len)));

    // オフセット位置をチャンクサイズ分移動
    offset += chunkSize;
  }
  return result;
}

/**
 * @brief Unicode(UTF16)バイト配列をLMBCSバイト配列に変換します。
 * @param unicode Unicodeバイト配列
 * @return 変換結果
 * @throw Status
 */
inline QByteArray unicodeToLmbcs(const QByteArray &unicode) noexcept(false)
{
  nls::LoadingInfo<NLS_CS_UNICODE> unicodeInfo;
  nls::LmbcsInfo lmbcsInfo;
  return translate<
      NLS_NONULLTERMINATE | NLS_SOURCEISUNICODE | NLS_TARGETISLMBCS,
      NLS_MAXRATIO_XLATE_TO_LMBCS>(
        unicode,
        unicodeInfo,
        lmbcsInfo
        );
}

/**
 * @brief LMBCSバイト配列をUnicode(UTF16)バイト配列に変換します。
 * @param lmbcs LMBCSバイト配列
 * @return 変換結果
 * @throw Status
 */
inline QByteArray lmbcsToUnicode(const QByteArray &lmbcs) noexcept(false)
{
  nls::LoadingInfo<NLS_CS_UNICODE> unicodeInfo;
  nls::LmbcsInfo lmbcsInfo;
  return translate<
      NLS_NONULLTERMINATE | NLS_SOURCEISLMBCS | NLS_TARGETISUNICODE,
      NLS_MAXRATIO_XLATE_FROM_LMBCS>(
        lmbcs,
        lmbcsInfo,
        unicodeInfo
        );
}

/**
 * @brief QStringをLMBCSバイト配列オブジェクトに変換します。
 * @tparam LMBCSバイト配列を格納する型(デフォルトはQByteArray)
 * @param qs QString文字列(変換元)
 * @return 変換結果のLMBCSバイト配列オブジェクト
 * @throw Status
 */
template <typename T = QByteArray>
T qstringToLmbcs(const QString &qs) noexcept(false)
{
  auto utf16 = QByteArray(
        reinterpret_cast<const char*>(qs.utf16()),
        qs.length() * 2
        );
  auto result = unicodeToLmbcs(utf16);
  return std::is_same<T, QByteArray>::value == true ? result : T(result);
}

/**
 * @brief LMBCSバイト配列オブジェクトをQStringに変換します。
 * @tparam LMBCSバイト配列を格納する型(デフォルトはQByteArray)
 * @param lmbcs LMBCSバイト配列オブジェクト
 * @return 変換結果のLMBCSバイト配列オブジェクト
 * @throw Status
 */
template <typename T = QByteArray>
QString lmbcsToQString(const T &lmbcs) noexcept(false)
{
  auto utf16 = lmbcsToUnicode(lmbcs);
  return QString::fromUtf16(
        reinterpret_cast<const ushort *>(utf16.constData()),
        utf16.length() / 2
        );
}

} // namespace nls
} // namespace notes
} // namespace notespp11

#endif // NOTESPP11_NOTES_NLS_XLATE_HPP
