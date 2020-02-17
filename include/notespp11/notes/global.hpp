#ifndef NOTESPP11_NOTES_GLOBAL_HPP
#define NOTESPP11_NOTES_GLOBAL_HPP

#include <functional>

#ifdef NT
#pragma pack(push, 1)
#endif

#include <global.h>

#ifdef NT
#pragma pack(pop)
#endif

namespace notespp11 {
namespace notes {

/**
 * @brief run APIの初期化したら関数を実行する。
 * @param argc コマンドライン引数数
 * @param argv コマンドライン引数配列
 * @param f 実行する関数オブジェクト
 * @return API初期化に成功したら関数の戻り値、失敗したらエラーコード
 */
inline int run(
    int argc,
    char *argv[],
    std::function<int(int,char**)> f
    ) noexcept
{
  // APIの初期化
  STATUS status = NotesInitExtended(argc, argv);

  // 初期化に成功した場合
  if (ERR(status) == NOERROR) {

    // 関数オブジェクトを実行
    auto result = f(argc, argv);

    // APIの後始末
    NotesTerm();

    // 戻り値を返す。
    return result;
  }

  // 初期化に失敗した場合
    // エラーコードを返す。
  return static_cast<int>(status);
}

} // namespace notes
} // namespace notespp11

#endif // NOTESPP11_NOTES_GLOBAL_HPP
