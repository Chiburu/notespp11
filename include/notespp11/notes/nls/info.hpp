#ifndef NOTESPP11_NOTES_NLS_INFO_HPP
#define NOTESPP11_NOTES_NLS_INFO_HPP

#include "./status.hpp"

#ifdef NT
#pragma pack(push, 1)
#endif

#include <osmisc.h> // OSGetLMBCSCLS

#ifdef NT
#pragma pack(pop)
#endif

namespace notespp11 {
namespace notes {
namespace nls {

/**
 * @brief NLS(National Language Service)情報のラッパークラスです。
 */
class Info
{
protected:
  NLS_PINFO ptr_; ///< NLSポインタ

public:
  /**
   * @brief コンストラクタです。
   * @param ptr NLS情報へのポインタ
   */
  explicit Info(NLS_PINFO ptr) noexcept : ptr_(ptr) {}

  /**
   * @brief デストラクタです。
   */
  virtual ~Info() = default;

  /**
   * @brief NLS情報へのポインタを返します。
   * @return NLS情報へのポインタ
   */
  NLS_PINFO get() const noexcept { return ptr_; }

  /**
   * @brief ワードサイズ制限内でバイト配列の文字数相当のバイト数を取得します。
   * @param s 対象のバイト配列
   * @param chars バイト数として測りたい文字数(ワードサイズ)
   * @return バイト数(ワードサイズ)
   * @throw Status NLS_STATUSを内包したクラス
   */
  WORD getStringWordBytes(const char *s, WORD chars) const noexcept(false)
  {
    // 文字数が0なら0を返す。
    if (chars < 1) return 0;

    // 文字数相当のバイト数を取得する。
    WORD result = 0;
    Status status = NLS_string_bytes(
          reinterpret_cast<const BYTE*>(s),
          chars,
          &result,
          ptr_
          );

    // エラーなら例外としてスロー。
    if (status.hasError()) throw status;
    return result;
  }

  /**
   * @brief ワードサイズ制限内でバイト配列の文字数を取得します。
   * @param s 対象のバイト配列
   * @param bytes 文字数として測りたいバイト数(ワードサイズ)
   * @return 文字数(ワードサイズ)
   * @throw Status NLS_STATUSを内包したクラス
   */
  WORD getStringWordChars(const char *s, WORD bytes) const noexcept(false)
  {
    // バイト数が0なら0を返す。
    if (bytes < 1) return 0;

    // バイト数相当の文字数を取得する。
    WORD result = 0;
    while (bytes > 0) {
      Status status = NLS_string_chars(
            reinterpret_cast<const BYTE*>(s),
            bytes,
            &result,
            ptr_
            );

      // エラーがなければ取得したサイズを返す。
      if (status.noError()) break;

      // 境界値の不具合以外なら例外としてスロー。
      if (status.error() != NLS_INVALIDDATA) throw status;

      // 1バイト減らすと0になるなら0を返す。
      if (--bytes < 1) return 0;

      // 境界値の不具合ならバイト数を減らして再度試す。
    }
    return result;
  }

  /**
   * @brief バイト配列の文字数を取得します。
   * @tparam T 数の型
   * @param s 対象のバイト配列
   * @param bytes 文字数として測りたいバイト数
   * @return 文字数
   * @throw Status NLS_STATUSを内包したクラス
   */
  template <typename T = int>
  T getStringChars(const char *s, T bytes) const noexcept(false)
  {
    // 文字数が0なら0を返す。
    if (bytes < 1) return 0;

    T offset = 0, chars = 0;
    while (offset < bytes) { // bytes - offset は必ず正

      // 測りたいバイト数とWORD最大値を比較して小さい方を一時範囲として取得。
      auto range = std::min<T>(bytes - offset, MAXWORD - 1);

      // 一時範囲内の文字数を取得する。
      auto c = getStringWordChars(s + offset, static_cast<WORD>(range));

      // 一時範囲内の文字数が0なら結果を返す。
      if (c < 1) break;

      // 一時範囲の文字数を結果に加算する。
      chars += static_cast<T>(c);

      // 一時範囲のバイト数分オフセットを移動する。
      offset += static_cast<T>(getStringWordBytes(s + offset, c));
    }
    return chars;
  }

  /**
   * @brief バイト配列の文字数相当のバイト数を取得します。
   * @tparam T 数の型
   * @param s 対象のバイト配列
   * @param chars バイト数として測りたい文字数
   * @return バイト数
   * @throw Status NLS_STATUSを内包したクラス
   */
  template <typename T = int>
  T getStringBytes(const char *s, T chars) const noexcept(false)
  {
    // 文字数が0なら0を返す。
    if (chars < 1) return 0;

    T offset = 0, bytes = 0;
    while (offset < chars) {

      // 測りたい文字数と(WORD最大値÷1文字当たりの最大バイト数)を比較して、小さい方を一時範囲として取得。
      auto range = std::min<T>(chars - offset, MAXWORD / NLS_MAXBYTESPERCHAR);

      // 一時範囲のバイト数を取得して加算する。
      bytes += static_cast<T>(
            getStringWordBytes(s + bytes, static_cast<WORD>(range))
            );

      // 文字数をオフセット分移動する。
      offset += range;
    }
    return bytes;
  }

  /**
   * @brief マルチバイト文字列の区切り位置を調整したバイト数を求めます。
   * @tparam T 数の型
   * @param s 対象のバイト配列
   * @param bytes 計測対象のバイト数
   * @return 調整したバイト数
   * @throw Status NLS_STATUSを内包したクラス
   */
  template <typename T = int>
  T adjustedByteSize(const char *s, T bytes) const noexcept(false)
  {
    auto chars = getStringChars<T>(s, bytes);
    return getStringBytes<T>(s, chars);
  }

};

/**
 * @brief ロードして使用するNLS情報クラスです。
 * @tparam CSID 文字セットID
 */
template <WORD CSID>
class LoadingInfo : public Info
{
public:
  /**
   * @brief コンストラクタです。
   */
  explicit LoadingInfo() noexcept
    : Info(nullptr)
  {
    NLS_load_charset(CSID, &ptr_);
  }

  /**
   * @brief デストラクタです。
   */
  virtual ~LoadingInfo() override { NLS_unload_charset(ptr_); }
};

/**
 * @brief LMBCS専用NLS情報クラスです。
 */
class LmbcsInfo : public Info
{
public:
  /**
   * @brief コンストラクタ
   */
  LmbcsInfo() noexcept : Info(OSGetLMBCSCLS()) {}

  /**
   * @brief デストラクタ
   */
  virtual ~LmbcsInfo() = default;
};

} // namespace nls
} // namespace notes
} // namespace notespp11

#endif // NOTESPP11_NOTES_NLS_INFO_HPP
