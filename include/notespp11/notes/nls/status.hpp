#ifndef NOTESPP11_NOTES_NLS_STATUS_HPP
#define NOTESPP11_NOTES_NLS_STATUS_HPP

#include <exception>

#ifdef NT
#pragma pack(push, 1)
#endif

#include <global.h>
#include <nls.h>

#ifdef NT
#pragma pack(pop)
#endif

namespace notespp11 {
namespace notes {
namespace nls {

/**
 * @brief NLS用ステータスクラス
 */
class Status
    : public std::exception
{
  NLS_STATUS status_; //<<< NLSステータス値

public:
  /**
   * @brief デフォルトコンストラクタ。
   */
  Status() noexcept : std::exception(), status_(NLS_SUCCESS) {}

  /**
   * @brief コンストラクタ。
   * @param status 初期NLSステータス値
   */
  Status(NLS_STATUS status) noexcept : std::exception(), status_(status) {}

  /**
   * @brief エラー値を返す。
   * @return エラー値(ステータス値)
   */
  NLS_STATUS error() const noexcept { return status_; }

  /**
   * @brief エラーがなければ真を返す。
   * @return エラーがなければ真
   */
  bool noError() const noexcept { return error() == NLS_SUCCESS; }

  /**
   * @brief エラーがあれば真を返す。
   * @return エラーがあれば真
   */
  bool hasError() const noexcept { return !noError(); }

  /**
   * @brief エラーメッセージを返す。
   * @return エラーメッセージ
   */
  virtual const char *what() const noexcept override
  {
    switch (status_) {
    case NLS_SUCCESS: return "Success.";
    case NLS_BADPARM: return "Bad Parameters.";
    case NLS_BUFFERTOOSMALL: return "Buffer too small.";
    case NLS_CHARSSTRIPPED: return "Chars stripped.";
    case NLS_ENDOFSTRING: return "End of string.";
    case NLS_FALLBACKUSED: return "Fallback used.";
    case NLS_FILEINVALID: return "File invalid.";
    case NLS_FILENOTFOUND: return "File not found.";
    case NLS_FINDFAILED: return "Find failed.";
    case NLS_INVALIDCHARACTER: return "Invalid character.";
    case NLS_INVALIDDATA: return "Invalid data.";
    case NLS_INVALIDENTRY: return "Invalid entry.";
    case NLS_INVALIDTABLE: return "Invalid table.";
    case NLS_PROPNOTFOUND: return "Prop not found.";
    case NLS_STARTOFSTRING: return "Start of string.";
    case NLS_STRINGSIZECHANGED: return "String size changed.";
    case NLS_TABLEHEADERINVALID: return "Table header invalid.";
    case NLS_TABLENOTFOUND: return "Table not found.";
    default: return "Unknown NLS status.";
    }
  }
};

} // namespace nls
} // namespace notes
} // namespace notespp11

#endif // NOTESPP11_NOTES_NLS_STATUS_HPP
