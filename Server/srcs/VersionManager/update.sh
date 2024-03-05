#!/bin/bash

BRANCH_NAME="test_checkupdate"

# リモートの release ブランチの最新のハッシュを取得
remote_commit=$(git ls-remote origin $BRANCH_NAME | awk '{print $1}')
# ローカルの release ブランチの最新のハッシュを取得
local_commit=$(git rev-parse $BRANCH_NAME)

# リモートとローカルのハッシュを比較
if [ "$remote_commit" != "$local_commit" ]; then
    echo "リモートの release ブランチに新しいコミットがあります。"

    # リモートの README を表示
    echo "リモートの最新の README ファイルの内容は以下の通りです:"
    git fetch origin $BRANCH_NAME
    git show origin/$BRANCH_NAME:README.md

    # ユーザに更新するかどうかを問いかける
    read -p "ローカルの release ブランチを更新しますか？ (y/n): " answer
    case $answer in
        [Yy]* )
            # ブランチを更新
            git checkout $BRANCH_NAME
            git pull origin $BRANCH_NAME
            echo "ローカルの release ブランチを更新しました。"
            ;;
        * )
            # 更新しない
            echo "ローカルの release ブランチの更新をスキップしました。"
            ;;
    esac
else
    echo "ローカルの release ブランチは最新の状態です。"
fi
