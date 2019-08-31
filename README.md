# vst3sample
これは、入力された音声信号をそのまま出力するだけのVST3プラグインのサンプルです。  
Visual Studio 2019を使ってできるだけ簡単にビルドできるように作っています。

# サンプルのビルド方法
## ビルド環境
- Windows 10 64bit
- Visual Studio 2019

## ビルド方法
下記方法でサンプルをビルドすることができます。
1. Visual Studio 2019を起動し、作業の開始から「コードの複製またはチェックアウトする」を選びます
2. 開いたダイアログの「リポジトリの場所」に「 https://github.com/Utsubo-Kazura/vst3sample.git 」を入力し「複製」ボタンを押します。
3. リポジトリの複製が始まるので完了するまで待ちます。（完了するとソリューションエクスプローラーにフォルダービューが表示されます。）
4. ソリューションエクスプローラーのフォルダービューから「vst3sdk」フォルダのツリーを展開します。
5. 「CMakeLists.txt」を右クリック。「vstsdkのキャッシュを生成」を選びます。CMAKEのキャッシュが生成されるまでしばらく待ちます
6. CMAKEの処理が完了したら、メニュー「ビルド」から「すべてビルド」を選びます。（これでVST3 SDKのビルドが完了します。)
7. ソリューションエクスプローラーのフォルダービューから「vst3sapmle.sln」を選びます。
8. vst3sapmleのプロジェクトが開くので、メニュー「ビルド」から「ソリューションのビルド」を選びます。
9. プロジェクトのフォルダ配下「vst3sample\x64\Debug\」に「vst3sample.vst3」ができていることを確認します。
10. 「vst3sample.vst3」をフォルダ「C:\Program Files\Common Files\VST3」配下に移動もしくはコピーすれば完了です。(DAWなどから読み込めるようになります。)

# 依存するライブラリ
このサンプルはVST3 SDKがに依存しています。(サブモジュールとして追加しています。)  
上記「サンプルのビルド方法」の手順4.～6.がVST3 SDKを導入している部分になります。  
「サンプルのビルド方法」通りにしていただければ問題ないと思います。

# ライセンス
ライセンスはGPLv3になります。

# 注意点
また、作成されたVSTプラグインは「Microsoft Visual C++ 2019 再頒布可能パッケージ」が必要になります。  
Visual Studioが入っているパソコンであれば問題なく動作すると思いますが、他のパソコンにコピーする場合は「Microsoft Visual C++ 2019 再頒布可能パッケージ」を用意する必要があります。

# 連絡先 他
Twitter → https://twitter.com/vstcpp  
Webサイト → http://vstcpp.wpblog.jp/