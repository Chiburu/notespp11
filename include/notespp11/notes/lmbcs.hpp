#ifndef NOTESPP11_NOTES_LMBCS_HPP
#define NOTESPP11_NOTES_LMBCS_HPP

#include "./nls/xlate.hpp"

namespace notespp11 {
namespace notes {

/**
 * @brief LMBCS文字列クラスです。
 */
class Lmbcs
    : public QByteArray
{
public:
  /**
   * @brief デフォルトコンストラクタです。
   */
  Lmbcs() : QByteArray() {}

  /**
   * @brief コピーコンストラクタです。
   * @param lmbcs コピー元LMBCS文字列
   */
  Lmbcs(const Lmbcs &lmbcs) : QByteArray(lmbcs) {}

  /**
   * @brief コンストラクタです。
   * @param bytes コピー元バイト配列
   */
  Lmbcs(const QByteArray &bytes) : QByteArray(bytes) {}

  /**
   * @brief デストラクタです。
   */
  virtual ~Lmbcs() {}

  /**
   * @brief QStringに変換して返します。
   * @return 変換されたQString
   */
  QString qs() const noexcept(false)
  {
    return nls::lmbcsToQString<Lmbcs>(*this);
  }

  /**
   * @brief QStringからLmbcsに変換して返します。
   * @param qstr QString文字列
   * @return Lmbcsオブジェクト
   */
  static Lmbcs fromQString(const QString &qstr) noexcept(false)
  {
    return nls::qstringToLmbcs<Lmbcs>(qstr);
  }
};

} // namespace notes
} // namespace notespp11

#endif // NOTESPP11_NOTES_LMBCS_HPP
