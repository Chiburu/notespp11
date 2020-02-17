#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>
#include <QTimer>
#include <QTextStream>

#include <notespp11/notes/global.hpp>
namespace npp = notespp11::notes;

int main(int argc, char *argv[])
{
  // Notes APIを初期化
  return npp::run(argc, argv, [](int argc, char *argv[]) {

    // QCoreApplicationを初期化
    QCoreApplication app(argc, argv);

    // 翻訳ファイルをインストール
    QTranslator tr;
    if (tr.load(QLocale::system(), "first-app", "_", ":/translations")) {
      app.installTranslator(&tr);
    }

    // シングルショットイベントを追加
    QTimer::singleShot(0, [&]() {

      // 標準出力ストリームを初期化
      QTextStream cout(stdout);

      // メッセージ表示
      cout << QObject::tr("Hello, World.") << endl;

      // イベントループ終了
      app.exit(0);
    });

    // イベントループを実行
    return app.exec();
  });
}
